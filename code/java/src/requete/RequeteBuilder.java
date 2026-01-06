package requete;

/* Patron de conception "Strategie" + map qui lie le type de traitement a l'interface.
 * Objectif: selon un `TypeTraitement commande` et de ses parametres,
 * construire une requete adapte a ce type de traitement contenant les fichiers passes.
 * */
public interface RequeteBuilder
{
	public String build(TypeTraitement commande, Object donnees);
}