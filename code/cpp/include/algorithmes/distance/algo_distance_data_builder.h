#ifndef ALGO_DISTANCE_DATA_BUILDER_H
#define ALGO_DISTANCE_DATA_BUILDER_H

#include <limits>
#include <vector>

#include "algorithmes/distance/algo_distance_data.h"
#include "modele/graphe/graphe.h"

/**
 * @class AlgoDistanceDataBuilder
 * @brief Classe utilitaire permettant de transformer un Graphe<T> en données exploitables.
 */
class AlgoDistanceDataBuilder
{
public:
    /**
     * @brief Construit une structure AlgoDistanceData à partir d'un graphe.
     * @param graphe Graphe à convertir en données exploitables.
     * @return Une structure AlgoDistanceData.
     */
    template <typename S, typename T>
    static AlgoDistanceData construireData(const Graphe<S, T>& graphe);

private:
    /**
     * @brief Construit la matrice carrée des distances entre tous les sommets.
     * @param graphe Graphe source.
     * @param sommets Liste des sommets.
     * @return Une matrice NxN des distances.
     */
    template <typename S, typename T>
    static std::vector<std::vector<double>> construireMatriceDistances(const Graphe<S, T>& graphe,
                                                                       const std::vector<Sommet<T>*>& sommets);

    /**
     * @brief Convertit une arête en distance exploitable par les algorithmes.
     * @param arete Arête reliant deux sommets.
     * @return La distance convertie en double, ou +inf si arete == nullptr.
     */
    template <typename S, typename T>
    static double convertirDistance(const Arete<S, T>* arete);
};

template <typename S, typename T>
inline AlgoDistanceData AlgoDistanceDataBuilder::construireData(const Graphe<S, T>& graphe)
{
    AlgoDistanceData data;

    // Récupération des sommets du graphe
    auto sommets = graphe.sommets();

    // Définition du nombre de sommets dans le graphe
    data._nombreSommets = sommets.size();

    // Construction de la matrice des distances à partir du graphe et des sommets
    data._distances = construireMatriceDistances(graphe, sommets);

    return data;
}

template <typename S, typename T>
inline std::vector<std::vector<double>> AlgoDistanceDataBuilder::construireMatriceDistances(
    const Graphe<S, T>& graphe, const std::vector<Sommet<T>*>& sommets)
{
    int n = sommets.size();
    std::vector<std::vector<double>> mat(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // Distance nulle pour un sommet vers lui-même
            if (i == j)
            {
                mat[i][j] = 0.0;
                continue;
            }

            // Récupération de l'arête et conversion en distance numérique
            mat[i][j] = convertirDistance(graphe.getAreteParSommets(sommets[i], sommets[j]));
        }
    }

    return mat;
}

template <typename S, typename T>
inline double AlgoDistanceDataBuilder::convertirDistance(const Arete<S, T>* arete)
{
    // Si l'arête n'existe pas, distance infinie
    if (!arete)
        return std::numeric_limits<double>::infinity();

    // Conversion générique en double de la valeur contenue dans l'arête
    return static_cast<double>(arete->_v);
}

#endif  // ALGO_DISTANCE_DATA_BUILDER_H