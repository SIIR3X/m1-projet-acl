#ifndef COORD_GEOGRAPHIQUE_H
#define COORD_GEOGRAPHIQUE_H

#include <stdexcept>

/**
 * @struct CoordGeographique
 * @brief Structure contenant une latitude et une longitude (position géographique).
 */
struct CoordGeographique
{
    double _latitude;
    double _longitude;

    /**
     * @brief Constructeur par défaut.
     */
    CoordGeographique() : CoordGeographique(0.0, 0.0) {}

    /**
     * @brief Constructeur principal.
     * @param latitude La latitude en degrés.
     * @param longitude La longitude en degrés.
     */
    CoordGeographique(double latitude, double longitude) : _latitude(latitude), _longitude(longitude)
    {
        if (!latitudeEstValide(latitude))
            throw std::out_of_range("Latitude invalide : doit être dans [-90, 90].");

        if (!longitudeEstValide(longitude))
            throw std::out_of_range("Longitude invalide : doit être dans [-180, 180].");
    }

    /**
     * @brief Vérifie que la latitude est dans les bornes acceptables.
     * @param latitude La latitude en degrés.
     * @return true si la latitude est valide, false sinon.
     */
    static bool latitudeEstValide(double latitude)
    {
        return latitude >= -90.0 && latitude <= 90.0;
    }

    /**
     * @brief Vérifie que la longitude est dans les bornes acceptables.
     * @param longitude La longitude en degrés.
     * @return true si la longitude est valide, false sinon.
     */
    static bool longitudeEstValide(double longitude)
    {
        return longitude >= -180.0 && longitude <= 180.0;
    }
};

#endif  // COORD_GEOGRAPHIQUE_H