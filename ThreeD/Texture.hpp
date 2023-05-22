#include <string>

namespace ThreeD {
    struct Texture {
        std::string path;
        int width = 0;
        int height = 0;
        int channels = 0;
        unsigned char* data;
    };
}