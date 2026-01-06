package chargement;

/**
 * Implémentation abstraite du Chain of Responsibility.
 *
 * @param <T> type de données chargées
 */
public abstract class ChargeurCOR<T> implements ChargeurDonnees<T> {
	protected ChargeurDonnees<T> _suivant;
	
	@Override
	public void definirSuivant(ChargeurDonnees<T> suivant) {
		this._suivant = suivant;
	}
	
	@Override
	public T charger(String cheminFichier) throws Exception {
		if (peutCharger(cheminFichier)) {
			return chargerInterne(cheminFichier);
		}
		
		if (_suivant != null) {
			return _suivant.charger(cheminFichier);
		}
		
        throw new IllegalArgumentException(
        		"Aucun chargeur ne reconnaît le fichier : " + cheminFichier
         );
	}
	
	/**
	 * Chargement effectif si le chargeur reconnaît le fichier.
	 */
	protected abstract T chargerInterne(String cheminFichier) throws Exception;
}
