#include "svg_parser.h"

#include <fstream>


// assumption is that each line of the svg contains description
// of one shape only

Diagram SVGParser::parseFile(const std::string& filename)
{
    Diagram diagram;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        // intialising to nullptr in case we see a shape we don't recognise
        std::shared_ptr<GraphicsObject> obj = nullptr;

        // each shape starts with <
        if (line.find("<circle ") != std::string::npos) obj = parseCircle(line);
        else if (line.find("<rect ") != std::string::npos) obj = parseRectangle(line);
        else if (line.find("<line ") != std::string::npos) obj = parseLine(line);
        else if (line.find("<hexagon ") != std::string::npos) obj = parseHexagon(line);
        else if (line.find("<polyline ") != std::string::npos) obj = parsePolyline(line);
        else if (line.find("<text ") != std::string::npos) obj = parseText(line);

        // if a shape has been recognised, then add it to objects_ in diagram
        if (obj != nullptr)
            diagram.addObject(obj);
    }

    return diagram;
}

std::string SVGParser::getAttribute(const std::string& line, const std::string& key)
{
    std::string attribute  = " " + key;             // each token must start with a new space
    size_t key_pos = line.find(attribute);          // finding position of the token
    if(key_pos == std::string::npos) return "";

    size_t start_quote = line.find('"', key_pos);
    if((start_quote) == std::string::npos) return "";   // quote before value

    size_t end_quote = line.find('"', start_quote + 1); // quote after value
    if(end_quote == std::string::npos) return "";

    return line.substr(start_quote + 1, end_quote - start_quote - 1);   // final value of token
}
