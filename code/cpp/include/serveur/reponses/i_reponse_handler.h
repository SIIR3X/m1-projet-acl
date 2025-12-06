#ifndef I_REPONSE_HANDLER_H
#define I_REPONSE_HANDLER_H

#include <any>
#include <memory>
#include <string>

#include "serveur/reponses/i_reponse.h"

class IReponseHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IReponseHandler() = default;

    void setSuivant(std::shared_ptr<IReponseHandler> suivant)
    {
        _suivant = suivant;
    }

    /**
     * @brief Fonction principale pour tenter de générer une réponse.
     * @param type Type de réponse.
     * @param data Le contenu de la réponse.
     * @return Une isntance de IReponse ou nullptr.
     */
    std::shared_ptr<IReponse> traiter(const std::string& type, const std::any& data);

protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de réponse.
     * @param type Le type de réponse.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutTraiter(const std::string& type) const = 0;

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @param data Le contenu de la réponse.
     * @return Un pointeur partagé var la réponse.
     */
    virtual std::shared_ptr<IReponse> genererReponse(const std::any& data) = 0;

private:
    std::shared_ptr<IReponseHandler> _suivant;  ///< Pointeur partagé vers le prochain handler.
};

inline std::shared_ptr<IReponse> IReponseHandler::traiter(const std::string& type, const std::any& data)
{
    if (peutTraiter(type))
        return genererReponse(data);

    if (_suivant)
        return _suivant->traiter(type, data);

    return nullptr;
}

#endif  // I_REPONSE_HANDLER_H