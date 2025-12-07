#ifndef COMMANDE_TYPE_H
#define COMMANDE_TYPE_H

#include <string>
#include <unordered_map>

/**
 * @class CommandeType
 * @brief Représente les différents types de commandes pouvant être envoyées dans les requêtes.
 */
enum class CommandeType
{
    ALGO_DISTANCE,
    INCONNU
};

/**
 * @brief Convertit une chaîne de caractères JSON en CommandeType.
 * @param str La chaîne extraite du JSON.
 * @return Le CommandeType associé.
 */
inline CommandeType commandeFromString(const std::string& str)
{
    static const std::unordered_map<std::string, CommandeType> map = {{"algo_distance", CommandeType::ALGO_DISTANCE}};

    auto iterateur = map.find(str);
    if (iterateur != map.end())
        return iterateur->second;

    return CommandeType::INCONNU;
}

/**
 * @brief Convertit un CommandeType vers sa représentation textuelle.
 * @param c Le CommandeType.
 * @return Sa représentation textuelle.
 */
inline std::string commandeToString(CommandeType c)
{
    switch (c)
    {
        case CommandeType::ALGO_DISTANCE:
            return "algo_distance";
        default:
            return "inconnu";
    }
}

#endif  // COMMANDE_TYPE_H