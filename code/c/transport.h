#ifndef TRANSPORT_H
#define TRANSPORT_H
#include "memoire.h"
#include "types_communs.h"

typedef struct
{
  duree_t r_dispo; /* Date dispo (Ci) */
  duree_t q_duree; /* Durée transport */
} TacheRobot_t;

typedef struct
{
  duree_t fin_r1;
  duree_t fin_r2;
  duree_t cmax_global;
} ResultatRobot_t;

status_e simulation_robots(GestionnaireMemoire_t *mem, TacheRobot_t *taches,
                           uint32_t n, ResultatRobot_t **out_res);
#endif
