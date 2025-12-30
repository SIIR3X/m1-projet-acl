#include "serveur/serveur_tcp.h"
#include "utils/debug_utils.h"

void ServeurTCP::demarrer()
{
    if (_serveurEstActif)
        return;

    initSockets();
    _serveurEstActif = true;

    _socketServeur = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socketServeur == INVALID_SOCKET_FD)
        ERREUR("demarrer", "socket()", true);

    // Réutilisation d'adresse
#ifdef _WIN32
    BOOL opt = TRUE;
    setsockopt(_socketServeur, SOL_SOCKET, SO_REUSEADDR,
               reinterpret_cast<const char*>(&opt), sizeof(opt));
#else
    int opt = 1;
    setsockopt(_socketServeur, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<uint16_t>(_port));

    if (::inet_pton(AF_INET, _ip.c_str(), &addr.sin_addr) <= 0)
    {
        socket_close(_socketServeur);
        ERREUR("demarrer", "inet_pton()", true);
    }

    if (::bind(_socketServeur,
               reinterpret_cast<sockaddr*>(&addr),
               sizeof(addr)) < 0)
    {
        socket_close(_socketServeur);
        ERREUR("demarrer", "bind()", true);
    }

    if (::listen(_socketServeur, SOMAXCONN) < 0)
    {
        socket_close(_socketServeur);
        ERREUR("demarrer", "listen()", true);
    }

    log(NiveauLog::INFO,
        "Serveur écoute sur " + _ip + ":" + std::to_string(_port));

    boucleServeur();
}

void ServeurTCP::arreter()
{
    if (!_serveurEstActif)
        return;

    _serveurEstActif = false;

    if (_socketServeur != INVALID_SOCKET_FD)
    {
        socket_close(_socketServeur);
        _socketServeur = INVALID_SOCKET_FD;
    }

    for (auto& thread : _threadsClients)
        if (thread.joinable())
            thread.join();

    _threadsClients.clear();
    cleanupSockets();
}

void ServeurTCP::gererClient(socket_t socketClient, int idClient)
{
    log(NiveauLog::INFO, "Client connecté", idClient);

    char buffer[2048];

#ifdef _WIN32
    int reception = recv(socketClient, buffer, sizeof(buffer) - 1, 0);
#else
    ssize_t reception = recv(socketClient, buffer, sizeof(buffer) - 1, 0);
#endif

    if (reception <= 0)
    {
        log(NiveauLog::ERREUR, "Échec de réception", idClient);
        socket_close(socketClient);
        return;
    }

    buffer[reception] = '\0';
    std::string requete(buffer);

    log(NiveauLog::INFO, "Requête reçue : " + requete, idClient);

    std::string reponse;
    try
    {
        reponse = traiterRequete(requete);
    }
    catch (const std::exception& e)
    {
        log(NiveauLog::ERREUR,
            std::string("Erreur traitement : ") + e.what(),
            idClient);
        socket_close(socketClient);
        return;
    }

    int envoi = send(socketClient,
                     reponse.c_str(),
                     static_cast<int>(reponse.size()),
                     0);

    if (envoi < 0)
    {
        log(NiveauLog::ERREUR,
            "Impossible d'envoyer la réponse",
            idClient);
        socket_close(socketClient);
        return;
    }

    log(NiveauLog::INFO,
        "Réponse envoyée (" + std::to_string(envoi) + " octets)",
        idClient);

    log(NiveauLog::DEBUG,
        "Contenu de la réponse : " + reponse,
        idClient);

    socket_close(socketClient);
    log(NiveauLog::INFO, "Client déconnecté", idClient);
}
