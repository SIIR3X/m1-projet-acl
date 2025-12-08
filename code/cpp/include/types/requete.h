#ifndef REQUETE_H
#define REQUETE_H

#include <string>

static const std::string REQUETE = R"json(
{
  "commande": "algo_distance",
  "algo": "tsp",
  "entite": "ville",
  "distance": "geodesique",
  "ensembles": [
    {
      "machines": 1,
      "donnees":
[
	{"ville": "Lyon", "latitude": 45.76, "longitude": 4.84},
	{"ville": "Grenoble", "latitude": 45.19, "longitude": 5.74},
	{"ville": "Saint-Étienne", "latitude": 45.44, "longitude": 4.39},
	{"ville": "Clermont-Ferrand", "latitude": 45.78, "longitude": 3.08},
	{"ville": "Villeurbanne", "latitude": 45.77, "longitude": 4.88},
	{"ville": "Annecy", "latitude": 45.90, "longitude": 6.13},
	{"ville": "Chambéry", "latitude": 45.56, "longitude": 5.92},
	{"ville": "Valence", "latitude": 44.93, "longitude": 4.89},
	{"ville": "Vienne", "latitude": 45.52, "longitude": 4.88},
	{"ville": "Bourg-en-Bresse", "latitude": 46.21, "longitude": 5.22},
	{"ville": "Montélimar", "latitude": 44.56, "longitude": 4.75},
	{"ville": "Roanne", "latitude": 46.03, "longitude": 4.08},
	{"ville": "Annemasse", "latitude": 46.19, "longitude": 6.24},
	{"ville": "Aix-les-Bains", "latitude": 45.69, "longitude": 5.92},
	{"ville": "Thonon-les-Bains", "latitude": 46.37, "longitude": 6.48},
	{"ville": "Le Puy-en-Velay", "latitude": 45.04, "longitude": 3.89},
	{"ville": "Aurillac", "latitude": 44.92, "longitude": 2.44},
	{"ville": "Albertville", "latitude": 45.67, "longitude": 6.39},
	{"ville": "Villefranche-sur-Saône", "latitude": 45.98, "longitude": 4.72}
]
    },

    {
      "machines": 1,
      "donnees":
[
  {"ville": "Dijon", "latitude": 47.32, "longitude": 5.04},
  {"ville": "Besançon", "latitude": 47.24, "longitude": 6.02},
  {"ville": "Belfort", "latitude": 47.64, "longitude": 6.85},
  {"ville": "Chalon-sur-Saône", "latitude": 46.78, "longitude": 4.85},
  {"ville": "Auxerre", "latitude": 47.80, "longitude": 3.57},
  {"ville": "Nevers", "latitude": 46.99, "longitude": 3.16},
  {"ville": "Mâcon", "latitude": 46.32, "longitude": 4.83},
  {"ville": "Sens", "latitude": 48.20, "longitude": 3.27},
  {"ville": "Montbéliard", "latitude": 47.51, "longitude": 6.80},
  {"ville": "Dole", "latitude": 47.09, "longitude": 5.49},
  {"ville": "Le Creusot", "latitude": 46.81, "longitude": 4.45},
  {"ville": "Beaune", "latitude": 47.02, "longitude": 4.84},
  {"ville": "Montceau-les-Mines", "latitude": 46.70, "longitude": 4.39},
  {"ville": "Lons-le-Saunier", "latitude": 46.67, "longitude": 5.55},
  {"ville": "Pontarlier", "latitude": 46.91, "longitude": 6.33},
  {"ville": "Vesoul", "latitude": 47.62, "longitude": 6.16},
  {"ville": "Chenôve", "latitude": 47.29, "longitude": 5.03},
  {"ville": "Audincourt", "latitude": 47.48, "longitude": 6.85},
  {"ville": "Autun", "latitude": 46.95, "longitude": 4.29},
  {"ville": "Talant", "latitude": 47.32, "longitude": 5.06}
]
    },

    {
      "machines": 1,
      "donnees":
[
  {"ville": "Rennes", "latitude": 48.11, "longitude": -1.68},
  {"ville": "Brest", "latitude": 48.39, "longitude": -4.50},
  {"ville": "Quimper", "latitude": 47.99, "longitude": -4.11},
  {"ville": "Lorient", "latitude": 47.75, "longitude": -3.36},
  {"ville": "Vannes", "latitude": 47.66, "longitude": -2.76},
  {"ville": "Saint-Malo", "latitude": 48.65, "longitude": -2.02},
  {"ville": "Dinan", "latitude": 48.45, "longitude": -2.04},
  {"ville": "Fougères", "latitude": 48.35, "longitude": -1.20},
  {"ville": "Redon", "latitude": 47.65, "longitude": -2.08},
  {"ville": "Châteaulin", "latitude": 48.20, "longitude": -4.09},
  {"ville": "Lanester", "latitude": 47.77, "longitude": -3.34},
  {"ville": "Pontivy", "latitude": 48.05, "longitude": -2.98},
  {"ville": "Morlaix", "latitude": 48.59, "longitude": -3.83},
  {"ville": "Ploufragan", "latitude": 48.52, "longitude": -2.76},
  {"ville": "Saint-Pol-de-Léon", "latitude": 48.69, "longitude": -3.99},
  {"ville": "Carhaix-Plouguer", "latitude": 48.28, "longitude": -3.57},
  {"ville": "Guingamp", "latitude": 48.56, "longitude": -3.15}
]
    },

    {
      "machines": 1,
      "donnees":
[
  {"ville": "Tours", "latitude": 47.39, "longitude": 0.68},
  {"ville": "Orléans", "latitude": 47.90, "longitude": 1.91},
  {"ville": "Blois", "latitude": 47.59, "longitude": 1.34},
  {"ville": "Chartres", "latitude": 48.45, "longitude": 1.49},
  {"ville": "Bourges", "latitude": 47.08, "longitude": 2.40},
  {"ville": "Châteauroux", "latitude": 46.81, "longitude": 1.70},
  {"ville": "Vierzon", "latitude": 47.23, "longitude": 2.07},
  {"ville": "Issoudun", "latitude": 46.95, "longitude": 1.99},
  {"ville": "Dreux", "latitude": 48.73, "longitude": 1.37},
  {"ville": "Saint-Amand-Montrond", "latitude": 46.72, "longitude": 2.51},
  {"ville": "Romorantin-Lanthenay", "latitude": 47.36, "longitude": 1.75},
  {"ville": "Gien", "latitude": 47.68, "longitude": 2.63},
  {"ville": "Montargis", "latitude": 47.99, "longitude": 2.73},
  {"ville": "Vendôme", "latitude": 47.80, "longitude": 1.06},
  {"ville": "Amboise", "latitude": 47.41, "longitude": 0.98},
  {"ville": "Loches", "latitude": 47.13, "longitude": 0.99},
  {"ville": "Chinon", "latitude": 47.17, "longitude": 0.24},
  {"ville": "Sully-sur-Loire", "latitude": 47.77, "longitude": 2.38},
  {"ville": "Nogent-le-Rotrou", "latitude": 48.32, "longitude": 0.83}
]
    },

    {
      "machines": 1,
      "donnees":
[
  {"ville": "Ajaccio", "latitude": 41.93, "longitude": 8.74},
  {"ville": "Bastia", "latitude": 42.70, "longitude": 9.45},
  {"ville": "Corte", "latitude": 42.31, "longitude": 9.10},
  {"ville": "Sartène", "latitude": 41.62, "longitude": 8.97},
  {"ville": "Propriano", "latitude": 41.68, "longitude": 8.90},
  {"ville": "Calvi", "latitude": 42.57, "longitude": 8.76},
  {"ville": "Borgo", "latitude": 42.57, "longitude": 9.38},
  {"ville": "Vico", "latitude": 42.24, "longitude": 9.29},
  {"ville": "Piedicroce", "latitude": 42.27, "longitude": 9.35},
  {"ville": "Morosaglia", "latitude": 42.45, "longitude": 9.30},
  {"ville": "Zicavo", "latitude": 41.88, "longitude": 9.05},
  {"ville": "Ghisonaccia", "latitude": 42.02, "longitude": 9.40},
  {"ville": "Cervione", "latitude": 42.34, "longitude": 9.42},
  {"ville": "L'Île-Rousse", "latitude": 42.64, "longitude": 8.94},
  {"ville": "Sisco", "latitude": 42.63, "longitude": 9.36},
  {"ville": "Moltifao", "latitude": 42.48, "longitude": 9.24},
  {"ville": "Poggio-di-Nazza", "latitude": 42.05, "longitude": 9.28}
]
    },

    {
      "machines": 1,
      "donnees":
[
  { "ville": "Strasbourg", "latitude": 48.58, "longitude": 7.75 },
  { "ville": "Reims", "latitude": 49.26, "longitude": 4.03 },
  { "ville": "Metz", "latitude": 49.12, "longitude": 6.17 },
  { "ville": "Mulhouse", "latitude": 47.75, "longitude": 7.34 },
  { "ville": "Nancy", "latitude": 48.69, "longitude": 6.18 },
  { "ville": "Colmar", "latitude": 48.08, "longitude": 7.36 },
  { "ville": "Troyes", "latitude": 48.30, "longitude": 4.08 },
  { "ville": "Charleville-Mézières", "latitude": 49.77, "longitude": 4.72 },
  { "ville": "Châlons-en-Champagne", "latitude": 48.96, "longitude": 4.36 },
  { "ville": "Thionville", "latitude": 49.36, "longitude": 6.17 },
  { "ville": "Épinal", "latitude": 48.18, "longitude": 6.45 },
  { "ville": "Haguenau", "latitude": 48.82, "longitude": 7.78 },
  { "ville": "Sarrebourg", "latitude": 48.73, "longitude": 7.05 },
  { "ville": "Sarreguemines", "latitude": 49.11, "longitude": 7.07 },
  { "ville": "Saint-Dié-des-Vosges", "latitude": 48.28, "longitude": 6.95 },
  { "ville": "Verdun", "latitude": 49.16, "longitude": 5.38 },
  { "ville": "Vesoul", "latitude": 47.62, "longitude": 6.15 },
  { "ville": "Bar-le-Duc", "latitude": 48.77, "longitude": 5.16 },
  { "ville": "Briey", "latitude": 49.25, "longitude": 5.93 },
  { "ville": "Forbach", "latitude": 49.19, "longitude": 6.90 }
]
    },

    {
      "machines": 1,
      "donnees":
[
  { "ville": "Lille", "latitude": 50.63, "longitude": 3.07 },
  { "ville": "Roubaix", "latitude": 50.69, "longitude": 3.17 },
  { "ville": "Dunkerque", "latitude": 51.03, "longitude": 2.37 },
  { "ville": "Valenciennes", "latitude": 50.36, "longitude": 3.52 },
  { "ville": "Amiens", "latitude": 49.89, "longitude": 2.30 },
  { "ville": "Tourcoing", "latitude": 50.72, "longitude": 3.16 },
  { "ville": "Douai", "latitude": 50.37, "longitude": 3.08 },
  { "ville": "Cambrai", "latitude": 50.18, "longitude": 3.24 },
  { "ville": "Saint-Quentin", "latitude": 49.84, "longitude": 3.29 },
  { "ville": "Béthune", "latitude": 50.53, "longitude": 2.64 },
  { "ville": "Arras", "latitude": 50.29, "longitude": 2.78 },
  { "ville": "Lens", "latitude": 50.43, "longitude": 2.83 },
  { "ville": "Laon", "latitude": 49.56, "longitude": 3.62 },
  { "ville": "Soissons", "latitude": 49.38, "longitude": 3.32 },
  { "ville": "Compiègne", "latitude": 49.41, "longitude": 2.82 },
  { "ville": "Creil", "latitude": 49.26, "longitude": 2.48 },
  { "ville": "Senlis", "latitude": 49.20, "longitude": 2.58 },
  { "ville": "Beauvais", "latitude": 49.43, "longitude": 2.09 },
  { "ville": "Château-Thierry", "latitude": 49.04, "longitude": 3.39 },
  { "ville": "Noyon", "latitude": 49.58, "longitude": 3.00 }
]
    },

    {
      "machines": 1,
      "donnees":
[
  {"ville": "Paris", "latitude": 48.86, "longitude": 2.35},
  {"ville": "Versailles", "latitude": 48.80, "longitude": 2.13},
  {"ville": "Boulogne-Billancourt", "latitude": 48.84, "longitude": 2.24},
  {"ville": "Saint-Denis", "latitude": 48.93, "longitude": 2.36},
  {"ville": "Nanterre", "latitude": 48.89, "longitude": 2.21},
  {"ville": "Créteil", "latitude": 48.79, "longitude": 2.46},
  {"ville": "Colombes", "latitude": 48.92, "longitude": 2.25},
  {"ville": "Aulnay-sous-Bois", "latitude": 48.94, "longitude": 2.50},
  {"ville": "Argenteuil", "latitude": 48.95, "longitude": 2.25},
  {"ville": "Asnières-sur-Seine", "latitude": 48.91, "longitude": 2.29},
  {"ville": "Montreuil", "latitude": 48.86, "longitude": 2.44},
  {"ville": "Levallois-Perret", "latitude": 48.89, "longitude": 2.28},
  {"ville": "Antony", "latitude": 48.75, "longitude": 2.30},
  {"ville": "Cergy", "latitude": 49.03, "longitude": 2.06},
  {"ville": "Poissy", "latitude": 48.93, "longitude": 2.04}
]
    },

    {
      "machines": 1,
      "donnees":
[
  { "ville": "Le Havre", "latitude": 49.49, "longitude": 0.10 },
  { "ville": "Rouen", "latitude": 49.44, "longitude": 1.10 },
  { "ville": "Caen", "latitude": 49.18, "longitude": -0.37 },
  { "ville": "Cherbourg-en-Cotentin", "latitude": 49.64, "longitude": -1.62 },
  { "ville": "Évreux", "latitude": 49.02, "longitude": 1.15 },
  { "ville": "Sotteville-lès-Rouen", "latitude": 49.40, "longitude": 1.10 },
  { "ville": "Saint-Étienne-du-Rouvray", "latitude": 49.36, "longitude": 1.09 },
  { "ville": "Dieppe", "latitude": 49.93, "longitude": 1.08 },
  { "ville": "Le Grand-Quevilly", "latitude": 49.39, "longitude": 1.03 },
  { "ville": "Alençon", "latitude": 48.43, "longitude": 0.09 },
  { "ville": "Vernon", "latitude": 49.09, "longitude": 1.47 },
  { "ville": "Hérouville-Saint-Clair", "latitude": 49.20, "longitude": -0.32 },
  { "ville": "Le Petit-Quevilly", "latitude": 49.42, "longitude": 1.05 },
  { "ville": "Mont-Saint-Aignan", "latitude": 49.46, "longitude": 1.08 },
  { "ville": "Lisieux", "latitude": 49.14, "longitude": 0.22 },
  { "ville": "Saint-Lô", "latitude": 49.12, "longitude": -1.09 },
  { "ville": "Louviers", "latitude": 49.21, "longitude": 1.17 },
  { "ville": "Fécamp", "latitude": 49.76, "longitude": 0.38 },
  { "ville": "Vire Normandie", "latitude": 48.84, "longitude": -0.89 },
  { "ville": "Elbeuf", "latitude": 49.29, "longitude": 1.00 }
]
    },

    {
      "machines": 1,
      "donnees":
[
  { "ville": "Bordeaux", "latitude": 44.84, "longitude": -0.58 },
  { "ville": "Limoges", "latitude": 45.85, "longitude": 1.26 },
  { "ville": "Poitiers", "latitude": 46.58, "longitude": 0.34 },
  { "ville": "Pau", "latitude": 43.30, "longitude": -0.36 },
  { "ville": "La Rochelle", "latitude": 46.16, "longitude": -1.15 },
  { "ville": "Angoulême", "latitude": 45.65, "longitude": 0.16 },
  { "ville": "Niort", "latitude": 46.33, "longitude": -0.46 },
  { "ville": "Bayonne", "latitude": 43.49, "longitude": -1.48 },
  { "ville": "Brive-la-Gaillarde", "latitude": 45.16, "longitude": 1.53 },
  { "ville": "Talence", "latitude": 44.80, "longitude": -0.58 },
  { "ville": "Mérignac", "latitude": 44.83, "longitude": -0.62 },
  { "ville": "Pessac", "latitude": 44.82, "longitude": -0.66 },
  { "ville": "Villenave-d'Ornon", "latitude": 44.79, "longitude": -0.60 },
  { "ville": "Arcachon", "latitude": 44.65, "longitude": -1.17 },
  { "ville": "Biarritz", "latitude": 43.48, "longitude": -1.55 },
  { "ville": "Royan", "latitude": 45.63, "longitude": -1.02 },
  { "ville": "Libourne", "latitude": 44.92, "longitude": -0.24 },
  { "ville": "Dax", "latitude": 43.71, "longitude": -1.05 },
  { "ville": "Mont-de-Marsan", "latitude": 43.89, "longitude": -0.50 },
  { "ville": "Agen", "latitude": 44.20, "longitude": 0.62 }
]
    },

    {
      "machines": 1,
      "donnees":
[
  { "ville": "Bordeaux", "latitude": 44.84, "longitude": -0.58 },
  { "ville": "Limoges", "latitude": 45.85, "longitude": 1.26 },
  { "ville": "Poitiers", "latitude": 46.58, "longitude": 0.34 },
  { "ville": "Pau", "latitude": 43.30, "longitude": -0.36 },
  { "ville": "La Rochelle", "latitude": 46.16, "longitude": -1.15 },
  { "ville": "Angoulême", "latitude": 45.65, "longitude": 0.16 },
  { "ville": "Niort", "latitude": 46.33, "longitude": -0.46 },
  { "ville": "Bayonne", "latitude": 43.49, "longitude": -1.48 },
  { "ville": "Brive-la-Gaillarde", "latitude": 45.16, "longitude": 1.53 },
  { "ville": "Talence", "latitude": 44.80, "longitude": -0.58 },
  { "ville": "Mérignac", "latitude": 44.83, "longitude": -0.62 },
  { "ville": "Pessac", "latitude": 44.82, "longitude": -0.66 },
  { "ville": "Villenave-d'Ornon", "latitude": 44.79, "longitude": -0.60 },
  { "ville": "Arcachon", "latitude": 44.65, "longitude": -1.17 },
  { "ville": "Biarritz", "latitude": 43.48, "longitude": -1.55 },
  { "ville": "Royan", "latitude": 45.63, "longitude": -1.02 },
  { "ville": "Libourne", "latitude": 44.92, "longitude": -0.24 },
  { "ville": "Dax", "latitude": 43.71, "longitude": -1.05 },
  { "ville": "Mont-de-Marsan", "latitude": 43.89, "longitude": -0.50 },
  { "ville": "Agen", "latitude": 44.20, "longitude": 0.62 }
]
    },

    {
      "machines": 1,
      "donnees": [
        {"ville": "Nantes", "latitude": 47.22, "longitude": -1.55},
        {"ville": "Angers", "latitude": 47.47, "longitude": -0.55},
        {"ville": "Le Mans", "latitude": 48.00, "longitude": 0.20},
        {"ville": "Saint-Nazaire", "latitude": 47.28, "longitude": -2.21},
        {"ville": "La Roche-sur-Yon", "latitude": 46.67, "longitude": -1.43},
        {"ville": "Cholet", "latitude": 47.06, "longitude": -0.88},
        {"ville": "Laval", "latitude": 48.07, "longitude": -0.77},
        {"ville": "Sables-d'Olonne", "latitude": 46.50, "longitude": -1.78},
        {"ville": "Saumur", "latitude": 47.26, "longitude": -0.08},
        {"ville": "Fontenay-le-Comte", "latitude": 46.47, "longitude": -0.81},
        {"ville": "Châteaubriant", "latitude": 47.72, "longitude": -1.38},
        {"ville": "Les Herbiers", "latitude": 46.87, "longitude": -1.02},
        {"ville": "Beaucouzé", "latitude": 47.48, "longitude": -0.62},
        {"ville": "Saint-Berthevin", "latitude": 48.07, "longitude": -0.83},
        {"ville": "Pornic", "latitude": 47.11, "longitude": -2.10},
        {"ville": "Vertou", "latitude": 47.17, "longitude": -1.49},
        {"ville": "Mauges-sur-Loire", "latitude": 47.35, "longitude": -0.93},
        {"ville": "Treillières", "latitude": 47.32, "longitude": -1.61},
        {"ville": "Sainte-Luce-sur-Loire", "latitude": 47.26, "longitude": -1.51},
        {"ville": "Carquefou", "latitude": 47.28, "longitude": -1.49}
      ]
    },

    {
      "machines": 1,
      "donnees": [
        {"ville": "Marseille", "latitude": 43.30, "longitude": 5.37},
        {"ville": "Nice", "latitude": 43.70, "longitude": 7.27},
        {"ville": "Toulon", "latitude": 43.12, "longitude": 5.93},
        {"ville": "Aix-en-Provence", "latitude": 43.53, "longitude": 5.44},
        {"ville": "Avignon", "latitude": 43.95, "longitude": 4.81},
        {"ville": "Antibes", "latitude": 43.58, "longitude": 7.12},
        {"ville": "Cannes", "latitude": 43.55, "longitude": 7.02},
        {"ville": "Fréjus", "latitude": 43.43, "longitude": 6.74},
        {"ville": "Grasse", "latitude": 43.66, "longitude": 6.92},
        {"ville": "Arles", "latitude": 43.68, "longitude": 4.63},
        {"ville": "Martigues", "latitude": 43.40, "longitude": 5.05},
        {"ville": "Cagnes-sur-Mer", "latitude": 43.66, "longitude": 7.15},
        {"ville": "Draguignan", "latitude": 43.54, "longitude": 6.47},
        {"ville": "Manosque", "latitude": 43.83, "longitude": 5.79},
        {"ville": "Aubagne", "latitude": 43.29, "longitude": 5.57},
        {"ville": "Istres", "latitude": 43.51, "longitude": 4.98},
        {"ville": "Salon-de-Provence", "latitude": 43.64, "longitude": 5.10},
        {"ville": "Menton", "latitude": 43.78, "longitude": 7.50}
      ]
    }
  ]
}
)json";

#endif