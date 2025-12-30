package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

public class NationalRoadDrawingStrategy extends AbstractRouteDrawingStrategy {

	@Override
	public Color getColor() {
        return Color.ORANGE;
    }

    @Override
	public BasicStroke getStroke() {
        return new BasicStroke(2f);
    }

}
