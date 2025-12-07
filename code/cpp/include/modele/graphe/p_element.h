#ifndef PELEMENT_H
#define PELEMENT_H

/**
 * @struct PElement
 * @brief Élément d'une liste chainée simple utilisée pour stocker sommets et arêtes.
 */
template <typename T>
struct PElement
{
    T _info;                ///< Donnée stockée dans le maillon.
    PElement<T>* _suivant;  ///< Pointeur vers le prochain maillon.

    /**
     * @brief Constructeur principal.
     * @param info Donnée stockée.
     *  @param suivant Maillon suivant.
     */
    PElement(const T& info, PElement<T>* suivant) : _info(info), _suivant(suivant) {}
};

#endif  // PELEMENT_H