#pragma once

#include "../FramesFactory/Frame.h"

#include <iostream>
#include <vector>


class id3tag {
public:

    void GetTagFromFile(std::fstream& buffer);
    void ParseTagFile(id3tag& tag, std::fstream& buffer);

    std::vector<Frame*> GetFramesVector() {
        return temp_vec_;
    }

    int GetFramesSize() {
        return id3v2_size_;
    }

private:
    std::vector<Frame*> temp_vec_;
    std::string identifier_;
    int id3v2_version_;
    bool is_desynchronization_;
    bool is_extended_header_;
    bool is_experimental_tag_;
    bool is_footer_;
    int id3v2_size_;
};



