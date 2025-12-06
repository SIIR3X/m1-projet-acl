#ifndef ALGO_DISTANCE_REPONSE_HANDLER_H
#define ALGO_DISTANCE_REPONSE_HANDLER_H

#include <any>
#include <string>
#include <vector>

#include "serveur/reponses/data/algo_distance_reponse_data.h"
#include "serveur/reponses/gestionnaires/i_reponse_handler.h"
#include "serveur/reponses/types/algo_distance_reponse.h"
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
     * @param data Le contenu de la réponse.
     * @return Un pointeur partagé var la réponse.
     */
    std::shared_ptr<IReponse> genererReponse(const std::any& data) override;
};

inline std::shared_ptr<IReponse> AlgoDistanceReponseHandler::genererReponse(const std::any& data)
{
    const auto& reponseData = std::any_cast<const AlgoDistanceReponseData&>(data);

    return std::make_shared<AlgoDistanceReponse>(reponseData._chemin, reponseData._distances,
                                                 reponseData._distanceTotale);
}

#endif  // ALGO_DISTANCE_REPONSE_HANDLER_H