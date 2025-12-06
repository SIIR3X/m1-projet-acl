#ifndef TSP_SOLVEUR_HANDLER_H
#define TSP_SOLVEUR_HANDLER_H

#include "algorithmes/distance/algo_distance_data_builder.h"
#include "algorithmes/gestionnaires/i_solveur_handler.h"
#include "modele/graphe/graphe.h"
#include "types/algo_type.h"

/**
 * @class TspSolveurHandler
 * @brief @brief Gestionnaire pour les algorithmes de type "tsp".
 */
template <typename S, typename T>
class TspSolveurHandler : public ISolveurHandler<S, T>
{
protected:
    /**
     * @brief Indique si ce solveur peut traiter l'algorithme demandé.
     * @param nomAlgo L'algorithme demandé.
     * @return true s'il peut traiter, false sinon.
     */
    virtual bool peutResoudre(const std::string& nomAlgo) const override
    {
        return algoFromString(nomAlgo) == AlgoType::TSP;
    }

    /**
     * @brief Exécute l'algorithme.
     * @param graphe Le graphe sur lequel exécuter l'algorithme.
     * @return Le résultat de l'algorithme sous forme d'un std::any.
     */
    virtual std::any executer(const Graphe<S, T>& graphe) override;
};

template <typename S, typename T>
inline std::any TspSolveurHandler<S, T>::executer(const Graphe<S, T>& graphe)
{
    // Construction des données à partir du graphe
    AlgoDistanceData data = AlgoDistanceDataBuilder::construireData(graphe);

    // TODO : Exécuter l'algorithme
    // AlgoDistanceData resultat =

    // return std::any{resultat};
    return std::any{};
}

#endif  // TSP_SOLVEUR_HANDLER_H