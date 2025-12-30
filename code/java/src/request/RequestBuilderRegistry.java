package ma_partie_acl;

import java.util.EnumMap;

public final class RequestBuilderRegistry
{
	private final EnumMap<TypeTraitement, RequestBuilder> builders = new EnumMap<>(TypeTraitement.class);
	
	public RequestBuilderRegistry()
	{
		for (TypeTraitement commande: TypeTraitement.values())
		{
			// ajoue des objets (RequestBuilder) par reflection dans l'enummap
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
	
	public RequestBuilder get(TypeTraitement commande)
	{
		RequestBuilder tt = builders.get(commande);
		if (tt == null)
		{
			throw new IllegalArgumentException("Pas de builder pour le type de traitement : "+commande);
		}
		return tt;
	}
}
/* utilisation : RequestBuilderRegistry registry; req = registry.get(cmd.type()).build(cmd) */
