#ifndef REPONSE_HANDLER_COR_H
#define REPONSE_HANDLER_COR_H

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "serveur/reponses/handlers/reponse_handler.h"

/**
 * @class ReponseHandlerCOR
 * @brief Maillon abstrait de la chaîne de responsabilité.
 */
class ReponseHandlerCOR : public ReponseHandler
{
public:
    /**
     * @brief Constructeur du maillon de la chaîne de responsabilité.
     * @param suivant Le maillon suivant dans la chaîne de responsabilité.
     */
    explicit ReponseHandlerCOR(std::shared_ptr<ReponseHandlerCOR> suivant = nullptr) : _suivant(std::move(suivant)) {}

    /**
     * @brief Tente de construire la réponse.
     * @param commande La commande demandée.
     * @param args Les arguments passés au handler.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    std::optional<std::string> construire(const std::string& commande, const std::vector<std::any>& args) override;

protected:
    /**
     * @brief Tente de construire une réponse à la requête.
     * @param commande La commande demandée.
     * @param args Les arguments passés au handler.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    virtual std::optional<std::string> construireReponse(const std::string& commande,
                                                         const std::vector<std::any>& args) = 0;

private:
    std::shared_ptr<ReponseHandlerCOR> _suivant;  ///< Le maillon suivant de la chaîne de responsabilité.
};

inline std::optional<std::string> ReponseHandlerCOR::construire(const std::string& commande,
                                                                const std::vector<std::any>& args)
{
    // La chaîne tente de construire la réponse localement
    std::optional<std::string> reponse = construireReponse(commande, args);

    // La chaîne a réussi
    if (reponse.has_value())
        return reponse;

    // S'il existe un prochain maillon, alors il essaye de construire la réponse
    if (_suivant)
        return _suivant->construire(commande, args);

    return std::nullopt;
}

#endif  // REPONSE_HANDLER_COR_H