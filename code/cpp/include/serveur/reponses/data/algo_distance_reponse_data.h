#ifndef ALGO_DISTANCE_REPONSE_DATA_H
#define ALGO_DISTANCE_REPONSE_DATA_H

#include <string>
#include <vector>

/**
 * @struct AlgoDistanceData
 * @brief Données produites par le solveur TSP.
 */
struct AlgoDistanceReponseData
{
    std::vector<std::string> _chemin;     ///< JSON déjà sérialisé des entités
    std::vector<std::string> _distances;  ///< JSON déjà sérialisé des distances
    std::string _distanceTotale;          ///< JSON déjà sérialisé de la distance totale
};

#endif  // ALGO_DISTANCE_REPONSE_DATA_H