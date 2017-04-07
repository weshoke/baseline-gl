#include "app/app.h"
// #include "app/trackball_state.h"
// #include "draw/camera.h"
#include "draw/color.h"
#include "draw/draw.h"
// #include "draw/trackball.h"

using namespace baseline;

class Demo {
public:
  Demo(app::App &app)
      : app(app)
  // , camera(draw::Camera::Default())
  // , trackball(draw::Trackball(1.3f, 1.f, 10.f))
  {}

  void Key(int32_t key, int32_t scancode, int32_t action, int32_t mods) {}

  void Mouse(int32_t button, int32_t action, int32_t mods) {
    // trackball_state.Mouse(button, action, mods);
  }

  void Cursor(double xpos, double ypos) {
    // using Vec2 = viz::draw::Vec2;
    // auto window_size = app.WindowSize();
    // auto mouse_pos = Vec2((float(xpos) / float(window_size[0])) * 2.f - 1.f,
    //                       (float(ypos) / float(window_size[0])) * 2.f - 1.f);
    //
    // trackball_state.Cursor(camera, trackball, mouse_pos);
  }

  void Scroll(int xoffset, int yoffset) {
    // trackball.Move(camera, float(yoffset) * 0.2f);
  }
  void Draw() {
    auto window_size = app.WindowSize();
    draw::ClearWindowWithDepth(window_size, draw::Colors::chromium);
    draw::Context::Get().ScreenSize(window_size);
  }

  app::App &app;
  // app::TrackballState trackball_state;
  // draw::Camera camera;
};

int main(void) {
  return app::App::Create("Baseline 01 GLFW", 640, 480, [](app::App &app) {
    auto demo = Demo(app);
    return app.Run(demo);
  });
}
