#include <string>

namespace ThreeD {
    struct Texture {
        unsigned int id;
        std::string path;
        int width;
        int height;
        int channels;

        Texture(){
            id = 0;
            path = "";
            width = 0;
            height = 0;
            channels = 0;
        }
    };
}