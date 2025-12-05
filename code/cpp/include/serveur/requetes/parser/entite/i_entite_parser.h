#ifndef I_ENTITE_PARSER_H
#define I_ENTITE_PARSER_H

#include <any>

#include "modele/generique/carte.h"
#include "serveur/requetes/parser/entite/i_entite_parser_base.h"
#include "serveur/requetes/parser/i_parser_base.h"

/**
 * @class IEntiteParser
 * @brief Interface générique pour les parseurs d'entités de type T.
 */
template <typename T>
class IEntiteParser : public IEntiteParserBase, public IParserBase<T>
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IEntiteParser() = default;

    /**
     * @brief Construit dynamiquement une carte.
     * @param entites Un std::any contenant std::vector<T>.
     * @param distance Un std::any contenant std::shared_ptr<Distance<T>>.
     * @return Un std::any contenant une instance de Carte<T>.
     */
    virtual std::any construireCarte(const std::any& entites, const std::any& distance) const override;
};

template <typename T>
inline std::any IEntiteParser<T>::construireCarte(const std::any& entites, const std::any& distance) const
{
    auto vecteurEntites = std::any_cast<std::vector<T>>(entites);
    auto strategieDistance = std::any_cast<std::shared_ptr<Distance<T>>>(distance);

    // Construction de la carte : la distance est injectée via un fonctor.
    Carte<T> carte(vecteurEntites, [strategieDistance](const T& a, const T& b) { return (*dist)(a, b); });

    return std::any{carte};
}

#endif  // I_ENTITE_PARSER_H