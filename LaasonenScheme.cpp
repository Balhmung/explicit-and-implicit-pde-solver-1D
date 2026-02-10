#include "LaasonenScheme.h"
#include "HeatProblem.h"
#include "Grid1D.h"
#include "TridiagonalSolver.h"
#include <vector>
#include <stdexcept>

LaasonenScheme::LaasonenScheme(const HeatProblem& problem)
    : TimeScheme(problem) {
}

void LaasonenScheme::step(std::vector<double>& T_curr,
    std::vector<double>& T_prev,
    double /*t*/, double dt)
{
    const Grid1D& grid = problem_.grid();
    std::size_t N = grid.size();

    if (N < 3) {
        throw std::runtime_error("LaasonenScheme::step: grid too small (N < 3)");
    }

    double dx = grid.dx();
    double D = problem_.diffusivity();
    double r = D * dt / (dx * dx);

    std::size_t n_internal = N - 2; // unknowns: nodes 1..N-2

    // Build tri-diagonal coefficients a (sub), b (main), c (super)
    a_.assign(n_internal, -r);
    b_.assign(n_internal, 1.0 + 2.0 * r);
    c_.assign(n_internal, -r);

    // RHS vector
    std::vector<double> rhs(n_internal);

    // Fill RHS: T_i^n + r*Tsur where BC enters
    const double Tsur = problem_.Tsur();

    for (std::size_t k = 0; k < n_internal; ++k) {
        std::size_t i = k + 1; // full-grid index

        double val = T_curr[i];

        if (i == 1) {              // left interior node
            val += r * Tsur;
        }
        if (i == N - 2) {          // right interior node
            val += r * Tsur;
        }

        rhs[k] = val;
    }

    // Solve tri-diagonal system: A * x = rhs
    TridiagonalSolver::solve(a_, b_, c_, rhs);

    // Build next time level
    std::vector<double> T_next(N);

    // Apply boundary conditions at n+1
    T_next[0] = Tsur;
    T_next[N - 1] = Tsur;

    // Internal nodes come from solution of the system
    for (std::size_t k = 0; k < n_internal; ++k) {
        std::size_t i = k + 1;
        T_next[i] = rhs[k];
    }

    // Shift time levels: prev <- curr, curr <- next
    T_prev = T_curr;
    T_curr = T_next;
}
