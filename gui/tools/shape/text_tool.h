// TextTool: creates a Text object at the click position.
//
// On mouse press, prompts the user for text input and inserts a Text
// object at the clicked location using an AddCommand.
#pragma once

#include "../tool.h"

class TextTool : public Tool
{
public:
    // Handle mouse press: open input dialog and add Text to diagram.
    void mousePress(Whiteboard* whiteboard, QMouseEvent* event) override;
};
