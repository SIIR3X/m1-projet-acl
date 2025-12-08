#ifndef GRAPHE_BUILDER_HANDLER_FACTORY_H
#define GRAPHE_BUILDER_HANDLER_FACTORY_H

#include <memory>

#include "algorithmes/builders/graphe/graphe_builder_handler_cor.h"
#include "algorithmes/builders/graphe/graphe_builder_handler_double.h"

class GrapheBuilderHandlerFactory
{
public:
    static std::shared_ptr<GrapheBuilderHandlerCOR> chaine()
    {
        static std::shared_ptr<GrapheBuilderHandlerCOR> instance = creerChaine();
        return instance;
    }

private:
    static std::shared_ptr<GrapheBuilderHandlerCOR> creerChaine();
};

inline std::shared_ptr<GrapheBuilderHandlerCOR> GrapheBuilderHandlerFactory::creerChaine()
{
    auto h1 = std::make_shared<GrapheBuilderHandlerDouble>();

    return h1;
}

#endif  // GRAPHE_BUILDER_HANDLER_H