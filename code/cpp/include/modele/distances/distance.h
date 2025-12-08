#ifndef DISTANCE_H
#define DISTANCE_H

template <typename T, typename R>
class Distance
{
public:
    virtual ~Distance() = default;

    virtual R operator()(const T& a, const T& b) const = 0;
};

#endif  // DISTANCE_H