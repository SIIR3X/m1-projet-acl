import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.io.IOException;

import request.*;
import client.*;

public class Main
{
  public static void main(String[] args)
  {
    // TEST
    // Parse un fichier, GrandEst par exemple
    Path filePath = Paths.get("data/13_fichiers_JSON/GrandEst.json");
    List<Path> paths = new ArrayList<>();
    paths.add(filePath);

    // Applique le traitement algo_distance et construit la requete
		TypeTraitement cmd = TypeTraitement.ALGO_DISTANCE;
		RequestBuilderRegistry registry = new RequestBuilderRegistry();
		String request = registry.get(cmd).build(cmd, paths);

    // Envoie la requete au server
    try
    {
      ClientTCP client = new ClientTCP("127.0.0.1", 8080);
      try
      {
        client.connect();
        client.write(request);
        String response = client.read();
      }
      finally
      {
        client.close();
      }
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }
  }
}
