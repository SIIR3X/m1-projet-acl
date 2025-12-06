#ifndef ALGO_TYPE_H
#define ALGO_TYPE_H

#include <string>
#include <unordered_map>

/**
 * @enum AlgoType
 * @brief Représente les différents types d'algorithme pouvant être utilisés.
 */
enum class AlgoType
{
    TSP,
    INCONNU
};

/**
 * @brief Convertit une chaîne de caractères JSON en AlgoType.
 * @param str La chaîne extraite du JSON.
 * @return Le AlgoType associé.
 */
inline AlgoType algoFromString(const std::string& str)
{
    static const std::unordered_map<std::string, AlgoType> map = {{"tsp", AlgoType::TSP}};

    auto iterateur = map.find(str);
    if (iterateur != map.end())
        return iterateur->second;

    return AlgoType::INCONNU;
}

/**
 * @brief Convertit un AlgoType vers sa représentation textuelle.
 * @param c Le AlgoType.
 * @return Sa représentation textuelle.
 */
inline std::string algoToString(AlgoType algo)
{
    switch (algo)
    {
        case AlgoType::TSP:
            return "tsp";
        default:
            return "inconnu";
    }
}

#endif  // ALGO_TYPE_H