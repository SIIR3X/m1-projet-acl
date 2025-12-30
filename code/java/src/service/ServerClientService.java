package service;

import java.io.IOException;
import java.nio.file.Path;
import java.util.List;

import request.*;
import client.*;

public class ServerClientService {
	private final String host;
    private final int port;

    public ServerClientService(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public String optimize(List<Path> paths) {

        TypeTraitement cmd = TypeTraitement.ALGO_DISTANCE;
        RequestBuilderRegistry registry = new RequestBuilderRegistry();
        String request = registry.get(cmd).build(cmd, paths);

        try (ClientTCP client = new ClientTCP(host, port)) {
            client.connect();
            client.write(request);
            return client.read();
        }
        catch (IOException e) {
            throw new RuntimeException("Erreur communication serveur", e);
        }
    }
}
