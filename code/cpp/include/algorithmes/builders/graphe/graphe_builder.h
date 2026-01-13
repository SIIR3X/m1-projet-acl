#ifndef GRAPHE_BUILDER_H
#define GRAPHE_BUILDER_H

#include <any>
#include <memory>
#include <vector>

#include "modele/distances/distance_effacee.h"
#include "modele/entites/entite.h"

class GrapheBuilder
{
public:
    virtual ~GrapheBuilder() = default;

    virtual std::any construire(const std::type_info& typeR, const std::vector<std::shared_ptr<Entite>>& entites,
                                const DistanceEffacee& distance) = 0;
};

#endif  // GRAPHE_BUILDER_H