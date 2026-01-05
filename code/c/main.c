#include "memoire.h"
#include "ordonnanceur.h"
#include "types_communs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Nécessaire pour l'aléatoire

int main(int argc, char *argv[])
{
  printf("=== ALGO ORDONNANCEMENT (JACKSON) - INSTANCE COMPLETE ===\n");

  // Vérification des arguments :
  // argv[1] : nombre de machines (camions)
  // argv[2] : nombre de villes à générer
  if (argc != 3)
  {
    fprintf(stderr,
            "Usage: %s <nb_machines> <nb_villes>\n",
            argv[0]);
    return 1;
  }

  // Initialisation du générateur aléatoire
  srand(time(NULL));

  Solution_t solution;

  // Lecture des paramètres depuis la ligne de commande
  uint32_t nb_machines = (uint32_t)atoi(argv[1]);
  uint32_t nb_villes = (uint32_t)atoi(argv[2]);

  if (nb_machines == 0 || nb_villes == 0)
  {
    fprintf(stderr,
            "Erreur : le nombre de machines et de villes doit etre > 0\n");
    return 1;
  }

  printf("[INFO] %d camions\n", nb_machines);
  printf("[INFO] %d villes generees\n", nb_villes);

  // 1. Initialisation
  if (ordonnanceur_creer(&solution, nb_machines) != STATUS_SUCCES)
  {
    fprintf(stderr, "Erreur mémoire\n");
    return 1;
  }

  // 2. Chargement des Données (Génération automatique des villes)
  // Chaque ville est représentée par une tâche
  for (identifiant_t i = 0; i < nb_villes; i++)
  {
    // p_i : Quantité à livrer / Durée (Simulé entre 10 et 30 min)
    duree_t p = 10 + (rand() % 21);

    // q_i : Latence / Temps de retour (Simulé entre 5 et 60 min)
    // C'est ce paramètre qui est crucial pour l'ordre de Jackson
    duree_t q = 5 + (rand() % 56);

    // L'identifiant i correspondra à la ville n°i du fichier JSON
    ordonnanceur_ajouter_tache_pool(&solution, i, p, q);
  }

  // 3. Résolution (Algorithme de Jackson)
  // Répartition des villes sur les camions
  ordonnanceur_resoudre_jackson(&solution);

  printf("[ALGO] L_max calcule : %d\n", solution.l_max);

  // 4. Exportation vers le module Java
  // Le fichier CSV sera lu par la partie Java pour construire les tournées
  const char *chemin = "data/ordonnancements/ordonnancement_jackson.csv";

  if (ordonnanceur_exporter_csv(&solution, chemin) == STATUS_SUCCES)
  {
    printf("[SUCCES] Export CSV termine : %s\n", chemin);
    printf("-> Ouvre l'interface Java : tu devrais voir environ %d villes par "
           "camion !\n",
           nb_villes / nb_machines);
  }
  else
  {
    printf("[ERREUR] Export CSV echoue. Verifie le dossier data.\n");
  }

  // 5. Nettoyage
  ordonnanceur_detruire(&solution);

  return 0;
}
