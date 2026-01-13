#ifndef DATA_BUILDER_TSP_H
#define DATA_BUILDER_TSP_H

#include <memory>
#include <vector>

#include "algorithmes/builders/data/data_builder.h"
#include "algorithmes/data/input/tsp_input_data.h"

#include "modele/entites/entite.h"
#include "modele/graphe/graphe.h"

class DataBuilderTSP : public DataBuilder
{
protected:
    std::unique_ptr<InputData> construireDonnees(const std::vector<std::any>& args) const override;
};

inline std::unique_ptr<InputData> DataBuilderTSP::construireDonnees(const std::vector<std::any>& args) const
{
    if (args.size() != 2)
        throw std::runtime_error("DataBuilderTSP::construireDonnees : nombre d'arguments invalide");

    using EntitePtr = std::shared_ptr<Entite>;
    using GrapheT   = Graphe<double, EntitePtr>;

    auto graphePtr = std::any_cast<std::shared_ptr<GrapheT>>(args[0]);
    if (!graphePtr)
        throw std::runtime_error("DataBuilderTSP : graphe nul");

    const GrapheT& graphe = *graphePtr;

    const auto& labels =
        std::any_cast<const std::vector<std::string>&>(args[1]);

    auto data = std::make_unique<TSPInputData>();
    const auto sommets = graphe.sommets();
    const int n = static_cast<int>(sommets.size());

    data->nombreSommets = n;
    data->labels = labels;
    data->distances.assign(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                data->distances[i][j] = 0.0;
                continue;
            }

            auto arete = graphe.getAreteParSommets(sommets[i], sommets[j]);
            if (arete)
                data->distances[i][j] = arete->_v;
        }
    }

    return data;
}

#endif  // DATA_BUILDER_TSP_H