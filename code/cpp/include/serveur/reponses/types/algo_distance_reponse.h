#ifndef ALGO_DISTANCE_REPONSE_H
#define ALGO_DISTANCE_REPONSE_H

#include <string>
#include <vector>

#include "serveur/reponses/i_reponse.h"

struct EnsembleData
{
    std::vector<std::string> _chemin;
    std::vector<std::string> _distances;
    std::string _distanceTotale;
};

/**
 * @class AlgoDistanceReponse
 * @brief Représente une réponse JSON contenant le résultat d'un algorithme de distance.
 */
class AlgoDistanceReponse : public IReponse
{
public:
    /**
     * @brief Constructeur pour une réponse simple.
     * @param chemin Liste des entités du chemin optimal.
     * @param distances Liste des distances entre entités successives.
     * @param distanceTotal Distance totale du chemin.
     */
    AlgoDistanceReponse(std::vector<std::string> chemin, std::vector<std::string> distances, std::string distanceTotale)
        : _chemin(std::move(chemin)), _distances(std::move(distances)), _distanceTotale(std::move(distanceTotale))
    {
    }

    /**
     * @brief Constructeur pour une réponse composée.
     * @param liste La liste des réponse.
     * @
     */
    AlgoDistanceReponse(std::vector<std::shared_ptr<IReponse>> enfants) : IReponse(std::move(enfants)) {}

protected:
    /**
     * @brief Construit le JSON d'une réponse simple.
     * @return La réponse en JSON.
     */
    std::string toJsonSeul() const override;

private:
    std::vector<std::string> _chemin;     ///< Chemin optimal
    std::vector<std::string> _distances;  ///< Distances intermédiaires
    std::string _distanceTotale;          ///< Distance totale du trajet
};

#endif  // ALGO_DISTANCE_REPONSE_H