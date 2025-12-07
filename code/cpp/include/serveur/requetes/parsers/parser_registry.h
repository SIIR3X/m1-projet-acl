#ifndef PARSER_REGISTRY_H
#define PARSER_REGISTRY_H

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @class ParserRegistry
 * @brief Registry générique pour enregistrer dynamiquement des parseurs.
 */
template <typename ParserBase>
class ParserRegistry
{
public:
    /**
     * @brief Enregistre un parseur sous un nom donné.
     * @param nom Nom utilisé dans le champ JSON pour identifier la stratégie.
     * @param parser Instance du parseur.
     */
    static void enregistrerParser(const std::string& nom, std::shared_ptr<ParserBase> parser)
    {
        getMap()[nom] = parser;
    }

    /**
     * @brief Récupère un parseur enregistré à partir de son nom.
     * @param nom Nom utilisé dans la requête.
     * @return Une instance partagée du parseur correspondant.
     * @throws std::runtime_error si le nom n’est pas enregistré.
     */
    static std::shared_ptr<ParserBase> get(const std::string& nom);

private:
    /**
     * @brief Accès interne à la map statique de parseurs.
     * @return Référence vers une map statique associant un nom à un parseur.
     */
    static std::unordered_map<std::string, std::shared_ptr<ParserBase>>& getMap();
};

template <typename ParserBase>
inline std::shared_ptr<ParserBase> ParserRegistry<ParserBase>::get(const std::string& nom)
{
    auto& map = getMap();
    auto it = map.find(nom);

    if (it == map.end())
        throw std::runtime_error("Aucun parseur enregistré sous le nom : " + nom);

    return it->second;
}

template <typename ParserBase>
inline std::unordered_map<std::string, std::shared_ptr<ParserBase>>& ParserRegistry<ParserBase>::getMap()
{
    static std::unordered_map<std::string, std::shared_ptr<ParserBase>> instance;
    return instance;
}

#endif  // PARSER_REGISTRY_H