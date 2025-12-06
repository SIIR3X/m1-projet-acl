#ifndef I_REPONSE_HANDLER_H
#define I_REPONSE_HANDLER_H

#include <any>
#include <memory>
#include <string>

#include "serveur/reponses/i_reponse.h"

/**
 * @class IReponseHandler
 * @brief Interface abstraite représentant un maillon de la chaîne de gestion des réponses.
 */
class IReponseHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IReponseHandler() = default;

    /**
     * @brief Définit le prochain maillon dans la chaîne de responsabilité.
     * @param suivant Le prochain handler.
     */
    void setSuivant(std::shared_ptr<IReponseHandler> suivant)
    {
        _suivant = suivant;
    }

    /**
     * @brief Fonction principale pour tenter de générer une réponse.
     * @param commande La commande demandée.
     * @param data Le contenu de la réponse.
     * @return Une instance de IReponse ou nullptr.
     */
    std::shared_ptr<IReponse> traiter(const std::string& typeRequete, const std::any& data);

protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de réponse.
     * @param commande La commande demandée.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutTraiter(const std::string& commande) const = 0;

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @param data Le contenu de la réponse.
     * @return Un pointeur partagé var la réponse.
     */
    virtual std::shared_ptr<IReponse> genererReponse(const std::any& data) = 0;

private:
    std::shared_ptr<IReponseHandler> _suivant;  ///< Pointeur partagé vers le prochain handler.
};

inline std::shared_ptr<IReponse> IReponseHandler::traiter(const std::string& commande, const std::any& data)
{
    if (peutTraiter(commande))
        return genererReponse(data);

    if (_suivant)
        return _suivant->traiter(commande, data);

    return nullptr;
}

#endif  // I_REPONSE_HANDLER_H