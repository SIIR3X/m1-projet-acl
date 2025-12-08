#ifndef DISTANCE_EFFACEE_H
#define DISTANCE_EFFACEE_H

#include <any>
#include <functional>
#include <typeinfo>

#include "modele/entites/entite.h"

class DistanceEffacee
{
public:
    using Fn = std::function<std::any(const Entite*, const Entite*)>;

    DistanceEffacee(Fn fn, const std::type_info& ti) : _fn(std::move(fn)), _typeRetour(ti) {}

    std::any operator()(const Entite* a, const Entite* b) const
    {
        return _fn(a, b);
    }

    const std::type_info& typeRetour() const
    {
        return _typeRetour;
    }

private:
    Fn _fn;
    const std::type_info& _typeRetour;
};

#endif  // DISTANCE_EFFACEE_H