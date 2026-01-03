package io.data;

import java.nio.file.Path;

public interface RouteTypeRepositoryFactory {
    RouteTypeRepository create(Path path);
}
