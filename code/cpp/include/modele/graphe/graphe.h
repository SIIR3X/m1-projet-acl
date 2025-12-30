#ifndef GRAPHE_H
#define GRAPHE_H

#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "modele/graphe/arete.h"
#include "modele/graphe/p_element.h"
#include "modele/graphe/sommet.h"

/**
 * @class Graphe
 * @brief Représentation générique d'un graphe basé sur des sommets et arêtes typés.
 */
template <typename S, typename T>
class Graphe
{
public:
    /**
     * @brief Constructeur par défaut.
     */
    Graphe() : _lSommets(nullptr), _lAretes(nullptr), _prochaineClef(0) {}

    /**
     * @brief Constructeur par copie.
     * @param other Graphe à copier.
     */
    Graphe(const Graphe<S, T>& other) : _lSommets(nullptr), _lAretes(nullptr), _prochaineClef(0)
    {
        copieDepuis(other);
    }

    /**
     * @brief Opérateur d'affectation.
     * @param other Graphe à copier.
     * @return Référence sur *this.
     */
    Graphe<S, T>& operator=(const Graphe<S, T>& other);

    /**
     * @brief Destructeur.
     */
    ~Graphe()
    {
        detruire();
    }

    std::vector<Sommet<T>*> sommets() const;

    /**
     * @brief Nombre total de sommets du graphe.
     * @return Le nombre de sommets du graphe.
     */
    int nombreSommets() const;

    /**
     * @brief Nombre total d'arêtes du graphe.
     * @return Le nombre d'arêtes du graphe.
     */
    int nombreAretes() const;

    /**
     * @brief Crée un sommet protant la valeur donnée.
     * @param valeur Valeur associée au sommet.
     * @return Un pointeur vers le sommet nouvelle crée.
     */
    Sommet<T>* creeSommet(const T& valeur);

    /**
     * @brief Crée une arête entre deux sommets donnés.
     * @param valeur Valeur portée par l'arête.
     * @param debut Sommet de départ.
     * @param fin Sommet d'arrivée.
     */
    Arete<S, T>* creeArete(const S& val, Sommet<T>* debut, Sommet<T>* fin);

    /**
     * @brief Retourne les arêtes incidentes à un sommet donné.
     */
    PElement<Arete<S, T>*>* aretesAdjacentes(const Sommet<T>* s) const;

    /**
     * @brief Retourne la liste des voisins du sommet.
     */
    PElement<Sommet<T>*>* voisins(const Sommet<T>* s) const;

    /**
     * @brief Retouurne la liste des couples (voisin, arête reliant au voisin).
     */
    PElement<std::pair<Sommet<T>*, Arete<S, T>*>>* adjacences(const Sommet<T>* s) const;

    /**
     * @brief Retourne l'arête reliant deux sommets, ou nullptr si aucune.
     */
    Arete<S, T>* getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const;

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant le graphe.
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param g Graphe à afficher.
     * @return Le flux après insertion.
     */
    template <typename X, typename Y>
    friend std::ostream& operator<<(std::ostream& os, const Graphe<X, Y>& g);

private:
    PElement<Sommet<T>*>* _lSommets;   ///< Liste chainée de pointeurs de sommets.
    PElement<Arete<S, T>*>* _lAretes;  ///< Liste chainée de pointeurs d'arêtes.
    int _prochaineClef;                ///< Clef du prochain sommet.

    /**
     * @brief Copie un autre objet de type graphe.
     * @param other Le graphe à copier.
     */
    void copieDepuis(const Graphe<S, T>& other);

    /**
     * @brief Détruit le graphe.
     */
    void detruire();
};

template <typename S, typename T>
inline Graphe<S, T>& Graphe<S, T>::operator=(const Graphe<S, T>& other)
{
    if (this != &other)
    {
        detruire();
        copieDepuis(other);
    }
    return *this;
}

template <typename S, typename T>
inline std::vector<Sommet<T>*> Graphe<S, T>::sommets() const
{
    std::vector<Sommet<T>*> res;

    for (auto p = _lSommets; p; p = p->_suivant) res.push_back(p->_info);

    return res;
}

template <typename S, typename T>
inline int Graphe<S, T>::nombreSommets() const
{
    int n = 0;

    for (auto p = _lSommets; p; p = p->_suivant) n++;

    return n;
}

template <typename S, typename T>
inline int Graphe<S, T>::nombreAretes() const
{
    int n = 0;

    for (auto p = _lAretes; p; p = p->_suivant) n++;

    return n;
}

