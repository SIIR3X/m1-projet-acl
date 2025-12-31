package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

public class LocalRoadDrawingStrategy extends AbstractRouteDrawingStrategy 
{
	@Override
	public Color getColor() 
	{
        return Color.BLACK;
    }

    @Override
	public BasicStroke getStroke() 
    {
        return new BasicStroke(
            1.5f,
            BasicStroke.CAP_ROUND,
            BasicStroke.JOIN_MITER,
            10,
            new float[]{5},
            0
        );
    }

}
