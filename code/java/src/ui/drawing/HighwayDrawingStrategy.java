package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

/**
 * Stratégie de dessin pour les autoroutes
 * (couleur rouge, trait plein, épaisseur importante).
 */
public class HighwayDrawingStrategy extends AbstractRouteDrawingStrategy 
{

	@Override
	public Color getColor() 
	{
        return Color.RED;
    }

    @Override
	public BasicStroke getStroke() 
    {
        return new BasicStroke(5f);
    }
}