template <typename S, typename T>
inline Sommet<T>* Graphe<S, T>::creeSommet(const T& valeur)
{
    Sommet<T>* s = new Sommet<T>(_prochaineClef++, valeur);
    _lSommets = new PElement<Sommet<T>*>(s, _lSommets);
    return s;
}

template <typename S, typename T>
inline Arete<S, T>* Graphe<S, T>::creeArete(const S& valeur, Sommet<T>* debut, Sommet<T>* fin)
{
    Arete<S, T>* a = new Arete<S, T>(_prochaineClef++, valeur, debut, fin);
    _lAretes = new PElement<Arete<S, T>*>(a, _lAretes);
    return a;
}

template <typename S, typename T>
inline PElement<Arete<S, T>*>* Graphe<S, T>::aretesAdjacentes(const Sommet<T>* s) const
{
    PElement<Arete<S, T>*>* res = nullptr;

    for (auto p = _lAretes; p; p = p->_suivant)
    {
        Arete<S, T>* a = p->_info;
        if (a->_debut == s || a->_fin == s)
            res = new PElement<Arete<S, T>*>(a, res);
    }

    return res;
}

template <typename S, typename T>
inline PElement<Sommet<T>*>* Graphe<S, T>::voisins(const Sommet<T>* s) const
{
    PElement<Sommet<T>*>* res = nullptr;

    for (auto p = _lAretes; p; p = p->_suivant)
    {
        Arete<S, T>* a = p->_info;

        if (a->_debut == s)
            res = new PElement<Sommet<T>*>(a->_fin, res);

        else if (a->_fin == s)
            res = new PElement<Sommet<T>*>(a->_debut, res);
    }

    return res;
}

template <typename S, typename T>
inline PElement<std::pair<Sommet<T>*, Arete<S, T>*>>* Graphe<S, T>::adjacences(const Sommet<T>* s) const
{
    PElement<std::pair<Sommet<T>*, Arete<S, T>*>>* res = nullptr;

    for (auto p = _lAretes; p; p = p->_suivant)
    {
        Arete<S, T>* a = p->_info;

        if (a->_debut == s)
            res = new PElement<std::pair<Sommet<T>*, Arete<S, T>*>>({a->_fin, a}, res);

        else if (a->_fin == s)
            res = new PElement<std::pair<Sommet<T>*, Arete<S, T>*>>({a->_debut, a}, res);
    }

    return res;
}

template <typename S, typename T>
inline Arete<S, T>* Graphe<S, T>::getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const
{
    for (auto p = _lAretes; p; p = p->_suivant)
    {
        if (p->_info->estEgal(s1, s2))
            return p->_info;
    }

    return nullptr;
}

template <typename S, typename T>
inline Graphe<S, T>::operator std::string() const
{
    std::stringstream ss;

    ss << "Sommets:\n";
    for (auto p = _lSommets; p; p = p->_suivant) ss << " " << static_cast<std::string>(*p->_info) << "\n";

    ss << "Arêtes:\n";
    for (auto p = _lAretes; p; p = p->_suivant) ss << " " << static_cast<std::string>(*p->_info) << "\n";

    return ss.str();
}

template <typename S, typename T>
inline std::ostream& operator<<(std::ostream& os, const Graphe<S, T>& g)
{
    os << static_cast<std::string>(g);
    return os;
}

template <typename S, typename T>
inline void Graphe<S, T>::copieDepuis(const Graphe<S, T>& other)
{
    _prochaineClef = other._prochaineClef;

    std::unordered_map<const Sommet<T>*, Sommet<T>*> mapSommets;

    // Copie des sommets
    for (auto p = other._lSommets; p; p = p->_suivant)
    {
        Sommet<T>* nouveau = creeSommet(p->_info->_v);
        nouveau->_clef = p->_info->_clef; // IMPORTANT
        mapSommets[p->_info] = nouveau;
    }

    // Copie des arêtes
    for (auto a = other._lAretes; a; a = a->_suivant)
    {
        auto oldA = a->_info;
        Sommet<T>* s1 = mapSommets.at(oldA->_debut);
        Sommet<T>* s2 = mapSommets.at(oldA->_fin);

        creeArete(oldA->_v, s1, s2);
    }
}

template <typename S, typename T>
inline void Graphe<S, T>::detruire()
{
    // Destruction des arêtes
    while (_lAretes)
    {
        PElement<Arete<S, T>*>* temp = _lAretes;
        _lAretes = _lAretes->_suivant;
        delete temp->_info;
        delete temp;
    }

    // Destruction des sommets
    while (_lSommets)
    {
        PElement<Sommet<T>*>* temp = _lSommets;
        _lSommets = _lSommets->_suivant;
        delete temp->_info;
        delete temp;
    }
}

#endif  // GRAPHE_H