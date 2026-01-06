package requete;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.Map;

import modele.Ville;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.lang.reflect.Field;
import java.lang.IllegalArgumentException;

/* Obligation d'immutabilite vis-a-vis de de l'enumMap. */
/* Construit la requete pour l'algorithme de distance, en raccord avec les attentes serveur. */
public class AlgoDistanceRequeteBuilder implements RequeteBuilder
{
	private static final String ALGO = "tsp";
	private static final String ENTITE = "ville";
	private static final String DISTANCE = "geodesique";

	@Override
	public String build(TypeTraitement commande, Object donnees)
	{
		Map<Integer, List<Ville>> ensembles =
				(Map<Integer, List<Ville>>)donnees;
		
		return construireJson(commande, ensembles);
	}
	
	private String construireJson(
			TypeTraitement commande,
			Map<Integer, List<Ville>> ensembles
	) {
		StringBuilder json = new StringBuilder();
		
        json.append("{\n")
        	.append("  \"commande\": \"")
	        .append(commande.toString().toLowerCase())
	        .append("\",\n")
	        .append("  \"algo\": \"").append(ALGO).append("\",\n")
	        .append("  \"entite\": \"").append(ENTITE).append("\",\n")
	        .append("  \"distance\": \"").append(DISTANCE).append("\",\n")
	        .append("  \"ensembles\": [\n");
        
        int i = 0;
        int total = ensembles.size();
        
        for (List<Ville> villes : ensembles.values()) {
        	json.append(construireEnsemble(villes));
        	
        	if (++i < total) {
        		json.append(",");
        	}
        	json.append("\n");
        }
        

        json.append("  ]\n")
            .append("}");
        
        return json.toString();
	}
	
	private String construireEnsemble(List<Ville> villes) {
        StringBuilder sb = new StringBuilder();

        sb.append("    {\n")
          .append("      \"donnees\": [\n");

        for (int i = 0; i < villes.size(); i++) {
            Ville v = villes.get(i);

            sb.append("        { ")
              .append("\"ville\": \"").append(v.getNom()).append("\", ")
              .append("\"latitude\": ").append(v.getLatitude()).append(", ")
              .append("\"longitude\": ").append(v.getLongitude())
              .append(" }");

            if (i < villes.size() - 1) {
                sb.append(",");
            }
            sb.append("\n");
        }

        sb.append("      ]\n")
          .append("    }");

        return sb.toString();
	}
}