#include "serveur/requetes/gestionnaires/tsp_requete_handler.h"

#include <any>
#include <stdexcept>

#include "serveur/requetes/parser/distance/i_distance_parser_base.h"
#include "serveur/requetes/parser/entite/i_entite_parser_base.h"
#include "serveur/requetes/parser/parser_registry.h"
#include "utils/json_parser_utils.h"

std::string TSPRequeteHandler::traiter(const std::string& requete)
{
    try
    {
        // Récupération des champs obligatoires
        std::string entite =
            JsonParserUtils::recupererObligatoire(requete, "entite", JsonParserUtils::extraireChampString);
        std::string distance =
            JsonParserUtils::recupererObligatoire(requete, "distance", JsonParserUtils::extraireChampString);
        std::string donnees = JsonParserUtils::recupererObligatoire(requete, "donnees", JsonParserUtils::extraireBloc);

        // Création des entités
        std::shared_ptr<IEntiteParserBase> entiteParser =
            ParserRegistry<IEntiteParserBase>::get(entite);  // Récupération du parseur d'entité correspondant

        std::any resultatEntites = entiteParser->parser(
            donnees);  // Le résultat (un std::vector<T>, dans notre projet, sera toujours un std::vector<Ville>)

        // Création de la stratégie de distance
        std::shared_ptr<IDistanceParserBase> distanceParser =
            ParserRegistry<IDistanceParserBase>::get(distance);  // Récupération du parseur de distance correspondant

        std::any strategieDistance =
            distanceParser->creerStrategieDistance();  // La stratégie de calcul de distance (dans notre projet, sera
                                                       // toujours la distance géodésique)

        // Construction de la carte
        std::any carte = entiteParser->construireCarte(resultatEntites, strategieDistance);

        // TODO : appel du solveur TSP
        // TspResult<T, R>

        // TODO : sérialisation du résultat TSP
        // TspData

        // TODO : passage au COR des réponses

        // TODO : retourner le json final
    }
    catch (const std::exception& e)
    {
        return "vide";
    }
}