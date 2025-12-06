#ifndef REPONSE_HANDLER_FACTORY_H
#define REPONSE_HANDLER_FACTORY_H

#include "serveur/reponses/gestionnaires/reponse_tsp_handler.h"
#include "serveur/reponses/i_reponse_handler.h"

class ReponseHandlerFactory
{
public:
    static std::shared_ptr<IReponseHandler> creer()
    {
        auto tsp = std::make_shared<ReponseTSPHandler>();
        return tsp;
    }
};

#endif  // REPONSE_HANDLER_FACTORY_H