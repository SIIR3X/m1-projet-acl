#include "serveur/requetes/gestionnaires/algo_distance_requete_handler.h"

#include <any>
#include <iostream>
#include <stdexcept>

#include "algorithmes/distance/data/algo_distance_data.h"
#include "algorithmes/gestionnaires/solveur_handler_factory.h"
#include "serveur/reponses/gestionnaires/i_reponse_handler.h"
#include "serveur/reponses/gestionnaires/reponse_handler_factory.h"
#include "serveur/requetes/parser/distance/i_distance_parser_base.h"
#include "serveur/requetes/parser/entite/i_entite_parser_base.h"
#include "serveur/requetes/parser/parser_registry.h"
#include "utils/json_parser_utils.h"

std::string AlgoDistanceRequeteHandler::genererReponse(const std::string& commande, const std::string& requete)
{
    try
    {
        // Récupération des champs obligatoires
        std::string algo = JsonParserUtils::recupererObligatoire(requete, "algo", JsonParserUtils::extraireChampString);
        std::string entite =
            JsonParserUtils::recupererObligatoire(requete, "entite", JsonParserUtils::extraireChampString);
        std::string distance =
            JsonParserUtils::recupererObligatoire(requete, "distance", JsonParserUtils::extraireChampString);
        std::string donnees = JsonParserUtils::recupererObligatoire(requete, "donnees", JsonParserUtils::extraireBloc);

        // Récupération des parseurs correspondant à l'entité et au type de distance demandée
        auto entiteParser =
            ParserRegistry<IEntiteParserBase>::get(entite);  // Récupération du parseur d'entité correspondant
        auto distanceParser =
            ParserRegistry<IDistanceParserBase>::get(distance);  // Récupération du parseur de distance correspondant

        // Construction des données de l'algorithme via le parseur d'entités
        std::any donneesAlgo = entiteParser->construireDonneesAlgorithmesDistance(requete, distanceParser);

        // Création de la chaîne COR des handlers de solveurs
        auto solveur = SolveurHandlerFactory::creer();

        // Calcul de la solution grace au solveur adapté
        std::any solution = solveur->resoudre(algo, donneesAlgo);

        // Création de la chaîne COR des handlers de réponses
        auto gestionnaire = ReponseHandlerFactory::creer();

        // Récupération des labels
        std::vector<std::string> labels = entiteParser->extraireLabels(donnees);

        // Création d'une réponse adaptée à la requête
        auto reponse = gestionnaire->traiter(commande, solution, labels, donneesAlgo);

        // Retour final de la réponse au format JSON
        return reponse->toJson();
    }
    catch (const std::exception& e)
    {
        return "vide";
    }
}