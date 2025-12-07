#ifndef REPONSE_HANDLER_FACTORY_H
#define REPONSE_HANDLER_FACTORY_H

#include <memory>

#include "serveur/reponses/handlers/reponse_handler.h"
#include "serveur/reponses/handlers/reponse_handler_algo_distance.h"

/**
 * @class ReponseHandlerFactory
 * @brief Factory responsable de créer la chaîne de responsabilité des gestionnaires de réponses.
 */
class ReponseHandlerFactory
{
public:
    /**
     * @brief Retourne la chaîne de handlers de réponses COR du serveur.
     * @return Un pointeur partagé vers le premier maillon.
     */
    static std::shared_ptr<ReponseHandler> chaine()
    {
        static std::shared_ptr<ReponseHandler> instance = creerChaine();
        return instance;
    }

private:
    /**
     * @brief Construit la chaîne complète des handlers de réponses.
     * @return Le premier maillon de la chaîne.
     */
    static std::shared_ptr<ReponseHandler> creerChaine();
};

inline std::shared_ptr<ReponseHandler> ReponseHandlerFactory::creerChaine()
{
    // Premier maillon
    auto h1 = std::make_shared<ReponseHandlerAlgoDistance>();

    return h1;
}

#endif  // REPONSE_HANDLER_FACTORY_H