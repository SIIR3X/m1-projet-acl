#include <gtest/gtest.h>
#include <sstream>

#include "modele/graphe/arete.h"
#include "modele/graphe/graphe.h"
#include "modele/graphe/sommet.h"

//
// Fonction pour libérer les listes.
//
template <typename T>
void libererListe(PElement<T>* liste)
{
    while (liste)
    {
        PElement<T>* tmp = liste;
        liste = liste->_suivant;
        delete tmp;
    }
}

TEST(GrapheTest, ConstructeurParDefaut)
{
    Graphe<std::string, std::string> g;

    EXPECT_EQ(g.nombreSommets(), 0);
    EXPECT_EQ(g.nombreAretes(), 0);
}

TEST(GrapheTest, CreeSommet)
{
    Graphe<std::string, int> g;

    auto* s1 = g.creeSommet(10);
    auto* s2 = g.creeSommet(20);

    EXPECT_EQ(g.nombreSommets(), 2);
    EXPECT_EQ(s1->_clef, 0);
    EXPECT_EQ(s1->_v, 10);
    EXPECT_EQ(s2->_clef, 1);
    EXPECT_EQ(s2->_v, 20);
}

TEST(GrapheTest, CreeArete)
{
    Graphe<std::string, std::string> g;

    auto* s1 = g.creeSommet("Paris");
    auto* s2 = g.creeSommet("Lyon");

    EXPECT_EQ(s1->_degre, 0);
    EXPECT_EQ(s2->_degre, 0);

    auto* a = g.creeArete("A6", s1, s2);

    EXPECT_EQ(g.nombreAretes(), 1);
    EXPECT_EQ(a->_v, "A6");
    EXPECT_EQ(s1->_degre, 1);
    EXPECT_EQ(s2->_degre, 1);
}

TEST(GrapheTest, AretesAdjacentes)
{
    Graphe<std::string, std::string> g;

    auto* s1 = g.creeSommet("Paris");
    auto* s2 = g.creeSommet("Lyon");
    auto* s3 = g.creeSommet("Metz");

    auto* a1 = g.creeArete("r1", s1, s2);
    auto* a2 = g.creeArete("r2", s1, s3);

    auto* list = g.aretesAdjacentes(s1);

    int count = 0;
    bool hasA1 = false, hasA2 = false;
    for (auto* p = list; p; p = p->_suivant)
    {
        if (p->_info == a1)
            hasA1 = true;
        if (p->_info == a2)
            hasA2 = true;
        count++;
    }

    EXPECT_EQ(count, 2);
    EXPECT_TRUE(hasA1);
    EXPECT_TRUE(hasA2);

    libererListe(list);
}

TEST(GrapheTest, Voisins)
{
    Graphe<std::string, std::string> g;

    auto* s1 = g.creeSommet("Paris");
    auto* s2 = g.creeSommet("Lyon");
    auto* s3 = g.creeSommet("Metz");

    g.creeArete("r1", s1, s2);
    g.creeArete("r2", s1, s3);

    auto* list = g.voisins(s1);

    int count = 0;
    bool hasS2 = false, hasS3 = false;
    for (auto* p = list; p; p = p->_suivant)
    {
        if (p->_info == s2)
            hasS2 = true;
        if (p->_info == s3)
            hasS3 = true;
        count++;
    }

    EXPECT_EQ(count, 2);
    EXPECT_TRUE(hasS2);
    EXPECT_TRUE(hasS3);

    libererListe(list);
}

TEST(GrapheTest, Adjacences)
{
    Graphe<std::string, int> g;

    auto* s1 = g.creeSommet(10);
    auto* s2 = g.creeSommet(20);

    auto* a = g.creeArete("r1", s1, s2);

    auto* list = g.adjacences(s1);

    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list->_info.first, s2);
    EXPECT_EQ(list->_info.second, a);

    libererListe(list);
}

TEST(GrapheTest, GetAreteParSommets)
{
    Graphe<std::string, int> g;

    auto* s1 = g.creeSommet(10);
    auto* s2 = g.creeSommet(20);
    auto* s3 = g.creeSommet(30);

    auto* a = g.creeArete("r1", s1, s2);

    auto* list = g.voisins(s1);

    EXPECT_EQ(g.getAreteParSommets(s1, s2), a);
    EXPECT_EQ(g.getAreteParSommets(s2, s1), a);
    EXPECT_EQ(g.getAreteParSommets(s1, s3), nullptr);

    libererListe(list);
}

TEST(GrapheTest, OperateurString)
{
    Graphe<std::string, std::string> g;

    auto* s1 = g.creeSommet("Paris");
    auto* s2 = g.creeSommet("Lyon");
    auto* a = g.creeArete("A6", s1, s2);

    std::string repr = static_cast<std::string>(g);

    EXPECT_TRUE(repr.find("Sommets:") != std::string::npos);
    EXPECT_TRUE(repr.find("Arêtes:") != std::string::npos);
    EXPECT_TRUE(repr.find("{0} : Paris") != std::string::npos);
    EXPECT_TRUE(repr.find("{1} : Lyon") != std::string::npos);
    EXPECT_TRUE(repr.find("{2} : A6") != std::string::npos);
}

TEST(GrapheTest, OperateurStream)
{
    Graphe<std::string, std::string> g;

    auto* s1 = g.creeSommet("Paris");
    auto* s2 = g.creeSommet("Lyon");
    auto* a = g.creeArete("A6", s1, s2);

    std::stringstream ss;
    ss << g;

    std::string repr = ss.str();

    EXPECT_TRUE(repr.find("Sommets:") != std::string::npos);
    EXPECT_TRUE(repr.find("Arêtes:") != std::string::npos);
    EXPECT_TRUE(repr.find("{0} : Paris") != std::string::npos);
    EXPECT_TRUE(repr.find("{1} : Lyon") != std::string::npos);
    EXPECT_TRUE(repr.find("{2} : A6") != std::string::npos);
}