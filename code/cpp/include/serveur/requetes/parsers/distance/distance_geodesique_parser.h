#ifndef DISTANCE_GEODESIQUE_PARSER_H
#define DISTANCE_GEODESIQUE_PARSER_H

#include <memory>

#include "modele/geographie/distance/distance_geodesique.h"
#include "serveur/requetes/parsers/distance/i_distance_parser.h"

/**
 * @class DistanceGeodesiqueParser
 * @brief Parseur concret permettant de convertir un tableau JSON en une stratégie de distance.
 */
template <typename T>
class DistanceGeodesiqueParser : public IDistanceParser<T>
{
public:
    /**
     * @brief Constructeur principal.
     */
    DistanceGeodesiqueParser() = default;

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
inline std::any DistanceGeodesiqueParser<T>::creerStrategieDistance() const
{
    // Pointeur typé sur la classe DERIVÉE
    auto ptrDerive = std::make_shared<DistanceGeodesique<T>>([](const T& x) { return x.latitude(); },
                                                             [](const T& x) { return x.longitude(); });

    // Cast vers la classe de BASE
    std::shared_ptr<Distance<T>> ptrBase = ptrDerive;

    // Stocker le pointeur DE BASE dans le any
    return std::any{ptrBase};
}

#endif  // DISTANCE_GEODESIQUE_PARSER_H