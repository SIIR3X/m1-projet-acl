#include <gtest/gtest.h>

#include <sstream>

#include "modele/generique/carte.h"
#include "modele/geographie/ville.h"

//
// Fonction de calcul de distance simple pour les tests
//
double distanceTest(const Ville& a, const Ville& b)
{
    return std::abs(a.latitude() - b.latitude()) + std::abs(a.longitude() - b.longitude());
}

TEST(CarteTest, ConstructeurPrincipal)
{
    std::vector<Ville> villes = {{"Paris", 48.85, 2.35}, {"Lyon", 45.76, 4.84}};

    Carte<Ville> c(villes, distanceTest);

    ASSERT_EQ(c.elements().size(), 2);
    EXPECT_EQ(c.elements()[0].nom(), "Paris");
    EXPECT_EQ(c.elements()[1].nom(), "Lyon");
}

TEST(CarteTest, AjouterElement)
{
    Carte<Ville> c({}, distanceTest);

    c.ajouter(Ville("Grenoble", 45.19, 5.72));

    ASSERT_EQ(c.elements().size(), 1);
    EXPECT_EQ(c.elements()[0].nom(), "Grenoble");
}

TEST(CarteTest, ConstruireGrapheCreeBonNombreSommetsEtAretes)
{
    std::vector<Ville> villes = {{"Paris", 48.85, 2.35}, {"Lyon", 45.76, 4.84}, {"Marseille", 43.30, 5.37}};

    Carte<Ville> c(villes, distanceTest);
    auto g = c.construireGraphe();

    EXPECT_EQ(g.nombreSommets(), 3);
    EXPECT_EQ(g.nombreAretes(), 6);
}

TEST(CarteTest, OperateurString)
{
    Carte<Ville> c({{"Paris", 48.85, 2.35}, {"Lyon", 45.76, 4.84}}, distanceTest);

    std::string s = static_cast<std::string>(c);

    EXPECT_NE(s.find("Carte (2 elements):"), std::string::npos);
    EXPECT_NE(s.find("Paris"), std::string::npos);
    EXPECT_NE(s.find("Lyon"), std::string::npos);
}

TEST(CarteTest, OperateurStream)
{
    Carte<Ville> c({{"Paris", 48.85, 2.35}}, distanceTest);

    std::stringstream ss;
    ss << c;

    std::string out = ss.str();

    EXPECT_NE(out.find("Paris"), std::string::npos);
    EXPECT_NE(out.find("Carte"), std::string::npos);
}