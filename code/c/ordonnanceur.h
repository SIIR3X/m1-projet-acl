#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

#include "types_communs.h"
#include <stdint.h>

/**
 * @brief Structure représentant une tâche (Ville).
 */
typedef struct
{
  identifiant_t id_tache; // ID original (index JSON)
  duree_t p_i;            // Durée opératoire (Temps de livraison)
  duree_t q_i;            // Latence (Temps de retour/transport)
  duree_t date_fin_C_i;   // Date de fin calculée
} Tache_t;

/**
 * @brief Structure représentant une machine (Camion).
 */
typedef struct
{
  uint32_t id_machine;       // 1, 2, 3...
  Tache_t *taches_assignees; // Tableau dynamique
  uint32_t nb_taches;
  uint32_t capacite;  // Pour realloc
  duree_t date_dispo; // Date où la machine devient libre
} Machine_t;

/**
 * @brief Structure globale de la solution.
 */
typedef struct
{
  Machine_t *machines;
  uint32_t nb_machines;

  // Pour l'algo : liste temporaire des tâches à ordonnancer
  Tache_t *pool_taches;
  uint32_t nb_taches_total;
  uint32_t capacite_pool;

  duree_t l_max; // Retard maximal global (objectif à minimiser)
} Solution_t;

// --- API ---

status_e ordonnanceur_creer(Solution_t *sol, uint32_t nb_machines);
status_e ordonnanceur_ajouter_tache_pool(Solution_t *sol, identifiant_t id,
                                         duree_t p, duree_t q);
status_e ordonnanceur_resoudre_jackson(Solution_t *sol);
status_e ordonnanceur_exporter_csv(const Solution_t *sol, const char *chemin);
void ordonnanceur_detruire(Solution_t *sol);

#endif