#include "serveur/reponses/types/algo_distance_reponse.h"

#include "utils/json_builder.h"

std::string AlgoDistanceReponse::toJson() const
{
    JsonBuilder jb;

    // Ajout du chemin
    jb.beginArray("chemin");
    for (const auto& chemin : _chemin) jb.addRawValue(chemin);
    jb.endArray();

    // Ajout des distances
    jb.beginArray("distances");
    for (const auto& distance : _distances) jb.addRawValue(distance);
    jb.endArray();

    // Ajout de la distance totale
    jb.addRaw("distanceTotale", _distanceTotale);

    return jb.build();
}