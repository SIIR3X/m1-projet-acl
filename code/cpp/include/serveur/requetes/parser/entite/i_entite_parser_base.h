#ifndef I_ENTITE_PARSER_BASE_H
#define I_ENTITE_PARSER_BASE_H

#include <any>
#include <memory>

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
     * @brief Construit dynamiquement une carte.
     * @param entites Un std::any contenant std::vector<T>.
     * @param distance Un std::any contenant std::shared_ptr<Distance<T>>.
     * @return Un std::any contenant une instance de Carte<T>.
     */
    virtual std::any construireCarte(const std::any& entites, const std::any& distance) const = 0;
};

#endif  // I_ENTITE_PARSER_BASE_H