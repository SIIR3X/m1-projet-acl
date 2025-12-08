#include "serveur/requetes/handlers/requete_handler_algo_distance.h"

#include <any>
#include <exception>
#include <memory>

#include "serveur/requetes/parsers/parseur_registry.h"

#include "algorithmes/builders/data_builder_registry.h"
#include "algorithmes/data/output/output_data.h"

#include "modele/distances/distance_erased.h"
#include "modele/entites/entite.h"
#include "modele/generique/carte.h"

#include "utils/json_parser_utils.h"

#include "factories/reponse_handler_factory.h"
#include "factories/solveur_handler_factory.h"
#include "types/commande_type.h"

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

        // Récupération des parseurs correspondant à l'entité et au type de distance demandée
        auto parseurEntites = RegistryParseur::instance().get(entite);
        auto parseurDistance = RegistryParseur::instance().get(distance);

        // Création de la chaîne COR des handlers de solveurs
        auto solveur = SolveurHandlerFactory::chaine();

        auto dataBuilder = DataBuilderRegistry::instance().get(algo);

        std::any distanceAny = parseurDistance->parser(requete);

        auto distanceErased = std::any_cast<DistanceErased>(distanceAny);

        using T = std::shared_ptr<Entite>;
        using R = double;

        Carte<T, R>::DistanceFunc distanceFunc = [distanceErased](const T& a, const T& b) -> R
        {
            // a.get() et b.get() donnent des Entite*
            std::any resAny = distanceErased(a.get(), b.get());
            return std::any_cast<R>(resAny);  // R == double
        };

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
            auto entites = std::any_cast<std::vector<T>>(entitesAny);

            std::vector<std::string> labels;
            labels.reserve(entites.size());

            for (const auto& entite : entites) labels.push_back(entite->nom());

            Carte<T, R> carte(entites, distanceFunc);
            auto graphe = carte.construireGraphe();

            auto inputData = dataBuilder->construire(graphe, labels, machines);

            auto resultatAny = solveur->resoudre(algo, static_cast<TSPInputData&>(*inputData));

            auto outputPtr = std::any_cast<std::shared_ptr<OutputData>>(resultatAny);

            solutions.push_back(outputPtr);
        }

        std::vector<std::any> args;
        args.emplace_back(solutions);  // un seul élément : le vecteur complet

        auto gestionnaire = ReponseHandlerFactory::chaine();

        auto reponse = gestionnaire->construire(commande, args);

        return reponse;
    }
    catch (const std::exception& e)
    {
        return "{\"erreur\":\"Impossible de traiter la requête\"}";
    }
}