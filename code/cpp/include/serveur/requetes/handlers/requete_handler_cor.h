#ifndef REQUETE_HANDLER_COR_H
#define REQUETE_HANDLER_COR_H

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "serveur/requetes/handlers/requete_handler.h"
#include "serveur/requetes/parsers/parser.h"

#include "factories/reponse_handler_factory.h"

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
    std::unique_ptr<Parser> _parseur;

    virtual bool peutTraiter(const std::string& commande) const = 0;

    virtual std::optional<std::vector<std::any>> traiterRequete(const std::string& commande,
                                                                const std::vector<std::any>& argsBruts) = 0;

private:
    std::shared_ptr<RequeteHandlerCOR> _suivant;  ///< Le maillon suivant de la chaîne de responsabilité.
};

inline std::optional<std::string> RequeteHandlerCOR::traiter(const std::string& commande, const std::string& requete)
{
    if (!peutTraiter(commande) || !_parseur)
    {
        if (_suivant)
            return _suivant->traiter(commande, requete);
        return std::nullopt;
    }

    // Extraction des arguments de la requête
    auto argsBruts = _parseur->parser(requete);

    // Transformation des données brutes en données métier
    auto args = traiterRequete(commande, argsBruts);

    auto gestionnaire = ReponseHandlerFactory::chaine();

    return gestionnaire->construire(commande, *args);
}

#endif  // REQUETE_HANDLER_COR_H