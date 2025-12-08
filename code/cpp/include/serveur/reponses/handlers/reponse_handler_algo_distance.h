#ifndef REPONSE_HANDLER_ALGO_DISTANCE_H
#define REPONSE_HANDLER_ALGO_DISTANCE_H

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "serveur/reponses/handlers/reponse_handler_cor.h"

#include "algorithmes/data/output/output_data.h"

#include "types/commande_type.h"

#include "utils/json_builder.h"

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
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    std::optional<std::string> construireReponse(const std::string& commande,
                                                 const std::vector<std::any>& args) override;
};

inline std::optional<std::string> ReponseHandlerAlgoDistance::construireReponse(const std::string& commande,
                                                                                const std::vector<std::any>& args)
{
    if (commandeFromString(commande) != CommandeType::ALGO_DISTANCE)
        return nullptr;

    const auto& outputs = std::any_cast<const std::vector<std::shared_ptr<OutputData>>&>(args[0]);

    JsonBuilder jb;

    jb.beginArray("reponse");
    for (const auto& output : outputs) jb.addRawValue(output->toJson());

    jb.endArray();

    return jb.build();
}

#endif  // REPONSE_HANDLER_ALGO_DISTANCE_H