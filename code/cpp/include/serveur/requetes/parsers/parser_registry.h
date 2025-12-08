#ifndef PARSER_REGISTRY_H
#define PARSER_REGISTRY_H

#include <functional>
#include <memory>

#include "serveur/requetes/parsers/parser.h"

class ParserRegistry
{
public:
    using CreateFn = std::function<std::unique_ptr<Parser>()>;

    static ParserRegistry& instance()
    {
        static ParserRegistry instance;
        return instance;
    }

    void enregistrer(const std::string& cle, std::function<std::unique_ptr<Parser>()> fn)
    {
        _parseurs[cle] = std::move(fn);
    }

    std::unique_ptr<Parser> get(const std::string& nom) const
    {
        return _parseurs.at(nom)();
    }

private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Parser>()>> _parseurs;
};

#endif  // PARSER_REGISTRY_H