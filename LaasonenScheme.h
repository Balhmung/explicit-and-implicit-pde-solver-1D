#pragma once
#include <vector>
#include "TimeScheme.h"

class LaasonenScheme : public TimeScheme {
public:
    explicit LaasonenScheme(const HeatProblem& problem);

    void step(std::vector<double>& T_curr,
        std::vector<double>& T_prev,
        double t, double dt) override;

private:
    // coefficients (could be resized each dt, or recomputed on the fly)
    std::vector<double> a_, b_, c_; // tri-diagonal
}; 

