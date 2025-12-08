#ifndef DATA_BUILDER_REGISTRY_H
#define DATA_BUILDER_REGISTRY_H

#include <functional>
#include <memory>

#include "algorithmes/builders/data_builder.h"

class DataBuilderRegistry
{
public:
    using CreateFn = std::function<std::unique_ptr<DataBuilder>()>;

    static DataBuilderRegistry& instance()
    {
        static DataBuilderRegistry instance;
        return instance;
    }

    void enregistrer(const std::string& cle, std::function<std::unique_ptr<DataBuilder>()> fn)
    {
        _builders[cle] = std::move(fn);
    }

    std::unique_ptr<DataBuilder> get(const std::string& nom) const
    {
        return _builders.at(nom)();
    }

private:
    std::unordered_map<std::string, std::function<std::unique_ptr<DataBuilder>()>> _builders;
};

#endif  // DATA_BUILDER_REGISTRY_H