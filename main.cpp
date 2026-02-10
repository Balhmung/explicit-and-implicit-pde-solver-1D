#include <iostream>
#include <memory>

#include "Grid1D.h"
#include "HeatProblem.h"
#include "Simulation.h"

#include "RichardsonScheme.h"
#include "DuFortFrankelScheme.h"
#include "LaasonenScheme.h"
#include "CrankNicolsonScheme.h"

#include "OutputManager.h"

int main() {
    try {
        std::cout << "=== 1D Heat Equation Solver ===\n";

        double L = 31.0;   // cm
        double dx = 0.05;   // cm
        double D = 93.0;   // cm^2/hr
        double Tin = 38.0;   // initial temperature
        double Tsur = 149.0;  // boundary temperature

        Grid1D grid(L, dx);
        HeatProblem problem(grid, D, Tin, Tsur);

        double dt = 0.01;  // hr  
        double t_end = 0.5;   // hr

        // OutputManager (base_folder is not used anymore)
        OutputManager out(".");

        // Run each scheme, store final-time results
        {
            auto scheme = std::make_unique<RichardsonScheme>(problem);
            Simulation sim(problem, std::move(scheme), dt, t_end);
            sim.run("Richardson", out);
        }

        {
            auto scheme = std::make_unique<DuFortFrankelScheme>(problem);
            Simulation sim(problem, std::move(scheme), dt, t_end);
            sim.run("DuFortFrankel", out);
        }

        {
            auto scheme = std::make_unique<LaasonenScheme>(problem);
            Simulation sim(problem, std::move(scheme), dt, t_end);
            sim.run("Laasonen", out);
        }

        {
            auto scheme = std::make_unique<CrankNicolsonScheme>(problem);
            Simulation sim(problem, std::move(scheme), dt, t_end);
            sim.run("CrankNicolson", out);
        }
      
        // Now write one combined CSV with all schemes + analytical solution
        out.write_combined_csv();

        std::cout << "Done. Check 1D_Heat_Equation_Solution.csv next to the EXE.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
