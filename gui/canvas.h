#pragma once
#include <QWidget>
#include "../model/diagram.h"
#include "../model/graphics_object.h"
#include <memory>


class Canvas : public QWidget
{
    Q_OBJECT

public:

    explicit Canvas(QWidget *parent = nullptr);

    enum class Tool {
        Select,
        Rectangle
    };

    void setDiagram(const Diagram& d);

    void setTool(Tool tool);

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:

    Diagram diagram;
    std::shared_ptr<GraphicsObject> selected_;

    Tool current_tool_ = Tool::Select;

    bool drawing_ = false;
    QPointF start_point_;
    std::shared_ptr<GraphicsObject> temp_object_;
};
