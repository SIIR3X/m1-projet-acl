package chargement;

/**
 * Interface d'un chargeur de données (Chain of Responsibility).
 *
 * @param <T> type de données chargées
 */
public interface ChargeurDonnees<T> {
	/**
	 * Définit le chargeur suivant dans la chaîne.
	 * 
	 * @param suivant Chargeur suivant
	 */
	void definirSuivant(ChargeurDonnees<T> suivant);
	
	/**
	 * Indique si le chargeur peut traiter ce fichier.
	 * 
	 * @param cheminFichier Chemin du fichier
	 * @return true si le chargeur reconnaît le format
	 * @throws Exception
	 */
	boolean peutCharger(String cheminFichier) throws Exception;
	
	/**
	 * Tente de charger des données depuis un fichier (format quelconque).
	 * 
	 * @param cheminFichier Chemin du fichier
	 * @return objet chargé (liste, carte, etc.)
	 * @throws Exception si aucun chargeur ne peut traiter le fichier
	 */
	T charger(String cheminFichier) throws Exception;
}
