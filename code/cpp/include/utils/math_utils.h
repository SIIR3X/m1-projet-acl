#ifndef MATH_UTILS
#define MATH_UTILS

#include <cmath>

/**
 * @class MathUtils
 * @brief Fournit des fonctions utilitaires mathématiques.
 */
class MathUtils
{
public:
    /**
     * @brief Convertit des degrés en radians.
     * @param degree Valeur en degrés.
     * @return Valeur correspondante en radians.
     */
    static double toRad(double degree);

    /**
     * @brief Applique la formule de Haversine pour calculer la distance angulaire entre deux points sur une sphère.
     * @param lat1 Latitude du point 1 en radians.
     * @param lon1 Longitude du point 1 en radians.
     * @param lat2 Latitude du point 2 en radians.
     * @param lon2 Longitude du point 2 en radians.
     * @return Distance en kilomètres.
     */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

private:
    static constexpr double EARTH_RADIUS_KM = 6371.0;  ///< Rayon moyen de la Terre en kilomètres.
    static constexpr double DEG_TO_RAD =
        0.017453292519943295;  ///< Facteur de conversion degrés vers radians (PI / 180)
};

inline double MathUtils::toRad(double degree)
{
    return degree * DEG_TO_RAD;
}

#endif  // MATH_UTILS