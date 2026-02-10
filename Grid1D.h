#pragma once
#include <vector>
#include <cstddef>

class Grid1D {
public:
    Grid1D(double length, double dx);

    std::size_t size() const;
    double dx() const;
    double length() const;
    double x(std::size_t i) const;
    const std::vector<double>& coords() const;

private:
    double L_;
    double dx_;
    std::vector<double> x_;
};

