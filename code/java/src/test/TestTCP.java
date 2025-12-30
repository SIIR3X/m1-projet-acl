package ma_partie_acl;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.CountDownLatch;

public class TestTCP {

    public static void main(String[] args) throws Exception {
        final int port = 12345;
        final CountDownLatch serverReady = new CountDownLatch(1);

        // server thread
        Thread serverThread = new Thread(() -> {
            try (ServerSocket server = new ServerSocket(port)) {
                serverReady.countDown();
                try (Socket s = server.accept();
                     BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream(), StandardCharsets.UTF_8));
                     PrintWriter out = new PrintWriter(s.getOutputStream(), true)) {

                    String line = in.readLine();
                    out.println(line);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
        serverThread.start();
        serverReady.await();

        // test du client
        ClientTCP client = new ClientTCP("127.0.0.1", port);
        client.connect();

        String m = "hello\n"; // sans le \n, boucle infinie, utilisation prevue pour recevoir des fichiers
        System.out.println("Client send: "+m);
        client.write(m);
        String resp = client.read();
        System.out.println("Server replied: " + resp);

        client.close();
        serverThread.join();
    }
}
