#ifndef GRAPHE_BUILDER_REGISTRY_H
#define GRAPHE_BUILDER_REGISTRY_H

#include <functional>
#include <memory>
#include <typeinfo>
#include <unordered_map>

#include "algorithmes/builders/graphe/graphe_builder.h"

class GrapheBuilderRegistry
{
public:
    using CreateFn = std::function<std::unique_ptr<GrapheBuilder>()>;

    static GrapheBuilderRegistry& instance()
    {
        static GrapheBuilderRegistry inst;
        return inst;
    }

    void enregistrer(const std::type_info& typeR, CreateFn fn)
    {
        _builders[typeR.hash_code()] = std::move(fn);
    }

    std::unique_ptr<GrapheBuilder> get(const std::type_info& typeR) const
    {
        auto iterateur = _builders.find(typeR.hash_code());
        if (iterateur == _builders.end())
            throw std::runtime_error("Aucun GrapheBuilder enregistré pour ce type de distance.");

        return iterateur->second();
    }

private:
    GrapheBuilderRegistry() = default;

    std::unordered_map<size_t, CreateFn> _builders;
};

#endif  // GRAPHE_BUILDER_REGISTRY_H