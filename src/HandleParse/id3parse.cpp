
#include "id3parse.h"
#include "../ConvertionFuncs/assistant.h"

void id3tag::GetTagFromFile(std::fstream& buffer) {

    ParseTagFile(*this, buffer);
    int frames_size = this->GetFramesSize();

    char frame_name[5];
    std::string name_str;
    InitializeEnumMap();

    while (!buffer.eof()) {
        buffer.read(frame_name, 4);
        name_str = frame_name;
        if (CheckNameFormat(name_str)) {
            Frame* temp_frame = Frame::CreateFrame(name_str, buffer);
            if (temp_frame != nullptr) {
                frames_size -= temp_frame->GetSize();
                temp_frame->SetId(frame_name);
                this->temp_vec_.push_back(temp_frame);
//                std::cout << "New Frame Just Parsed: " << temp_frame->GetId() << "\n";
            }
        } else {
            break;
        }
    }

//    std::cout << "Frames have ended... Closing Function..." << "\n";
}

void id3tag::ParseTagFile(id3tag& tag, std::fstream& buffer) {

    char tag_name[4];
    char tag_version[3];
    char tag_flags[2];
    char tag_size[5];

    buffer.read(tag_name, 3);
    buffer.read(tag_version, 2);
    buffer.read(tag_flags, 1);
    buffer.read(tag_size, 4);

    tag.identifier_ = tag_name;
    tag.id3v2_version_ = int(tag_version[0]);
    tag.id3v2_size_ = ConvertToSynchSafe(tag_size);

    auto bitset = GetTagFlags(tag_flags);
    tag.is_desynchronization_ = bitset[1];
    tag.is_extended_header_ = bitset[2];
    tag.is_experimental_tag_ = bitset[3];
    tag.is_footer_ = bitset[4];
}

