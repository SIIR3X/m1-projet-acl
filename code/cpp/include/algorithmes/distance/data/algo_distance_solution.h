#ifndef ALGO_DISTANCE_SOLUTION_H
#define ALGO_DISTANCE_SOLUTION_H

#include <vector>

/**
 * @struct AlgoDistanceSolution
 * @brief Structure représentant la solution générique d'un algorithme basé sur des distances.
 */
struct AlgoDistanceSolution
{
    std::vector<int> _chemin;      ///< Chemin résultant de l'algorithme.
    double _distanceTotale = 0.0;  ///< Distance totale associée au chemin calculé.
};

#endif  // ALGO_DISTANCE_SOLUTION_H