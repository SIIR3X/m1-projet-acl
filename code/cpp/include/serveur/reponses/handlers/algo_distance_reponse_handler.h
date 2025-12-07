#ifndef ALGO_DISTANCE_REPONSE_HANDLER_H
#define ALGO_DISTANCE_REPONSE_HANDLER_H

#include <any>
#include <string>
#include <vector>

#include "serveur/reponses/handlers/i_reponse_handler.h"
#include "serveur/reponses/types/algo_distance_reponse.h"

#include "algorithmes/distance/data/algo_distance_data.h"
#include "algorithmes/distance/data/algo_distance_solution.h"

#include "types/commande_type.h"

/**
 * @class AlgoDistanceReponseHandler
 * @brief Gestionnaire pour les requêtes de type "algo_distance".
 */
class AlgoDistanceReponseHandler : public IReponseHandler
{
protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de réponse.
     * @param commande La commande demandée.
     * @return true s'il peut traiter, false sinon.
     */
    bool peutTraiter(const std::string& commande) const override
    {
        return commandeFromString(commande) == CommandeType::ALGO_DISTANCE;
    }

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @tparam Args Types des objets reçus.
     * @param args Objets passés au handler.
     * @return Un pointeur partagé var la réponse.
     */
    std::shared_ptr<IReponse> genererReponse(const std::vector<std::any>& args) override;
};

inline std::shared_ptr<IReponse> AlgoDistanceReponseHandler::genererReponse(const std::vector<std::any>& args)
{
    // Cast des paramètres
    const auto& solution = std::any_cast<const AlgoDistanceSolution&>(args[0]);
    const auto& labels = std::any_cast<const std::vector<std::string>&>(args[1]);
    const auto& donneesAlgo = std::any_cast<const AlgoDistanceData&>(args[2]);

    // Conversion du chemin en string
    std::vector<std::string> cheminStr;
    cheminStr.reserve(solution._chemin.size());
    for (int idx : solution._chemin) cheminStr.push_back(labels[idx]);

    // Conversion des distances en string
    std::vector<std::string> distancesStr;
    for (size_t i = 0; i + 1 < solution._chemin.size(); ++i)
    {
        int a = solution._chemin[i];
        int b = solution._chemin[i + 1];
        distancesStr.push_back(std::to_string(donneesAlgo._distances[a][b]));
    }

    return std::make_shared<AlgoDistanceReponse>(std::move(cheminStr), std::move(distancesStr),
                                                 std::to_string(solution._distanceTotale));
}

#endif  // ALGO_DISTANCE_REPONSE_HANDLER_H