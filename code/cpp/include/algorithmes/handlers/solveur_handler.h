#ifndef SOLVEUR_HANDLER_H
#define SOLVEUR_HANDLER_H

#include <any>
#include <string>

/**
 * @class SolveurHandler
 * @brief Interface générale d'un gestionnaire capable de construire un solveur.
 */
class SolveurHandler
{
public:
    /**
     * @brief Destructeur.
     */
    virtual ~SolveurHandler() = default;

    /**
     * @brief Tente de résoudre les données via l'algorithme demandé.
     * @param nomAlgo Le nom de l'algorithme demandé.
     * @param donnees Les données sur lesquelles exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    virtual std::any resoudre(const std::string& nomAlgo, const std::any& donnees) = 0;
};

#endif  // SOLVEUR_HANDLER_H