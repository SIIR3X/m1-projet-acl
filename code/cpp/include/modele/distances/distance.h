#ifndef DISTANCE_H
#define DISTANCE_H

#include <typeinfo>

template <typename T, typename R>
class Distance
{
public:
    virtual ~Distance() = default;

    virtual R operator()(const T& a, const T& b) const = 0;

    virtual const std::type_info& typeRetour() const
    {
        return typeid(R);
    }
};

#endif  // DISTANCE_H