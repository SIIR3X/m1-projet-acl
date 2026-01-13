#include "ordonnanceur.h"
#include "memoire.h" // Supposé contenir vos wrappers malloc/free si existant
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// FONCTIONS PRIVÉES (STATIC) - HELPERS
// ============================================================================

/**
 * @brief Comparateur pour qsort : Tri décroissant selon q_i (Latence).
 * C'est le cœur de l'règle de Jackson.
 */
static int comparer_taches_jackson(const void *a, const void *b)
{
  const Tache_t *t1 = (const Tache_t *)a;
  const Tache_t *t2 = (const Tache_t *)b;

  // Ordre décroissant de q_i
  if (t1->q_i < t2->q_i)
    return 1;
  if (t1->q_i > t2->q_i)
    return -1;
  return 0;
}

/**
 * @brief Trouve la machine disponible le plus tôt (Min Load).
 */
static uint32_t trouver_machine_dispo(const Solution_t *sol)
{
  uint32_t index_min = 0;
  duree_t min_date = sol->machines[0].date_dispo;

  for (uint32_t i = 1; i < sol->nb_machines; i++)
  {
    if (sol->machines[i].date_dispo < min_date)
    {
      min_date = sol->machines[i].date_dispo;
      index_min = i;
    }
  }
  return index_min;
}

/**
 * @brief Ajoute une tâche assignée à une machine spécifique (Gestion mémoire).
 */
static status_e assigner_tache_machine(Machine_t *m, Tache_t t)
{
  if (m->nb_taches >= m->capacite)
  {
    uint32_t new_cap = (m->capacite == 0) ? 4 : m->capacite * 2;
    Tache_t *tmp =
        (Tache_t *)realloc(m->taches_assignees, new_cap * sizeof(Tache_t));
    if (!tmp)
      return STATUS_ERREUR_MEMOIRE_PLEINE;

    m->taches_assignees = tmp;
    m->capacite = new_cap;
  }

  // Mise à jour des temps
  // Date fin = Date dispo avant tache + durée tache p_i
  t.date_fin_C_i = m->date_dispo + t.p_i;

  // Mise à jour machine
  m->taches_assignees[m->nb_taches] = t;
  m->nb_taches++;
  m->date_dispo = t.date_fin_C_i; // La machine est occupée jusqu'à C_i

  return STATUS_SUCCES;
}

// ============================================================================
// FONCTIONS PUBLIQUES
// ============================================================================

status_e ordonnanceur_creer(Solution_t *sol, uint32_t nb_machines)
{
  if (!sol || nb_machines == 0)
    return STATUS_ERREUR_ARGUMENT_INVALIDE;

  memset(sol, 0, sizeof(Solution_t));
  sol->nb_machines = nb_machines;

  sol->machines = (Machine_t *)calloc(nb_machines, sizeof(Machine_t));
  if (!sol->machines)
    return STATUS_ERREUR_MEMOIRE_PLEINE;

  for (uint32_t i = 0; i < nb_machines; i++)
  {
    sol->machines[i].id_machine = i + 1; // ID commence à 1
    sol->machines[i].date_dispo = 0;
    sol->machines[i].taches_assignees = NULL;
    sol->machines[i].nb_taches = 0;
    sol->machines[i].capacite = 0;
  }

  // Pool de tâches initial
  sol->capacite_pool = 10;
  sol->pool_taches = (Tache_t *)calloc(sol->capacite_pool, sizeof(Tache_t));
  if (!sol->pool_taches)
  {
    free(sol->machines);
    return STATUS_ERREUR_MEMOIRE_PLEINE;
  }

  return STATUS_SUCCES;
}

status_e ordonnanceur_ajouter_tache_pool(Solution_t *sol, identifiant_t id,
                                         duree_t p, duree_t q)
{
  if (!sol)
    return STATUS_ERREUR_NULL_POINTER;

  if (sol->nb_taches_total >= sol->capacite_pool)
  {
    uint32_t new_cap = sol->capacite_pool * 2;
    Tache_t *tmp =
        (Tache_t *)realloc(sol->pool_taches, new_cap * sizeof(Tache_t));
    if (!tmp)
      return STATUS_ERREUR_MEMOIRE_PLEINE;
    sol->pool_taches = tmp;
    sol->capacite_pool = new_cap;
  }

  Tache_t *t = &sol->pool_taches[sol->nb_taches_total];
  t->id_tache = id;
  t->p_i = p;
  t->q_i = q;
  t->date_fin_C_i = 0; // Sera calculé

  sol->nb_taches_total++;
  return STATUS_SUCCES;
}

/**
 * @brief Algorithme Principal : Jackson étendu aux machines parallèles.
 * 1. Trie les tâches par q_i décroissant.
 * 2. Affecte chaque tâche à la machine la moins chargée.
 */
status_e ordonnanceur_resoudre_jackson(Solution_t *sol)
{
  if (!sol)
    return STATUS_ERREUR_NULL_POINTER;
  if (sol->nb_taches_total == 0)
    return STATUS_SUCCES; // Rien à faire

  // 1. Tri (Règle de Jackson)
  qsort(sol->pool_taches, sol->nb_taches_total, sizeof(Tache_t),
        comparer_taches_jackson);

  // 2. Affectation Gloutonne (Greedy)
  for (uint32_t i = 0; i < sol->nb_taches_total; i++)
  {
    Tache_t courante = sol->pool_taches[i];

    // Trouver la machine qui se libère le plus tôt
    uint32_t idx_machine = trouver_machine_dispo(sol);

    // Assigner
    status_e res =
        assigner_tache_machine(&sol->machines[idx_machine], courante);
    if (res != STATUS_SUCCES)
      return res;
  }

  // 3. Calcul du L_max global (C_i + q_i)
  sol->l_max = 0;
  for (uint32_t m = 0; m < sol->nb_machines; m++)
  {
    Machine_t *machine = &sol->machines[m];
    for (uint32_t t = 0; t < machine->nb_taches; t++)
    {
      Tache_t *tache = &machine->taches_assignees[t];
      duree_t l_i = tache->date_fin_C_i + tache->q_i;
      if (l_i > sol->l_max)
      {
        sol->l_max = l_i;
      }
    }
  }

  return STATUS_SUCCES;
}

/**
 * @brief Exporte la solution pour JAVA (Format: id_machine;id_ville)
 */
status_e ordonnanceur_exporter_csv(const Solution_t *sol, const char *chemin)
{
  if (!sol || !chemin)
    return STATUS_ERREUR_NULL_POINTER;

  FILE *f = fopen(chemin, "w");
  if (!f)
    return STATUS_ERREUR_ARGUMENT_INVALIDE;

  for (uint32_t m = 0; m < sol->nb_machines; m++)
  {
    Machine_t *mach = &sol->machines[m];
    for (uint32_t t = 0; t < mach->nb_taches; t++)
    {
      // Format: ID_MACHINE;INDEX_VILLE
      fprintf(f, "%u;%u\n", mach->id_machine,
              mach->taches_assignees[t].id_tache);
    }
  }

  fclose(f);
  return STATUS_SUCCES;
}

void ordonnanceur_detruire(Solution_t *sol)
{
  if (!sol)
    return;

  if (sol->machines)
  {
    for (uint32_t i = 0; i < sol->nb_machines; i++)
    {
      free(sol->machines[i].taches_assignees);
    }
    free(sol->machines);
  }

  if (sol->pool_taches)
  {
    free(sol->pool_taches);
  }

  memset(sol, 0, sizeof(Solution_t));
}