#ifndef TSP_SOLVEUR_HANDLER_H
#define TSP_SOLVEUR_HANDLER_H

#include <algorithm>
#include <random>

#include "algorithmes/distance/builder/algo_distance_data_builder.h"
#include "algorithmes/distance/data/algo_distance_solution.h"
#include "algorithmes/handlers/i_solveur_handler.h"
#include "modele/graphe/graphe.h"
#include "types/algo_type.h"

/**
 * @class TspSolveurHandler
 * @brief @brief Gestionnaire pour les algorithmes de type "tsp".
 */
class TspSolveurHandler : public ISolveurHandler
{
protected:
    /**
     * @brief Indique si ce solveur peut traiter l'algorithme demandé.
     * @param nomAlgo L'algorithme demandé.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutResoudre(const std::string& nomAlgo) const override
    {
        return algoFromString(nomAlgo) == AlgoType::TSP;
    }

    /**
     * @brief Exécute l'algorithme.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    virtual std::any executer(const std::any& donnees) override;
};

inline std::any TspSolveurHandler::executer(const std::any& donnees)
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

#endif  // TSP_SOLVEUR_HANDLER_H