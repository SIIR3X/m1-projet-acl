#ifndef GRAPHE_BUILDER_HANDLER_COR_H
#define GRAPHE_BUILDER_HANDLER_COR_H

#include <any>
#include <memory>
#include <vector>

#include "algorithmes/builders/graphe/graphe_builder_handler.h"

#include "modele/distances/distance_effacee.h"
#include "modele/entites/entite.h"

class GrapheBuilderHandlerCOR : public GrapheBuilderHandler
{
public:
    explicit GrapheBuilderHandlerCOR(std::shared_ptr<GrapheBuilderHandlerCOR> suivant = nullptr)
        : _suivant(std::move(suivant))
    {
    }

    std::any construire(const std::type_info& typeR, const std::vector<std::shared_ptr<Entite>>& entites,
                        const DistanceEffacee& distance) override;

protected:
    virtual std::any constuireGraphe(const std::type_info& typeR, const std::vector<std::shared_ptr<Entite>>& entites,
                                     const DistanceEffacee& distance) = 0;

private:
    std::shared_ptr<GrapheBuilderHandlerCOR> _suivant;  ///< Le maillon suivant de la chaîne de responsabilité.
};

inline std::any GrapheBuilderHandlerCOR::construire(const std::type_info& typeR,
                                                    const std::vector<std::shared_ptr<Entite>>& entites,
                                                    const DistanceEffacee& distance)
{
    // La chaîne tente de résoudre localement
    std::any solution = constuireGraphe(typeR, entites, distance);

    // La chaîne a réussi
    if (solution.has_value())
        return solution;

    // S'il existe un prochain maillon, alors il essaye de résoudre
    if (_suivant)
        return _suivant->construire(typeR, entites, distance);

    return std::any{};
}

#endif  // GRAPHE_BUILDER_HANDLER_COR_H