#ifndef PARSEUR_VILLE_H
#define PARSEUR_VILLE_H

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "serveur/requetes/parsers/parseur.h"

#include "modele/entites/entite.h"
#include "modele/entites/geographie/ville.h"

#include "utils/json_parser_utils.h"

class ParseurVille : public Parseur
{
public:
    std::any parser(const std::string& json) const override;
};

inline std::any ParseurVille::parser(const std::string& json) const
{
    std::vector<std::shared_ptr<Entite>> resultat;

    auto objets = JsonParserUtils::extraireListeObjets(json);
    for (auto& obj : objets)
    {
        // Récupération des champs obligatoires
        std::string nom = JsonParserUtils::recupererObligatoire(obj, "nom", JsonParserUtils::extraireChampObjet);
        std::string latStr =
            JsonParserUtils::recupererObligatoire(obj, "latitude", JsonParserUtils::extraireChampObjet);
        std::string lonStr =
            JsonParserUtils::recupererObligatoire(obj, "longitude", JsonParserUtils::extraireChampObjet);

        // Conversion des données
        double lat = std::stod(latStr);
        double lon = std::stod(lonStr);

        resultat.push_back(std::make_shared<Ville>(nom, lat, lon));
    }

    return resultat;
}

#endif  // PARSEUR_VILLE_H