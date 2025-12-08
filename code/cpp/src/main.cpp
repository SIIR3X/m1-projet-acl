#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "serveur/requetes/handlers/requete_handler.h"

#include "factories/registry.h"
#include "factories/requete_handler_factory.h"

#include "types/requete.h"

#include "utils/json_parser_utils.h"

int main(int argc, char *argv[])
{
    auto debut = std::chrono::high_resolution_clock::now();

    Registry::enregistrerTout();

    std::shared_ptr<RequeteHandler> requeteHandler = RequeteHandlerFactory::chaine();
    if (!requeteHandler)
        return 1;

    std::string commande =
        JsonParserUtils::recupererObligatoire(REQUETE, "commande", JsonParserUtils::extraireChampString);

    std::optional<std::string> reponse = requeteHandler->traiter(commande, REQUETE);

    std::cout << "Commande : " << commande << std::endl;

    if (reponse)
        std::cout << reponse.value() << std::endl;

    auto fin = std::chrono::high_resolution_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Temps d'exécution : " << duree.count() << " ms" << std::endl;

    return 0;
}