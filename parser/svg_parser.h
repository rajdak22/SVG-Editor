#ifndef SVG_PARSER_H
#define SVG_PARSER_H

#include <string>
#include "../model/diagram.h"

// static methods everywhere because no memory used by this class (no data members)
// it is basically a utility class, and just needs to return a diagram object
// static keyword allows us to use function without instantiating an object (efficient memorywise)
class SVGParser {

public:

    static Diagram parseFile(const std::string& filename);

private:

    static std::string getAttribute(const std::string& line, const std::string& key);

    static std::shared_ptr<GraphicsObject> parseCircle(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseRectangle(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseLine(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseHexagon(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseRoundedRect(const std::string& line);
    static std::shared_ptr<GraphicsObject> parsePolyline(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseText(const std::string& line);
};

#endif
