#ifndef PARSEUR_REGISTRY_H
#define PARSEUR_REGISTRY_H

#include <functional>
#include <memory>

#include "serveur/requetes/parsers/parseur.h"

class RegistryParseur
{
public:
    using CreateFn = std::function<std::unique_ptr<Parseur>()>;

    static RegistryParseur& instance()
    {
        static RegistryParseur instance;
        return instance;
    }

    void enregistrer(const std::string& cle, std::function<std::unique_ptr<Parseur>()> fn)
    {
        _parseurs[cle] = std::move(fn);
    }

    std::unique_ptr<Parseur> get(const std::string& nom) const
    {
        return _parseurs.at(nom)();
    }

private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Parseur>()>> _parseurs;
};

#endif  // PARSEUR_REGISTRY_H