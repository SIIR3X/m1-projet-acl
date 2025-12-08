#ifndef REPONSE_HANDLER_H
#define REPONSE_HANDLER_H

#include <any>
#include <optional>
#include <string>
#include <vector>

/**
 * @class ReponseHandler
 * @brief Interface générale d'un gestionnaire capable de construire une réponse.
 */
class ReponseHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~ReponseHandler() = default;

    /**
     * @brief Tente de construire la réponse.
     * @param commande La commande demandée.
     * @param args Les arguments passés au handler.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    virtual std::optional<std::string> construire(const std::string& commande, const std::vector<std::any>& args) = 0;
};

#endif  // REPONSE_HANDLER_H