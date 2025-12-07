#ifndef REQUETE_HANDLER_COR_H
#define REQUETE_HANDLER_COR_H

#include <memory>
#include <optional>
#include <string>

#include "serveur/requetes/handlers/requete_handler.h"

/**
 * @class RequeteHandlerCOR
 * @brief Maillon abstrait de la chaîne de responsabilité.
 */
class RequeteHandlerCOR : public RequeteHandler
{
public:
    /**
     * @brief Constructeur du maillon de la chaîne de responsabilité.
     * @param suivant Le maillon suivant dans la chaîne de responsabilité.
     */
    explicit RequeteHandlerCOR(std::shared_ptr<RequeteHandlerCOR> suivant = nullptr) : _suivant(std::move(suivant)) {}

    /**
     * @brief Tente de traiter la requête.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    std::optional<std::string> traiter(const std::string& commande, const std::string& requete) override;

protected:
    /**
     * @brief Tente de générer une réponse à la requête.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    virtual std::optional<std::string> traiterRequete(const std::string& commande, const std::string& requete) = 0;

private:
    std::shared_ptr<RequeteHandlerCOR> _suivant;  ///< Le maillon suivant de la chaîne de responsabilité.
};

inline std::optional<std::string> RequeteHandlerCOR::traiter(const std::string& commande, const std::string& requete)
{
    // La chaîne tente de traiter la requête localement
    std::optional<std::string> reponse = traiterRequete(commande, requete);

    // La chaîne a réussi
    if (reponse.has_value())
        return reponse;

    // S'il existe un prochain maillon, alors il essaye de traiter la requête
    if (_suivant)
        return _suivant->traiter(commande, requete);

    return std::nullopt;
}

#endif  // REQUETE_HANDLER_COR_H