#include "diagram.h"
#include <sstream>
#include <algorithm>

void Diagram::addObject(std::shared_ptr<GraphicsObject> obj) {
    objects_.push_back(obj);
}

const std::vector<std::shared_ptr<GraphicsObject>>& Diagram::getObjects() const {
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

void Diagram::removeObject(std::shared_ptr<GraphicsObject> obj)
{
    objects_.erase(
        std::remove(objects_.begin(), objects_.end(), obj),
        objects_.end()
        );
}

void Diagram::insertObject(int index,
                           std::shared_ptr<GraphicsObject> obj)
{
    objects_.insert(objects_.begin() + index, obj);
}
