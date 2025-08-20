#pragma once
#include "../utils/utils.h"
#include "label.h"
#include <string>

struct LabelList {
    std::vector<Label> labels;
    Vector2 position;
    float h_size;
    Color label_color;
    Color border_color;
};