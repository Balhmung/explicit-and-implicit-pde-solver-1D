#pragma once
#include <memory>
#include <vector>
#include "HeatProblem.h"
#include "TimeScheme.h"
#include "OutputManager.h"

class Simulation {
public:
    Simulation(const HeatProblem& problem,
        std::unique_ptr<TimeScheme> scheme,
        double dt, double t_end);

    void run(const std::string& scheme_name,
        OutputManager& out);

private:
    const HeatProblem& problem_;
    std::unique_ptr<TimeScheme> scheme_;
    double dt_;
    double t_end_;
    std::vector<double> T_curr_;
    std::vector<double> T_prev_;
};