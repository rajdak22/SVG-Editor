#pragma once

#include <vector>
#include <memory>
#include "graphics_object.h"

class Diagram {

private:

    std::vector<std::shared_ptr<GraphicsObject>> objects_;

public:

    void addObject(std::shared_ptr<GraphicsObject> obj);
    void unAddObject();
    const std::vector<std::shared_ptr<GraphicsObject>>& getObjects() const;
    std::string toSVG() const;

    // phase 3
    void removeObject(std::shared_ptr<GraphicsObject> obj);
    void insertObject(int index, std::shared_ptr<GraphicsObject> obj);
};
