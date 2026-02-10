#include "RichardsonScheme.h"
#include "HeatProblem.h"
#include "Grid1D.h"
#include <vector>
#include <stdexcept>

RichardsonScheme::RichardsonScheme(const HeatProblem& problem)
    : TimeScheme(problem) {
}

void RichardsonScheme::step(std::vector<double>& T_curr,
    std::vector<double>& T_prev,
    double t, double dt)
{
    const Grid1D& grid = problem_.grid();
    std::size_t N = grid.size();
    double dx = grid.dx();
    double D = problem_.diffusivity();

    double r = D * dt / (dx * dx);

    // Temporary vector for T_next (n+1)
    std::vector<double> T_next(N);

    // --- Apply boundary conditions first ---
    T_next[0] = problem_.Tsur();
    T_next[N - 1] = problem_.Tsur();

    // --- Special case: first step (n = 0 -> 1) ---
    // Richardson needs T[-1], which does not exist.
    // So we use FTCS to compute the first level:
    if (t == 0.0) {
        for (std::size_t i = 1; i < N - 1; ++i) {
            T_next[i] =
                r * T_curr[i - 1] +
                (1.0 - 2.0 * r) * T_curr[i] +
                r * T_curr[i + 1];
        }

        // swap prev <-> curr <-> next correctly
        T_prev = T_curr;
        T_curr = T_next;
        return;
    }

    // --- General Richardson CTCS time stepping ---
    for (std::size_t i = 1; i < N - 1; ++i) {
        T_next[i] =
            2.0 * r * (T_curr[i - 1] - 2.0 * T_curr[i] + T_curr[i + 1]) +
            T_prev[i];
    }

    // Swap time levels:
    // prev <- curr
    // curr <- next
    T_prev = T_curr;
    T_curr = T_next;
}
