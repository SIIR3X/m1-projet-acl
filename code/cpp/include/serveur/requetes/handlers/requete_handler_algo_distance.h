#ifndef REQUETE_HANDLER_ALGO_DISTANCE_H
#define REQUETE_HANDLER_ALGO_DISTANCE_H

#include <optional>
#include <string>

#include "serveur/requetes/handlers/requete_handler_cor.h"

/**
 * @class RequeteHandlerAlgoDistance
 * @brief Maillon chargé de gérer les requêtes de types "algo_distance" dans la chaîne de responsabilité.
 */
class RequeteHandlerAlgoDistance : public RequeteHandlerCOR
{
protected:
    /**
     * @brief Tente de générer une réponse à la requête.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    std::optional<std::string> traiterRequete(const std::string& commande, const std::string& requete) override;
};

#endif  // REQUETE_HANDLER_ALGO_DISTANCE_H