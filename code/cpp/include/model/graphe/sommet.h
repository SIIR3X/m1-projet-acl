#ifndef SOMMET_H
#define SOMMET_H

#include <ostream>
#include <sstream>
#include <string>

#include "model/graphe/g_element.h"

/**
 * @class Sommet
 * @brief Représente un sommet dans un graphe générique.
 */
template <typename T>
class Sommet : public GElement<T>
{
public:
    int _degre;  ///< Nombre d'arêtes incidentes.

    /**
     * @brief Constructeur principal.
     * @param clef Identifiant unique du sommet.
     * @param v Valeur contenue dans le sommet.
     */
    Sommet(int clef, const T& v) : GElement<T>(clef, v), _degre(0) {}

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant le sommet sous forme "{clef} : valeur (deg=degre)".
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param s Sommet à afficher.
     * @return Le flux après insertion.
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Sommet<U>& s);
};

template <typename T>
inline Sommet<T>::operator std::string() const
{
    std::stringstream ss;

    ss << GElement<T>::operator std::string() << " (deg=" << _degre << ")";

    return ss.str();
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Sommet<T>& s)
{
    os << static_cast<std::string>(s);
    return os;
}

#endif  // SOMMET_H