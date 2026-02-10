#pragma once
#include <vector>
#include "TimeScheme.h"

class CrankNicolsonScheme : public TimeScheme {
public:
    explicit CrankNicolsonScheme(const HeatProblem& problem);

    void step(std::vector<double>& T_curr,
        std::vector<double>& T_prev,
        double t, double dt) override;

private:
    std::vector<double> a_, b_, c_;
}; 

