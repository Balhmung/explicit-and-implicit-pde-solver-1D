#include "Grid1D.h"
#include <stdexcept>

Grid1D::Grid1D(double length, double dx)
    : L_(length), dx_(dx)
{
    if (L_ <= 0 || dx_ <= 0)
        throw std::runtime_error("Grid1D: length and dx must be positive");

    std::size_t N = static_cast<std::size_t>(L_ / dx_) + 1;
    x_.resize(N);

    for (std::size_t i = 0; i < N; ++i)
        x_[i] = i * dx_;
}

std::size_t Grid1D::size() const {
    return x_.size();
}

double Grid1D::dx() const {
    return dx_;
}

double Grid1D::length() const {
    return L_;
}

double Grid1D::x(std::size_t i) const {
    return x_.at(i);
}

const std::vector<double>& Grid1D::coords() const {
    return x_;
}
