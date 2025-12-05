#ifndef REQUETE_HANDLER_FACTORY_H
#define REQUETE_HANDLER_FACTORY_H

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "serveur/requetes/i_requete_handler.h"

/**
 * @class RequeteHandleFactory
 * @brief Fabrique de gestionnaires de requêtes.
 */
class RequeteHandlerFactory
{
public:
    /**
     * @brief Type fonctionnel pour créer dynamiquement un gestionnaire.
     */
    using CreateFunc = std::function<std::unique_ptr<IRequeteHandler>()>;

    /**
     * @brief Renvoie un gestionnaire correspondant au type demandé.
     * @param type Type de requête.
     * @return Le bon handler.
     */
    static std::unique_ptr<IRequeteHandler> creerHandler(const std::string& type);

    /**
     * @brief Enregistre un créateur de gestionnaire dans la factory.
     * @param type Type de requête.
     * @param func Fonction capable de créer une instance du handler.
     */
    static void enregistrerHandler(const std::string& type, CreateFunc func);

private:
    /**
     * @brief Registre internet associant un type de requête à une fonction de création du handler.
     */
    static std::unordered_map<std::string, CreateFunc>& obtenirRegistre();
};

inline std::unique_ptr<IRequeteHandler> RequeteHandlerFactory::creerHandler(const std::string& type)
{
    auto& registre = obtenirRegistre();

    auto iterator = registre.find(type);
    if (iterator == registre.end())
    {
        throw std::runtime_error("Aucun handler enregistré pour le type : " + type);
    }

    return iterator->second();
}

inline void RequeteHandlerFactory::enregistrerHandler(const std::string& type, CreateFunc func)
{
    obtenirRegistre()[type] = func;
}

inline std::unordered_map<std::string, RequeteHandlerFactory::CreateFunc>& RequeteHandlerFactory::obtenirRegistre()
{
    static std::unordered_map<std::string, CreateFunc> registre;
    return registre;
}

#endif  // REQUETE_HANDLER_FACTORY_H