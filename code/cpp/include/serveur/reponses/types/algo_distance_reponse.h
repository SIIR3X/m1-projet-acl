#ifndef ALGO_DISTANCE_REPONSE_H
#define ALGO_DISTANCE_REPONSE_H

#include <string>
#include <vector>

#include "serveur/reponses/i_reponse.h"

/**
 * @class AlgoDistanceReponse
 * @brief Représente une réponse JSON cotnenant le résultat du TSP.
 */
class AlgoDistanceReponse : public IReponse
{
public:
    /**
     * @brief Constructeur principal.
     * @param chemin Liste des entités du chemin optimal.
     * @param distances Liste des distances entre entités successives.
     * @param distanceTotal Distance totale du chemin.
     */
    AlgoDistanceReponse(std::vector<std::string> chemin, std::vector<std::string> distances, std::string distanceTotale)
        : _chemin(std::move(chemin)), _distances(std::move(distances)), _distanceTotale(std::move(distanceTotale))
    {
    }

    /**
     * @brief Construit la réponse.
     * @return La réponse sous forme d'une chaîne.
     */
    std::string toJson() const override;

private:
    std::vector<std::string> _chemin;     ///< Le chemin.
    std::vector<std::string> _distances;  ///< Les distances entre les entités.
    std::string _distanceTotale;          ///< La distance totale du chemin.
};

#endif  // ALGO_DISTANCE_REPONSE_H