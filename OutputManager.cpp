#include "OutputManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>

OutputManager::OutputManager(const std::string& base_folder)
    : base_folder_(base_folder)
{
    // base_folder_ is ignored in this simple version.
    // CSV will be written in the current working directory.
}

void OutputManager::store_scheme_result(const std::string& scheme_name,
    const Grid1D& grid,
    const std::vector<double>& T_num,
    const std::vector<double>& T_exact)
{
    std::size_t N = grid.size();
    if (T_num.size() != N || T_exact.size() != N) {
        throw std::runtime_error("OutputManager::store_scheme_result: size mismatch");
    }

    // First time: initialize x, exact, and column vectors
    if (!initialized_) {
        x_m_.resize(N);
        exact_ = T_exact;

        duFort_.assign(N, 0.0);
        richardson_.assign(N, 0.0);
        laasonen_.assign(N, 0.0);
        crank_.assign(N, 0.0);

        // Our grid is in cm → convert to meters for the CSV header "x (m)"
        for (std::size_t i = 0; i < N; ++i) {
            x_m_[i] = grid.x(i) / 100.0; // cm → m
        }

        initialized_ = true;
    }

    if (scheme_name == "DuFortFrankel") {
        duFort_ = T_num;
    }
    else if (scheme_name == "Richardson") {
        richardson_ = T_num;
    }
    else if (scheme_name == "Laasonen") {
        laasonen_ = T_num;
    }
    else if (scheme_name == "CrankNicolson") {
        crank_ = T_num;
    }
    else {
        std::cerr << "Warning: unknown scheme name '" << scheme_name
            << "' in store_scheme_result\n";
    }
}

void OutputManager::write_combined_csv() const
{
    if (!initialized_) {
        throw std::runtime_error("OutputManager::write_combined_csv: no data stored");
    }

    // Build filename in working directory
    std::string filename = "1D_Heat_Equation_Solution.csv";

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    // Header exactly like your example file
    file << "x (m),"
        << "T (K) Exact_Solution,"
        << "T (K) DuFort_Frankel_Explicit_Scheme,"
        << "T (K) Richardson_Explicit_Scheme,"
        << "T (K) Laasonen_Simple_Implicit_Scheme,"
        << "T (K) Crank_Nicholson_Implicit_Scheme\n";

    file << std::fixed << std::setprecision(4);

    std::size_t N = x_m_.size();
    for (std::size_t i = 0; i < N; ++i) {
        file << x_m_[i] << ","
            << exact_[i] << ","
            << duFort_[i] << ","
            << richardson_[i] << ","
            << laasonen_[i] << ","
            << crank_[i] << "\n";
    }

    file.close();

    std::cout << "Combined CSV written to: " << filename << "\n";
}
