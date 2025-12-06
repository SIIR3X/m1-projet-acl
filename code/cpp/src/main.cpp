#include <iostream>

#include "serveur/requetes/gestionnaires/algo_distance_requete_handler.h"
#include "serveur/requetes/gestionnaires/requete_handler_factory.h"
#include "serveur/requetes/parser/distance/distance_geodesique_parser.h"
#include "serveur/requetes/parser/entite/ville_parser.h"
#include "serveur/requetes/parser/parser_registry.h"

static const std::string REQUETE_TSP = R"json(
{
    "commande": "calcul",
    "algo": "tsp",
    "entite": "ville",
    "distance": "geodesique",
    "donnees": [
        {
            "nom": "Strasbourg",
            "latitude": 48.58,
            "longitude": 7.75
        },
        {
            "nom": "Metz",
            "latitude": 49.12,
            "longitude": 6.17
        },
        {
            "nom": "Nancy",
            "latitude": 48.69,
            "longitude": 6.18
        }
    ]
}
)json";

int main(int argc, char *argv[])
{
    // Enregistrement du TSPrequeteHandler
    RequeteHandlerFactory::enregistrerHandler("TSP", [] { return std::make_unique<AlgoDistanceRequeteHandler>(); });

    auto handler = RequeteHandlerFactory::creerHandler("TSP");

    // Enregistrement du parseur de ville
    ParserRegistry<IEntiteParserBase>::enregistrerParser("ville", std::make_shared<VilleParser>());

    // Enregistrement du parseur de distance pour les villes
    ParserRegistry<IDistanceParserBase>::enregistrerParser("geodesique",
                                                           std::make_shared<DistanceGeodesiqueParser<Ville>>());

    std::string test = handler->traiter(REQUETE_TSP);

    std::cout << test << std::endl;

    return 0;
}