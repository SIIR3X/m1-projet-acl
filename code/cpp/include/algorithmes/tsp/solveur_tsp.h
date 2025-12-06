#ifndef SOLVEUR_TSP_H
#define SOLVEUR_TSP_H

#include <vector>

#include "algorithmes/tsp/tsp_data.h"
#include "algorithmes/tsp/tsp_solution.h"

class SolveurTSP
{
public:
    static TSPSolution resoudre(const TSPData& data);

private:
    static std::vector<int> _cheminFictif(int n);
};

inline TSPSolution SolveurTSP::resoudre(const TSPData& data)
{
    TSPSolution solution;

    // TODO : appel vers un solveur externe (en C en l'occurence)

    // Pour l'instant on simule
    solution._chemin = _cheminFictif(data._nombreSommets);
    solution._distanceTotale = 0.0;

    return solution;
}

inline std::vector<int> SolveurTSP::_cheminFictif(int n)
{
    std::vector<int> chemin(n);

    for (int i = 0; i < n; ++i) chemin[i] = i;

    return chemin;
}

#endif  // SOLVEUR_TSP_H