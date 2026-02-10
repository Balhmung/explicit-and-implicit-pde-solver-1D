#include "HeatProblem.h"

HeatProblem::HeatProblem(const Grid1D& grid, double D, double Tin, double Tsur)
    : grid_(grid), D_(D), Tin_(Tin), Tsur_(Tsur) {
}

double HeatProblem::diffusivity() const {
    return D_;
}

double HeatProblem::Tin() const {
    return Tin_;
}

double HeatProblem::Tsur() const {
    return Tsur_;
}

const Grid1D& HeatProblem::grid() const {
    return grid_;
}

void HeatProblem::set_initial_condition(std::vector<double>& T) const {
    for (double& v : T)
        v = Tin_;
}

void HeatProblem::apply_boundary_conditions(std::vector<double>& T) const {
    T.front() = Tsur_;
    T.back() = Tsur_;
}
