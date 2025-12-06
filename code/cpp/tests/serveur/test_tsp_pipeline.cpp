#include <gtest/gtest.h>

#include "algorithmes/tsp/tsp_solution.h"
#include "modele/geographie/ville.h"
#include "serveur/requetes/gestionnaires/tsp_requete_handler.h"
#include "serveur/requetes/parser/distance/distance_geodesique_parser.h"
#include "serveur/requetes/parser/entite/ville_parser.h"
#include "serveur/requetes/parser/parser_registry.h"
#include "serveur/requetes/requete_handler_factory.h"

static const std::string REQUETE_TSP = R"json(
{
    "entite": "ville",
    "distance": "geodesique",
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
}
)json";

TEST(TSPPipelineTest, PipelineComplet)
{
    // Enregistrement du TSPrequeteHandler
    RequeteHandlerFactory::enregistrerHandler("TSP", [] { return std::make_unique<TSPRequeteHandler>(); });

    // Récupération du bon handler via la factory
    auto handler = RequeteHandlerFactory::creerHandler("TSP");
    ASSERT_TRUE(handler);

    ParserRegistry<IEntiteParserBase>::enregistrerParser("ville", std::make_shared<VilleParser>());

    std::string test = handler->traiter(REQUETE_TSP);
    // EXPECT_EQ(test, "");
}