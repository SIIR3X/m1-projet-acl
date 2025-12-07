#ifndef I_DISTANCE_PARSER_H
#define I_DISTANCE_PARSER_H

#include "modele/generique/distance.h"
#include "serveur/requetes/parsers/distance/i_distance_parser_base.h"
#include "serveur/requetes/parsers/i_parser_base.h"

/**
 * @class IDistanceParser
 * @brief Interface générique pour les parseurs de stratégies de distances de type T.
 */
template <typename T>
class IDistanceParser : public IDistanceParserBase, public IParserBase<T>
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IDistanceParser() = default;
};

#endif  // I_DISTANCE_PARSER_H