#ifndef TYPES_COMMUNS_H
#define TYPES_COMMUNS_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Codes de retour pour la gestion d'erreur stricte.
 */
typedef enum
{
  STATUS_SUCCES = 0,
  STATUS_ERREUR_NULL_POINTER = 1,
  STATUS_ERREUR_MEMOIRE_PLEINE = 2,
  STATUS_ERREUR_ARGUMENT_INVALIDE = 3,
  STATUS_ERREUR_ETAT_INCOHERENT = 4,
  STATUS_INFO_MEMOIRE_INSUFFISANTE_POUR_OPTIMAL = 5
} status_e;

typedef int32_t duree_t;        /* Pour p_i, q_i, C_i */
typedef uint32_t identifiant_t; /* Pour les IDs */

/* Limite physique pour les tableaux statiques dans la DP (évite malloc dans
 * struct) */
#define MAX_MACHINES_HARD_LIMIT 16

#endif
