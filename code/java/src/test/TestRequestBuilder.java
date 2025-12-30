package ma_partie_acl;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class TestRequestBuilder {

	public static void main(String[] args)
	{
		// ajoute le(s) fichier(s)
        Path filePath = Paths.get("test.json");
        List<Path> paths = new ArrayList<>();
        paths.add(filePath);

		TypeTraitement cmd = TypeTraitement.ALGO_DISTANCE;
		RequestBuilderRegistry registry = new RequestBuilderRegistry();
		String request = registry.get(cmd).build(cmd, paths);
		System.out.println(request);
	}
}
