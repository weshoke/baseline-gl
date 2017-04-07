#include "app.h"
#include "draw/context.h"

namespace baseline {
    namespace app {
        std::array<uint32_t, 2> App::WindowSize()
        {
            int32_t width, height;
            glfwGetFramebufferSize(window(), &width, &height);
            return {uint32_t(width), uint32_t(height)};
        }

        float App::AspectRatio()
        {
            auto size = WindowSize();
            return float(size[0]) / float(size[1]);
        }

        void App::AddSearchPath(filesystem::path path)
        {
            return search_paths().AddSearchPath(path);
        }
        filesystem::path App::FindFile(filesystem::path file_name)
        {
            return search_paths().FindFile(file_name);
        }

        std::string App::LoadFile(filesystem::path file_name)
        {
            return search_paths().LoadFile(file_name);
        }

        void App::LoadProgram(const std::string &name)
        {
            return draw::Context::Get().RegisterProgram(
                name,
                [&](const auto &file_name) { return LoadFile(file_name); },
                [&](const auto &file_name) { return FindFile(file_name).is_file(); });
        }
    }
}
