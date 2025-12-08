[← Retour au README](../../README.md)

# Documentation de la partie C++ (Ancienne)

## Cycle d'une requête

### 3.1. Réception de la requête

Le serveur reçoit une requête JSON depuis le client.
Le seul champ **obligatoire** est :

- `commande` : détermine le type de traitement à effectuer et permet de sélectionner le `RequeteHandler` approprié.

#### Exemple de requête minimale

```json
{
    "commande": "algo_distance"
}
```

#### Structure complète d'une requête pour exécuter un algorithme TSP

Une requête permettant d'exécuter un algorithme de distance (ex : TSP) peut contenir **un ou plusieurs ensembles** :


```json
{
    "commande": "algo_distance",
    "algo": "tsp",
    "entite": "ville",
    "distance": "geodesique",

    "ensembles": [
        {
            "machines": 1,
            "donnees": [
                { "ville": "Strasbourg", "latitude": 48.58, "longitude": 7.75 },
                { "ville": "Metz", "latitude": 49.12, "longitude": 6.17 },
                { "ville": "Nancy", "latitude": 48.69, "longitude": 6.18 }
            ]
        },
        {
            "machines": 3,
            "donnees": [
                { "ville": "Paris", "latitude": 48.85, "longitude": 2.35 },
                { "ville": "Lyon", "latitude": 45.75, "longitude": 4.85 },
                { "ville": "Dijon", "latitude": 47.32, "longitude": 5.04 }
            ]
        }
    ]
}
```

---

### 3.2. Traitement par le RequeteHandler

Le `RequeteHandler` responsable de la commande effectue les actions suivantes :

1. Extraction des champs JSON obligatoires (`algo`, `entite`, `distance`, `ensembles`).
2. Sélection du parseur d'entité et du parseur de distance via *ParserRegistry*.
3. Sélection du solveur via *SolutionHandler*.
4. Pour chaque ensemble du tableau `ensembles` :
    - extraction de `machines` et `donnees`.
    - construction des données algorithmiques via le parseur d’entité.
    - exécution du solveur correspondant (`algo`).
    - génération d’une réponse simple via un *ReponseHandler*.
5. Toutes les réponses simples sont ensuite :
   - soit renvoyées telles quelles si une seule existe
   - soit regroupées dans une réponse composée automatiquement gérée par `IReponse`
6. Le *RequeteHandler* retourne la réponse finale au serveur.

---

### 3.3. Exécution de l'algorithme

Le *SolveurHandler* sélectionne l'algorithme à utiliser (via le champ JSON `algo`, dans notre projet = TSP).
Il calcule la solution en utilisant les données préparées.

---

### 3.4. Renvoie de la réponse

Le serveur renvoie toujours un JSON contenant un tableau nommé `"reponse"`.

Ce tableau contient :

- une seule entrée si la requête contient un seul ensemble
- plusieurs entrées si plusieurs ensembles ont été fournis

#### Structure de la réponse JSON (type TSP)

Lorsqu'un algorithme de distance (type TSP) est exécuté sur les données fournies d ans la requête, le serveur renvoie
une réponse JSON contenant :

- `chemin` : l'ordre optimal des entités visitées.
- `distances` : les distances entre chaque étape du chemin.
- `distanceTotale` : la distance totale du parcours optimisé.

Voici un exemple de réponse renvoyée par le serveur :

```json
{
    "reponse": [
        {
            "chemin": ["Strasbourg", "Nancy", "Metz"],
            "distances": ["116", "130"],
            "distanceTotale": "246"
        },
        {
            "chemin": ["Paris", "Lyon", "Dijon"],
            "distances": ["392", "195"],
            "distanceTotale": "588"
        }
    ]
}
```

---

### 3.5. Diagramme de séquence

![Diagramme du cycle d'une requête](../images/diagramme_sequence_requete.png)
