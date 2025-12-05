#ifndef TSP_REQUETE_HANDLER_H
#define TSP_REQUETE_HANDLER_H

#include "serveur/requetes/i_requete_handler.h"

class TSPRequeteHandler : public IRequeteHandler
{
public:
    /**
     * @brief Constructeur par défaut.
     */
    TSPRequeteHandler() = default;

    /**
     * @brief Destructeur.
     */
    virtual ~TSPRequeteHandler() = default;

    /**
     * @brief Traite une requête et renvoie une réponse.
     * @param requete La requête reçue par le serveur.
     * @return Le réponse.
     */
    std::string traiter(const std::string& requete) override;
};

#endif  // TSP_REQUETE_HANDLER_H