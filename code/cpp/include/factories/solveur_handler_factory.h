#ifndef SOLVEUR_HANDLER_FACTORY_H
#define SOLVEUR_HANDLER_FACTORY_H

#include <memory>

#include "algorithmes/handlers/solveur_handler.h"
#include "algorithmes/handlers/solveur_handler_tsp.h"

/**
 * @class SolveurHandlerFactory
 * @brief Factory responsable de créer la chaîne de responsabilité des solveurs.
 */
class SolveurHandlerFactory
{
public:
    /**
     * @brief Retourne la chaîne de handlers de solveurs COR du serveur.
     * @return Un pointeur partagé vers le premier maillon.
     */
    static std::shared_ptr<SolveurHandler> chaine()
    {
        static std::shared_ptr<SolveurHandler> instance = creerChaine();
        return instance;
    }

private:
    /**
     * @brief Construit la chaîne complète des handlers de solveurs.
     * @return Le premier maillon de la chaîne.
     */
    static std::shared_ptr<SolveurHandler> creerChaine();
};

inline std::shared_ptr<SolveurHandler> SolveurHandlerFactory::creerChaine()
{
    // Premier maillon
    auto h1 = std::make_shared<SolveurHandlerTSP>();

    return h1;
}

#endif  // SOLVEUR_HANDLER_FACTORY_H