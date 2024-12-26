#version 460

#include <registers_common.fx>
#include <common_math.fx>


layout(location = 0) in vec4 fs_in_color;

layout(location = 0) out vec4 fs_out_color;


layout(location = 256) uniform float u_elapsedTime;


void main()
{
#if defined(ENV_DEBUG)
    fs_out_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
#else
    fs_out_color = fs_in_color * abs(sin(u_elapsedTime * M_PI));
#endif
}