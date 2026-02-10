#pragma once
#include <vector>

class HeatProblem;

class TimeScheme {
public:
    explicit TimeScheme(const HeatProblem& problem);
    virtual ~TimeScheme() = default;

    // T_curr: current time level
    // T_prev: previous time level (or second previous for multi-level schemes)
    // t: current time
    // dt: time step
    virtual void step(std::vector<double>& T_curr,
        std::vector<double>& T_prev,
        double t, double dt) = 0;

protected:
    const HeatProblem& problem_;
};

