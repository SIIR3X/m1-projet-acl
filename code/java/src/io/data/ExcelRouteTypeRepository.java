package io.data;

import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

import model.City;
import model.RoadType;

// Pour utiliser -> rajouter un fichier de config Maven avec Apache POI pour lire les excel

public class ExcelRouteTypeRepository implements RouteTypeRepository 
{

	private final Map<RouteKey, RoadType> _routeTypes = new HashMap<>();

    public ExcelRouteTypeRepository(Path excelPath) 
    {
        load(excelPath);
    }

    private void load(Path path) 
    {
//        try (Workbook workbook = WorkbookFactory.create(path.toFile())) {
//            Sheet sheet = workbook.getSheetAt(0);
//
//            // 1. Lire les villes (ligne 0)
//            List<String> cities = new ArrayList<>();
//            Row header = sheet.getRow(0);
//            for (int col = 1; col < header.getLastCellNum(); col++) {
//                cities.add(header.getCell(col).getStringCellValue());
//            }
//
//            // 2. Lire la matrice (partie droite)
//            for (int i = 1; i <= cities.size(); i++) {
//                Row row = sheet.getRow(i);
//                String cityA = row.getCell(0).getStringCellValue();
//
//                for (int j = i + 1; j <= cities.size(); j++) {
//                    Cell cell = row.getCell(j);
//                    if (cell != null && cell.getCellType() == CellType.STRING) {
//                        RoadType type = RoadType.fromCode(cell.getStringCellValue());
//
//                        String cityB = cities.get(j - 1);
//                        routeTypes.put(new RouteKey(cityA, cityB), type);
//                        routeTypes.put(new RouteKey(cityB, cityA), type); // symétrie
//                    }
//                }
//            }
//
//        } catch (IOException e) {
//            throw new RuntimeException("Failed to load route types", e);
//        }
    }

    @Override
    public RoadType findType(City from, City to) 
    {
		return null;
//        return routeTypes.getOrDefault(
//            new RouteKey(from.getName(), to.getName()),
//            RoadType.LOCAL
//        );
    }

}
