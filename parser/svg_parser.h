#pragma once

#include <string>
#include "../model/diagram.h"

// SVGParser
// Utility class responsible for constructing a Diagram from an SVG file.
// This class does not store state — it only provides parsing helpers.
// All methods are static so the class does not need to be instantiated.

class SVGParser {

public:

    // Parse the SVG file at `filename` and return a populated Diagram.
    // Assumes a simple, line-based SVG where each drawable element
    // appears fully on a single line.
    static Diagram parseFile(const std::string& filename);

private:

    // Extract the value of attribute `key` from a single SVG element line.
    // Returns empty string if the attribute is not found.
    static std::string getAttribute(const std::string& line, const std::string& key);

    // Apply common paint attributes (fill, stroke, stroke-width) to `obj`
    // if present in the SVG element line.
    static void setPaintAttributes(const std::string& line, const std::shared_ptr<GraphicsObject>& obj);

    // Parse individual SVG element types into concrete GraphicsObject instances.
    static std::shared_ptr<GraphicsObject> parseCircle(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseRectangle(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseLine(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseHexagon(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseRoundedRect(const std::string& line);
    static std::shared_ptr<GraphicsObject> parsePolyline(const std::string& line);
    static std::shared_ptr<GraphicsObject> parseText(const std::string& line);
};
