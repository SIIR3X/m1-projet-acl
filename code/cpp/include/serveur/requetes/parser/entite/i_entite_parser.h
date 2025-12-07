#ifndef I_ENTITE_PARSER_H
#define I_ENTITE_PARSER_H

#include <any>

#include "algorithmes/distance/builder/algo_distance_data_builder.h"
#include "modele/generique/carte.h"
#include "modele/generique/distance.h"
#include "serveur/requetes/parser/distance/i_distance_parser_base.h"
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
     * @brief Parse le JSON, créer la stratégie de distance et construit les données prêtes pour utilisation dans un
     * algorithme.
     * @param json Chaîne JSON représentant un tableau d'entités.
     * @param distanceParser Le parseur de distance permettant de créer la stratégie.
     * @param machines Le nombre de machines.
     * @return std::any contenant les données prêtes pour les algorithmes de distance.
     */
    std::any construireDonneesAlgorithmesDistance(const std::string& json,
                                                  const std::shared_ptr<IDistanceParserBase>& distanceParser,
                                                  int machines) const override;
};

template <typename T>
inline std::any IEntiteParser<T>::construireDonneesAlgorithmesDistance(
    const std::string& json, const std::shared_ptr<IDistanceParserBase>& distanceParser, int machines) const
{
    // Récupération de entités depuis le JSON
    std::any entites =
        parser(json);  // Les entités (un std::vector<T>, dans notre projet, sera toujours un std::vector<Ville>)

    // Création de la stratégie de distance
    std::any strategie = distanceParser->creerStrategieDistance();  // La stratégie de calcul de distance (dans notre
                                                                    // projet, sera toujours la distance géodésique)

    // Cast des entités en vecteur
    const auto& vecteurEntites = std::any_cast<const std::vector<T>&>(entites);

    // Cast de la stratégie en stratégie de distance
    const auto& strategieDistance = std::any_cast<const std::shared_ptr<Distance<T>>&>(strategie);

    // Récupération du type de retour de la fonction de distance (R)
    using R = decltype((*strategieDistance)(std::declval<T>(), std::declval<T>()));

    // Construction de la carte
    Carte<T, R> carte(vecteurEntites,
                      [strategieDistance](const T& a, const T& b) { return (*strategieDistance)(a, b); });

    // Construction du graphe générique
    auto graphe = carte.construireGraphe();

    // Construction des données nécessaires aux algos de distance
    AlgoDistanceData data = AlgoDistanceDataBuilder::construireDonnees(graphe, machines);

    // Retour encapsulé dans std::any
    return std::any{data};
}

#endif  // I_ENTITE_PARSER_H