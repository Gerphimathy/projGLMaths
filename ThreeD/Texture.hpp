#include <string>

namespace ThreeD {
    struct Texture {
        unsigned int id;
        std::string path;
        int width;
        int height;
        int channels;
    };
}