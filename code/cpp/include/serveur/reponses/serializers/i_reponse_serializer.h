#ifndef I_REPONSE_SERIALIZER_H
#define I_REPONSE_SERIALIZER_H

#include <any>
#include <string>

/**
 * @class IReponseSerializer
 * @brief Interface générique pour les sérialiseurs de réponses.
 */
class IReponseSerializer
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~IReponseSerializer() = default;

    /**
     * @brief Sérialise des données brutes en un format exploitable par un handler.
     * @param data Résultat brut.
     * @return Un std::any contenant les données sérialisées.
     */
    virtual std::any serialize(const std::any& data) const = 0;
};

#endif  // I_REPONSE_SERIALIZER_H