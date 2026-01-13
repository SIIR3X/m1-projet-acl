#ifndef REQUETE_HANDLER_H
#define REQUETE_HANDLER_H

#include <optional>
#include <string>

/**
 * @class RequeteHandler
 * @brief Interface générale d'un gestionnaire capable de traiter une requête.
 */
class RequeteHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~RequeteHandler() = default;

    /**
     * @brief Tente de traiter la requête.
     * @param commande La commande demandée.
     * @param requete La requête au format JSON.
     * @return Une réponse JSON ou std::nullopt si non traité.
     */
    virtual std::optional<std::string> traiter(const std::string& commande, const std::string& requete) = 0;
};

#endif  // REQUETE_HANDLER_H