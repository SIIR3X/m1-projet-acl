package ui.view;

import javax.swing.JFrame;

import ui.controller.AppController;
import ui.controller.MapController;

public class MainFrame extends JFrame 
{
	public MainFrame(AppController controller, MapController mapController) 
	{
        setTitle("Optimisation de tournée");
        setSize(1000, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        setContentPane(new HomePanel(controller, mapController));
    }
}
