#ifndef I_REPONSE_H
#define I_REPONSE_H

#include <memory>
#include <string>
#include <vector>

#include "utils/json_builder.h"

/**
 * @class IReponse
 * @brief Interface représentant une réponse JSON renvoyée au client.
 */
class IReponse
{
public:
    /**
     * @brief Constructeur pour réponse simple.
     */
    IReponse() = default;

    /**
     * @brief Constructeur pour réponse multiple.
     * @param enfants Les réponses enfants.
     */
    IReponse(std::vector<std::shared_ptr<IReponse>> enfants) : _enfants(std::move(enfants)) {}

    /**
     * @brief Destructeur.
     */
    virtual ~IReponse() = default;

    /**
     * @brief Génère le JSON complet de la réponse.
     * @return La réponse en JSON.
     */
    std::string toJson() const;

protected:
    /**
     * @brief Construit le JSON d'une réponse simple.
     * @return La réponse en JSON.
     */
    virtual std::string toJsonSeul() const = 0;

private:
    std::vector<std::shared_ptr<IReponse>> _enfants;  ///< Réponses enfants en cas de réponse composée.
};

inline std::string IReponse::toJson() const
{
    JsonBuilder jb;

    jb.beginArray("reponse");

    if (_enfants.empty())
        jb.addRawValue(toJsonSeul());
    else
        for (auto& enfant : _enfants) jb.addRawValue(enfant->toJson());

    jb.endArray();

    return jb.build();
}

#endif  // I_REPONSE_H