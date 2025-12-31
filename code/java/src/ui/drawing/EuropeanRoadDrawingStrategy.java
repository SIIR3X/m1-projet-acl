package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

public class EuropeanRoadDrawingStrategy extends AbstractRouteDrawingStrategy 
{

	@Override
	public Color getColor() 
	{
        return Color.BLUE;
    }

    @Override
	public BasicStroke getStroke() 
    {
        return new BasicStroke(
            2f,
            BasicStroke.CAP_BUTT,
            BasicStroke.JOIN_MITER,
            10,
            new float[]{5},
            0
        );
    }

}
