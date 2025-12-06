#ifndef REPONSE_TSP_HANDLER_H
#define REPONSE_TSP_HANDLER_H

#include <any>
#include <string>
#include <vector>

#include "serveur/reponses/data/tsp_reponse_data.h"
#include "serveur/reponses/i_reponse_handler.h"
#include "serveur/reponses/types/reponse_tsp.h"

/**
 * @class ReponseTSPHandler
 * @brief Handler COR qui génère une réponse JSON pour une solution TSP.
 */
class ReponseTSPHandler : public IReponseHandler
{
protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de réponse.
     * @param type Le type de réponse.
     * @return true s'il peut traiter, false sinon.
     */
    bool peutTraiter(const std::string& type) const override
    {
        return type == "TSP";
    }

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @param data Le contenu de la réponse.
     * @return Un pointeur partagé var la réponse.
     */
    std::shared_ptr<IReponse> genererReponse(const std::any& data) override;
};

inline std::shared_ptr<IReponse> ReponseTSPHandler::genererReponse(const std::any& data)
{
    const auto& tsp = std::any_cast<const TSPReponseData&>(data);

    return std::make_shared<ReponseTSP>(tsp._chemin, tsp._distances, tsp._distanceTotale);
}

#endif  // REPONSE_TSP_HANDLER_H