package service;

import io.data.RouteTypeRepository;
import model.City;
import model.RoadType;

public class RouteTypeService 
{

    private final RouteTypeRepository _repository;

    public RouteTypeService(RouteTypeRepository repository) 
    {
        this._repository = repository;
    }

    public RoadType getType(City from, City to) 
    {
    	 RoadType type = _repository.findType(from, to);
         return type != null ? type : RoadType.COMMUNALE;
    }

}
