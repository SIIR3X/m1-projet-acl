#include <arpa/inet.h>
#include <chrono>
#include <gtest/gtest.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include "serveur/serveur_tcp.h"

TEST(ServeurTCPTest, TestConnexionEtReponse)
{
    // Lancement du serveur
    ServeurTCP serveur("127.0.0.1", 8000);
    std::thread threadServeur([&]() { serveur.demarrer(); });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Test d'une connexion client
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_GE(sock, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    ASSERT_EQ(connect(sock, (sockaddr*)&addr, sizeof(addr)), 0);

    // Envoi d'un message (PING)
    const char* message = "PING";
    ASSERT_GT(send(sock, message, strlen(message), 0), 0);

    // Réception de la réponse
    char buffer[1024];
    ssize_t reception = recv(sock, buffer, sizeof(buffer) - 1, 0);
    ASSERT_GT(reception, 0);
    buffer[reception] = '\0';

    // Nettoyage
    close(sock);
    serveur.arreter();

    // Force le lancement de accept() pour éviter d'être bloqué dans le test
    int wake = socket(AF_INET, SOCK_STREAM, 0);
    connect(wake, (sockaddr*)&addr, sizeof(addr));
    close(wake);

    if (threadServeur.joinable())
        threadServeur.join();
}