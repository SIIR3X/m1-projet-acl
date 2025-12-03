#ifndef DISTANCE_H
#define DISTANCE_H

/**
 * @brief Interface générique représentant une stratégie de calcul de distance entre deux objets T.
 */
template <typename T>
class Distance
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~Distance() = default;

    /**
     * @brief Calcule la distance (peut être n'importe quel type de distance) entre deux objets T.
     * @param a Premier objet.
     * @param b Deuxième objet.
     * @return La distance entre les deux objets.
     */
    virtual double operator()(const T& a, const T& b) const = 0;
};

#endif  // DISTANCE_H