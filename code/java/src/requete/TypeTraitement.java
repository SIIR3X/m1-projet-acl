package requete;

/* enumeration des types de traitement a effectuer avec leur classe analogue */
public enum TypeTraitement
{
	/* constante, appel au constructeur, stock leur classe correspondante */
	ALGO_DISTANCE(AlgoDistanceRequeteBuilder.class);
	// exemple : ALGO_TEMPS(AlgoTempsRequestBuilder.class);

	/* stocker uniquement les classes qui derivent de RequestBuilder par constante */
	final Class<? extends RequeteBuilder> _builderClass;

	/* ce constructeur est appele une fois par constante, chaque constante a son champ _builderClass et donc sa classe associe */
	TypeTraitement(Class<? extends RequeteBuilder> builderClass)
	{
		this._builderClass = builderClass;
	}
}