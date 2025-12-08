#include <iostream>
#include <memory>
#include <string>

#include "serveur/requetes/handlers/requete_handler.h"

#include "factories/registry.h"
#include "factories/requete_handler_factory.h"

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
                    "ville": "Strasbourg",
                    "latitude": 48.58,
                    "longitude": 7.75
                },
                {
                    "ville": "Metz",
                    "latitude": 49.12,
                    "longitude": 6.17
                },
                {
                    "ville": "Nancy",
                    "latitude": 48.69,
                    "longitude": 6.18
                }
            ]
        },
        {
            "machines": 3,
            "donnees": [
                {
                    "ville": "Paris",
                    "latitude": 48.85,
                    "longitude": 2.35
                },
                {
                    "ville": "Lyon",
                    "latitude": 45.75,
                    "longitude": 4.85
                },
                {
                    "ville": "Dijon",
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
    Registry::enregistrerTout();

    std::shared_ptr<RequeteHandler> requeteHandler = RequeteHandlerFactory::chaine();
    if (!requeteHandler)
        return 1;

    std::string commande =
        JsonParserUtils::recupererObligatoire(REQUETE, "commande", JsonParserUtils::extraireChampString);

    std::optional<std::string> reponse = requeteHandler->traiter(commande, REQUETE);

    std::cout << "Commande : " << commande << std::endl;
    std::cout << reponse.value() << std::endl;

    return 0;
}