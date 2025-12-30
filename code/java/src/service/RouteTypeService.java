package service;

import io.data.RouteTypeRepository;
import model.City;
import model.RoadType;

public class RouteTypeService {

    private final RouteTypeRepository repository;

    public RouteTypeService(RouteTypeRepository repository) {
        this.repository = repository;
    }

    public RoadType getType(City from, City to) {
        return repository.findType(from, to);
    }

}
