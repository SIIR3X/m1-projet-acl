#include "serveur/requetes/handlers/requete_handler_algo_distance.h"

#include <any>
#include <exception>
#include <memory>

#include "serveur/requetes/parsers/parser_registry.h"

#include "algorithmes/builders/data/data_builder_registry.h"
#include "algorithmes/data/output/output_data.h"

#include "factories/graphe_builder_handler_factory.h"
#include "factories/reponse_handler_factory.h"
#include "factories/solveur_handler_factory.h"

#include "modele/distances/distance_effacee.h"

#include "types/commande_type.h"

#include "utils/json_parser_utils.h"

std::optional<std::string> RequeteHandlerAlgoDistance::traiterRequete(const std::string& commande,
                                                                      const std::string& requete)
{
    if (commandeFromString(commande) != CommandeType::ALGO_DISTANCE)
        return std::nullopt;

    try
    {
        // Récupération des champs obligatoires
        std::string algo = JsonParserUtils::recupererObligatoire(requete, "algo", JsonParserUtils::extraireChampString);
        std::string entite =
            JsonParserUtils::recupererObligatoire(requete, "entite", JsonParserUtils::extraireChampString);
        std::string distance =
            JsonParserUtils::recupererObligatoire(requete, "distance", JsonParserUtils::extraireChampString);
        std::vector<std::string> ensembles =
            JsonParserUtils::extraireListeObjets(JsonParserUtils::extraireBloc(requete, "ensembles"));

        auto parseurEntites = ParserRegistry::instance().get(entite);
        auto parseurDistance = ParserRegistry::instance().get(distance);

        auto solveur = SolveurHandlerFactory::chaine();
        auto grapheBuilder = GrapheBuilderHandlerFactory::chaine();
        auto dataBuilder = DataBuilderRegistry::instance().get(algo);

        std::any distanceAny = parseurDistance->parser(requete);
        auto distanceEffacee = std::any_cast<DistanceEffacee>(distanceAny);

        const std::type_info& typeR = distanceEffacee.typeRetour();

        std::vector<std::shared_ptr<OutputData>> solutions;
        solutions.reserve(ensembles.size());

        for (const std::string& ensembleJson : ensembles)
        {
            std::string donneesEnsemble =
                JsonParserUtils::recupererObligatoire(ensembleJson, "donnees", JsonParserUtils::extraireBloc);
            std::string machinesStr =
                JsonParserUtils::recupererObligatoire(ensembleJson, "machines", JsonParserUtils::extraireChampObjet);
            int machines = std::stoi(machinesStr);

            std::any entitesAny = parseurEntites->parser(donneesEnsemble);
            auto entites = std::any_cast<std::vector<std::shared_ptr<Entite>>>(entitesAny);

            std::vector<std::string> labels;
            labels.reserve(entites.size());

            for (const auto& entite : entites) labels.push_back(entite->nom());

            std::any grapheAny = grapheBuilder->construire(typeR, entites, distanceEffacee);

            auto inputData = dataBuilder->construire(grapheAny, labels, machines);

            auto resultatAny = solveur->resoudre(algo, static_cast<TSPInputData&>(*inputData));

            auto outputPtr = std::any_cast<std::shared_ptr<OutputData>>(resultatAny);

            solutions.push_back(outputPtr);
        }

        std::vector<std::any> args;
        args.emplace_back(solutions);

        auto gestionnaire = ReponseHandlerFactory::chaine();

        auto reponse = gestionnaire->construire(commande, args);

        return reponse;
    }
    catch (const std::exception& e)
    {
        return "{\"erreur\":\"Impossible de traiter la requête\"}";
    }
}