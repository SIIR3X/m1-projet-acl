#ifndef TSP_DATA_BUILDER_H
#define TSP_DATA_BUILDER_H

#include <limits>
#include <vector>

#include "algorithmes/tsp/tsp_data.h"
#include "modele/graphe/graphe.h"

class TSPDataBuilder
{
public:
    template <typename S, typename T>
    static TSPData construireDepuisGraphe(const Graphe<S, T>& graphe);

private:
    template <typename S, typename T>
    static std::vector<Sommet<T>*> extraireSommets(const Graphe<S, T>& graphe);

    template <typename S, typename T>
    static std::vector<std::vector<double>> construireMatriceDistances(const Graphe<S, T>& graphe,
                                                                       const std::vector<Sommet<T>*>& sommets);

    template <typename S, typename T>
    static double convertirDistance(const Arete<S, T>* arete);
};

template <typename S, typename T>
inline TSPData TSPDataBuilder::construireDepuisGraphe(const Graphe<S, T>& graphe)
{
    TSPData data;

    auto sommets = extraireSommets(graphe);
    data._nombreSommets = sommets.size();

    data._distances = construireMatriceDistances(graphe, sommets);

    return data;
}

template <typename S, typename T>
inline std::vector<Sommet<T>*> TSPDataBuilder::extraireSommets(const Graphe<S, T>& graphe)
{
    return graphe.sommets();
}

template <typename S, typename T>
inline std::vector<std::vector<double>> TSPDataBuilder::construireMatriceDistances(
    const Graphe<S, T>& graphe, const std::vector<Sommet<T>*>& sommets)
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

            mat[i][j] = convertirDistance(graphe.getAreteParSommets(sommets[i], sommets[j]));
        }
    }

    return mat;
}

template <typename S, typename T>
inline double TSPDataBuilder::convertirDistance(const Arete<S, T>* arete)
{
    if (!arete)
        return std::numeric_limits<double>::infinity();

    return static_cast<double>(arete->_v);
}

#endif  // TSP_DATA_BUILDER_H