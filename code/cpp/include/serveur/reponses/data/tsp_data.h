#ifndef TSP_DATA_H
#define TSP_DATA_H

#include <string>
#include <vector>

/**
 * @struct TSPData
 * @brief Données produites par le solveur TSP.
 */
struct TSPData
{
    std::vector<std::string> _chemin;     ///< JSON déjà sérialisé des entités
    std::vector<std::string> _distances;  ///< JSON déjà sérialisé des distances
    std::string _distanceTotale;          ///< JSON déjà sérialisé de la distance totale
};

#endif  // TSP_DATA_H