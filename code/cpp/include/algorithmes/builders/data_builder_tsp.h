#ifndef DATA_BUILDER_TSP_H
#define DATA_BUILDER_TSP_H

#include <memory>
#include <vector>

#include "algorithmes/builders/data_builder.h"
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
    if (args.size() != 3)
        throw std::runtime_error("DataBuilderTSP: invalid argument count");

    using EntitePtr = std::shared_ptr<Entite>;
    const auto& graphe = std::any_cast<const Graphe<double, EntitePtr>&>(args[0]);

    const auto& labels = std::any_cast<const std::vector<std::string>&>(args[1]);

    int machines = std::any_cast<int>(args[2]);

    TSPInputData data;

    int n = graphe.nombreSommets();
    data.nombreSommets = n;
    data.machines = machines;
    data.labels = labels;

    data.distances.assign(n, std::vector<double>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            auto s1 = graphe.sommets()[i];
            auto s2 = graphe.sommets()[j];
            auto a = graphe.getAreteParSommets(s1, s2);
            data.distances[i][j] = a ? a->_v : 0.0;
        }
    }

    return std::make_unique<TSPInputData>(std::move(data));
}

#endif  // DATA_BUILDER_TSP_H