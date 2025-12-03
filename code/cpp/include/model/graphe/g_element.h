#ifndef GELEMENT_H
#define GELEMENT_H

#include <ostream>
#include <sstream>
#include <string>

#include "model/graphe/a_element.h"

/**
 * @class GElement
 * @brief Élément générique du graphe contenant une valeur de type T.
 */
template <typename T>
class GElement : public AElement
{
public:
    T _v;  ///< Valeur portée par l'élément.

    /**
     * @brief Constructeur principal.
     * @param clef Clef unique de l'élément.
     * @param v Valeur stockée dans l'élément.
     */
    GElement(int clef, const T& v) : AElement(clef), _v(v) {}

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant l'élément sous forme "{clef} : valeur".
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param e Élément à afficher.
     * @return Le flux après insertion.
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const GElement<U>& e);
};

template <typename T>
inline GElement<T>::operator std::string() const
{
    std::string base = AElement::operator std::string();

    std::stringstream ss;
    ss << _v;

    return base + " : " + ss.str();
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const GElement<T>& e)
{
    os << static_cast<std::string>(e);
    return os;
}

#endif  // GELEMENT_H