#ifndef NOM_TYPE_H
#define NOM_TYPE_H

#include <string>
#include <typeinfo>

/**
 * @brief Trait générique pour obtenir un nom lisible d'un type T.
 */
template <typename T>
struct NomType
{
    static std::string value()
    {
        return typeid(T).name();
    }
};

#endif  // NOM_TYPE_H