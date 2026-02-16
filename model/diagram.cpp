#include "diagram.h"
#include <sstream>
#include <algorithm>

void Diagram::addObject(std::shared_ptr<GraphicsObject> obj) {
    objects_.push_back(obj);
}

void Diagram::unAddObject() {
    objects_.pop_back();
}

void Diagram::removeObject(std::shared_ptr<GraphicsObject> obj)
{
    // Compare shared_ptr instances (identity comparison of underlying object).
    auto it = std::find(objects_.begin(), objects_.end(), obj);
    if (it != objects_.end()) {
        objects_.erase(it);
    }
}

void Diagram::insertObject(int index, std::shared_ptr<GraphicsObject> obj)
{
    objects_.insert(objects_.begin() + index, obj);
}

const std::vector<std::shared_ptr<GraphicsObject>>&
Diagram::getObjects() const {
    return objects_;
}

std::string Diagram::toSVG() const {
    std::ostringstream oss;

    oss << "<svg width=\"800\" height=\"600\" "
        << "xmlns=\"http://www.w3.org/2000/svg\">\n";

    for (const auto& obj : objects_) {
        oss << "  " << obj->toSVG() << "\n";
    }

    oss << "</svg>";
    return oss.str();
}
