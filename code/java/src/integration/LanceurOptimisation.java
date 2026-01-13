package integration;

import java.io.File;
import java.io.IOException;

/**
 * Lance l'algorithme C d'optimisation.
 */
public class LanceurOptimisation {
	
    /**
     * Lance l'exécutable C avec les paramètres.
     *
     * @param executable chemin de l'exécutable
     * @param nbCamions nombre de camions
     * @param nbElements nombre d'éléments sélectionnées
     */
	public static void lancer(
			String executable,
			int nbCamions,
			int nbElements
	) throws IOException, InterruptedException {
	    File exec = new File(executable);

	    if (!exec.exists()) {
	        throw new IllegalArgumentException(
	                "Exécutable introuvable : " + exec.getAbsolutePath()
	        );
	    }
		
		ProcessBuilder pb = new ProcessBuilder(
				exec.getAbsolutePath(),
				String.valueOf(nbCamions),
				String.valueOf(nbElements)
		);
		
		pb.directory(new File("."));
		pb.redirectErrorStream(true);

		Process process = pb.start();
		int codeRetour = process.waitFor();
		
		if (codeRetour != 0) {
            throw new RuntimeException(
                    "Erreur lors de l'exécution du programme C (code "
                            + codeRetour + ")"
            );
		}
	}
}
