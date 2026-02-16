// Diagram is the document model.
//
// Owns all GraphicsObject instances currently present on the whiteboard.
// Provides controlled insertion/removal and SVG serialization.
// Whiteboard operates on this class via the command system.

#pragma once

#include <vector>
#include <memory>
#include "graphics_object.h"

class Diagram {

private:

    // Ordered list of all objects in the diagram.
    // Later elements appear on top (defines Z-order).
    // Objects are shared_ptr so they can be referenced by commands,
    // selection state, and clipboard simultaneously.
    std::vector<std::shared_ptr<GraphicsObject>> objects_;

public:

    // Append `obj` to the diagram's object list (ownership via shared_ptr).
    // puts the object on the top of the Z order
    void addObject(std::shared_ptr<GraphicsObject> obj);

    // Undo the last addition (helper used by command pattern / undo stack).
    void unAddObject();

    // Returns read-only access to all objects.
    const std::vector<std::shared_ptr<GraphicsObject>>& getObjects() const;

    // Serialize the entire diagram into an SVG document string.
    std::string toSVG() const;

    // Removes the first and only occurrence of `obj` from the drawing.
    void removeObject(std::shared_ptr<GraphicsObject> obj);

    // Insert `obj` at `index` position in the internal vector.
    void insertObject(int index, std::shared_ptr<GraphicsObject> obj);
};
