#include <gtest/gtest.h>

#include "utils/json_builder.h"

TEST(JsonBuilderTest, BuildSimpleString)
{
    JsonBuilder jb;
    jb.addString("type", "TSP");

    std::string json = jb.build();

    EXPECT_NE(json.find("\"type\": \"TSP\""), std::string::npos);
}

TEST(JsonBuilderTest, BuildSimpleNumber)
{
    JsonBuilder jb;
    jb.addValue("distance_totale", 123.45);

    std::string json = jb.build();

    EXPECT_NE(json.find("\"distance_totale\": 123.45"), std::string::npos);
}

TEST(JsonBuilderTest, BuildArray)
{
    JsonBuilder jb;
    jb.beginArray("chemin");
    jb.addRawValue("{\"nom\": \"Paris\"}");
    jb.addRawValue("{\"nom\": \"Lyon\"}");
    jb.endArray();

    std::string json = jb.build();

    EXPECT_TRUE(json.find("\"chemin\":[") != std::string::npos || json.find("\"chemin\": [") != std::string::npos);

    EXPECT_NE(json.find("\"nom\": \"Paris\""), std::string::npos);
    EXPECT_NE(json.find("\"nom\": \"Lyon\""), std::string::npos);
}

TEST(JsonBuilderTest, BuildNestedObject)
{
    JsonBuilder jb;

    jb.beginObject("info");
    jb.addString("nom", "Paris");
    jb.addValue("lat", 48.85);
    jb.addValue("lon", 2.35);
    jb.endObject();

    std::string json = jb.build();

    EXPECT_NE(json.find("\"info\": {"), std::string::npos);
    EXPECT_NE(json.find("\"nom\": \"Paris\""), std::string::npos);
    EXPECT_NE(json.find("\"lat\": 48.85"), std::string::npos);
    EXPECT_NE(json.find("\"lon\": 2.35"), std::string::npos);
}

TEST(JsonBuilderTest, BuildTSPExample)
{
    JsonBuilder jb;

    jb.beginObject("");
    jb.addString("type", "TSP");
    jb.addString("entite", "ville");

    jb.beginArray("chemin");
    jb.addRawValue("{\"nom\":\"Paris\"}");
    jb.addRawValue("{\"nom\":\"Lyon\"}");
    jb.endArray();

    jb.endObject();

    std::string json = jb.build();

    EXPECT_TRUE(json.find("\"chemin\":[") != std::string::npos || json.find("\"chemin\": [") != std::string::npos);

    EXPECT_NE(json.find("\"nom\":\"Paris\""), std::string::npos);
    EXPECT_NE(json.find("\"nom\":\"Lyon\""), std::string::npos);
}