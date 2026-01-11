package vue;

import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

/**
 * Barre de contrôle située en bas de la fenêtre principale.
 * 
 * Ce panneau regroupe les contrôles permettant de configurer
 * l’optimisation : choix du nombre de camions, mode de sélection
 * (aléatoire ou manuel), sélection des fichiers d’entrée et
 * déclenchement du calcul d’optimisation.
 */
public class BarreControle extends JPanel
{
	
	private static final long serialVersionUID = 1L;
	
	private final JComboBox<Integer> _selectCamions;
	private final JRadioButton _radioAleatoire;
	private final JRadioButton _radioManuel;
	private final JButton _boutonOptimiser;
	
	private final JButton _boutonFichiers;
	private final JLabel _labelFichiers;
	private final List<Path> _fichiersSelectionnes = new ArrayList<>();
	
	private Runnable _listenerFichiers;
	
	public BarreControle(int nbVilles) 
	{
		// Layout horizontal simple
        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        setBorder(BorderFactory.createEtchedBorder());
		
		// Sélecteur de camions
		add(new JLabel("Camions"));
		
		Integer[] valeurs = new Integer[nbVilles];
		for (int i = 0; i < nbVilles; ++i) {
			valeurs[i] = i + 1;
		}
		
		_selectCamions = new JComboBox<>(valeurs);
		add(_selectCamions);
		
		// Boutons radio
		_radioAleatoire = new JRadioButton("Aléatoire", true);
		_radioManuel = new JRadioButton("Manuel");
		
		ButtonGroup groupe = new ButtonGroup();
		groupe.add(_radioAleatoire);
		groupe.add(_radioManuel);
		
		add(Box.createHorizontalStrut(20));
		add(_radioAleatoire);
		add(_radioManuel);
		
		// Sélection des fichiers
		add(Box.createHorizontalStrut(20));
		
		_boutonFichiers = new JButton("Fichiers...");
		_labelFichiers = new JLabel("Aucun fichier");
		
        add(_boutonFichiers);
        add(Box.createHorizontalStrut(5));
        add(_labelFichiers);

        initialiserSelectionFichiers();
		
		// Espace extensible
		add(Box.createHorizontalGlue());
		
		// Bouton optimiser
		_boutonOptimiser = new JButton("Optimiser");
		add(_boutonOptimiser);
	}
	
	public List<Path> getFichiersSelectionnes() 
	{
		return List.copyOf(_fichiersSelectionnes);
	}
	
	public void mettreAJourCamions(int max) 
	{
		_selectCamions.removeAllItems();
		
		for (int i = 1; i <= max; ++i) {
			_selectCamions.addItem(i);
		}
		
		
		// Sélection par défaut de 1
		if (max > 0) {
			_selectCamions.setSelectedIndex(0);
		}
	}
	
	public int getNombreCamions() 
	{
		return (Integer)_selectCamions.getSelectedItem();
	}
	
	public boolean estAleatoire() 
	{
		return _radioAleatoire.isSelected();
	}
	
	public JRadioButton getRadioAleatoire() 
	{
		return _radioAleatoire;
	}
	
	public JRadioButton getRadioManuel() 
	{
		return _radioManuel;
	}
	
	public JButton getBoutonOptimiser() 
	{
		return _boutonOptimiser;
	}
	
	public void setListenerFichiers(Runnable listener) 
	{
		this._listenerFichiers = listener;
	}
	
    private void initialiserSelectionFichiers() 
    {
        _boutonFichiers.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser("data/13_fichiers_JSON");
            chooser.setMultiSelectionEnabled(true);
            chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);

            int result = chooser.showOpenDialog(this);

            if (result == JFileChooser.APPROVE_OPTION) {
                _fichiersSelectionnes.clear();

                for (var f : chooser.getSelectedFiles()) {
                    _fichiersSelectionnes.add(f.toPath());
                }

                mettreAJourLabelFichiers();
                
                if (_listenerFichiers != null) {
                	_listenerFichiers.run();
                }
            }
        });
    }
	
	private void mettreAJourLabelFichiers() 
	{
        if (_fichiersSelectionnes.isEmpty()) {
            _labelFichiers.setText("Aucun fichier");
        } else {
            _labelFichiers.setText(
                _fichiersSelectionnes.size() + " fichier(s)"
            );
        }
	}
}
