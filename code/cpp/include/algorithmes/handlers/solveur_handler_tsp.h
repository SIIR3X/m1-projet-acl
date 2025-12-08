#ifndef SOLVEUR_HANDLER_TSP_H
#define SOLVEUR_HANDLER_TSP_H

#include <algorithm>
#include <any>
#include <random>
#include <string>

#include "algorithmes/data/input/tsp_input_data.h"
#include "algorithmes/data/output/tsp_output_data.h"
#include "algorithmes/handlers/solveur_handler_cor.h"

#include "types/algo_type.h"

/**
 * @class RequeteHandlerAlgoDistance
 * @brief Maillon chargé de gérer les requêtes de types "algo_distance" dans la chaîne de responsabilité.
 */
class SolveurHandlerTSP : public SolveurHandlerCOR
{
protected:
    /**
     * @brief Tente de résoudre les données via l'algorithme demandé.
     * @param nomAlgo Le nom de l'algorithme demandé.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    std::any resoudreDonnees(const std::string& nomAlgo, const std::any& donnees) override;
};

inline std::any SolveurHandlerTSP::resoudreDonnees(const std::string& nomAlgo, const std::any& donnees)
{
    if (algoFromString(nomAlgo) != AlgoType::TSP)
        return std::any{};

    const auto& inputData = std::any_cast<const TSPInputData&>(donnees);

    int n = inputData.nombreSommets;

    std::vector<int> chemin(n);
    for (int i = 0; i < n; ++i) chemin[i] = i;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(chemin.begin(), chemin.end(), gen);

    auto output = std::make_unique<TSPOutputData>();
    output->chemin = chemin;
    output->distances.reserve(n - 1);
    output->labels = inputData.labels;

    double total = 0.0;
    for (int i = 0; i + 1 < n; ++i)
    {
        int a = chemin[i];
        int b = chemin[i + 1];

        double d = inputData.distances[a][b];
        output->distances.push_back(d);
        total += d;
    }
    output->distanceTotale = total;

    return std::any{std::shared_ptr<OutputData>(std::move(output))};
}

#endif  // SOLVEUR_HANDLER_TSP_H