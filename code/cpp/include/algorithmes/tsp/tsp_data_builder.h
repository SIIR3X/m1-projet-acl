#ifndef TSP_DATA_BUILDER_H
#define TSP_DATA_BUILDER_H

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

#endif  // TSP_DATA_BUILDER_H