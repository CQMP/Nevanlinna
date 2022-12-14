#pragma once
#include <triqs/gfs.hpp>
#include <triqs/mesh.hpp>
#include <nda/nda.hpp>
#include <h5/h5.hpp>
#include "nevanlinna_parameters_t.hpp"
#include "kernel.hpp"

namespace nevanlinna {

  /**
   * Nevanlinna analytical continuation solver for TRIQS GFs
   *
   * @note Perform analytical continuation for the diagonal part of the matrix-values TRIQS Green's function
   * @include nevanlinna/nevanlinna.hpp
   */
  class solver {

    public:
    ~solver() = default;

    CPP2PY_ARG_AS_DICT
    solver(nevanlinna_parameters_t const & p);

    // Copy/Move construction
    solver(solver const &) = default;
    solver(solver &&)      = default;

    /// Copy/Move assignment
    solver &operator=(solver const &) = default;
    solver &operator=(solver &&) = default;

    /**
     * Construct a Nevanlinna factorization for matrix-valued Matsubara frequency Green's function
     *
     * @param g_iw - matrix-valued Matsubara frequency Green's function
     */
    void solve(const triqs::gfs::gf<triqs::mesh::imfreq, triqs::gfs::matrix_valued>& g_iw);

    /**
     * Evaluate diagonal part of the real-frequency Green's function on a chosen grid
     * based on the precomputed Nevanlinna factorization
     *
     * @param grid - real frequency grid
     * @param eta - Lorentzian broadening
     * @return Real-frequency matrix-valued TRIQS Green's function on a chosen grid.
     */
    [[nodiscard]] triqs::gfs::gf<triqs::mesh::refreq, triqs::gfs::matrix_valued> evaluate(const triqs::mesh::refreq & grid, double eta) const;

    private:
    // vector of Nevanlinna factorization kernels for multi-orbital factorization
    std::vector<kernel> _kernels;
  };

//  typedef solver<mpf_class> SolverMpf;
} // namespace nevanlinna
