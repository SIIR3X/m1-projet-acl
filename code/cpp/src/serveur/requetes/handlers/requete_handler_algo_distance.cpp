#include "serveur/requetes/handlers/requete_handler_algo_distance.h"

#include <any>
#include <exception>

#include "serveur/reponses/handlers/reponse_handler_factory.h"
#include "serveur/reponses/types/algo_distance_reponse.h"
#include "serveur/requetes/parsers/distance/i_distance_parser_base.h"
#include "serveur/requetes/parsers/entite/i_entite_parser_base.h"
#include "serveur/requetes/parsers/parser_registry.h"

#include "algorithmes/handlers/solveur_handler_factory.h"

#include "utils/json_parser_utils.h"

#include "types/commande_type.h"

std::optional<std::string> RequeteHandlerAlgoDistance::traiterRequete(const std::string& commande,
                                                                      const std::string& requete)
{
    if (commandeFromString(commande) != CommandeType::ALGO_DISTANCE)
        return std::nullopt;

    try
    {
        // Récupération des champs obligatoires
        std::string algo = JsonParserUtils::recupererObligatoire(requete, "algo", JsonParserUtils::extraireChampString);
        std::string entite =
            JsonParserUtils::recupererObligatoire(requete, "entite", JsonParserUtils::extraireChampString);
        std::string distance =
            JsonParserUtils::recupererObligatoire(requete, "distance", JsonParserUtils::extraireChampString);
        std::vector<std::string> ensembles =
            JsonParserUtils::extraireListeObjets(JsonParserUtils::extraireBloc(requete, "ensembles"));

        // Récupération des parseurs correspondant à l'entité et au type de distance demandée
        auto entiteParser =
            ParserRegistry<IEntiteParserBase>::get(entite);  // Récupération du parseur d'entité correspondant
        auto distanceParser =
            ParserRegistry<IDistanceParserBase>::get(distance);  // Récupération du parseur de distance correspondant

        // Création de la chaîne COR des handlers de solveurs
        auto solveur = SolveurHandlerFactory::creer();

        // Création de la chaîne COR des handlers de réponses
        auto gestionnaire = ReponseHandlerFactory::creer();

        // Création d'un vecteur contenant les réponses simples
        std::vector<std::shared_ptr<IReponse>> reponsesSimple;

        // Itération sur les ensembles de la requête
        for (const std::string& ensembleJson : ensembles)
        {
            // Récupération des champs obligatoires
            std::string donneesEnsemble =
                JsonParserUtils::recupererObligatoire(ensembleJson, "donnees", JsonParserUtils::extraireBloc);
            std::string machinesStr =
                JsonParserUtils::recupererObligatoire(ensembleJson, "machines", JsonParserUtils::extraireChampObjet);
            int machines = std::stoi(machinesStr);

            // Construction des données de l'algorithme via le parseur d'entités
            std::any donneesAlgoEnsemble =
                entiteParser->construireDonneesAlgorithmesDistance(donneesEnsemble, distanceParser, machines);

            // Calcul de la solution grace au solveur adapté
            std::any solutionEnsemble = solveur->resoudre(algo, donneesAlgoEnsemble);

            // Récupération des labels
            std::vector<std::string> labelsEnsemble = entiteParser->extraireLabels(donneesEnsemble);

            // Création de la réponse à l'ensemble en quesiton
            auto reponseEnsemble =
                gestionnaire->traiter(commande, solutionEnsemble, labelsEnsemble, donneesAlgoEnsemble);

            // Ajout de la réponse à la liste des réponses
            reponsesSimple.push_back(reponseEnsemble);
        }

        if (reponsesSimple.empty())
            throw std::runtime_error("Aucun ensemble n'a pu être traité.");

        // Cas : une seule réponse
        if (reponsesSimple.size() == 1)
            return reponsesSimple[0]->toJson();

        // Cas : plusieurs réponses
        auto reponseFinale = std::make_shared<AlgoDistanceReponse>(reponsesSimple);
        return reponseFinale->toJson();
    }
    catch (const std::exception& e)
    {
        return "{\"erreur\":\"Impossible de traiter la requête\"}";
    }
}