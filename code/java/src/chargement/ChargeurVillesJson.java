package chargement;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import json.LecteurJson;

import modele.Ville;

public class ChargeurVillesJson extends ChargeurCOR<List<Ville>> {
	@Override
	public boolean peutCharger(String cheminFichier) throws Exception {
		if (!cheminFichier.endsWith(".json")) {
			return false;
		}
		
		String contenu = Files.readString(Path.of(cheminFichier));
		
	     return contenu.contains("\"ville\"")
	    		&& contenu.contains("\"latitude\"")
	    		&& contenu.contains("\"longitude\"");
	}
	
	@Override
	protected List<Ville> chargerInterne(String cheminFichier) throws Exception {
		String tableau = LecteurJson.lireTableau(cheminFichier);
		String[] objets = LecteurJson.decouperObjets(tableau);
		
		List<Ville> villes = new ArrayList<>();
		
		for (String objet : objets) {
			Map<String, String> champs =
					LecteurJson.extraireChamps(objet);
			
			String nom = champs.get("ville");
			double latitude =
					Double.parseDouble(champs.get("latitude"));
			double longitude =
					Double.parseDouble(champs.get("longitude"));
			
			villes.add(new Ville(nom, latitude, longitude));
		}
		
		return villes;
	}
}
