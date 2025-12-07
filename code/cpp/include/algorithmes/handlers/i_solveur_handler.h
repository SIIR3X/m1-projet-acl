#ifndef I_SOLVEUR_HANDLER_H
#define I_SOLVEUR_HANDLER_H

#include <any>
#include <memory>

/**
 * @class ISolveurHandler
 * @brief Interface abstraite représentant un maillon de la chaîne de gestion des solveurs.
 */
class ISolveurHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~ISolveurHandler() = default;

    /**
     * @brief Définit le prochain maillon dans la chaîne de responsabilité.
     * @param suivant Le prochain handler.
     */
    void setSuivant(std::shared_ptr<ISolveurHandler> suivant)
    {
        _suivant = suivant;
    }

    /**
     * @brief Tente de résoudre un algorithme de distance.
     * @param nomAlgo Le nom de l'algorithme demandé.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    std::any resoudre(const std::string& nomAlgo, const std::any& donnes);

protected:
    /**
     * @brief Indique si ce solveur peut traiter l'algorithme demandé.
     * @param nomAlgo L'algorithme demandé.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutResoudre(const std::string& nomAlgo) const = 0;

    /**
     * @brief Exécute l'algorithme.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    virtual std::any executer(const std::any& donnees) = 0;

private:
    std::shared_ptr<ISolveurHandler> _suivant;
};

inline std::any ISolveurHandler::resoudre(const std::string& nomAlgo, const std::any& donnees)
{
    if (peutResoudre(nomAlgo))
        return executer(donnees);

    if (_suivant)
        return _suivant->resoudre(nomAlgo, donnees);

    return std::any{};
}

#endif  // I_SOLVEUR_HANDLER_H