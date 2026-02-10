#include "TimeScheme.h"
#include "HeatProblem.h"

TimeScheme::TimeScheme(const HeatProblem& problem)
    : problem_(problem) {
}
