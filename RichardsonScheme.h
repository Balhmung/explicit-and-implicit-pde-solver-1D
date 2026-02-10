#pragma once
#include "TimeScheme.h"

class RichardsonScheme : public TimeScheme {
public:
    explicit RichardsonScheme(const HeatProblem& problem);

    void step(std::vector<double>& T_curr,
        std::vector<double>& T_prev,
        double t, double dt) override;
};

