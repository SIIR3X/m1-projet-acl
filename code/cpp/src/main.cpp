#include <string>

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

#include <iostream>
#include <memory>

#include "serveur/requetes/handlers/requete_handler.h"
#include "serveur/requetes/parsers/distances/parseur_distance_geodesique.h"
#include "serveur/requetes/parsers/entites/parseur_ville.h"
#include "serveur/requetes/parsers/parseur_registry.h"

#include "algorithmes/builders/data_builder_registry.h"
#include "algorithmes/builders/data_builder_tsp.h"

#include "factories/requete_handler_factory.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<RequeteHandler> requeteHandler = RequeteHandlerFactory::chaine();
    if (!requeteHandler)
        return 1;

    RegistryParseur::instance().enregistrer("ville", []() { return std::make_unique<ParseurVille>(); });
    RegistryParseur::instance().enregistrer("geodesique",
                                            []() { return std::make_unique<ParseurDistanceGeodesique>(); });

    DataBuilderRegistry::instance().enregistrer("tsp", []() { return std::make_unique<DataBuilderTSP>(); });

    std::string commande =
        JsonParserUtils::recupererObligatoire(REQUETE, "commande", JsonParserUtils::extraireChampString);

    std::optional<std::string> reponse = requeteHandler->traiter(commande, REQUETE);

    std::cout << "Commande : " << commande << std::endl;
    std::cout << reponse.value() << std::endl;

    return 0;
}