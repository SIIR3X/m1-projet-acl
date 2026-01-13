#include "memoire.h"
#include <stdlib.h>
#include <string.h>

struct GestionnaireMemoire_t
{
  uint8_t *debut_buffer;
  size_t taille_totale;
  size_t offset_actuel;
};

status_e memoire_initialiser(size_t taille_octets,
                             GestionnaireMemoire_t **out_gestionnaire)
{
  if (!out_gestionnaire || taille_octets == 0)
    return STATUS_ERREUR_ARGUMENT_INVALIDE;

  /* Allocation contiguë pour la structure et le buffer */
  size_t total = sizeof(GestionnaireMemoire_t) + taille_octets;
  uint8_t *bloc = calloc(1, total);
  if (!bloc)
    return STATUS_ERREUR_MEMOIRE_PLEINE;

  GestionnaireMemoire_t *g = (GestionnaireMemoire_t *)(void *)bloc;
  g->debut_buffer = bloc + sizeof(GestionnaireMemoire_t);
  g->taille_totale = taille_octets;
  g->offset_actuel = 0;

  *out_gestionnaire = g;
  return STATUS_SUCCES;
}

void *memoire_allouer(GestionnaireMemoire_t *gestionnaire, size_t taille)
{
  if (!gestionnaire || taille == 0)
    return NULL;

  /* Alignement 8 octets */
  size_t align = 8;
  size_t offset_aligne =
      (gestionnaire->offset_actuel + (align - 1)) & ~(align - 1);

  if (offset_aligne + taille > gestionnaire->taille_totale)
    return NULL;

  void *ptr = gestionnaire->debut_buffer + offset_aligne;
  gestionnaire->offset_actuel = offset_aligne + taille;
  /* Zero-init par sécurité */
  memset(ptr, 0, taille);
  return ptr;
}

void memoire_detruire(GestionnaireMemoire_t **gestionnaire)
{
  if (gestionnaire && *gestionnaire)
  {
    free(*gestionnaire);
    *gestionnaire = NULL;
  }
}
