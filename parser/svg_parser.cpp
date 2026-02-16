// svg_parser.cpp
//
// Minimal line-oriented SVG parsing. Each supported SVG element is
// expected to appear entirely on a single line. The parser performs
// simple string matching and attribute extraction rather than full XML parsing.

#include "svg_parser.h"

#include <fstream>

// Parse the file line-by-line and construct a Diagram.
// Dispatches to shape-specific parsers based on the element tag.
Diagram SVGParser::parseFile(const std::string& filename)
{
    Diagram diagram;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::shared_ptr<GraphicsObject> obj = nullptr;

        // Identify element type via substring match on opening tag.
        if (line.find("<circle ") != std::string::npos) obj = parseCircle(line);
        else if (line.find("<rect ") != std::string::npos) obj = parseRectangle(line);
        else if (line.find("<line ") != std::string::npos) obj = parseLine(line);
        else if (line.find("<hexagon ") != std::string::npos) obj = parseHexagon(line);
        else if (line.find("<polyline ") != std::string::npos) obj = parsePolyline(line);
        else if (line.find("<text ") != std::string::npos) obj = parseText(line);

        // Only add recognized shapes to the diagram.
        if (obj != nullptr)
            diagram.addObject(obj);
    }

    return diagram;
}

// Extract the value of attribute `key` from `line`.
// Assumes attributes follow the pattern: key="value".
std::string SVGParser::getAttribute(const std::string& line, const std::string& key)
{
    std::string attribute = " " + key;  // ensure we match full attribute names
    size_t key_pos = line.find(attribute);
    if (key_pos == std::string::npos) return "";

    size_t start_quote = line.find('"', key_pos);
    if (start_quote == std::string::npos) return "";

    size_t end_quote = line.find('"', start_quote + 1);
    if (end_quote == std::string::npos) return "";

    return line.substr(start_quote + 1, end_quote - start_quote - 1);
}

// Apply common paint attributes (fill, stroke, stroke-width) if present.
// Missing attributes leave the object's default styling unchanged.
void SVGParser::setPaintAttributes(const std::string& line, const std::shared_ptr<GraphicsObject>& obj)
{
    std::string fill = getAttribute(line, "fill");
    std::string stroke = getAttribute(line, "stroke");
    std::string strokeWidth = getAttribute(line, "stroke-width");

    if (!fill.empty())
        obj->setFillColor(fill);

    if (!stroke.empty())
        obj->setStrokeColor(stroke);

    if (!strokeWidth.empty())
        obj->setStrokeWidth(std::stoi(strokeWidth));
}
