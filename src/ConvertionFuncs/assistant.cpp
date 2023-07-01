
#include "assistant.h"

#include <iostream>
#include <bitset>
#include <vector>


int ConvertToSynchSafe(char* input) {

    std::string temp_str;
    std::string answer;
    std::vector<std::bitset<8>> vec;

    temp_str += std::bitset<8>(*input).to_string();
    input++;
    temp_str += std::bitset<8>(*input).to_string();
    input++;
    temp_str += std::bitset<8>(*input).to_string();
    input++;
    temp_str += std::bitset<8>(*input).to_string();

    for (int i = 0; i < temp_str.size(); i += 8) {
        answer += temp_str[i + 1];
        answer += temp_str[i + 2];
        answer += temp_str[i + 3];
        answer += temp_str[i + 4];
        answer += temp_str[i + 5];
        answer += temp_str[i + 6];
        answer += temp_str[i + 7];
    }

    int test = stoi(answer, 0, 2);

    return stoi(answer, 0, 2);
}


// get frame flags
std::bitset<8> GetFrameFlags(char* input) {

    std::bitset<8> temp_first(*input);
    std::bitset<8> temp_sec(*input + 1);
    std::bitset<8> answer;
    answer[1] = temp_first[2];
    answer[2] = temp_first[3];
    answer[3] = temp_first[4];
    answer[4] = temp_sec[2];
    answer[5] = temp_sec[5];
    answer[6] = temp_sec[6];
    answer[7] = temp_sec[7];
    answer[8] = temp_sec[8];

    return answer;
}


// get tag flags

std::bitset<4> GetTagFlags(char* input) {

    std::bitset<8> temp_first(*input);
    std::bitset<4> answer;
    answer[1] = temp_first[1];
    answer[2] = temp_first[2];
    answer[3] = temp_first[3];
    answer[4] = temp_first[4];

    return answer;
}

bool CheckNameFormat(std::string to_check) {

    if (!isalpha(to_check[0])) {
        return false;
    }

    if (!isalpha(to_check[1])) {
        return false;
    }

    if (!isalpha(to_check[2])) {
        return false;
    }

    if (!isalpha(to_check[3]) && !isdigit(to_check[3])) {
        return false;
    }

    return true;
}

std::string EncodingType(std::string type) {

    if (int(type[0]) == 0) {
        return "ISO-8859-1";
    }

    if (int(type[0]) == 1) {
        return "UTF-16";
    }

    if (int(type[0]) == 2) {
        return "UTF-16BE";
    }

    if (int(type[0]) == 3) {
        return "UTF-8";
    }

}

