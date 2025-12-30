#include "serveur/requetes/handlers/requete_handler_algo_distance.h"

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "algorithmes/builders/data/data_builder_registry.h"
#include "algorithmes/builders/graphe/graphe_builder_registry.h"
#include "algorithmes/data/output/output_data.h"

#include "factories/solveur_handler_factory.h"

#include "modele/distances/distance_effacee.h"
#include "modele/entites/entite.h"

std::optional<std::vector<std::any>> RequeteHandlerAlgoDistance::traiterRequete(const std::string& commande,
                                                                                const std::vector<std::any>& argsBruts)
{
    if (argsBruts.size() != 4)
        return std::nullopt;

    try
    {
        std::string algo = std::any_cast<std::string>(argsBruts[0]);

        DistanceEffacee distanceEffacee = std::any_cast<DistanceEffacee>(argsBruts[1]);

        const auto& ensemblesEntites =
            std::any_cast<const std::vector<std::vector<std::shared_ptr<Entite>>>&>(argsBruts[2]);

        const auto& ensemblesLabels = std::any_cast<const std::vector<std::vector<std::string>>&>(argsBruts[3]);

        const std::type_info& typeR = distanceEffacee.typeRetour();

        auto solveur = SolveurHandlerFactory::chaine();
        auto grapheBuilder = GrapheBuilderRegistry::instance().get(typeR);
        auto dataBuilder = DataBuilderRegistry::instance().get(algo);

        std::vector<std::shared_ptr<OutputData>> solutions;
        solutions.reserve(ensemblesEntites.size());

        for (size_t i = 0; i < ensemblesEntites.size(); ++i)
        {
            const auto& entites = ensemblesEntites[i];

            const auto& labels = ensemblesLabels[i];

            std::any grapheAny = grapheBuilder->construire(typeR, entites, distanceEffacee);

            auto inputData = dataBuilder->construire(grapheAny, labels);

            std::any solAny = solveur->resoudre(algo, static_cast<TSPInputData&>(*inputData));

            auto solPtr = std::any_cast<std::shared_ptr<OutputData>>(solAny);

            solutions.push_back(solPtr);
        }

        std::vector<std::any> args;
        args.emplace_back(solutions);

        return args;
    }
    catch (...)
    {
        return std::nullopt;
    }
}