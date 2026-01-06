package service;

import io.data.RouteTypeRepository;
import modele.RoadType;
import modele.Ville;

/**
 * Service métier qui encapsule la logique d'obtention du type de route
 * entre deux villes, avec une valeur par défaut lorsque le type est inconnu.
 */
public class RouteTypeService 
{
    private final RouteTypeRepository _repository;

    public RouteTypeService(RouteTypeRepository repository) 
    {
        this._repository = repository;
    }

    public RoadType getType(Ville from, Ville to) 
    {
    	 RoadType type = _repository.findType(from, to);
         return type != null ? type : RoadType.COMMUNALE;
    }
}
