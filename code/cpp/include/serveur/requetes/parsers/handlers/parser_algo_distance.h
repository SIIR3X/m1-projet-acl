#ifndef PARSER_ALGO_DISTANCE_H
#define PARSER_ALGO_DISTANCE_H

#include <any>
#include <string>

#include "serveur/requetes/parsers/parser.h"

class ParserAlgoDistance : public Parser
{
public:
    std::vector<std::any> parser(const std::string& json) const override;
};

#endif  // PARSER_ALGO_DISTANCE_H