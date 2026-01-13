package service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import integration.AffectationVille;
import modele.EntiteGeographique;
import modele.Ville;

public class RegroupeurParCamion {
    public static <T extends EntiteGeographique>
    Map<Integer, List<T>> regrouperParIdCamion(
            List<AffectationVille> affectations,
            List<T> toutesLesEntites
    ) {
        Map<Integer, List<T>> ensembles = new HashMap<>();

        for (AffectationVille a : affectations) {
            int camion = a.getCamion();
            int id = a.getIdVille();

            T entite = toutesLesEntites.get(id);

            ensembles
                .computeIfAbsent(camion, k -> new ArrayList<>())
                .add(entite);
        }

        return ensembles;
    }

    public static Map<String, Ville> regrouperParNomCamion(
            List<AffectationVille> affectations,
            List<Ville> villes
    ) {
        Map<String, Ville> ensembles = new HashMap<>();

        for (AffectationVille a : affectations) {
        	Ville ville = villes.get(a.getIdVille());
        	
        	ensembles.put(ville.getNom(), ville);
        }

        return ensembles;
    }
}
