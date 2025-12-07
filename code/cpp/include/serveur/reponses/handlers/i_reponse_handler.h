#ifndef I_REPONSE_HANDLER_H
#define I_REPONSE_HANDLER_H

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "serveur/reponses/types/i_reponse.h"

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
     * @tparam Args Types des objets reçus.
     * @param args Objets passés au handler.
     * @return Une instance de IReponse ou nullptr.
     */
    template <typename... Args>
    std::shared_ptr<IReponse> traiter(const std::string& commande, Args&&... args)
    {
        std::vector<std::any> packed = {std::forward<Args>(args)...};
        return traiterImplementation(commande, packed);
    }

protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de réponse.
     * @param commande La commande demandée.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutTraiter(const std::string& commande) const = 0;

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @tparam Args Types des objets reçus.
     * @param args Objets passés au handler.
     * @return Un pointeur partagé var la réponse.
     */
    virtual std::shared_ptr<IReponse> genererReponse(const std::vector<std::any>& args) = 0;

private:
    std::shared_ptr<IReponseHandler> _suivant;  ///< Pointeur partagé vers le prochain handler.

    /**
     * @brief Implémentation concrète de la méthode de traitement.
     * @param commande La commande demandée.
     * @tparam Args Types des objets reçus.
     * @param args Objets passés au handler.
     * @return Une instance de IReponse ou nullptr.
     */
    std::shared_ptr<IReponse> traiterImplementation(const std::string& commande, const std::vector<std::any>& args);
};

inline std::shared_ptr<IReponse> IReponseHandler::traiterImplementation(const std::string& commande,
                                                                        const std::vector<std::any>& args)
{
    if (peutTraiter(commande))
        return genererReponse(args);

    if (_suivant)
        return _suivant->traiterImplementation(commande, args);

    return nullptr;
}

#endif  // I_REPONSE_HANDLER_H