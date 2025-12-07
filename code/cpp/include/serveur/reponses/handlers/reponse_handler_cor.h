#ifndef REPONSE_HANDLER_COR_H
#define REPONSE_HANDLER_COR_H

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "serveur/reponses/handlers/reponse_handler.h"
#include "serveur/reponses/types/i_reponse.h"

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
     * @return Une instance de IReponse ou nullptr.
     */
    std::shared_ptr<IReponse> construire(const std::string& commande, const std::vector<std::any>& args) override;

protected:
    /**
     * @brief Tente de construire une réponse à la requête.
     * @param commande La commande demandée.
     * @param args Les arguments passés au handler.
     * @return Une instance de IReponse ou nullptr.
     */
    virtual std::shared_ptr<IReponse> construireReponse(const std::string& commande,
                                                        const std::vector<std::any>& args) = 0;

private:
    std::shared_ptr<ReponseHandlerCOR> _suivant;  ///< Le maillon suivant de la chaîne de responsabilité.
};

inline std::shared_ptr<IReponse> ReponseHandlerCOR::construire(const std::string& commande,
                                                               const std::vector<std::any>& args)
{
    // La chaîne tente de construire la réponse localement
    std::shared_ptr<IReponse> reponse = construireReponse(commande, args);

    // La chaîne a réussi
    if (reponse)
        return reponse;

    // S'il existe un prochain maillon, alors il essaye de construire la réponse
    if (_suivant)
        return _suivant->construire(commande, args);

    return nullptr;
}

#endif  // REPONSE_HANDLER_COR_H