#ifndef VILLE_PARSER_H
#define VILLE_PARSER_H

#include <string>
#include <vector>

#include "serveur/requetes/parsers/entite/i_entite_parser.h"

#include "modele/geographie/ville.h"

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

    /**
     * @brief Extrait une liste de labels directement depuis le JSON fourni.
     * @param json Le bloc JSON contenant les entités.
     * @return Un vecteur de labels.
     */
    std::vector<std::string> extraireLabels(const std::string& json) const override;
};

#endif  // VILLE_PARSER_H