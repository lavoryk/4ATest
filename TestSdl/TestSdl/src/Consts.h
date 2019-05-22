#pragma once
const float PIXEL_WIDTH  = 1280;
const float PIXEL_HEIGHT = 960;
const float METER_PER_PIXEL = 1.0f;
const float PIXEL_PER_METER = 1.0f / METER_PER_PIXEL;
const float METER_WIDTH  = PIXEL_WIDTH  * METER_PER_PIXEL;
const float METER_HEIGHT = PIXEL_HEIGHT * METER_PER_PIXEL;
// #define DEBUG_HIT_POINT