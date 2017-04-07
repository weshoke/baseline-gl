#include "search_paths.h"
#include <fstream>

namespace baseline {
    namespace app {
        void SearchPaths::Add(filesystem::path path) { paths_.push_back(path); }
        filesystem::path SearchPaths::FindFile(filesystem::path file_name)
        {
            if (file_name.is_file()) {
                return file_name;
            }

            for (const auto &path : paths_) {
                auto full_path = path / file_name;
                if (full_path.is_file()) {
                    return full_path;
                }
            }
            return filesystem::path();
        }

        std::string SearchPaths::LoadFile(filesystem::path file_name)
        {
            return ReadFile(FindFile(file_name));
        }

        std::string SearchPaths::ReadFile(filesystem::path file_name)
        {
            std::ifstream ifs(file_name.str());
            ifs.seekg(0, std::ios::end);
            auto length = ifs.tellg();
            ifs.seekg(std::ios::beg);

            auto text = std::string();
            text.reserve(length);
            text.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
            return text;
        }
    }
}
