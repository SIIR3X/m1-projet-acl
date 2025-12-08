#ifndef TSP_OUTPUT_DATA_H
#define TSP_OUTPUT_DATA_H

#include <string>
#include <vector>

#include "algorithmes/data/output/output_data.h"

#include "utils/json_builder.h"

struct TSPOutputData : public OutputData
{
    std::vector<int> chemin;
    std::vector<std::string> labels;
    std::vector<double> distances;
    double distanceTotale = 0.0;

    std::string toJson() const override
    {
        JsonBuilder jb;

        // Chemin
        jb.beginArray("chemin");
        for (int idx : chemin) jb.addRawValue("\"" + labels[idx] + "\"");

        // Distances entre étapes
        jb.beginArray("distances");
        for (double distance : distances) jb.addRawValue(std::to_string(distance));
        jb.endArray();

        // Distance totale
        jb.addRaw("distanceTotale", std::to_string(distanceTotale));

        return jb.build();
    }
};

#endif  // TSP_OUTPUT_DATA_H