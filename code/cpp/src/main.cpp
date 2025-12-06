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

    return 0;
}