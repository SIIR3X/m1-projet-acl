#ifndef I_ENTITE_PARSER_BASE_H
#define I_ENTITE_PARSER_BASE_H

#include <any>
#include <memory>
#include <string>
#include <vector>

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

    /**
     * @brief Construit un graphe à partir d'un ensemble d'entités et d'une stratégie de distance.
     * @param entites Un std::any contenant un std::vector<T>, où T est le type concret des entités.
     * @param strategieDistance Un std::any contenant un std::shared_ptr<Distance<T>>.
     * @return std::any contenant le graphe.
     * @throws std::bad_any_cast si les types contenus dans les std::any ne correspondent pas.
     */
    virtual std::any construireDonnees(const std::any& entites, const std::any& strategieDistance) const = 0;
};

#endif  // I_ENTITE_PARSER_BASE_H