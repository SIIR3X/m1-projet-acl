#ifndef I_REQUETE_HANDLER_H
#define I_REQUETE_HANDLER_H

#include <memory>
#include <string>

/**
 * @class IRequeteHandler
 * @brief Interface abstraite représentant un maillon de la chaîne de gestion des requêtes.
 */
class IRequeteHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IRequeteHandler() = default;

    /**
     * @brief Définit le prochain maillon dans la chaîne de responsabilité.
     * @param suivant Le prochain handler.
     */
    void setSuivant(std::shared_ptr<IRequeteHandler> suivant)
    {
        _suivant = suivant;
    }

    /**
     * @brief Fonction principale pour tenter de gérer une requête.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return La réponse en format JSON.
     */
    std::string traiter(const std::string& commande, const std::string& requete);

protected:
    /**
     * @brief Indique si ce handler peut traiter ce type de requête.
     * @param commande La commande demandée.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutTraiter(const std::string& commande) const = 0;

    /**
     * @brief Génère la réponse correspondant à ce handler.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return La réponse au format JSON.
     */
    virtual std::string genererReponse(const std::string& commande, const std::string& requete) = 0;

private:
    std::shared_ptr<IRequeteHandler> _suivant;
};

inline std::string IRequeteHandler::traiter(const std::string& commande, const std::string& requete)
{
    if (peutTraiter(commande))
        return genererReponse(commande, requete);

    if (_suivant)
        return _suivant->traiter(commande, requete);

    return "null";
}

#endif  // I_REQUETE_HANDLER_H