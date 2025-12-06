#include <iostream>

#include "serveur/requetes/gestionnaires/requete_handler_factory.h"
#include "serveur/requetes/parser/distance/distance_geodesique_parser.h"
#include "serveur/requetes/parser/entite/ville_parser.h"

static const std::string REQUETE = R"json(
{
    "commande": "algo_distance",
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