package ui.drawing;

import java.awt.BasicStroke;
import java.awt.Color;

public class DepartmentalRoadDrawingStrategy extends AbstractRouteDrawingStrategy {

	@Override
	public Color getColor() {
        return Color.BLACK;
    }

    @Override
	public BasicStroke getStroke() {
        return new BasicStroke(1.5f);
    }
}
