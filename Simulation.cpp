#include "Simulation.h"
#include "Grid1D.h"
#include "AnalyticalSolution.h"
#include <cmath>

Simulation::Simulation(const HeatProblem& problem,
    std::unique_ptr<TimeScheme> scheme,
    double dt, double t_end)
    : problem_(problem),
    scheme_(std::move(scheme)),
    dt_(dt),
    t_end_(t_end)
{
    std::size_t N = problem_.grid().size();
    T_curr_.resize(N);
    T_prev_.resize(N);
}

void Simulation::run(const std::string& scheme_name,
    OutputManager& out)
{
    const Grid1D& grid = problem_.grid();

    // Initial condition at t = 0
    problem_.set_initial_condition(T_curr_);
    T_prev_ = T_curr_;   // for schemes that need n-1 at first step

    AnalyticalSolution analytical(problem_);

    int n_steps = static_cast<int>(std::round(t_end_ / dt_));
    double t = 0.0;

    for (int n = 0; n < n_steps; ++n) {
        scheme_->step(T_curr_, T_prev_, t, dt_);
        t += dt_;
        // IMPORTANT: no std::swap(T_curr_, T_prev_) here
    }

    // T_curr_ now holds the solution at time t ≈ t_end
    std::vector<double> T_exact(grid.size());
    for (std::size_t i = 0; i < grid.size(); ++i) {
        T_exact[i] = analytical(grid.x(i), t);
    }

    out.store_scheme_result(scheme_name, grid, T_curr_, T_exact);
}
