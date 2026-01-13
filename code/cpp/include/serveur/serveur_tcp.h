#ifndef SERVEUR_TCP_H
#define SERVEUR_TCP_H

#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "factories/requete_handler_factory.h"
#include "serveur/requetes/handlers/requete_handler.h"
#include "utils/json_parser_utils.h"

// Sockets (portable)
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")

    using socket_t = SOCKET;
    static constexpr socket_t INVALID_SOCKET_FD = INVALID_SOCKET;

    inline int socket_close(socket_t s) { return ::closesocket(s); }

#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>

    using socket_t = int;
    static constexpr socket_t INVALID_SOCKET_FD = -1;

    inline int socket_close(socket_t s) { return ::close(s); }
#endif

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
          _socketServeur(INVALID_SOCKET_FD),
          _serveurEstActif(false),
          _compteurClients(0),
          _requeteHandler(RequeteHandlerFactory::chaine())
    {
    }

    /**
     * @brief Destructeur.
     */
    ~ServeurTCP() { arreter(); }

    /**
     * @brief Démarre le serveur.
     */
    void demarrer();

    /**
     * @brief Arrête le serveur.
     */
    void arreter();

private:
    std::string _ip;                                  ///< L'adresse IP d'écoute du serveur.
    int _port;                                        ///< Le port d'écoute du serveur.
    socket_t _socketServeur;                          ///< Le socket principal du serveur.
    std::atomic<bool> _serveurEstActif;               ///< État du serveur.
    std::atomic<int> _compteurClients;                ///< Le compteur de clients.
    std::vector<std::thread> _threadsClients;         ///< Threads des différents clients
    std::mutex _mutexCout;                            ///< Mutex (verrou)
    std::shared_ptr<RequeteHandler> _requeteHandler;  ///< Tête de la chaîne COR des handlers de requêtes.

    // Init/cleanup sockets (Windows seulement)
    void initSockets();
    void cleanupSockets();

    /**
     * @brief Boucle du serveur.
     */
    void boucleServeur();

    /**
     * @brief Thread de gestion d'un client.
     * @param socketClient Le socket du client à gérer.
     * @param idClient L'id du client.
     */
    void gererClient(socket_t socketClient, int idClient);

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

inline void ServeurTCP::initSockets()
{
#ifdef _WIN32
    WSADATA wsa{};
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        throw std::runtime_error("WSAStartup() a échoué");
#endif
}

inline void ServeurTCP::cleanupSockets()
{
#ifdef _WIN32
    WSACleanup();
#endif
}

inline void ServeurTCP::boucleServeur()
{
    log(NiveauLog::INFO, "Serveur en attente de connexions...");

    while (_serveurEstActif)
    {
        socket_t socketClient = ::accept(_socketServeur, nullptr, nullptr);

        if (!_serveurEstActif)
            break;

        if (socketClient == INVALID_SOCKET_FD)
        {
            log(NiveauLog::ERREUR, "accept()");
            continue;
        }

        int idClient = ++_compteurClients;
        log(NiveauLog::INFO, "Nouvelle connexion acceptée", idClient);

        try
        {
            _threadsClients.emplace_back(&ServeurTCP::gererClient, this, socketClient, idClient);
        }
        catch (const std::exception& e)
        {
            log(NiveauLog::ERREUR, std::string("Impossible de créer un thread : ") + e.what(), idClient);
            socket_close(socketClient);
        }
    }
}

inline std::string ServeurTCP::traiterRequete(const std::string& requete)
{
    try
    {
        if (!_requeteHandler)
            return "{\"erreur\": \"Handler non initialisé\"}";

        std::string commande =
            JsonParserUtils::recupererObligatoire(requete, "commande", JsonParserUtils::extraireChampString);

        std::optional<std::string> reponse = _requeteHandler->traiter(commande, requete);

        return reponse.value_or("{\"erreur\": \"Aucun handler n'a pu traiter la requête\"}");
    }
    catch (const std::exception& e)
    {
        return std::string("{\"erreur\": \"") + e.what() + "\"}";
    }
    catch (...)
    {
        return "{\"erreur\": \"Erreur inconnue\"}";
    }
}

inline void ServeurTCP::log(NiveauLog niveau, const std::string& message, int idClient)
{
    static const std::unordered_map<NiveauLog, std::string> texteNiveau = {
        {NiveauLog::INFO, "INFO"},
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
