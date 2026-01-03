package ui.view;

import java.awt.CardLayout;

import javax.swing.JPanel;

import ui.controller.AppController;
import ui.controller.MapController;

public class MainViewPanel extends JPanel 
{
	public static final String CARD_HOME = "HOME";
    public static final String CARD_MAP  = "MAP";

    private final CardLayout _layout;
    private final HomePanel _homePanel;
    private final MapPanel _mapPanel;

    public MainViewPanel(AppController appController, MapController mapController) 
    {
        _layout = new CardLayout();
        setLayout(_layout);

        _mapPanel = new MapPanel(mapController, this);
        _homePanel = new HomePanel(appController, _mapPanel, this);

        add(_homePanel, CARD_HOME);
        add(_mapPanel, CARD_MAP);

        _layout.show(this, CARD_HOME);
    }

    public void showHome() { _layout.show(this, CARD_HOME); }
    public void showMap()  { _layout.show(this, CARD_MAP); }
}
