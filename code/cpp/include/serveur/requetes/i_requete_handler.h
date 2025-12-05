#ifndef I_REQUETE_HANDLER_H
#define I_REQUETE_HANDLER_H

#include <string>

/**
 * @class IRequeteHandler
 * @brief Interface abstraite représentant un gestionnaire de requête.
 */
class IRequeteHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IRequeteHandler() = default;

    /**
     * @brief Traite une requête et renvoie une réponse.
     * @param requete La requête reçue par le serveur.
     * @return Le réponse.
     */
    virtual std::string traiter(const std::string& requete) = 0;
};

#endif  // I_REQUETE_HANDLER_H