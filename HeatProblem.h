#pragma once
#include <vector>
#include "Grid1D.h"

class HeatProblem {
public:
    HeatProblem(const Grid1D& grid, double D, double Tin, double Tsur);

    double diffusivity() const;
    double Tin() const;
    double Tsur() const;
    const Grid1D& grid() const;

    void set_initial_condition(std::vector<double>& T) const;
    void apply_boundary_conditions(std::vector<double>& T) const;

private:
    const Grid1D& grid_;
    double D_;
    double Tin_;
    double Tsur_;
};

