#include "CrankNicolsonScheme.h"
#include "HeatProblem.h"
#include "Grid1D.h"
#include "TridiagonalSolver.h"
#include <vector>
#include <stdexcept>

CrankNicolsonScheme::CrankNicolsonScheme(const HeatProblem& problem)
    : TimeScheme(problem) {
}

void CrankNicolsonScheme::step(std::vector<double>& T_curr,
    std::vector<double>& T_prev,
    double /*t*/, double dt)
{
    const Grid1D& grid = problem_.grid();
    std::size_t N = grid.size();

    if (N < 3) {
        throw std::runtime_error("CrankNicolsonScheme::step: grid too small (N < 3)");
    }

    double dx = grid.dx();
    double D = problem_.diffusivity();
    double r = D * dt / (dx * dx);

    std::size_t n_internal = N - 2; // unknowns: nodes 1..N-2

    // Prepare tri-diagonal coefficients
    a_.assign(n_internal, -r / 2.0);
    b_.assign(n_internal, 1.0 + r);
    c_.assign(n_internal, -r / 2.0);

    // RHS
    std::vector<double> rhs(n_internal);

    double d = r / 2.0;
    double e = (1.0 - r);
    double f = r / 2.0;

    double Tsur = problem_.Tsur();

    // Assemble RHS vector
    for (std::size_t k = 0; k < n_internal; ++k) {
        std::size_t i = k + 1; // full grid index

        double val =
            d * T_curr[i - 1] +
            e * T_curr[i] +
            f * T_curr[i + 1];

        if (i == 1)
            val += (r / 2.0) * Tsur;
        if (i == N - 2)
            val += (r / 2.0) * Tsur;

        rhs[k] = val;
    }

    // Solve tri-diagonal system
    TridiagonalSolver::solve(a_, b_, c_, rhs);

    // Build T_next
    std::vector<double> T_next(N);

    // Apply boundary conditions
    T_next[0] = Tsur;
    T_next[N - 1] = Tsur;

    // Insert interior solution
    for (std::size_t k = 0; k < n_internal; ++k) {
        std::size_t i = k + 1;
        T_next[i] = rhs[k];
    }

    // Shift time levels
    T_prev = T_curr;
    T_curr = T_next;
}
