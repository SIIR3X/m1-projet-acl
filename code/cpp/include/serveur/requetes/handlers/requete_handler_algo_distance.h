#ifndef REQUETE_HANDLER_ALGO_DISTANCE_H
#define REQUETE_HANDLER_ALGO_DISTANCE_H

#include <any>
#include <optional>
#include <string>
#include <vector>

#include "serveur/requetes/handlers/requete_handler_cor.h"
#include "serveur/requetes/parsers/handlers/parser_algo_distance.h"

#include "types/commande_type.h"

/**
 * @class RequeteHandlerAlgoDistance
 * @brief Maillon chargé de gérer les requêtes de types "algo_distance" dans la chaîne de responsabilité.
 */
class RequeteHandlerAlgoDistance : public RequeteHandlerCOR
{
public:
    RequeteHandlerAlgoDistance(std::shared_ptr<RequeteHandlerCOR> suivant = nullptr) : RequeteHandlerCOR(suivant)
    {
        _parseur = std::make_unique<ParserAlgoDistance>();
    }

protected:
    bool peutTraiter(const std::string& commande) const override
    {
        return commandeFromString(commande) == CommandeType::ALGO_DISTANCE;
    }

    std::optional<std::vector<std::any>> traiterRequete(const std::string& commande,
                                                        const std::vector<std::any>& argsBruts) override;
};

#endif  // REQUETE_HANDLER_ALGO_DISTANCE_H