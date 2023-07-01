
#include "../src/HandleParse/id3parse.h"

int main() {

    std::fstream file("C:\\test\\leva.mp3", std::ios::in|std::ios::binary);
    id3tag my_tag;
    my_tag.GetTagFromFile(file);

    for (auto el : my_tag.GetFramesVector()) {
        el->PrintFrameInfo();
    }


    return 0;
}
