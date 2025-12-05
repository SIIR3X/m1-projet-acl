#ifndef I_DISTANCE_PARSER_BASE_H
#define I_DISTANCE_PARSER_BASE_H

#include <any>

/**
 * @class IEntiteParserBase
 * @brief Interface polymorphe de base pour les parseurs de stratégies de distances.
 */
class IDistanceParserBase
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IDistanceParserBase() = default;

    /**
     * @brief Crée une stratégie de distance encapsulée dans un std::any.
     * @return std::any contenant un std::shared_ptr<Distance<T>>.
     */
    virtual std::any creerStrategieDistance() const = 0;
};

#endif  // I_DISTANCE_PARSER_BASE_H