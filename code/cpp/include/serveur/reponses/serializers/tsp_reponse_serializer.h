#ifndef TSP_RESPONSE_SERIALIZER
#define TSP_RESPONSE_SERIALIZER

#include "algorithmes/tsp/tsp_solution.h"
#include "serveur/reponses/data/tsp_reponse_data.h"
#include "serveur/reponses/serializers/i_reponse_serializer.h"
#include "utils/json_builder.h"

class TSPReponseSerializer : public IReponseSerializer
{
public:
    std::any serialize(const std::any& data) const override;

    std::string type() const override
    {
        return "TSP";
    }
};

inline std::any TSPReponseSerializer::serialize(const std::any& data) const
{
    const auto& solution = std::any_cast<const TSPSolution&>(data);

    TSPReponseData out;

    // Sérialisation du chemin
    for (int idx : solution._chemin) out._chemin.push_back(std::to_string(idx));

    out._distanceTotale = std::to_string(solution._distanceTotale);

    return out;
}

#endif  // TSP_RESPONSE_SERIALIZER