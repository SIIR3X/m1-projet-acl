#ifndef REPONSE_HANDLER_FACTORY_H
#define REPONSE_HANDLER_FACTORY_H

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "serveur/reponses/handlers/algo_distance_reponse_handler.h"
#include "serveur/reponses/handlers/i_reponse_handler.h"

/**
 * @class ReponseHandlerFactory
 * @brief Fabrique de gestionnaires de réponses.
 */
class ReponseHandlerFactory
{
public:
    /**
     * @brief Type fonctionnel pour créer dynamiquement un gestionnaire de réponse.
     */
    using CreateFunc = std::function<std::shared_ptr<IReponseHandler>()>;

    /**
     * @brief Crée la chaîne de responsabilité des handlers de réponse.
     * @return Le premir handler de la chaîne COR.
     */
    static std::shared_ptr<IReponseHandler> creer();

    /**
     * @brief Renvoie un gestionnaire correspondant au type demandé.
     * @param type Type de réponse (ex : "TSP").
     * @return Le bon handler.
     */
    static std::shared_ptr<IReponseHandler> creerHandler(const std::string& type);

    /**
     * @brief Enregistre un créateur de gestionnaire dans la factory.
     * @param type Type de réponse.
     * @param func Fonction permettant de créer une instance du handler.
     */
    static void enregistrerHandler(const std::string& type, CreateFunc func);

private:
    /**
     * @brief Registre associant un type de réponse à une fonction créatrice.
     */
    static std::unordered_map<std::string, CreateFunc>& obtenirRegistre();
};

inline std::shared_ptr<IReponseHandler> ReponseHandlerFactory::creer()
{
    // Création d'une instance (singleton créer au premier appel)
    static std::shared_ptr<IReponseHandler> instance = []
    {
        // Création des handlers
        auto h1 = std::make_shared<AlgoDistanceReponseHandler>();

        // Retourne la tête de la chaîne
        return h1;
    }();

    return instance;
}

inline std::shared_ptr<IReponseHandler> ReponseHandlerFactory::creerHandler(const std::string& type)
{
    auto& registre = obtenirRegistre();

    auto it = registre.find(type);
    if (it == registre.end())
    {
        throw std::runtime_error("Aucun handler de réponse enregistré pour le type : " + type);
    }

    return it->second();
}

inline void ReponseHandlerFactory::enregistrerHandler(const std::string& type, CreateFunc func)
{
    obtenirRegistre()[type] = func;
}

inline std::unordered_map<std::string, ReponseHandlerFactory::CreateFunc>& ReponseHandlerFactory::obtenirRegistre()
{
    static std::unordered_map<std::string, CreateFunc> registre;
    return registre;
}

#endif  // REPONSE_HANDLER_FACTORY_H