#ifndef GRAPHE_BUILDER_HANDLER_DOUBLE_H
#define GRAPHE_BUILDER_HANDLER_DOUBLE_H

#include <any>
#include <memory>

#include "algorithmes/builders/graphe/graphe_builder_handler_cor.h"

#include "modele/graphe/carte.h"

class GrapheBuilderHandlerDouble : public GrapheBuilderHandlerCOR
{
protected:
    std::any constuireGraphe(const std::type_info& typeR, const std::vector<std::shared_ptr<Entite>>& entites,
                             const DistanceEffacee& distance) override;
};

inline std::any GrapheBuilderHandlerDouble::constuireGraphe(const std::type_info& typeR,
                                                            const std::vector<std::shared_ptr<Entite>>& entites,
                                                            const DistanceEffacee& distance)
{
    if (typeR != typeid(double))
        return std::any{};

    using T = std::shared_ptr<Entite>;
    using R = double;

    typename Carte<T, R>::DistanceFunc distanceFunc = [distance](const T& a, const T& b) -> R
    { return std::any_cast<R>(distance(a.get(), b.get())); };

    Carte<T, R> carte(entites, distanceFunc);

    auto graphe = carte.construireGraphe();

    return std::any{std::make_shared<Graphe<R, T>>(std::move(graphe))};
}

#endif  // GRAPHE_BUILDER_HANDLER_DOUBLE_H