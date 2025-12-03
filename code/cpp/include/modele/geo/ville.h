#ifndef VILLE_H
#define VILLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "modele/geo/coordonne/coord_geo.h"

/**
 * @class Ville
 * @brief Représente une ville géographique définie par un nom, une latitude et une longitude.
 */
class Ville
{
public:
    /**
     * @brief Constructeur par défaut.
     *
     * Initialise une ville vide (sans nom) avec latitude et longitude à 0.0.
     */
    Ville() = default;

    /**
     * @brief Constructeur principal.
     * @param nom Nom de la ville.
     * @param latitude Latitude de la ville (en degrés).
     * @param longitude Longitude de la ville (en degrés).
     */
    Ville(const std::string& nom, double latitude, double longitude) : _nom(nom), _coord(latitude, longitude) {}

    /**
     * @brief Constructeur alternatif pour construction à partir de coordonnées géographiques.
     * @param nom Nom de la ville.
     * @param coord Les coordonnées.
     */
    Ville(const std::string& nom, const CoordGeo& coord) : _nom(nom), _coord(coord) {}

    /**
     * @brief Getter pour le nom de la ville.
     * @return Référence constante vers le nom.
     */
    const std::string& nom() const
    {
        return _nom;
    }

    /**
     * @brief Getter pour la latitude de la ville.
     * @return La latitude en degrés.
     */
    double latitude() const
    {
        return _coord._latitude;
    }

    /**
     * @brief Getter pour la longitude de la ville.
     * @return La longitude en degrés.
     */
    double longitude() const
    {
        return _coord._longitude;
    }

    /**
     * @brief Getter pour les coordonnées de la ville.
     * @return Les coordonnées en degrés.
     */
    const CoordGeo& coordonnees() const
    {
        return _coord;
    }

    /**
     * @brief Opérateur pour vérifier l'égalité entre deux villes.
     * @param other Ville à comparer.
     * @return true si les deux villes sont égales, false sinon.
     */
    bool operator==(const Ville& other) const;

    /**
     * @brief Opérateur pour vérifier l'inégalité entre deux villes.
     * @param other Ville à comparer.
     * @return true si les deux villes sont différentes, true sinon.
     */
    bool operator!=(const Ville& other) const;

    /**
     * @brief Conversion implicite vers une chaîne de caractères.
     * @return Une chaine de caractère représentant la ville sous forme "Nom (lat, lon)".
     */
    operator std::string() const;

    /**
     * @brief Opérateur d'insertion dans un flux.
     * @param os Flux de sortie.
     * @param v Ville à afficher.
     * @return Le flux après insertion.
     */
    friend std::ostream& operator<<(std::ostream& os, const Ville& v);

private:
    std::string _nom;  ///< Nom de la ville.
    CoordGeo _coord;   ///< Coordonnées géographiques de la ville (latitude/longitude en degrés).
};

inline bool Ville::operator==(const Ville& other) const
{
    return _nom == other._nom && _coord._latitude == other._coord._latitude &&
           _coord._longitude == other._coord._longitude;
}

inline bool Ville::operator!=(const Ville& other) const
{
    return !(*this == other);
}

inline Ville::operator std::string() const
{
    return _nom + " (" + std::to_string(_coord._latitude) + ", " + std::to_string(_coord._longitude) + ")";
}

inline std::ostream& operator<<(std::ostream& os, const Ville& v)
{
    os << static_cast<std::string>(v);
    return os;
}

#endif  // VILLE_H