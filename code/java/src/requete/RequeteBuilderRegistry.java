package requete;

import java.util.EnumMap;

public final class RequeteBuilderRegistry
{
  /* lie les types de traitement a leur classe concrete */
	private final EnumMap<TypeTraitement, RequeteBuilder> builders = new EnumMap<>(TypeTraitement.class);
	
  /* construit l'enummap avec toutes les constantes dans TypeTraitement et leur classe associe */
	public RequeteBuilderRegistry()
	{
		for (TypeTraitement commande: TypeTraitement.values())
		{
			// ajout des objets (RequestBuilder) par reflection dans l'enummap
			try
			{
				builders.put(commande, commande._builderClass.getConstructor().newInstance());
			}
			catch (ReflectiveOperationException e)
			{
				throw new IllegalStateException("Builder invalide pour : "+commande, e);
			}
		}
	}
	
  /* obtient la classe concrete pour un TypeTraitement donne */
	public RequeteBuilder get(TypeTraitement commande)
	{
		RequeteBuilder tt = builders.get(commande);
		if (tt == null)
		{
			throw new IllegalArgumentException("Pas de builder pour le type de traitement : "+commande);
		}
		return tt;
	}
}
/* utilisation : req = registry.get(cmd.type()).build(cmd) */