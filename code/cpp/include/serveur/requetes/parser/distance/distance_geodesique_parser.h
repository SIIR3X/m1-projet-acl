#ifndef DISTANCE_GEODESIQUE_PARSER_H
#define DISTANCE_GEODESIQUE_PARSER_H

#include <memory>

#include "modele/geographie/distance/distance_geodesique.h"
#include "serveur/requetes/parser/distance/i_distance_parser.h"
#include "serveur/requetes/parser/parser_registry.h"

/**
 * @class DistanceGeodesiqueParser
 * @brief Parseur concret permettant de convertir un tableau JSON en une stratégie de distance.
 */
template <typename T>
class DistanceGeodesiqueParser : public IDistanceParser<T>
{
public:
    /**
     * @brief Constructeur principal. Se charge d'enregistrer le parseur dans le registry.
     */
    DistanceGeodesiqueParser();

    /**
     * @brief Nom associé à ce parseur (ex : "ville").
     */
    std::string nom() const override
    {
        return "geodesique";
    }

    /**
     * @brief Crée une stratégie de distance encapsulée dans un std::any.
     * @return std::any contenant un std::shared_ptr<Distance<T>>.
     */
    virtual std::any creerStrategieDistance() const override;
};

template <typename T>
inline DistanceGeodesiqueParser<T>::DistanceGeodesiqueParser()
{
    ParserRegistry<IDistanceParserBase>::enregistrerParser("geodesique",
                                                           std::make_shared<DistanceGeodesiqueParser<T>>());
}

template <typename T>
inline std::any DistanceGeodesiqueParser<T>::creerStrategieDistance() const
{
    auto ptr = std::make_shared<DistanceGeodesique<T>>([](const T& x) { return x.latitude(); },
                                                       [](const T& x) { return x.longitude(); });

    return std::any{ptr};
}

#endif  // DISTANCE_GEODESIQUE_PARSER_H