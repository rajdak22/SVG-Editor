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

    static std::shared_ptr<GraphicsObject> parseCircle(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseRectangle(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseLine(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseHexagon(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseRoundedRect(const std::string& line);
    static std::shared_ptr<GraphicsObject> parsePolyline(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseText(const std::string& line);
};

#endif
