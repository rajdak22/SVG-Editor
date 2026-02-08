#include "svg_parser.h"

#include <fstream>


Diagram SVGParser::parseFile(const std::string& filename)
{
    Diagram diagram;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::shared_ptr<GraphicsObject> obj = nullptr;

        if (line.find("<circle") != std::string::npos)
            obj = parseCircle(line);

        else if (line.find("<rect") != std::string::npos)
            obj = parseRectangle(line);

        else if (line.find("<line") != std::string::npos)
            obj = parseLine(line);

        else if (line.find("<hexagon") != std::string::npos)
            obj = parseHexagon(line);

        else if (line.find("<polyline") != std::string::npos)
            obj = parsePolyline(line);

        else if (line.find("<text") != std::string::npos)
            obj = parseText(line);

        if (obj)
            diagram.addObject(obj);
    }

    return diagram;
}

std::string SVGParser::getAttribute(
    const std::string& line,
    const std::string& key
    ) {
    std::string pattern = key + "=\"";
    size_t start = line.find(pattern);

    if (start == std::string::npos)
        return "";

    start += pattern.length();
    size_t end = line.find("\"", start);

    if (end == std::string::npos)
        return "";

    return line.substr(start, end - start);
}
