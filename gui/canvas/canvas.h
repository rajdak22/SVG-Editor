#pragma once
#include <QWidget>
#include <memory>
#include <vector>
#include <QRectF>
#include "../../model/diagram.h"
#include "../../model/graphics_object.h"
#include "../tools/tool.h"
#include "../../command/command.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:

    explicit Canvas(QWidget *parent = nullptr);

    // phase 1 (just diagrams)
    void setDiagram(const Diagram& d);
    void setTool(std::unique_ptr<Tool> tool);

    Diagram& getDiagram();
    std::shared_ptr<GraphicsObject>& getSelected();
    std::shared_ptr<GraphicsObject> getTempObject() const;

    // phase 2 (selection and dragging and drawing)
    void setSelected(std::shared_ptr<GraphicsObject> obj);
    void setTempObject(std::shared_ptr<GraphicsObject> obj);
    void clearTempObject();

    // phase 3 (shifting from canvas and undo/redo)
    void executeCommand(std::unique_ptr<Command> cmd);
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();

    // phase 4 (saving, etc.)
    void clearSelection();
    void clearHistory();

protected:

    // phase 1 (just diagrams)
    void paintEvent(QPaintEvent *event) override;

    // phase 2 + 3
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    // phase 4
    void keyPressEvent(QKeyEvent* event) override;

private:

    // phase 1 (just diagrams)
    Diagram diagram;

    // phase 2 (selection and dragging and drawing)
    std::shared_ptr<GraphicsObject> selected_;
    std::shared_ptr<GraphicsObject> temp_object_;
    std::unique_ptr<Tool> current_tool_;

    // phase 3 (shifting from canvas and undo/redo)
    std::vector<std::unique_ptr<Command>> undo_stack_;
    std::vector<std::unique_ptr<Command>> redo_stack_;

    // phase 4 (cut copy paste)
    std::shared_ptr<GraphicsObject> clipboard_;

    enum class ResizeHandle {
        None,
        TopLeft, Top, TopRight,
        Right,
        BottomRight, Bottom, BottomLeft,
        Left
    };

    ResizeHandle active_handle_ = ResizeHandle::None;
    QRectF original_box_;
    bool resizing_ = false;

};
