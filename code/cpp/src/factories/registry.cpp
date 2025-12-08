#include "factories/registry.h"

#include "serveur/requetes/parsers/distances/parser_distance_geodesique.h"
#include "serveur/requetes/parsers/entites/parser_ville.h"
#include "serveur/requetes/parsers/parser_registry.h"

#include "algorithmes/builders/data/data_builder_registry.h"
#include "algorithmes/builders/data/data_builder_tsp.h"

namespace Registry
{
    void enregistrerTout()
    {
        // Enregistrement des parseurs
        ParserRegistry::instance().enregistrer("ville", []() { return std::make_unique<ParseurVille>(); });
        ParserRegistry::instance().enregistrer("geodesique",
                                               []() { return std::make_unique<ParseurDistanceGeodesique>(); });

        // Enregistrement des builders
        DataBuilderRegistry::instance().enregistrer("tsp", []() { return std::make_unique<DataBuilderTSP>(); });
    }
}  // namespace Registry