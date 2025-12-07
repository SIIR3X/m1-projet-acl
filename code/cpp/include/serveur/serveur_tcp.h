#ifndef SERVEUR_TCP_H
#define SERVEUR_TCP_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "serveur/requetes/handlers/requete_handler_factory.h"
#include "utils/json_parser_utils.h"

/**
 * @enum NiveauLog
 * @brief Les différents niveaux possibles de log pour le serveur.
 */
enum class NiveauLog
{
    INFO,
    ERREUR,
    DEBUG,
    WARNING
};

class ServeurTCP
{
public:
    /**
     * @brief Constructeur principal.
     * @param ip L'ip d'écoute du serveur.
     * @param port Le port d'écoute du serveur.
     */
    ServeurTCP(const std::string& ip, int port)
        : _ip(ip),
          _port(port),
          _serveurEstActif(false),
          _compteurClients(0),
          _socketServeur(-1),
          _requeteHandler(RequeteHandlerFactory::creer())
    {
    }

    /**
     * @brief Destructeur.
     */
    ~ServeurTCP()
    {
        arreter();
    }

    /**
     * @brief Démarre le serveur.
     */
    void demarrer();

    /**
     * @brief Arrête le serveur.
     */
    void arreter();

private:
    std::string _ip;                                   ///< L'adresse IP d'écoute du serveur.
    int _port;                                         ///< Le port d'écoute du serveur.
    int _socketServeur;                                ///< Le socket principal du serveur.
    std::atomic<bool> _serveurEstActif;                ///< État du serveur.
    std::atomic<int> _compteurClients;                 ///< Le compteur de clients.
    std::vector<std::thread> _threadsClients;          ///< Threads des différents clients
    std::mutex _mutexCout;                             ///< Mutex (verrou)
    std::shared_ptr<IRequeteHandler> _requeteHandler;  ///< La tête de la chaîne COR des handlers de requêtes.

    /**
     * @brief Boucle du serveur.
     */
    void boucleServeur();

    /**
     * @brief Thread de gestion d'un client.
     * @param socketClient Le socket du client à gérer.
     * @param idClient L'id du client.
     */
    void gererClient(int socketClient, int idClient);

    /**
     * @brief Traite une requête envoyée par un client.
     * @param requete La requête du client
     * @return La réponse du serveur.
     */
    std::string traiterRequete(const std::string& requete);

    /**
     * @brief Affiche un message sur le serveur (protégé)
     * @param message Le message à afficher.
     */
    void log(NiveauLog niveau, const std::string& message, int idClient = 0);
};

inline void ServeurTCP::boucleServeur()
{
    log(NiveauLog::INFO, "Serveur en attente de connexions...");

    while (_serveurEstActif)
    {
        // Essaye d'accepter un nouveau client
        int socketClient = accept(_socketServeur, nullptr, nullptr);

        if (!_serveurEstActif)
            break;

        if (socketClient < 0)
        {
            log(NiveauLog::ERREUR, "accept()");
            continue;
        }

        // Attribution d'un id de client unique
        int idClient = ++_compteurClients;

        log(NiveauLog::INFO, "Nouvelle connexion acceptée", idClient);

        // Essaye de lancer un thread gestion client
        try
        {
            _threadsClients.emplace_back(&ServeurTCP::gererClient, this, socketClient, idClient);
        }
        catch (const std::exception& e)
        {
            log(NiveauLog::ERREUR, std::string("Impossible de créer un thread : ") + e.what(), idClient);
            close(socketClient);
        }
    }
}

inline std::string ServeurTCP::traiterRequete(const std::string& requete)
{
    try
    {
        if (!_requeteHandler)
            return "{\"erreur\": \"Handler non initialisé\"}";

        // Extraction de la commande demandée
        std::string commande =
            JsonParserUtils::recupererObligatoire(requete, "commande", JsonParserUtils::extraireChampString);

        // Traitement de la requête via les handlers
        std::string reponse = _requeteHandler->traiter(commande, requete);

        return reponse;
    }
    catch (const std::exception& e)
    {
        std::string err = std::string("{\"erreur\": \"") + e.what() + "\"}";
        return err;
    }
    catch (...)
    {
        return "{\"erreur\": \"Erreur inconnue\"}";
    }
}

inline void ServeurTCP::log(NiveauLog niveau, const std::string& message, int idClient)
{
    static const std::unordered_map<NiveauLog, std::string> texteNiveau = {{NiveauLog::INFO, "INFO"},
                                                                           {NiveauLog::ERREUR, "ERREUR"},
                                                                           {NiveauLog::DEBUG, "DEBUG"},
                                                                           {NiveauLog::WARNING, "WARNING"}};

    std::lock_guard<std::mutex> verrou(_mutexCout);

    std::string prefix = "[" + texteNiveau.at(niveau) + "]";

    if (idClient > 0)
        std::cout << prefix << " Client #" << idClient << " : " << message << std::endl;
    else
        std::cout << prefix << " " << message << std::endl;
}

#endif  // SERVEUR_TCP_H