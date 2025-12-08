#ifndef PARSEUR_H
#define PARSEUR_H

#include <any>
#include <string>

class Parseur
{
public:
    virtual ~Parseur() = default;

    virtual std::any parser(const std::string& json) const = 0;
};

#endif  // PARSEUR_H