#include "serveur/serveur_tcp.h"

void ServeurTCP::demarrer()
{
    _serveurEstActif = true;

    // Création du socket serveur
    _socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketServeur < 0)
        ERREUR("demarrer", "socket()", true);

    // Autorisation de la réutilisation du port
    int opt = 1;
    setsockopt(_socketServeur, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Construction de l'adresse IP du serveur
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);

    // Conversion de l'adresse IP (de string à binaire)
    if (inet_pton(AF_INET, _ip.c_str(), &addr.sin_addr) <= 0)
    {
        close(_socketServeur);
        ERREUR("demarrer", "inet_pton()", true);
    }

    // Liaison du socket à l'IP et au port
    if (bind(_socketServeur, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        close(_socketServeur);
        ERREUR("demarrer", "bind()", true);
    }

    // Mise en écoute
    if (listen(_socketServeur, 10) < 0)
    {
        close(_socketServeur);
        ERREUR("demarrer", "listen()", true);
    }

    log(NiveauLog::INFO, "Serveur écoute sur " + _ip + ":" + std::to_string(_port));

    // Lance la boucle principale du serveur
    boucleServeur();
}

void ServeurTCP::arreter()
{
    if (!_serveurEstActif)
        return;

    _serveurEstActif = false;

    // Fermeture du socket serveur
    close(_socketServeur);

    // Arrêt propre de tous les threads clients
    for (auto& thread : _threadsClients)
        if (thread.joinable())
            thread.join();
}

void ServeurTCP::gererClient(int socketClient, int idClient)
{
    log(NiveauLog::INFO, "Client connecté", idClient);

    char buffer[2048];

    // Réception de la requête du client
    ssize_t reception = recv(socketClient, buffer, sizeof(buffer) - 1, 0);
    if (reception <= 0)
    {
        log(NiveauLog::ERREUR, "Échec de réception");
        close(socketClient);
        return;
    }

    buffer[reception] = '\0';
    std::string requete = buffer;

    log(NiveauLog::INFO, "Requête reçue : " + requete, idClient);

    // Traitement de la requête
    std::string reponse;

    try
    {
        reponse = traiterRequete(requete);
    }
    catch (const std::exception& e)
    {
        log(NiveauLog::ERREUR, std::string("Erreur pendant le traitement : ") + e.what(), idClient);
        close(socketClient);
        return;
    }
    catch (...)
    {
        log(NiveauLog::ERREUR, "Erreur inconnue pendant le traitement", idClient);
        close(socketClient);
        return;
    }

    // Envoi de la réponse au client
    ssize_t envoi = send(socketClient, reponse.c_str(), reponse.size(), 0);

    if (envoi < 0)
    {
        log(NiveauLog::ERREUR, "Impossible d'envoyer la réponse au client", idClient);
        close(socketClient);
        return;
    }

    log(NiveauLog::INFO, "Réponse envoyée (" + std::to_string(envoi) + " octets)", idClient);

    // Fin de la communication
    close(socketClient);
    log(NiveauLog::INFO, "Client déconnecté", idClient);
}