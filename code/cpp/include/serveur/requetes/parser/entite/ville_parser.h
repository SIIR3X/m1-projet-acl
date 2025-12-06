#ifndef VILLE_PARSER_H
#define VILLE_PARSER_H

#include <string>
#include <vector>

#include "modele/geographie/ville.h"
#include "serveur/requetes/parser/entite/i_entite_parser.h"
#include "serveur/requetes/parser/parser_registry.h"

/**
 * @class VilleParser
 * @brief Parseur concret permettant de convertir un tableau JSON en une collection de Villes.
 */
class VilleParser : public IEntiteParser<Ville>
{
public:
    /**
     * @brief Constructeur principal.
     */
    VilleParser() = default;

    /**
     * @brief Nom associé à ce parseur (ex : "ville").
     */
    std::string nom() const override
    {
        return "ville";
    }

    /**
     * @brief Parse un tableau JSON en collection typée de T.
     * @param json Chaîne JSON représentant un tableau d'entités.
     * @return std::any contenant un std::vector<T>
     */
    std::any parser(const std::string& json) const override;
};

#endif  // VILLE_PARSER_H