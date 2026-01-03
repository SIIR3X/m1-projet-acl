package request;

import java.util.List;
import java.util.ArrayList;
import java.nio.file.Path;

/* Patron de conception "Strategie" + map qui lie le type de traitement a l'interface.
 * Objectif: selon un `TypeTraitement commande` et de ses parametres,
 * construire une requete adapte a ce type de traitement contenant les fichiers passes.
 * */
public interface RequestBuilder
{
	public String build(TypeTraitement commande, ArrayList<String> parameters, List<Path> files);
}
