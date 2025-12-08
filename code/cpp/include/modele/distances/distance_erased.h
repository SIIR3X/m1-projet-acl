#ifndef DISTANCE_ERASED_H
#define DISTANCE_ERASED_H

#include <any>
#include <functional>

#include "modele/entites/entite.h"

class DistanceErased
{
public:
    using Fn = std::function<std::any(const Entite*, const Entite*)>;

    DistanceErased(Fn fn) : _fn(std::move(fn)) {}

    std::any operator()(const Entite* a, const Entite* b) const
    {
        return _fn(a, b);
    }

private:
    Fn _fn;
};

#endif  // DISTANCE_ERASED_H