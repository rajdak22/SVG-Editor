#pragma once

#include "../tool.h"

class TextTool : public Tool
{
public:
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
};
