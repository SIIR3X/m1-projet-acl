#ifndef PARSER_H
#define PARSER_H

#include <any>
#include <string>

class Parser
{
public:
    virtual ~Parser() = default;

    virtual std::any parser(const std::string& json) const = 0;
};

#endif  // PARSER_H