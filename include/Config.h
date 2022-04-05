#pragma once
#ifndef CONFIG_H
#define CONFIG_H

// ==============================
// settings
const int WIN_SIZE_X = 1200;
const int WIN_SIZE_Y = 800;

const int FPS = 60;

#if defined(_WIN32) || defined(__CYGWIN__)
// windows
const auto FONT_PATH = "C:/Windows/Fonts/Arial.ttf";
#elif defined(__linux__)
// Linux
const auto FONT_PATH = "/usr/share/fonts/noto/NotoSansMono-Regular.ttf";
#endif

#endif