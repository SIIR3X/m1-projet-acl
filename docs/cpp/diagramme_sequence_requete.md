sequenceDiagram
    participant Client
    participant Serveur
    participant RequeteHandler
    participant ParserRegistry
    participant SolveurHandler
    participant ReponseHandler

    Client->>Serveur: Envoie une requête JSON
    Serveur->>RequeteHandler: Transmet la requête

    RequeteHandler->>ParserRegistry: Parse la requête
    ParserRegistry-->>RequeteHandler: Renvoie les données préparées

    RequeteHandler->>SolveurHandler: Envoie les données préparées
    SolveurHandler-->>RequeteHandler: Renvoie la solution

    RequeteHandler->>ReponseHandler: Envoie la solution
    ReponseHandler-->>RequeteHandler: Renvoie la réponse finale

    RequeteHandler-->>Serveur: Transmet la réponse finale
    Serveur-->>Client: Retourne la réponse JSON