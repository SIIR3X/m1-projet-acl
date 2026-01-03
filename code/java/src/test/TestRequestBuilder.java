package test;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;

import request.*;

public class TestRequestBuilder
{
	public static void main(String[] args)
	{
    // ajoute le(s) fichier(s)
    Path filePath = Paths.get("data/13_fichiers_JSON/GrandEst.json");
    List<Path> paths = new ArrayList<>();
    paths.add(filePath);

		TypeTraitement cmd = TypeTraitement.ALGO_DISTANCE;
    HashMap<String,String> parameters = new HashMap<>();
		RequestBuilderRegistry registry = new RequestBuilderRegistry();
		String request = registry.get(cmd).build(cmd, parameters, paths);
		System.out.println(request);
	}
}
