#include "AnalyticalSolution.h"
#include "HeatProblem.h"
#include "Grid1D.h"

#include <cmath>

namespace {
    // Local to this file only
    constexpr double pi = 3.14159265358979323846;
}

AnalyticalSolution::AnalyticalSolution(const HeatProblem& problem,
    std::size_t max_terms)
    : problem_(problem),
    max_terms_(max_terms) {
}

double AnalyticalSolution::operator()(double x, double t) const {
    const double D = problem_.diffusivity();
    const double Tin = problem_.Tin();
    const double Tsur = problem_.Tsur();
    const double L = problem_.grid().length();

    double series = 0.0;

    for (std::size_t m = 1; m <= max_terms_; ++m) {
        double m_d = static_cast<double>(m);
        double mPiL = (m_d * pi) / L;
        double expo = std::exp(-D * mPiL * mPiL * t);
        double coef = (1.0 - std::pow(-1.0, m_d)) / (m_d * pi);
        double sine = std::sin(mPiL * x);

        series += expo * coef * sine;
    }

    return Tsur + 2.0 * (Tin - Tsur) * series;
}
