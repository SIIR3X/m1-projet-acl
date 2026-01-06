package requete;

/* Patron de conception "Strategie".
 * Objectif: selon un `TypeTraitement commande`,
 * construire une requete adapte a ce type de traitement.
 * */
public interface RequeteBuilder
{
	public String build(TypeTraitement commande, Object donnees);
}