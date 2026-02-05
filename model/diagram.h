#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <vector>
#include <memory>
#include "graphics_object.h"

class Diagram {
public:
    void addObject(std::shared_ptr<GraphicsObject> obj);

    const std::vector<std::shared_ptr<GraphicsObject>>& getObjects() const;

    std::string toSVG() const;

private:
    std::vector<std::shared_ptr<GraphicsObject>> objects_;
};

#endif
