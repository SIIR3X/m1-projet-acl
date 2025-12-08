#ifndef REQUETE_HANDLER_FACTORY_H
#define REQUETE_HANDLER_FACTORY_H

#include <memory>

#include "serveur/requetes/handlers/requete_handler.h"
#include "serveur/requetes/handlers/requete_handler_algo_distance.h"

/**
 * @class RequeteHandlerFactory
 * @brief Factory responsable de créer la chaîne de responsabilité des gestionnaires de requêtes.
 */
class RequeteHandlerFactory
{
public:
    /**
     * @brief Retourne la chaîne de handlers de requêtes COR du serveur.
     * @return Un pointeur partagé vers le premier maillon.
     */
    static std::shared_ptr<RequeteHandler> chaine()
    {
        static std::shared_ptr<RequeteHandler> instance = creerChaine();
        return instance;
    }

private:
    /**
     * @brief Construit la chaîne complète des handlers de requêtes.
     * @return Le premier maillon de la chaîne.
     */
    static std::shared_ptr<RequeteHandler> creerChaine();
};

inline std::shared_ptr<RequeteHandler> RequeteHandlerFactory::creerChaine()
{
    // Premier maillon
    auto h1 = std::make_shared<RequeteHandlerAlgoDistance>();

    return h1;
}

#endif  // REQUETE_HANDLER_FACTORY_H