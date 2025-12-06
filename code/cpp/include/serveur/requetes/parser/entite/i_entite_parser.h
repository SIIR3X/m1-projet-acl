#ifndef I_ENTITE_PARSER_H
#define I_ENTITE_PARSER_H

#include <any>
#include <utility>

#include "algorithmes/tsp/solveur_tsp.h"
#include "algorithmes/tsp/tsp_data_builder.h"
#include "modele/generique/carte.h"
#include "modele/generique/distance.h"
#include "serveur/reponses/serializers/tsp_reponse_serializer.h"
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

    /**
     * @brief Lance la résolution du TSP sur les entités fournies.
     * @param entites Un std::any contenant std::vector<T>.
     * @param distance Un std::any contenant std::shared_ptr<Distance<T>>.
     * @return std::any contenant un TSPData<T,R>.
     */
    virtual std::any lancerTSP(const std::any& entites, const std::any& distance) const override;
};

template <typename T>
inline std::any IEntiteParser<T>::construireCarte(const std::any& entites, const std::any& distance) const
{
    auto vecteurEntites = std::any_cast<std::vector<T>>(entites);
    auto strategieDistance = std::any_cast<std::shared_ptr<Distance<T>>>(distance);

    // Déduction automatique du type R retourné par la stratégie de distance
    using R = decltype((*strategieDistance)(std::declval<T>(), std::declval<T>()));

    // Construction de la carte : la distance est injectée via un fonctor.
    Carte<T, R> carte(vecteurEntites,
                      [strategieDistance](const T& a, const T& b) { return (*strategieDistance)(a, b); });

    return std::any{carte};
}

template <typename T>
inline std::any IEntiteParser<T>::lancerTSP(const std::any& entites, const std::any& distance) const
{
    // Récupération des véritables types des paramètres
    auto vecteurEntites = std::any_cast<std::vector<T>>(entites);
    auto strategieDistance = std::any_cast<std::shared_ptr<Distance<T>>>(distance);

    // Déduction automatique du type R (type des distances)
    using R = decltype((*strategieDistance)(std::declval<T>(), std::declval<T>()));

    // Construction de la carte
    Carte<T, R> carte(vecteurEntites,
                      [strategieDistance](const T& a, const T& b) { return (*strategieDistance)(a, b); });

    // Construction du graphe associé à la carte
    auto graphe = carte.construireGraphe();

    // Construction des données TSP pour le solveur
    TSPData data = TSPDataBuilder::construireDepuisGraphe(graphe);

    // Appel du solveur générique sur les données
    TSPSolution solution = SolveurTSP::resoudre(data);

    // Sérialisation de TSPSolution vers TSPData
    TSPReponseSerializer serializer;
    auto serialized = serializer.serialize(solution);

    return std::any{serialized};
}

#endif  // I_ENTITE_PARSER_H