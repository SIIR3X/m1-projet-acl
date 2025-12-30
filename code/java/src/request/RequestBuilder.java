package request;

import java.nio.file.Path;
import java.util.List;

/* Patron de conception "Strategie" + map qui lie le type de traitement a l'interface ici presente
 * Objectif: selon un `TypeTraitement commande`,
 * construire une requete adapte a ce type de traitement contenant les fichiers passes.
 * */
public interface RequestBuilder
{
	public String build(TypeTraitement commande, List<Path> files); // ajouter entre commade et files un objet abstrait
}
