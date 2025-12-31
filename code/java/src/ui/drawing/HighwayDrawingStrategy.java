package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

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
