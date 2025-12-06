#ifndef I_ENTITE_PARSER_H
#define I_ENTITE_PARSER_H

#include <any>
#include <utility>

#include "algorithmes/gestionnaires/solveur_handler_factory.h"
#include "modele/generique/carte.h"
#include "modele/generique/distance.h"
#include "serveur/reponses/serializers/algo_distance_serializer.h"
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
     * @brief Lance la résolution via un algortihme sur les entités fournies.
     * @param nomAlgo Le nom de l'algorithme à utiliser.
     * @param entites Un std::any contenant std::vector<T>.
     * @param distance Un std::any contenant std::shared_ptr<Distance<T>>.
     * @return std::any contenant les données de résolution.
     */
    virtual std::any executerAlgorithme(const std::string& nomAlgo, const std::any& entites,
                                        const std::any& distance) const override;
};

template <typename T>
inline std::any IEntiteParser<T>::executerAlgorithme(const std::string& nomAlgo, const std::any& entites,
                                                     const std::any& distance) const
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

    // Création de la chaîne COR des handlers de solveurs
    auto gestionnaire = SolveurHandlerFactory<R, T>::creer();

    // Résolution via l'algorithme sur le graphe générique
    auto resultat = std::any_cast<AlgoDistanceSolution>(gestionnaire->resoudre(nomAlgo, graphe));

    // Sérialisation de la solution (dans notre projet, AlgoDistanceSolution vers AlgoDistanceData)
    auto resultatSerialise = AlgoDistanceSerializer::lancerSerialisation(resultat);

    return std::any{resultatSerialise};
}

#endif  // I_ENTITE_PARSER_H