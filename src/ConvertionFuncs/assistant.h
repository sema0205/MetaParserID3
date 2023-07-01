#pragma once

#include <bitset>

// 32 bit synsafe number
int ConvertToSynchSafe(char* input);

// get frame flags
std::bitset<8> GetFrameFlags(char* input);

// get tag flags
std::bitset<4> GetTagFlags(char* input);

bool CheckNameFormat(std::string to_check);

std::string EncodingType(std::string type);
