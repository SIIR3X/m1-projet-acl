#ifndef VILLE_H
#define VILLE_H

#include <ostream>
#include <stdexcept>
#include <string>

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
    Ville(const std::string& nom, double latitude, double longitude);

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
        return _latitude;
    }

    /**
     * @brief Getter pour la longitude de la ville.
     * @return La longitude en degrés.
     */
    double longitude() const
    {
        return _longitude;
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
    std::string _nom;         ///< Nom de la ville.
    double _latitude = 0.0;   ///< Latitude en degrés.
    double _longitude = 0.0;  ///< Longitude en degrés.
};

inline Ville::Ville(const std::string& nom, double latitude, double longitude)
    : _nom(nom), _latitude(latitude), _longitude(longitude)
{
    if (latitude < -90.0 || latitude > 90.0)
        throw std::out_of_range("Latitude invalide : doit être dans [-90, 90].");

    if (longitude < -180.0 || longitude > 180.0)
        throw std::out_of_range("Longitude invalide : doit être dans [-180, 180].");
}

inline bool Ville::operator==(const Ville& other) const
{
    return _nom == other._nom && _latitude == other._latitude && _longitude == other._longitude;
}

inline bool Ville::operator!=(const Ville& other) const
{
    return !(*this == other);
}

inline Ville::operator std::string() const
{
    return _nom + " (" + std::to_string(_latitude) + ", " + std::to_string(_longitude) + ")";
}

inline std::ostream& operator<<(std::ostream& os, const Ville& v)
{
    os << static_cast<std::string>(v);
    return os;
}

#endif  // VILLE_H