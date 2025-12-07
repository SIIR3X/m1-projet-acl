#ifndef REPONSE_HANDLER_ALGO_DISTANCE_H
#define REPONSE_HANDLER_ALGO_DISTANCE_H

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "serveur/reponses/handlers/reponse_handler_cor.h"
#include "serveur/reponses/types/algo_distance_reponse.h"
#include "serveur/reponses/types/i_reponse.h"

#include "algorithmes/distance/data/algo_distance_data.h"
#include "algorithmes/distance/data/algo_distance_solution.h"

#include "types/commande_type.h"

/**
 * @class ReponseHandlerAlgoDistance
 * @brief Maillon chargé de gérer les réponses aux requêtes de types "algo_distance" dans la chaîne de responsabilité.
 */
class ReponseHandlerAlgoDistance : public ReponseHandlerCOR
{
protected:
    /**
     * @brief Tente de construire une réponse à la requête.
     * @param commande La commande demandée.
     * @param args Les arguments passés au handler.
     * @return Une instance de IReponse ou nullptr.
     */
    std::shared_ptr<IReponse> construireReponse(const std::string& commande,
                                                const std::vector<std::any>& args) override;
};

inline std::shared_ptr<IReponse> ReponseHandlerAlgoDistance::construireReponse(const std::string& commande,
                                                                               const std::vector<std::any>& args)
{
    if (commandeFromString(commande) != CommandeType::ALGO_DISTANCE)
        return nullptr;

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

#endif  // REPONSE_HANDLER_ALGO_DISTANCE_H