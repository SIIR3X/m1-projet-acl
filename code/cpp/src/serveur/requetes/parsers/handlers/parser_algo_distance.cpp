#include "serveur/requetes/parsers/handlers/parser_algo_distance.h"

#include <vector>

#include "serveur/requetes/parsers/parser_registry.h"

#include "modele/entites/entite.h"

#include "utils/json_parser_utils.h"

std::vector<std::any> ParserAlgoDistance::parser(const std::string& json) const
{
    std::vector<std::any> argsBruts;

    std::string algo = JsonParserUtils::recupererObligatoire(json, "algo", JsonParserUtils::extraireChampString);
    std::string typeEntite =
        JsonParserUtils::recupererObligatoire(json, "entite", JsonParserUtils::extraireChampString);
    std::string typeDistance =
        JsonParserUtils::recupererObligatoire(json, "distance", JsonParserUtils::extraireChampString);

    argsBruts.emplace_back(algo);

    auto parseurDistance = ParserRegistry::instance().get(typeDistance);
    auto distVec = parseurDistance->parser(json);

    if (distVec.empty())
        return {};

    argsBruts.emplace_back(distVec[0]);

    auto ensemblesJson = JsonParserUtils::extraireListeObjets(JsonParserUtils::extraireBloc(json, "ensembles"));

    std::vector<std::vector<std::shared_ptr<Entite>>> ensemblesEntites;
    std::vector<std::vector<std::string>> ensemblesLabels;

    auto parseurEntites = ParserRegistry::instance().get(typeEntite);

    for (auto& ensembleJson : ensemblesJson)
    {
        std::string donneesBloc =
            JsonParserUtils::recupererObligatoire(ensembleJson, "donnees", JsonParserUtils::extraireBloc);

        auto entsVec = parseurEntites->parser(donneesBloc);
        if (entsVec.empty())
            return {};

        auto& entites = std::any_cast<const std::vector<std::shared_ptr<Entite>>&>(entsVec[0]);

        std::vector<std::string> labels;
        labels.reserve(entites.size());
        for (const auto& e : entites) labels.push_back(e->nom());

        ensemblesEntites.push_back(entites);
        ensemblesLabels.push_back(labels);
    }

    argsBruts.emplace_back(ensemblesEntites);
    argsBruts.emplace_back(ensemblesLabels);

    return argsBruts;
}