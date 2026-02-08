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

std::shared_ptr<GraphicsObject>
SVGParser::parseCircle(const std::string& line)
{
    double cx = std::stod(getAttribute(line, "cx"));
    double cy = std::stod(getAttribute(line, "cy"));
    double r  = std::stod(getAttribute(line, "r"));

    auto circle = std::make_shared<Circle>(cx, cy, r);

    std::string fill = getAttribute(line, "fill");
    std::string stroke = getAttribute(line, "stroke");
    std::string strokeWidth = getAttribute(line, "stroke-width");

    if (!fill.empty()) circle->setFillColor(fill);
    if (!stroke.empty()) circle->setStrokeColor(stroke);
    if (!strokeWidth.empty())
        circle->setStrokeWidth(std::stoi(strokeWidth));

    return circle;
}

std::shared_ptr<GraphicsObject>
SVGParser::parseRectangle(const std::string& line)
{
    double x = std::stod(getAttribute(line, "x"));
    double y = std::stod(getAttribute(line, "y"));
    double width = std::stod(getAttribute(line, "width"));
    double height = std::stod(getAttribute(line, "height"));

    std::string rxStr = getAttribute(line, "rx");
    std::string ryStr = getAttribute(line, "ry");

    std::shared_ptr<GraphicsObject> obj;

    if (!rxStr.empty() || !ryStr.empty()) {
        double rx = rxStr.empty() ? 0 : std::stod(rxStr);
        double ry = ryStr.empty() ? 0 : std::stod(ryStr);
        obj = std::make_shared<RoundedRectangle>(x, y, width, height, rx, ry);
    } else {
        obj = std::make_shared<Rectangle>(x, y, width, height);
    }

    std::string fill = getAttribute(line, "fill");
    std::string stroke = getAttribute(line, "stroke");
    std::string strokeWidth = getAttribute(line, "stroke-width");

    if (!fill.empty()) obj->setFillColor(fill);
    if (!stroke.empty()) obj->setStrokeColor(stroke);
    if (!strokeWidth.empty())
        obj->setStrokeWidth(std::stoi(strokeWidth));

    return obj;
}

std::shared_ptr<GraphicsObject>
SVGParser::parseLine(const std::string& line)
{
    double x1 = std::stod(getAttribute(line, "x1"));
    double y1 = std::stod(getAttribute(line, "y1"));
    double x2 = std::stod(getAttribute(line, "x2"));
    double y2 = std::stod(getAttribute(line, "y2"));

    auto lineObj = std::make_shared<Line>(x1, y1, x2, y2);

    std::string stroke = getAttribute(line, "stroke");
    std::string strokeWidth = getAttribute(line, "stroke-width");

    if (!stroke.empty())
        lineObj->setStrokeColor(stroke);

    if (!strokeWidth.empty())
        lineObj->setStrokeWidth(std::stoi(strokeWidth));

    return lineObj;
}

std::shared_ptr<GraphicsObject>
SVGParser::parseHexagon(const std::string& line)
{
    double cx = std::stod(getAttribute(line, "cx"));
    double cy = std::stod(getAttribute(line, "cy"));
    double r  = std::stod(getAttribute(line, "r"));

    auto hex = std::make_shared<Hexagon>(cx, cy, r);

    std::string fill = getAttribute(line, "fill");
    std::string stroke = getAttribute(line, "stroke");
    std::string strokeWidth = getAttribute(line, "stroke-width");

    if (!fill.empty())
        hex->setFillColor(fill);

    if (!stroke.empty())
        hex->setStrokeColor(stroke);

    if (!strokeWidth.empty())
        hex->setStrokeWidth(std::stoi(strokeWidth));

    return hex;
}

std::shared_ptr<GraphicsObject>
SVGParser::parsePolyline(const std::string& line)
{
    std::string pointsStr = getAttribute(line, "points");

    std::vector<QPointF> points;
    std::stringstream ss(pointsStr);
    std::string token;

    while (ss >> token) {
        size_t comma = token.find(",");
        double x = std::stod(token.substr(0, comma));
        double y = std::stod(token.substr(comma + 1));
        points.emplace_back(x, y);
    }

    auto poly = std::make_shared<Polyline>(points);

    std::string stroke = getAttribute(line, "stroke");
    std::string strokeWidth = getAttribute(line, "stroke-width");

    if (!stroke.empty())
        poly->setStrokeColor(stroke);

    if (!strokeWidth.empty())
        poly->setStrokeWidth(std::stoi(strokeWidth));

    return poly;
}

std::shared_ptr<GraphicsObject>
SVGParser::parseText(const std::string& line)
{
    double x = std::stod(getAttribute(line, "x"));
    double y = std::stod(getAttribute(line, "y"));

    size_t start = line.find(">");
    size_t end = line.find("</text>");

    if (start == std::string::npos || end == std::string::npos)
        return nullptr;

    std::string content = line.substr(start + 1, end - start - 1);

    auto textObj = std::make_shared<Text>(x, y, content);

    std::string fill = getAttribute(line, "fill");

    if (!fill.empty())
        textObj->setFillColor(fill);

    return textObj;
}
