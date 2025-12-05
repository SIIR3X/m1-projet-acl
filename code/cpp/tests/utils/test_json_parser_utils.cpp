#include <gtest/gtest.h>

#include "utils/json_parser_utils.h"

static const std::string JSON_TEST = R"(
{
  "type": "TSP",
  "entite": "ville",
  "donnees": [
      { "nom": "Paris", "lat": 48.85, "lon": 2.35 }
  ]
}
)";

TEST(JsonParserUtilsTest, ExtraireChampString)
{
    std::string type = JsonParserUtils::extraireChampString(JSON_TEST, "type");
    EXPECT_EQ(type, "TSP");
}

TEST(JsonParserUtilsTest, ExtraireBloc)
{
    std::string bloc = JsonParserUtils::extraireBloc(JSON_TEST, "donnees");

    EXPECT_FALSE(bloc.empty());
    EXPECT_EQ(bloc.front(), '[');
    EXPECT_EQ(bloc.back(), ']');
}

TEST(JsonParserUtilsTest, ExtraireListeObjets)
{
    std::string bloc = JsonParserUtils::extraireBloc(JSON_TEST, "donnees");
    auto objets = JsonParserUtils::extraireListeObjets(bloc);

    EXPECT_EQ(objets.size(), 1);
}

TEST(JsonParserUtilsTest, ExtraireChampObjet)
{
    std::string bloc = JsonParserUtils::extraireBloc(JSON_TEST, "donnees");
    auto objets = JsonParserUtils::extraireListeObjets(bloc);

    std::string nom = JsonParserUtils::extraireChampObjet(objets[0], "nom");
    EXPECT_EQ(nom, "Paris");
}