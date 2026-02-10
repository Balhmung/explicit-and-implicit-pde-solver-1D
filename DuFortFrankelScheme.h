#pragma once
#include "TimeScheme.h"
#include <vector>

class DuFortFrankelScheme : public TimeScheme {
public:
    explicit DuFortFrankelScheme(const HeatProblem& problem);

    void step(std::vector<double>& T_curr,
        std::vector<double>& T_prev,
        double t, double dt) override;

private:
    bool first_step_ = true;  // needed for the very first time step
};
