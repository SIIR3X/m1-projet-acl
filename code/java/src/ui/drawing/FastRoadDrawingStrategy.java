package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

/**
 * Stratégie de dessin pour les voies rapides,
 * (couleur rouge, trait plein, épaisseur fine).
 */
public class FastRoadDrawingStrategy extends AbstractRouteDrawingStrategy 
{
	@Override
	public Color getColor() 
	{
        return Color.RED;
    }

    @Override
	public BasicStroke getStroke() 
    {
        return new BasicStroke(1f);
    }

}
