#ifndef REGISTERS_COMMON_H
#define REGISTERS_COMMON_H

#include <system.fx>
#include <texture_constants.fx>


DECLARE_SRV_TEXTURE(sampler2D, GBUFFER_ALBEDO_TEX, 0, TEXTURE_FORMAT_RGBA8, COMMON_SMP_CLAMP_LINEAR_IDX);
DECLARE_SRV_TEXTURE(sampler2D, GBUFFER_NORMAL_TEX, 1, TEXTURE_FORMAT_RGBA8, COMMON_SMP_CLAMP_LINEAR_IDX);
DECLARE_SRV_TEXTURE(sampler2D, GBUFFER_SPECULAR_TEX, 2, TEXTURE_FORMAT_RGBA8, COMMON_SMP_CLAMP_LINEAR_IDX);

DECLARE_SRV_TEXTURE(sampler2D, COMMON_DEPTH_TEX, 3, TEXTURE_FORMAT_DEPTH32, COMMON_SMP_CLAMP_LINEAR_IDX);

DECLARE_SRV_TEXTURE(sampler2D, TEST_TEXTURE, 4, TEXTURE_FORMAT_RGBA8, COMMON_SMP_REPEAT_NEAREST_IDX);


DECLARE_CBV(COMMON_CB, 0)
{
    float COMMON_ELAPSED_TIME;
    float COMMON_DELTA_TIME;
};

#endif