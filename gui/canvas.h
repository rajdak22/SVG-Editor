#pragma once
#include <QWidget>
#include <memory>
#include "../model/diagram.h"
#include "../model/graphics_object.h"
#include "tools/tool.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:

    explicit Canvas(QWidget *parent = nullptr);

    void setDiagram(const Diagram& d);
    void setTool(std::unique_ptr<Tool> tool);

    Diagram& getDiagram();
    std::shared_ptr<GraphicsObject>& getSelected();
    std::shared_ptr<GraphicsObject> getTempObject() const;
    void setSelected(std::shared_ptr<GraphicsObject> obj);
    void setTempObject(std::shared_ptr<GraphicsObject> obj);
    void clearTempObject();

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:

    Diagram diagram;
    std::shared_ptr<GraphicsObject> selected_;
    std::shared_ptr<GraphicsObject> temp_object_;
    std::unique_ptr<Tool> current_tool_;
};
