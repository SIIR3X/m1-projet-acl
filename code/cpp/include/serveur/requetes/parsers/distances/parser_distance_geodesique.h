#ifndef PARSER_DISTANCE_GEODESIQUE_H
#define PARSER_DISTANCE_GEODESIQUE_H

#include <any>
#include <string>

#include "serveur/requetes/parsers/parser.h"

#include "modele/distances/distance_effacee.h"
#include "modele/distances/distance_geodesique.h"

class ParseurDistanceGeodesique : public Parser
{
public:
    std::vector<std::any> parser(const std::string& json) const override;
};

inline std::vector<std::any> ParseurDistanceGeodesique::parser(const std::string& json) const
{
    DistanceGeodesique distance;

    DistanceEffacee distEffacee(
        [distance](const Entite* a, const Entite* b) -> std::any
        {
            auto A = dynamic_cast<const EntiteGeographique*>(a);
            auto B = dynamic_cast<const EntiteGeographique*>(b);

            if (!A || !B)
                return std::any{};

            return std::any(distance(*A, *B));
        },
        typeid(double));

    return {distEffacee};
}

#endif  // PARSER_DISTANCE_GEODESIQUE_H