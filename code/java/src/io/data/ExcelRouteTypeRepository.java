package io.data;

import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

import modele.RoadType;
import modele.Ville;

/**
 * Implémentation prévue de RouteTypeRepository pour lire les types de routes
 * depuis un fichier Excel (basée sur Apache POI, non finalisée dans cette version).
 */
public class ExcelRouteTypeRepository implements RouteTypeRepository 
{
	private final Map<RouteKey, RoadType> _routeTypes = new HashMap<>();

    public ExcelRouteTypeRepository(Path excelPath) 
    {
        load(excelPath);
    }

    private void load(Path path) {
//        try (Workbook workbook = WorkbookFactory.create(path.toFile())) {
//            Sheet sheet = workbook.getSheetAt(0);
//
//            // 1. Lire les villes (ligne 0)
//            Row header = sheet.getRow(0);
//            if (header == null) {
//                throw new IllegalArgumentException("Ligne d'en-tête manquante dans le fichier Excel : " + path);
//            }
//
//            List<String> cities = new ArrayList<>();
//            // On commence en 1 pour ignorer la cellule (0,0)
//            for (int col = 1; col < header.getLastCellNum(); col++) {
//                Cell cell = header.getCell(col);
//                if (cell != null && cell.getCellType() == CellType.STRING) {
//                    String cityName = cell.getStringCellValue().trim();
//                    if (!cityName.isEmpty()) {
//                        cities.add(cityName);
//                    } else {
//                        cities.add(""); // garder l'indexation cohérente
//                    }
//                } else {
//                    cities.add("");
//                }
//            }
//
//            // 2. Lire la matrice (partie droite)
//            // On parcourt les lignes 1..n, en supposant qu'il y a autant de lignes que de villes
//            for (int i = 1; i <= cities.size(); i++) {
//                Row row = sheet.getRow(i);
//                if (row == null) {
//                    continue;
//                }
//
//                Cell cityACell = row.getCell(0);
//                if (cityACell == null || cityACell.getCellType() != CellType.STRING) {
//                    continue;
//                }
//
//                String cityA = cityACell.getStringCellValue().trim();
//                if (cityA.isEmpty()) {
//                    continue;
//                }
//
//                // j démarre à i pour éviter de traiter deux fois (A,B) / (B,A)
//                for (int j = i; j <= cities.size(); j++) {
//                    Cell cell = row.getCell(j);
//                    if (cell == null || cell.getCellType() != CellType.STRING) {
//                        continue;
//                    }
//
//                    String raw = cell.getStringCellValue().trim();
//                    if (raw.isEmpty()) {
//                        continue;
//                    }
//
//                    // cityB est dans la liste header : index j-1
//                    String cityB = cities.get(j - 1);
//                    if (cityB == null || cityB.isEmpty()) {
//                        continue;
//                    }
//
//                    // Convertir le texte (label) en RoadType
//                    RoadType type = RoadType.fromLabel(raw);
//
//                    // Stocker les deux sens avec une RouteKey normalisée
//                    RouteKey keyAB = new RouteKey(cityA, cityB);
//                    RouteKey keyBA = new RouteKey(cityB, cityA);
//                    _routeTypes.put(keyAB, type);
//                    _routeTypes.put(keyBA, type); // symétrie
//                }
//            }
//
//        } catch (IOException e) {
//            throw new RuntimeException("Erreur lors de la lecture du fichier Excel : " + path, e);
//        }
    }

    @Override
    public RoadType findType(Ville from, Ville to) {
        if (from == null || to == null) {
            return null;
        }
        return _routeTypes.get(new RouteKey(from.toString(), to.toString()));
    }
}
