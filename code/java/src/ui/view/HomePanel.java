package ui.view;

import java.awt.Component;
import java.awt.Container;
import java.awt.Font;
import java.nio.file.Path;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;

import ui.controller.AppController;
import ui.controller.MapController;

public class HomePanel extends JPanel {
	private Path selectedCsv;
    private final JButton optimizeButton;
    private final MapPanel mapPanel;


    public HomePanel(AppController controller, MapController mapController) {
        this.mapPanel = new MapPanel(mapController);
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        setBorder(BorderFactory.createEmptyBorder(40, 40, 40, 40));

        JLabel title = new JLabel("Optimisation de tournée");
        title.setFont(new Font("Arial", Font.BOLD, 22));
        title.setAlignmentX(Component.CENTER_ALIGNMENT);

        JButton chooseFileButton = new JButton("Choisir un fichier CSV");
        chooseFileButton.setAlignmentX(Component.CENTER_ALIGNMENT);

        optimizeButton = new JButton("Optimiser");
        optimizeButton.setEnabled(false);
        optimizeButton.setAlignmentX(Component.CENTER_ALIGNMENT);

        JLabel fileLabel = new JLabel("Aucun fichier sélectionné");
        fileLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        add(title);
        add(Box.createVerticalStrut(30));
        add(chooseFileButton);
        add(Box.createVerticalStrut(15));
        add(fileLabel);
        add(Box.createVerticalStrut(30));
        add(optimizeButton);

        // Action choisir fichier
        chooseFileButton.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setDialogTitle("Choisir un fichier CSV");

            int result = chooser.showOpenDialog(this);
            if (result == JFileChooser.APPROVE_OPTION) {
                selectedCsv = chooser.getSelectedFile().toPath();
                fileLabel.setText("Fichier : " + selectedCsv.getFileName());
                optimizeButton.setEnabled(true);
            }
        });

        // Action optimiser
        optimizeButton.addActionListener(e -> {
            controller.optimize(selectedCsv);
            // Afficher la carte à la place du HomePanel
            removeAll();
            add(mapPanel);
            revalidate();
            repaint();
        });
    }
}
