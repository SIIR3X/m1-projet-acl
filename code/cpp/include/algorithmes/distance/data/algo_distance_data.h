#ifndef ALGO_DISTANCE_DATA_H
#define ALGO_DISTANCE_DATA_H

#include <vector>

/**
 * @struct AlgoDistanceData
 * @brief Contient les données nécessaires à l'exécution d'algorithmes basés sur une matrice de distances.
 */
struct AlgoDistanceData
{
    std::vector<std::vector<double>> _distances;  ///< Matrice des distances (matrice carrée NxN).
    int _nombreSommets;                           ///< Nombre total de sommets dans le graphe.
    int _machines;                                ///< Machines
};

#endif  // ALGO_DISTANCE_DATA_H