#ifndef MEMOIRE_H
#define MEMOIRE_H
#include "types_communs.h"
#include <stddef.h>

typedef struct GestionnaireMemoire_t GestionnaireMemoire_t;

status_e memoire_initialiser(size_t taille_octets,
                             GestionnaireMemoire_t **out_gestionnaire);
void *memoire_allouer(GestionnaireMemoire_t *gestionnaire, size_t taille);
void memoire_detruire(GestionnaireMemoire_t **gestionnaire);

#endif
