#ifndef I_REPONSE_H
#define I_REPONSE_H

#include <string>

/**
 * @class IReponse
 * @brief Interface représentant une réponse JSON renvoyée au client.
 */
class IReponse
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IReponse() = default;

    /**
     * @brief Construit la réponse.
     * @return La réponse sous forme d'une chaîne.
     */
    virtual std::string toJson() const = 0;
};

#endif  // I_REPONSE_H