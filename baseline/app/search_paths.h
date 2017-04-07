#ifndef BASELINE_APP_SEARCH_PATHS_H
#define BASELINE_APP_SEARCH_PATHS_H

#include "filesystem/path.h"

namespace baseline {
    namespace app {
        class SearchPaths {
           public:
            SearchPaths() {}
            void Add(filesystem::path path);
            filesystem::path FindFile(filesystem::path file_name);
            std::string LoadFile(filesystem::path file_name);

           private:
            static std::string ReadFile(filesystem::path file_name);

            std::vector<filesystem::path> paths_;
        };
    }
}

#endif
