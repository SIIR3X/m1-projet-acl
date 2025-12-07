#ifndef I_PARSER_BASE_H
#define I_PARSER_BASE_H

#include <string>

#include "types/nom_type.h"

/**
 * @class IParserBase
 * @brief Interface de base commune à tous les parseurs déclaratifs du système.
 */
template <typename T>
class IParserBase
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IParserBase() = default;

    /**
     * @brief Nom associé à ce parseur (ex : "ville").
     */
    virtual std::string nom() const = 0;

    /**
     * @brief Nom du type cyble réel T (ex : "Ville").
     */
    std::string typeCible() const
    {
        return NomType<T>::value();
    }
};

#endif  // I_PARSER_BASE_H