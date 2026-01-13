#include "transport.h"
#include <stdlib.h>

static int cmp_dispo(const void *a, const void *b)
{
  return (((const TacheRobot_t *)a)->r_dispo -
          ((const TacheRobot_t *)b)->r_dispo);
}

status_e simulation_robots(GestionnaireMemoire_t *mem, TacheRobot_t *taches,
                           uint32_t n, ResultatRobot_t **out_res)
{
  ResultatRobot_t *res = memoire_allouer(mem, sizeof(ResultatRobot_t));
  if (!res)
    return STATUS_ERREUR_MEMOIRE_PLEINE;

  /* Tri par date d'arrivée (r_i) */
  qsort(taches, n, sizeof(TacheRobot_t), cmp_dispo);

  duree_t f1 = 0, f2 = 0;
  for (uint32_t i = 0; i < n; i++)
  {
    duree_t start;
    /* Affectation au premier robot dispo */
    if (f1 <= f2)
    {
      start = (taches[i].r_dispo > f1) ? taches[i].r_dispo : f1;
      f1 = start + taches[i].q_duree;
    }
    else
    {
      start = (taches[i].r_dispo > f2) ? taches[i].r_dispo : f2;
      f2 = start + taches[i].q_duree;
    }
  }
  res->fin_r1 = f1;
  res->fin_r2 = f2;
  res->cmax_global = (f1 > f2) ? f1 : f2;
  *out_res = res;
  return STATUS_SUCCES;
}
