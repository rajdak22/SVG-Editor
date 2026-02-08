#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include "../command/delete_command.h"
#include "../command/add_command.h"
#include "tools/tool.h"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600, 400);
    setFocusPolicy(Qt::StrongFocus);
}

void Canvas::setDiagram(const Diagram &d)
{
    diagram = d;
    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (const auto& obj : diagram.getObjects()) {
        obj->draw(painter, obj == selected_);
    }

    if (temp_object_) {
        temp_object_->draw(painter, false);
    }

    if (selected_) {

        QRectF box = selected_->boundingBox();

        painter.save();

        QPen pen(Qt::blue);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawRect(box);

        // ----------------------------
        // Draw resize handles
        // ----------------------------
        const double handleSize = 6;

        auto drawHandle = [&](QPointF center) {
            QRectF handle(center.x() - handleSize / 2,
                          center.y() - handleSize / 2,
                          handleSize,
                          handleSize);

            painter.fillRect(handle, Qt::white);
            painter.drawRect(handle);
        };

        QPointF tl = box.topLeft();
        QPointF tr = box.topRight();
        QPointF bl = box.bottomLeft();
        QPointF br = box.bottomRight();
        QPointF tm((box.left() + box.right()) / 2, box.top());
        QPointF bm((box.left() + box.right()) / 2, box.bottom());
        QPointF ml(box.left(), (box.top() + box.bottom()) / 2);
        QPointF mr(box.right(), (box.top() + box.bottom()) / 2);

        drawHandle(tl);
        drawHandle(tr);
        drawHandle(bl);
        drawHandle(br);
        drawHandle(tm);
        drawHandle(bm);
        drawHandle(ml);
        drawHandle(mr);

        painter.restore();
    }
}

void Canvas::setTool(std::unique_ptr<Tool> tool)
{
    current_tool_ = std::move(tool);
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mousePress(this, event);

    update();
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mouseMove(this, event);

    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (current_tool_)
        current_tool_->mouseRelease(this, event);

    update();
}

Diagram& Canvas::getDiagram() {
    return diagram;
}

std::shared_ptr<GraphicsObject>& Canvas::getSelected() {
    return selected_;
}

std::shared_ptr<GraphicsObject> Canvas::getTempObject() const {
    return temp_object_;
}

void Canvas::setSelected(std::shared_ptr<GraphicsObject> obj) {
    selected_ = obj;
}

void Canvas::setTempObject(std::shared_ptr<GraphicsObject> obj) {
    temp_object_ = obj;
}

void Canvas::clearTempObject() {
    temp_object_.reset();
}

void Canvas::executeCommand(std::unique_ptr<Command> cmd)
{
    cmd->execute();
    undo_stack_.push_back(std::move(cmd));
    redo_stack_.clear();
    update();
}

void Canvas::undo()
{
    if (undo_stack_.empty())
        return;

    auto cmd = std::move(undo_stack_.back());
    undo_stack_.pop_back();

    cmd->undo();
    redo_stack_.push_back(std::move(cmd));
    update();
}

void Canvas::redo()
{
    if (redo_stack_.empty())
        return;

    auto cmd = std::move(redo_stack_.back());
    redo_stack_.pop_back();

    cmd->execute();
    undo_stack_.push_back(std::move(cmd));
    update();
}

void Canvas::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
    {
        if (selected_)
        {
            executeCommand(
                std::make_unique<DeleteCommand>(
                    diagram,
                    selected_
                    )
                );

            selected_.reset();
            update();
        }
    }
}

void Canvas::clearSelection()
{
    selected_.reset();
    update();
}

void Canvas::clearHistory()
{
    undo_stack_.clear();
    redo_stack_.clear();
}

void Canvas::copy()
{
    if (!selected_)
        return;

    clipboard_ = selected_->clone();   // IMPORTANT
}

void Canvas::cut()
{
    if (!selected_)
        return;

    copy();

    executeCommand(
        std::make_unique<DeleteCommand>(
            diagram,
            selected_
            )
        );

    selected_.reset();
}

void Canvas::paste()
{
    if (!clipboard_)
        return;

    auto newObj = clipboard_->clone();

    // Slight offset so pasted object is visible
    newObj->move(10, 10);

    executeCommand(
        std::make_unique<AddCommand>(
            diagram,
            newObj
            )
        );

    selected_ = newObj;
}
