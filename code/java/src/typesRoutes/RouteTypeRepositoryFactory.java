package typesRoutes;

import java.nio.file.Path;

/**
 * Fabrique fonctionnelle permettant de créer un RouteTypeRepository
 * à partir d'un chemin de fichier donné (utilisé par MultiRouteTypeRepository).
 */
public interface RouteTypeRepositoryFactory {
    RouteTypeRepository create(Path path);
}
