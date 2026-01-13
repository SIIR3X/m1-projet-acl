package integration;

public class AffectationVille {
	private final int _camion;
	private final int _idVille;
	
	public AffectationVille(int camion, int idVille) {
		this._camion = camion;
		this._idVille = idVille;
	}
	
	public int getCamion() {
		return _camion;
	}
	
	public int getIdVille() {
		return _idVille;
	}
}
