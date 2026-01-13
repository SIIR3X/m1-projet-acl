package integration;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Lit un fichier de solution produit par le programme C.
 *
 * Format attendu :
 * camion;idVille
 */
public class LecteurSolutionVille {
    /**
     * Lit le fichier et retourne les affectations.
     *
     * @param chemin chemin du fichier
     * @return liste des affectations camion → ville
     */
    public static List<AffectationVille> lire(String chemin)
            throws Exception {

        List<AffectationVille> resultat = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(chemin))) {
            String ligne;

            while ((ligne = br.readLine()) != null) {
                if (ligne.isBlank()) continue;

                String[] parts = ligne.split(";");
                int camion = Integer.parseInt(parts[0]);
                int ville = Integer.parseInt(parts[1]);

                resultat.add(new AffectationVille(camion, ville));
            }
        }

        return resultat;
    }
}
