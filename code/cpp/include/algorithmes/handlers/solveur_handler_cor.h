#ifndef SOLVEUR_HANDLER_COR_H
#define SOLVEUR_HANDLER_COR_H

#include <any>
#include <memory>
#include <string>

#include "algorithmes/handlers/solveur_handler.h"

/**
 * @class SolveurHandlerCOR
 * @brief Maillon abstrait de la chaîne de responsabilité.
 */
class SolveurHandlerCOR : public SolveurHandler
{
public:
    /**
     * @brief Constructeur du maillon de la chaîne de responsabilité.
     * @param suivant Le maillon suivant dans la chaîne de responsabilité.
     */
    explicit SolveurHandlerCOR(std::shared_ptr<SolveurHandlerCOR> suivant = nullptr) : _suivant(std::move(suivant)) {}

    /**
     * @brief Tente de résoudre les données via l'algorithme demandé.
     * @param nomAlgo Le nom de l'algorithme demandé.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    std::any resoudre(const std::string& nomAlgo, const std::any& donnees) override;

protected:
    /**
     * @brief Tente de résoudre les données via l'algorithme demandé.
     * @param nomAlgo Le nom de l'algorithme demandé.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    virtual std::any resoudreDonnees(const std::string& nomAlgo, const std::any& donnees) = 0;

private:
    std::shared_ptr<SolveurHandlerCOR> _suivant;  ///< Le maillon suivant de la chaîne de responsabilité.
};

inline std::any SolveurHandlerCOR::resoudre(const std::string& nomAlgo, const std::any& donnees)
{
    // La chaîne tente de résoudre localement
    std::any solution = resoudreDonnees(nomAlgo, donnees);

    // La chaîne a réussi
    if (solution.has_value())
        return solution;

    // S'il existe un prochain maillon, alors il essaye de résoudre
    if (_suivant)
        return _suivant->resoudre(nomAlgo, donnees);

    return std::any{};
}

#endif  // SOLVEUR_HANDLER_COR_H