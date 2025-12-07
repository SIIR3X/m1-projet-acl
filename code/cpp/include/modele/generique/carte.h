#ifndef CARTE_H
#define CARTE_H

#include <functional>
#include <ostream>
#include <sstream>
#include <vector>

#include "modele/graphe/graphe.h"

/**
 * @class Carte
 * @brief Carte générique contenant des éléments de type T.
 */
template <typename T, typename R>
class Carte
{
public:
    /**
     * @brief Type représentant une fonction de distance entre deux éléments renvoyant un type R.
     */
    using DistanceFunc = std::function<R(const T&, const T&)>;

    /**
     * @brief Constructeur principal.
     * @param elements Liste d'éléments de type T.
     * @param distance Fonction donnant la distance entre deux éléments.
     */
    Carte(const std::vector<T>& elements, DistanceFunc distance) : _elements(elements), _distance(distance) {}

    /**
     * @brief Ajoute un élément à la carte.
     * @param element L'élément à ajouter.
     */
    void ajouter(const T& element)
    {
        _elements.push_back(element);
    }

    /**
     * @brief Retourne la liste des éléments.
     * @return La liste (vecteur) des éléments.
     */
    const std::vector<T>& elements() const
    {
        return _elements;
    }

    /**
     * @brief Construit un graphe complte en utilisant la fonction de distance.
     * @return Le graphe construit.
     */
    Graphe<R, T> construireGraphe() const;

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant la carte.
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param c Carte à afficher.
     * @return Le flux après insertion.
     */
    template <typename U, typename S>
    friend std::ostream& operator<<(std::ostream& os, const Carte<U, S>& v);

private:
    std::vector<T> _elements;  ///< Liste d'éléments de type T stockées dans la carte.
    DistanceFunc _distance;    ///< Fonction permettant de calculer la distance entre les éléments.
};

template <typename T, typename R>
inline Graphe<R, T> Carte<T, R>::construireGraphe() const
{
    Graphe<R, T> g;
    std::vector<Sommet<T>*> sommets;
    sommets.reserve(_elements.size());

    // Création des sommets
    for (const T& element : _elements) sommets.push_back(g.creeSommet(element));

    // Création des arêtes pondérées
    const int n = sommets.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            R d = _distance(sommets[i]->_v, sommets[j]->_v);
            g.creeArete(d, sommets[i], sommets[j]);
            g.creeArete(d, sommets[j], sommets[i]);
        }
    }

    return g;
}

template <typename T, typename R>
inline Carte<T, R>::operator std::string() const
{
    std::stringstream ss;
    ss << "Carte (" << _elements.size() << " elements):\n";

    for (const T& element : _elements) ss << " - " << static_cast<std::string>(element) << "\n";

    return ss.str();
}

template <typename U, typename S>
inline std::ostream& operator<<(std::ostream& os, const Carte<U, S>& c)
{
    os << static_cast<std::string>(c);
    return os;
}

#endif  // CARTE_H