#ifndef AELEMENT_H
#define AELEMENT_H

#include <ostream>
#include <sstream>
#include <string>

/**
 * @class AElement
 * @brief Élément abstrait du graphe, défini uniquement par une clef unique.
 */
class AElement
{
public:
    int _clef;  ///< Identifiant unique.

    /**
     * @brief Constructeur principal.
     * @param clef Identifiant unique.
     */
    AElement(int clef) : _clef(clef) {}

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant l'élément sous forme "{clef}".
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param e Élément à afficher.
     * @return Le flux après insertion.
     */
    friend std::ostream& operator<<(std::ostream& os, const AElement& e);
};

inline AElement::operator std::string() const
{
    std::stringstream ss;
    ss << "{" << _clef << "}";
    return ss.str();
}

inline std::ostream& operator<<(std::ostream& os, const AElement& e)
{
    os << static_cast<std::string>(e);
    return os;
}

#endif  // AELEMENT_H