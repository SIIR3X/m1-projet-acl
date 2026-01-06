package controleur;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Gère la sélection d'éléments affichés.
 * Indépendant du modèle métier.
 *
 * @param <T> type des éléments sélectionnables
 */
public class GestionSelection<T> {
	public enum Mode {
		ALEATOIRE,
		MANUEL
	}
	
	private Mode _mode = Mode.ALEATOIRE;
	
	/** Ensemble des éléments sélectionnées */
	private final Set<T> _selection = new HashSet<>();
	
	/** Toutes les éléments affichées */
	private final List<T> _elements;

	private SelectionListener _listener;
	
	public GestionSelection(List<T> elements) {
		this._elements = elements;
		activerModeAleatoire();
	}
	
	public void activerModeAleatoire() {
		_mode = Mode.ALEATOIRE;
		_selection.clear();
		_selection.addAll(_elements);
		
		notifier();
	}
	
	public void activerModeManuel() {
		_mode = Mode.MANUEL;
		_selection.clear();
		
		notifier();
	}
	
	public void toggle(T element) {
		if (_mode != Mode.MANUEL) {
			return;
		}
		
		if (_selection.contains(element)) {
			_selection.remove(element);
		} else {
			_selection.add(element);
		}
		
		notifier();
	}
	
	public Mode getMode() {
		return _mode;
	}	

	public Set<T> getSelection() {
		return Set.copyOf(_selection);
	}
	
	public void setListener(SelectionListener listener) {
		this._listener = listener;
	}
	
	public boolean estSelectionnee(T element) {
		return _selection.contains(element);
	}
		
	private void notifier() {
		if (_listener != null) {
			_listener.selectionChangee(_selection.size());
		}
	}
}
