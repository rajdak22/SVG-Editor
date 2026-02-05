#ifndef SVG_PARSER_H
#define SVG_PARSER_H

#include <string>
#include "../model/diagram.h"

class SVGParser {
public:
    static Diagram parseFile(const std::string& filename);

private:
    static std::string getAttribute(
        const std::string& line,
        const std::string& key
        );
};

#endif
