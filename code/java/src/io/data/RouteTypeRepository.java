package io.data;

import model.City;
import model.RoadType;

public interface RouteTypeRepository 
{
	RoadType findType(City from, City to);
}
