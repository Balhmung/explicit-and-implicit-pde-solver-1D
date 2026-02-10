#pragma once
#include <vector>

class TridiagonalSolver {
public:
    // Solves tri-diagonal system with coefficients a (sub), b (main), c (super)
    // On return, d holds the solution.
    static void solve(const std::vector<double>& a,
        const std::vector<double>& b,
        const std::vector<double>& c,
        std::vector<double>& d);
};