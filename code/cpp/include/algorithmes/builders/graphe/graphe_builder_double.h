#ifndef GRAPHE_BUILDER_DOUBLE_H
#define GRAPHE_BUILDER_DOUBLE_H

#include <any>
#include <memory>
#include <vector>

#include "algorithmes/builders/graphe/graphe_builder.h"

#include "modele/distances/distance_effacee.h"
#include "modele/entites/entite.h"
#include "modele/graphe/carte.h"

class GrapheBuilderDouble : public GrapheBuilder
{
public:
    std::any construire(const std::type_info& typeR, const std::vector<std::shared_ptr<Entite>>& entites,
                        const DistanceEffacee& distance) override;
};

inline std::any GrapheBuilderDouble::construire(const std::type_info& typeR,
                                                const std::vector<std::shared_ptr<Entite>>& entites,
                                                const DistanceEffacee& distance)
{
    if (typeR != typeid(double))
        return std::any{};

    using T = std::shared_ptr<Entite>;
    using R = double;

    typename Carte<T, R>::DistanceFunc distFn = [distance](const T& a, const T& b) -> R
    { return std::any_cast<R>(distance(a.get(), b.get())); };

    Carte<T, R> carte(entites, distFn);
    auto graphe = carte.construireGraphe();

    return std::make_shared<Graphe<R, T>>(graphe);
}

#endif  // GRAPHE_BUILDER_DOUBLE_H