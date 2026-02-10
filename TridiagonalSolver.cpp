#include "TridiagonalSolver.h"
#include <stdexcept>
#include <vector>

void TridiagonalSolver::solve(const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c,
    std::vector<double>& d)
{
    const std::size_t n = d.size();

    if (a.size() != n || b.size() != n || c.size() != n) {
        throw std::runtime_error("TridiagonalSolver::solve: size mismatch between a, b, c, d");
    }
    if (n == 0) {
        return; // nothing to do
    }

    // Temporary arrays for modified coefficients
    std::vector<double> c_prime(n);
    std::vector<double> d_prime(n);

    // Forward sweep
    double beta = b[0];
    if (beta == 0.0) {
        throw std::runtime_error("TridiagonalSolver::solve: zero pivot at row 0");
    }

    c_prime[0] = c[0] / beta;
    d_prime[0] = d[0] / beta;

    for (std::size_t i = 1; i < n; ++i) {
        beta = b[i] - a[i] * c_prime[i - 1];
        if (beta == 0.0) {
            throw std::runtime_error("TridiagonalSolver::solve: zero pivot during forward sweep");
        }

        if (i == n - 1) {
            c_prime[i] = 0.0;              // last row has no super-diagonal
        }
        else {
            c_prime[i] = c[i] / beta;
        }

        d_prime[i] = (d[i] - a[i] * d_prime[i - 1]) / beta;
    }

    // Back substitution
    std::vector<double> x(n);
    x[n - 1] = d_prime[n - 1];

    for (std::size_t i = n - 1; i-- > 0; ) {
        x[i] = d_prime[i] - c_prime[i] * x[i + 1];
    }

    // Copy solution back into d
    d = x;
}
