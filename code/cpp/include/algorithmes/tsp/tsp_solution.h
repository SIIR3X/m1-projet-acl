#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H

#include <vector>

struct TSPSolution
{
    std::vector<int> _chemin;
    double _distanceTotale = 0.0;
};

#endif  // TSP_SOLUTION_H