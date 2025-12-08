#ifndef VILLE_H
#define VILLE_H

#include "modele/entites/geographie/entite_geographique.h"

class Ville : public EntiteGeographique
{
public:
    Ville(const std::string& nom, double latitude, double longitude) : EntiteGeographique(nom, latitude, longitude) {}

    operator std::string() const override
    {
        return nom() + " (" + std::to_string(latitude()) + ", " + std::to_string(longitude()) + ")";
    }
};

#endif  // VILLE_H