#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <cstdlib>
#include <iostream>
#include <string>

#define ERREUR(func, msg, stop) DebugUtils::erreur(func, msg, stop)

/**
 * @class DebugUtils
 * @brief Fournit des fonctions de debug.
 */
class DebugUtils
{
public:
    /**
     * @brief Fonction permettant d'afficher un message d'erreur.
     * @param nomFonction Le nom de la fonction dans lequel se produit l'erreur.
     * @param message Le message à afficher.
     * @param arreterProgramme Un boolean permettant de savoir s'il faut arrêter le programme.
     */
    static void erreur(const std::string& nomFonction, const std::string& message, bool arreterProgramme);
};

inline void DebugUtils::erreur(const std::string& nomFonction, const std::string& message, bool arreterProgramme)
{
    std::cerr << "[ERREUR] (" << nomFonction << ") : " << message << std::endl;

    if (arreterProgramme)
    {
        std::cerr << ">>> Arrêt du programme demandé." << std::endl;
        exit(EXIT_FAILURE);
    }
}

#endif  // DEBUG_UTILS_H