#ifndef ARETE_H
#define ARETE_H

#include <ostream>
#include <sstream>
#include <string>

#include "modele/graphe/g_element.h"
#include "modele/graphe/sommet.h"

template <typename S, typename T>
class Arete : public GElement<S>
{
public:
    Sommet<T>* _debut;  ///< Pointeur vers le sommet de départ.
    Sommet<T>* _fin;    ///< Pointeur vers le sommet d'arrivée.

    /**
     * @brief Constructeur principal.
     * @param clef Clef unique de l'élément.
     * @param v Valeur stockée dans l'élément.
     * @param debut Sommet de départ.
     * @param fin Sommet d'arrivée.
     */
    Arete(int clef, const S& valeur, Sommet<T>* debut, Sommet<T>* fin);

    /**
     * @brief Destructeur.
     */
    ~Arete();

    bool estEgal(const Sommet<T>* s1, const Sommet<T>* s2) const;

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant l'arête sous forme "{clef} : valeur [clef_debut -> clef_fin]".
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param a Arête à afficher.
     * @return Le flux après insertion.
     */
    template <typename U, typename V>
    friend std::ostream& operator<<(std::ostream& os, const Arete<U, V>& a);
};

template <typename S, typename T>
inline Arete<S, T>::Arete(int clef, const S& valeur, Sommet<T>* debut, Sommet<T>* fin)
    : GElement<S>(clef, valeur), _debut(debut), _fin(fin)
{
    if (_debut)
        _debut->_degre++;

    if (_fin)
        _fin->_degre++;
}

template <typename S, typename T>
inline Arete<S, T>::~Arete()
{
    if (_debut)
        _debut->_degre--;

    if (_fin)
        _fin->_degre--;
}

template <typename S, typename T>
inline bool Arete<S, T>::estEgal(const Sommet<T>* s1, const Sommet<T>* s2) const
{
    return (_debut == s1 && _fin == s2) || (_debut == s2 && _fin == s1);
}

template <typename S, typename T>
inline Arete<S, T>::operator std::string() const
{
    std::stringstream ss;

    ss << GElement<S>::operator std::string() << " [" << (_debut ? _debut->_clef : -1) << " -> "
       << (_fin ? _fin->_clef : -1) << "]";

    return ss.str();
}

template <typename S, typename T>
inline std::ostream& operator<<(std::ostream& os, const Arete<S, T>& a)
{
    os << static_cast<std::string>(a);
    return os;
}

#endif  // ARETE_H