#ifndef ENTITE_H
#define ENTITE_H

#include <string>

class Entite
{
public:
    Entite(const std::string& nom) : _nom(nom) {}

    virtual ~Entite() = default;

    const std::string& nom() const
    {
        return _nom;
    }

    virtual operator std::string() const = 0;

private:
    std::string _nom;
};

#endif  // ENTITE_H