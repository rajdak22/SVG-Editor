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

    // phase 3
    void removeObject(std::shared_ptr<GraphicsObject> obj);
    void insertObject(int index, std::shared_ptr<GraphicsObject> obj);

private:
    std::vector<std::shared_ptr<GraphicsObject>> objects_;
};

#endif
