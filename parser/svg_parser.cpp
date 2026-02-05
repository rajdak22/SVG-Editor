#include "svg_parser.h"

#include <fstream>
#include <sstream>

#include "../model/circle.h"
#include "../model/rectangle.h"
#include "../model/rounded_rectangle.h"
#include "../model/line.h"
#include "../model/hexagon.h"
#include "../model/text.h"
#include "../model/polyline.h"


Diagram SVGParser::parseFile(const std::string& filename) {
    Diagram diagram;

    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {

        // ===================== CIRCLE =====================
        if (line.find("<circle") != std::string::npos) {

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

            diagram.addObject(circle);
        }

        // ===================== RECTANGLE / ROUNDED =====================
        else if (line.find("<rect") != std::string::npos) {

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

            diagram.addObject(obj);
        }

        // ===================== LINE =====================
        else if (line.find("<line") != std::string::npos) {

            double x1 = std::stod(getAttribute(line, "x1"));
            double y1 = std::stod(getAttribute(line, "y1"));
            double x2 = std::stod(getAttribute(line, "x2"));
            double y2 = std::stod(getAttribute(line, "y2"));

            auto lineObj = std::make_shared<Line>(x1, y1, x2, y2);

            std::string stroke = getAttribute(line, "stroke");
            std::string strokeWidth = getAttribute(line, "stroke-width");

            if (!stroke.empty()) lineObj->setStrokeColor(stroke);
            if (!strokeWidth.empty())
                lineObj->setStrokeWidth(std::stoi(strokeWidth));

            diagram.addObject(lineObj);
        }

        // ===================== HEXAGON =====================
        else if (line.find("<hexagon") != std::string::npos) {

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

            diagram.addObject(hex);
        }

        // ===================== POLYLINE =====================
        else if (line.find("<polyline") != std::string::npos) {

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

            if (!stroke.empty()) poly->setStrokeColor(stroke);
            if (!strokeWidth.empty())
                poly->setStrokeWidth(std::stoi(strokeWidth));

            diagram.addObject(poly);
        }

        // ===================== TEXT =====================
        else if (line.find("<text") != std::string::npos) {

            double x = std::stod(getAttribute(line, "x"));
            double y = std::stod(getAttribute(line, "y"));

            size_t start = line.find(">");
            size_t end = line.find("</text>");

            if (start != std::string::npos && end != std::string::npos) {
                std::string content = line.substr(start + 1, end - start - 1);

                auto textObj = std::make_shared<Text>(x, y, content);

                std::string fill = getAttribute(line, "fill");
                if (!fill.empty())
                    textObj->setStrokeColor(fill);

                diagram.addObject(textObj);
            }
        }
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
