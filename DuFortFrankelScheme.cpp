#include "DuFortFrankelScheme.h"
#include "HeatProblem.h"
#include "Grid1D.h"
#include <vector>
#include <algorithm> // for std::fill

DuFortFrankelScheme::DuFortFrankelScheme(const HeatProblem& problem)
    : TimeScheme(problem) {
}

void DuFortFrankelScheme::step(std::vector<double>& T_curr,
    std::vector<double>& T_prev,
    double t, double dt)
{
    const Grid1D& grid = problem_.grid();
    std::size_t N = grid.size();
    double dx = grid.dx();
    double alpha = problem_.diffusivity();
    double Tsur = problem_.Tsur();

    if (N < 3) return;  // nothing to do on tiny grid

    double r = alpha * dt / (dx * dx);

    // Enforce boundary conditions on the *known* time levels
    T_curr.front() = Tsur;
    T_curr.back() = Tsur;
    T_prev.front() = Tsur;
    T_prev.back() = Tsur;

    // Storage for u^{n+1}
    std::vector<double> T_next(N);
    T_next.front() = Tsur;
    T_next.back() = Tsur;

    
    if (first_step_) {
        for (std::size_t i = 1; i < N - 1; ++i) {

            T_next[i] = T_curr[i]
                + r * (T_curr[i - 1] - 2.0 * T_curr[i] + T_curr[i + 1]);
        }

        // Rotate time levels: n-1 <- n, n <- n+1
        T_prev = T_curr;
        T_curr = T_next;

        first_step_ = false;
        return;
    }

    // ----- General DuFort–Frankel step using Hoffmann -----
    double a = (1.0 - 2.0 * r);
    double b = 2.0 * r;
    double denom = 1.0 + 2.0 * r;

    for (std::size_t i = 1; i < N - 1; ++i) {
        T_next[i] = (a * T_prev[i]
            + b * (T_curr[i - 1] + T_curr[i + 1])) / denom;
    }

    // Rotate time levels: n-1 <- n, n <- n+1
    T_prev = T_curr;
    T_curr = T_next;
}
