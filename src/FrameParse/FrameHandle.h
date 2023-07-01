#pragma once

// parse header and USE SETTERS to set values
template<class frame_child>
void ParseFrameHeader(frame_child& frame, std::fstream& buffer);

void ParseUndefined(std::fstream& buffer);

// unique parsers for child frames
UFIDFrame* ParseUFID(std::fstream& buffer);

TextFrame* ParseText(std::fstream& buffer);

TXXXFrame* ParseTXXX(std::fstream& buffer);

URLFrame* ParseURL(std::fstream& buffer);

WXXXFrame* ParseWXXX(std::fstream& buffer);

ETCOFrame* ParseETCO(std::fstream& buffer);

USLTFrame* ParseUSLT(std::fstream& buffer);

SYLTFrame* ParseSYLT(std::fstream& buffer);

COMMFrame* ParseCOMM(std::fstream& buffer);

RVA2Frame* ParseRVA2(std::fstream& buffer);

EQU2Frame* ParseEQU2(std::fstream& buffer);

PCNTFrame* ParsePCNT(std::fstream& buffer);

POPMFrame* ParsePOPM(std::fstream& buffer);

RBUFFrame* ParseRBUF(std::fstream& buffer);

LINKFrame* ParseLINK(std::fstream& buffer);

POSSFrame* ParsePOSS(std::fstream& buffer);

USERFrame* ParseUSER(std::fstream& buffer);

OWNEFrame* ParseOWNE(std::fstream& buffer);

COMRFrame* ParseCOMR(std::fstream& buffer);

ENCRFrame* ParseENCR(std::fstream& buffer);

GRIDFrame* ParseGRID(std::fstream& buffer);

PRIVFrame* ParsePRIV(std::fstream& buffer);

SEEKFrame* ParseSEEK(std::fstream& buffer);


