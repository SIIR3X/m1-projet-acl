#include <iostream>

#include "modele/geographie/ville.h"
#include "serveur/requetes/handlers/requete_handler_factory.h"
#include "serveur/requetes/parsers/distance/distance_geodesique_parser.h"
#include "serveur/requetes/parsers/distance/i_distance_parser_base.h"
#include "serveur/requetes/parsers/entite/i_entite_parser_base.h"
#include "serveur/requetes/parsers/entite/ville_parser.h"
#include "serveur/requetes/parsers/parser_registry.h"
#include "utils/json_parser_utils.h"

static const std::string REQUETE = R"json(
{
    "commande": "algo_distance",
    "algo": "tsp",
    "entite": "ville",
    "distance": "geodesique",

    "ensembles": [
        {
            "machines": 1,
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
        },
        {
            "machines": 3,
            "donnees": [
                {
                    "nom": "Paris",
                    "latitude": 48.85,
                    "longitude": 2.35
                },
                {
                    "nom": "Lyon",
                    "latitude": 45.75,
                    "longitude": 4.85
                },
                {
                    "nom": "Dijon",
                    "latitude": 47.32,
                    "longitude": 5.04
                }
            ]
        }
    ]
}
)json";

int main(int argc, char *argv[])
{
    std::shared_ptr<IRequeteHandler> requeteHandler = RequeteHandlerFactory::creer();

    ParserRegistry<IEntiteParserBase>::enregistrerParser("ville", std::make_shared<VilleParser>());
    ParserRegistry<IDistanceParserBase>::enregistrerParser("geodesique",
                                                           std::make_shared<DistanceGeodesiqueParser<Ville>>());

    if (!requeteHandler)
        return 1;

    std::string commande =
        JsonParserUtils::recupererObligatoire(REQUETE, "commande", JsonParserUtils::extraireChampString);

    std::string reponse = requeteHandler->traiter(commande, REQUETE);

    std::cout << "Commande : " << commande << std::endl;
    std::cout << reponse << std::endl;

    return 0;
}