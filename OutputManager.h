#pragma once
#include <string>
#include <vector>
#include "Grid1D.h"

class OutputManager {
public:
    explicit OutputManager(const std::string& base_folder);

    // Store final-time result for a given scheme
    void store_scheme_result(const std::string& scheme_name,
        const Grid1D& grid,
        const std::vector<double>& T_num,
        const std::vector<double>& T_exact);

    // Write single combined CSV with all schemes + exact solution
    void write_combined_csv() const;

private:
    std::string base_folder_;

    // Common x and exact solution (same for all schemes)
    std::vector<double> x_m_;     // x in meters
    std::vector<double> exact_;

    // One column per scheme
    std::vector<double> duFort_;
    std::vector<double> richardson_;
    std::vector<double> laasonen_;
    std::vector<double> crank_;

    bool initialized_ = false;
};
