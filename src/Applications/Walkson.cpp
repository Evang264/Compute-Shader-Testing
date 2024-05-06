#include "Walkson.h"

bool Walkson::on_init(sf::Window& window)
{
    if (!walkson_compute_.load_stage("assets/shaders/Walkson.glsl", ShaderType::Compute) ||
        !walkson_compute_.link_shaders())
    {
        return false;
    }

    // Set up the double buffer
    screen_texture_.create(window.getSize().x, window.getSize().y, 1, TextureFormat::RGBA32F);
    screen_texture_.set_wrap_s(TextureWrap::Repeat);
    screen_texture_.set_wrap_t(TextureWrap::Repeat);
    screen_texture_.set_min_filter(TextureMinFilter::Nearest);
    screen_texture_.set_mag_filter(TextureMagFilter::Nearest);

    return true;
}

void Walkson::frame(sf::Window& window)
{
    // The compute shader uses a double buffer to prevent read/write to same pixel by different work groups
    walkson_compute_.bind();
    glBindImageTexture(0, screen_texture_.id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(ceil(window.getSize().x / 8), ceil(window.getSize().y / 4), 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    screen_shader_.bind();
    screen_texture_.bind(0);
    screen_vao_.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}