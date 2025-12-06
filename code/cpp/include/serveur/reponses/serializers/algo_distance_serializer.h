#ifndef ALGO_DISTANCE_SERIALIZER_H
#define ALGO_DISTANCE_SERIALIZER_H

#include "algorithmes/distance/algo_distance_solution.h"
#include "serveur/reponses/data/algo_distance_reponse_data.h"
#include "serveur/reponses/serializers/i_reponse_serializer.h"
#include "utils/json_builder.h"

/**
 * @class AlgoDistanceSerializer
 * @brief Sérialiseur dédié aux algorithmes de distance.
 */
class AlgoDistanceSerializer : public IReponseSerializer
{
public:
    /**
     * @brief Lance la sérialisation via l'instance unique du sérialiseur.
     * @param data Résultat brut.
     * @return Un std::any contenant les données sérialisées.
     */
    static std::any lancerSerialisation(const std::any& data)
    {
        return instance().serialize(data);
    }

protected:
    /**
     * @brief Accès à l'instance unique du sérialiseur.
     * @return Référence constante vers l'instance unique.
     */
    static const AlgoDistanceSerializer& instance()
    {
        static AlgoDistanceSerializer inst;
        return inst;
    }

    /**
     * @brief Sérialise des données brutes en un format exploitable par un handler.
     * @param data Résultat brut.
     * @return Un std::any contenant les données sérialisées.
     */
    std::any serialize(const std::any& data) const override;
};

inline std::any AlgoDistanceSerializer::serialize(const std::any& data) const
{
    const auto& solution = std::any_cast<const AlgoDistanceSolution&>(data);

    AlgoDistanceReponseData out;

    // Sérialisation du chemin
    for (int idx : solution._chemin) out._chemin.push_back(std::to_string(idx));

    out._distanceTotale = std::to_string(solution._distanceTotale);

    return out;
}

#endif  // ALGO_DISTANCE_SERIALIZER_H