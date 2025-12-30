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

#include <iostream>

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

private:
    std::vector<int> construireGlouton(const TSPInputData& data);

    void optimiser2Opt(const TSPInputData& data, std::vector<int>& chemin);

    double calculerCout(const TSPInputData& data, const std::vector<int>& chemin);
};

inline std::any SolveurHandlerTSP::resoudreDonnees(const std::string& nomAlgo, const std::any& donnees)
{
    if (algoFromString(nomAlgo) != AlgoType::TSP)
        return std::any{};

    const auto& inputData = std::any_cast<const TSPInputData&>(donnees);

    // 1. Construction gloutonne
    std::vector<int> chemin = construireGlouton(inputData);

    // 2. Optimisation locale
    optimiser2Opt(inputData, chemin);

    // 3. Coût final
    double cout = calculerCout(inputData, chemin);

    // 4. Construction de la sortie
    auto output = std::make_unique<TSPOutputData>();
    output->chemin = chemin;
    output->distanceTotale = cout;
    output->labels = inputData.labels;

    output->distances.reserve(chemin.size() - 1);
    for (size_t i = 0; i + 1 < chemin.size(); ++i)
        output->distances.push_back(inputData.distances[chemin[i]][chemin[i + 1]]);

    return std::any{std::shared_ptr<OutputData>(std::move(output))};
}

inline std::vector<int> SolveurHandlerTSP::construireGlouton(const TSPInputData& data)
{
    int n = data.nombreSommets;

    std::vector<int> chemin;
    chemin.reserve(n + 1);

    std::vector<bool> visite(n, false);

    int courant = 0;
    chemin.push_back(courant);
    visite[courant] = true;

    for (int k = 1; k < n; ++k)
    {
        int suivant = -1;
        double minDist = std::numeric_limits<double>::max();

        for (int i = 0; i < n; ++i)
        {
            if (!visite[i])
            {
                double d = data.distances[courant][i];
                if (d < minDist)
                {
                    minDist = d;
                    suivant = i;
                }
            }
        }

        visite[suivant] = true;
        chemin.push_back(suivant);
        courant = suivant;
    }

    // Retour au départ
    chemin.push_back(chemin.front());
    return chemin;
}

inline void SolveurHandlerTSP::optimiser2Opt(const TSPInputData& data, std::vector<int>& chemin)
{
    bool amelioration = true;
    int n = chemin.size();
    int maxIter = 100;

    while (amelioration && maxIter-- > 0)
    {
        amelioration = false;

        for (int i = 1; i < n - 2; ++i)
        {
            for (int j = i + 1; j < n - 1; ++j)
            {
                int a = chemin[i - 1];
                int b = chemin[i];
                int c = chemin[j];
                int d = chemin[j + 1];

                double avant =
                    data.distances[a][b] + data.distances[c][d];
                double apres =
                    data.distances[a][c] + data.distances[b][d];

                if (apres < avant)
                {
                    std::reverse(chemin.begin() + i,
                                 chemin.begin() + j + 1);
                    amelioration = true;
                }
            }
        }
    }
}

inline double SolveurHandlerTSP::calculerCout(const TSPInputData& data, const std::vector<int>& chemin)
{
    double total = 0.0;

    for (size_t i = 0; i + 1 < chemin.size(); ++i)
        total += data.distances[chemin[i]][chemin[i + 1]];

    return total;   
}

#endif  // SOLVEUR_HANDLER_TSP_H