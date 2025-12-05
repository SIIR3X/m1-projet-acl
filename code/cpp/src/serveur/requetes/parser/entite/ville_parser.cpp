#include "serveur/requetes/parser/entite/ville_parser.h"

#include <cstdlib>
#include <stdexcept>

#include "serveur/requetes/parser/parser_registry.h"
#include "utils/json_parser_utils.h"

std::any VilleParser::parser(const std::string& json) const
{
    std::vector<Ville> villes;

    // Extraction de la liste des villes en objets JSON
    auto objets = JsonParserUtils::extraireListeObjets(json);

    for (const auto& obj : objets)
    {
        // Récupération des champs obligatoires
        std::string nom = JsonParserUtils::recupererObligatoire(obj, "nom", JsonParserUtils::extraireChampObjet);
        std::string latStr = JsonParserUtils::recupererObligatoire(obj, "lat", JsonParserUtils::extraireChampObjet);
        std::string lonStr = JsonParserUtils::recupererObligatoire(obj, "lon", JsonParserUtils::extraireChampObjet);

        // Conversion des données
        double lat = std::stod(latStr);
        double lon = std::stod(lonStr);

        villes.emplace_back(nom, lat, lon);
    }

    return std::any{villes};
}