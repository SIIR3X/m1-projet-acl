package client;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;

public class ClientTCP
{
	private final InetSocketAddress _endpoint;
	private Socket _socket;
	private InputStream _inputStream;
	private OutputStream _outputStream;
	private static final int _timeout = 5000; /* en ms, pour connect */

	/* constructeur de ClientTCP */
	public ClientTCP(String adresse, int port) throws UnknownHostException, IOException
	{
		this._endpoint = new InetSocketAddress(adresse, port);
		this._socket = new Socket();
	}

	/* le socket se connecte au serveur */
	public void connect() throws IOException
	{
		this._socket.connect(this._endpoint, ClientTCP._timeout);
		this._inputStream = this._socket.getInputStream();
		this._outputStream = this._socket.getOutputStream();
	}

	/* on recoit du serveur */
	public String read() throws IOException
	{
		byte[] all = this._inputStream.readAllBytes(); // jusqu'a eof
		return new String(all, StandardCharsets.UTF_8);
	}

	/* on envoie au serveur */
	public void write(String data) throws IOException
	{
		this._outputStream.write(data.getBytes(StandardCharsets.UTF_8));
		this._outputStream.flush();
	 	_socket.shutdownOutput();
	}

	/* fermeture du socket et des flux d'entrees sorties */
	public void close() throws IOException
	{
		// this._inputStream.close();
		// this._outputStream.close();
		this._socket.close(); // ferme aussi les flux io
	}
	
	/* getter address (InetAddress) */
	public InetAddress getInetAddress()
	{
		return this._socket.getInetAddress();
	}

	/* getter address (String) */
	public String getStringAddress()
	{
		return this._socket.getInetAddress().toString();
	}
	
	/* getter port (int) */
	public int getPort()
	{
		return this._socket.getPort();
	}
}