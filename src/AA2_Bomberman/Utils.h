#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

static std::string F2StrFormat(float num, int decimals)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(decimals) << num;
    return static_cast<std::string>(stream.str());
}

static VEC2 MapToScreen(RECT position, RECT frame)
{
    return { (position.x + frame.w / 2) / FRAME_SIZE - 1, ((position.y + frame.h / 2) - (80 + FRAME_SIZE)) / FRAME_SIZE };
}