#ifndef ALGO_DISTANCE_REQUETE_HANDLER_H
#define ALGO_DISTANCE_REQUETE_HANDLER_H

#include "serveur/requetes/handlers/i_requete_handler.h"
#include "types/commande_type.h"
#include "utils/json_parser_utils.h"

/**
 * @class AlgoDistanceRequeteHandler
 * @brief Gestionnaire pour les requêtes de type "algo_distance".
 */
class AlgoDistanceRequeteHandler : public IRequeteHandler
{
protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de requête.
     * @param commande La commande demandée.
     * @return true s'il peut traiter, false sinon.
     */
    bool peutTraiter(const std::string& commande) const override
    {
        return commandeFromString(commande) == CommandeType::ALGO_DISTANCE;
    }

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return La réponse au format JSON.
     */
    std::string genererReponse(const std::string& commande, const std::string& requete) override;
};

#endif  // ALGO_DISTANCE_REQUETE_HANDLER_H