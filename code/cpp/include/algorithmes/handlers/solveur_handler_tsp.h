#ifndef SOLVEUR_HANDLER_TSP_H
#define SOLVEUR_HANDLER_TSP_H

#include <algorithm>
#include <any>
#include <random>
#include <string>

#include "algorithmes/distance/data/algo_distance_data.h"
#include "algorithmes/distance/data/algo_distance_solution.h"
#include "algorithmes/handlers/solveur_handler_cor.h"

/**
 * @class RequeteHandlerAlgoDistance
 * @brief Maillon chargé de gérer les requêtes de types "algo_distance" dans la chaîne de responsabilité.
 */
class SolveurHandlerTSP : public SolveurHandlerCOR
{
protected:
    /**
     * @brief Tente de résoudre les données via l'algorithme demandé.
     * @param nomAlgo Le nom de l'algorithme demandé.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    std::any resoudreDonnees(const std::string& nomAlgo, const std::any& donnees) override;
};

inline std::any SolveurHandlerTSP::resoudreDonnees(const std::string& nomAlgo, const std::any& donnees)
{
    // Cast des données
    const auto& donneesAlgo = std::any_cast<const AlgoDistanceData&>(donnees);

    AlgoDistanceSolution solution;

    // TODO : TSP
    int n = donneesAlgo._nombreSommets;
    solution._chemin.reserve(n);
    for (int i = 0; i < n; ++i) solution._chemin.push_back(i);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(solution._chemin.begin(), solution._chemin.end(), gen);
    solution._distanceTotale = 123.456;

    return std::any{solution};
}

#endif  // SOLVEUR_HANDLER_TSP_H