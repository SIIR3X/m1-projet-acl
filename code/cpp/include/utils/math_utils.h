#ifndef MATH_UTILS_H
#define MATH_UTILS_H

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

private:
    static constexpr double DEG_TO_RAD =
        0.017453292519943295;  ///< Facteur de conversion degrés vers radians (PI / 180)
};

inline double MathUtils::toRad(double degree)
{
    return degree * DEG_TO_RAD;
}

#endif  // MATH_UTILS_H