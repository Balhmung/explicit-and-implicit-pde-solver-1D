#pragma once
#include "HeatProblem.h"
#include <cstddef>

class AnalyticalSolution {
public:
    // Constructor: only HeatProblem + optional number of terms
    AnalyticalSolution(const HeatProblem& problem,
        std::size_t max_terms = 100);

    // Evaluate T(x,t)
    double operator()(double x, double t) const;

private:
    const HeatProblem& problem_;
    std::size_t max_terms_;
};
