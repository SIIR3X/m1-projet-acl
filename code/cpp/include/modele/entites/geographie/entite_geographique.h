#ifndef ENTITE_GEOGRAPHIQUE_H
#define ENTITE_GEOGRAPHIQUE_H

#include <string>

#include "modele/entites/entite.h"

class EntiteGeographique : public Entite
{
public:
    EntiteGeographique(const std::string& nom, double latitude, double longitude)
        : Entite(nom), _latitude(latitude), _longitude(longitude)
    {
    }

    double latitude() const
    {
        return _latitude;
    }

    double longitude() const
    {
        return _longitude;
    }

private:
    double _latitude;
    double _longitude;
};

#endif  // ENTITE_GEOGRAPHIQUE_H