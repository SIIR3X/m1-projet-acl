package service;

import java.io.IOException;
import java.util.List;
import java.util.Map;

import client.ClientTCP;
import modele.EntiteGeographique;
import requete.RequeteBuilder;
import requete.RequeteBuilderRegistry;
import requete.TypeTraitement;

public class ServeurClientService {
	private final String _host;
	private final int _port;
	
	public ServeurClientService(String host, int port) {
		this._host = host;
		this._port = port;
	}
	
	
    public <T extends EntiteGeographique>
    String optimiser(Map<Integer, List<T>> ensembles) {
    	// 1. Récupération du builder via le registry
    	RequeteBuilderRegistry registry = new RequeteBuilderRegistry();
    	RequeteBuilder builder =
    			registry.get(TypeTraitement.ALGO_DISTANCE);
    	
    	// 2. Construction de la requête JSON
    	String requeteJson =
    			builder.build(TypeTraitement.ALGO_DISTANCE, ensembles);
    	
    	// 3. Communication TCP
    	try {
    		ClientTCP client = new ClientTCP(_host, _port);
    		
    		try {
	            client.connect();
	            client.write(requeteJson);
	            return client.read();
    		} finally {
    			client.close();
    		}
    	} catch (IOException e) {
    		throw new RuntimeException("Erreur communication serveur", e);
    	}
    }
}
