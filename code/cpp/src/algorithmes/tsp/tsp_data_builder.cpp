#include "algorithmes/tsp/tsp_data_builder.h"

#include <limits>

template <typename S, typename T>
TSPData TSPDataBuilder::construireDepuisGraphe(const Graphe<S, T>& graphe)
{
    TSPData data;

    auto sommets = extraireSommets(graphe);
    data._nombreSommets = sommets.size();

    data._distances = construireMatriceDistances(graphe, sommets);

    return data;
}

template <typename S, typename T>
std::vector<Sommet<T>*> TSPDataBuilder::extraireSommets(const Graphe<S, T>& graphe)
{
    std::vector<Sommet<T>*> sommets;
    sommets.reserve(graphe.nombreSommets());

    for (auto p = graphe._lSommets; p; p = p->_suivant) sommets.push_back(p->_info);

    return sommets;
}

template <typename S, typename T>
std::vector<std::vector<double>> TSPDataBuilder::construireMatriceDistances(const Graphe<S, T>& graphe,
                                                                            const std::vector<Sommet<T>*>& sommets)
{
    int n = sommets.size();
    std::vector<std::vector<double>> mat(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                mat[i][j] = 0.0;
                continue;
            }

            mat[i][j] = convertirDistance(graphe.getAreteParSommets(sommets[i], sommets[j]);)
        }
    }

    return mat;
}

template <typename S, typename T>
double TSPDataBuilder::convertirDistance(const Arete<S, T>* arete)
{
    if (!arete)
        return std::numeric_limits<double>::infinity();

    return static_cast<double>(arete->_v);
}