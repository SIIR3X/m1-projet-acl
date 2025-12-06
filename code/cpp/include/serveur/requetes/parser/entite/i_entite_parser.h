#ifndef I_ENTITE_PARSER_H
#define I_ENTITE_PARSER_H

#include <any>
#include <utility>

#include "algorithmes/distance/builder/algo_distance_data_builder.h"
#include "algorithmes/gestionnaires/solveur_handler_factory.h"
#include "modele/generique/carte.h"
#include "modele/generique/distance.h"
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
     * @brief Construit un graphe à partir d'un ensemble d'entités et d'une stratégie de distance.
     * @param entites Un std::any contenant un std::vector<T>, où T est le type concret des entités.
     * @param strategieDistance Un std::any contenant un std::shared_ptr<Distance<T>>.
     * @return std::any contenant le graphe.
     * @throws std::bad_any_cast si les types contenus dans les std::any ne correspondent pas.
     */
    std::any construireDonnees(const std::any& entites, const std::any& strategieDistance) const override;
};

template <typename T>
inline std::any IEntiteParser<T>::construireDonnees(const std::any& entites, const std::any& strategieDistance) const
{
    // Cast des entités en vecteur
    const auto& vecteurEntites = std::any_cast<const std::vector<T>&>(entites);

    // Cest de la stratégie en stratégie de distance
    const auto& strategie = std::any_cast<const std::shared_ptr<Distance<T>>&>(strategieDistance);

    // Récupération du type de retour de la fonction de distance (R)
    using R = decltype((*strategie)(std::declval<T>(), std::declval<T>()));

    // Construction de la carte
    Carte<T, R> carte(vecteurEntites, [strategie](const T& a, const T& b) { return (*strategie)(a, b); });

    // Construction du graphe générique
    auto graphe = carte.construireGraphe();

    // Construction des données nécessaires aux algos de distance
    AlgoDistanceData data = AlgoDistanceDataBuilder::construireDonnees(graphe);

    // Retour encapsulé dans std::any
    return std::any{data};
}

#endif  // I_ENTITE_PARSER_H