#include "svg_parser.h"

#include <sstream>
#include <QPointF>
#include <vector>

#include "../model/circle.h"
#include "../model/rectangle.h"
#include "../model/rounded_rectangle.h"
#include "../model/line.h"
#include "../model/hexagon.h"
#include "../model/text.h"
#include "../model/polyline.h"

std::shared_ptr<GraphicsObject> SVGParser::parseCircle(const std::string& line)
{
    double cx = std::stod(getAttribute(line, "cx"));
    double cy = std::stod(getAttribute(line, "cy"));
    double r  = std::stod(getAttribute(line, "r"));

    auto circleObj = std::make_shared<Circle>(cx, cy, r);

    setPaintAttributes(line, circleObj);

    return circleObj;
}

std::shared_ptr<GraphicsObject> SVGParser::parseRectangle(const std::string& line)
{
    double x = std::stod(getAttribute(line, "x"));
    double y = std::stod(getAttribute(line, "y"));
    double width = std::stod(getAttribute(line, "width"));
    double height = std::stod(getAttribute(line, "height"));

    std::string rxString = getAttribute(line, "rx");
    std::string ryString = getAttribute(line, "ry");

    std::shared_ptr<GraphicsObject> rectObj;

    if (!rxString.empty() || !ryString.empty())
    {
        double rx = rxString.empty() ? 0 : std::stod(rxString);
        double ry = ryString.empty() ? 0 : std::stod(ryString);
        rectObj = std::make_shared<RoundedRectangle>(x, y, width, height, rx, ry);
    }
    else
    {
        rectObj = std::make_shared<Rectangle>(x, y, width, height);
    }

    setPaintAttributes(line, rectObj);

    return rectObj;
}

std::shared_ptr<GraphicsObject> SVGParser::parseLine(const std::string& line)
{
    double x1 = std::stod(getAttribute(line, "x1"));
    double y1 = std::stod(getAttribute(line, "y1"));
    double x2 = std::stod(getAttribute(line, "x2"));
    double y2 = std::stod(getAttribute(line, "y2"));

    auto lineObj = std::make_shared<Line>(x1, y1, x2, y2);

    setPaintAttributes(line, lineObj);

    return lineObj;
}

std::shared_ptr<GraphicsObject> SVGParser::parseHexagon(const std::string& line)
{
    double cx = std::stod(getAttribute(line, "cx"));
    double cy = std::stod(getAttribute(line, "cy"));
    double r  = std::stod(getAttribute(line, "r"));

    auto hexObj = std::make_shared<Hexagon>(cx, cy, r);

    setPaintAttributes(line, hexObj);

    return hexObj;
}

std::shared_ptr<GraphicsObject> SVGParser::parsePolyline(const std::string& line)
{
    std::string pointsList = getAttribute(line, "points");

    std::vector<QPointF> points;
    std::stringstream ss(pointsList);
    std::string coordinate;

    while (ss >> coordinate) {
        size_t comma = coordinate.find(",");
        double x = std::stod(coordinate.substr(0, comma));
        double y = std::stod(coordinate.substr(comma + 1));
        points.push_back(QPointF(x, y));
    }

    auto polyObj = std::make_shared<Polyline>(points);

    setPaintAttributes(line, polyObj);

    return polyObj;
}

std::shared_ptr<GraphicsObject> SVGParser::parseText(const std::string& line)
{
    double x = std::stod(getAttribute(line, "x"));
    double y = std::stod(getAttribute(line, "y"));
    std::string fontSizeString = getAttribute(line, "font-size");
    int fontSize = fontSizeString.empty() ? 14 : std::stoi(fontSizeString);

    // example: <text x="2" y="1">Hello</text>
    // getAttribute not used since content isn't between ""
    size_t start = line.find(">");
    if (start == std::string::npos) return nullptr;
    size_t end = line.find("</text>");
    if (end == std::string::npos) return nullptr;

    std::string content = line.substr(start + 1, end - start - 1);

    auto textObj = std::make_shared<Text>(x, y, content, fontSize);

    setPaintAttributes(line, textObj);

    return textObj;
}
