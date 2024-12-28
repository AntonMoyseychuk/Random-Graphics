#ifndef REGISTERS_COMMON_H
#define REGISTERS_COMMON_H

#include <reflection.fx>

DECLARE_CONSTANT(uint, COMMON_MAX_TEXTURES_COUNT, 4096);

DECLARE_SRV_VARIABLE(float, COMMON_ELAPSED_TIME, 0, 0.f);

#endif