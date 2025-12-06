#ifndef I_ENTITE_PARSER_BASE_H
#define I_ENTITE_PARSER_BASE_H

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "serveur/requetes/parser/distance/i_distance_parser_base.h"

/**
 * @class IEntiteParserBase
 * @brief Interface polymorphe de base pour les parseurs d'entités.
 */
class IEntiteParserBase
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IEntiteParserBase() = default;

    /**
     * @brief Parse le JSON, créer la stratégie de distance et construit les données prêtes pour utilisation dans un
     * algorithme.
     * @param json Chaîne JSON représentant un tableau d'entités.
     * @param distanceParser Le parseur de distance permettant de créer la stratégie.
     * @return std::any contenant les données prêtes pour les algorithmes de distance.
     */
    virtual std::any construireDonneesAlgorithmesDistance(
        const std::string& json, const std::shared_ptr<IDistanceParserBase>& distanceParser) const = 0;

    /**
     * @brief Parse un tableau JSON en collection typée de T.
     * @param json Chaîne JSON représentant un tableau d'entités.
     * @return std::any contenant un std::vector<T>
     */
    virtual std::any parser(const std::string& json) const = 0;

    /**
     * @brief Extrait une liste de labels directement depuis le JSON fourni.
     * @param json Le bloc JSON contenant les entités.
     * @return Un vecteur de labels.
     */
    virtual std::vector<std::string> extraireLabels(const std::string& json) const = 0;
};

#endif  // I_ENTITE_PARSER_BASE_H