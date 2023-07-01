

#include "Frame.h"
#include "../FrameParse/FrameHandle.h"

void InitializeEnumMap() {

    string_enum["UFID"] = FrameType::UFID;

    string_enum["TIT1"] = FrameType::TEXT;
    string_enum["TIT2"] = FrameType::TEXT;
    string_enum["TIT3"] = FrameType::TEXT;
    string_enum["TALB"] = FrameType::TEXT;
    string_enum["TOAL"] = FrameType::TEXT;
    string_enum["TRCK"] = FrameType::TEXT;
    string_enum["TPOS"] = FrameType::TEXT;
    string_enum["TSST"] = FrameType::TEXT;
    string_enum["TSRC"] = FrameType::TEXT;
    string_enum["TPE1"] = FrameType::TEXT;
    string_enum["TPE2"] = FrameType::TEXT;
    string_enum["TPE3"] = FrameType::TEXT;
    string_enum["TPE4"] = FrameType::TEXT;
    string_enum["TOPE"] = FrameType::TEXT;
    string_enum["TEXT"] = FrameType::TEXT;
    string_enum["TOLY"] = FrameType::TEXT;
    string_enum["TCOM"] = FrameType::TEXT;
    string_enum["TMCL"] = FrameType::TEXT;
    string_enum["TIPL"] = FrameType::TEXT;
    string_enum["TENC"] = FrameType::TEXT;
    string_enum["TBPM"] = FrameType::TEXT;
    string_enum["TLEN"] = FrameType::TEXT;
    string_enum["TKEY"] = FrameType::TEXT;
    string_enum["TLAN"] = FrameType::TEXT;
    string_enum["TCON"] = FrameType::TEXT;
    string_enum["MIME"] = FrameType::TEXT;
    string_enum["TMOO"] = FrameType::TEXT;
    string_enum["TCOP"] = FrameType::TEXT;
    string_enum["TPRO"] = FrameType::TEXT;
    string_enum["TPUB"] = FrameType::TEXT;
    string_enum["TOWN"] = FrameType::TEXT;
    string_enum["TRSN"] = FrameType::TEXT;
    string_enum["TRSO"] = FrameType::TEXT;
    string_enum["TOFN"] = FrameType::TEXT;
    string_enum["TDLY"] = FrameType::TEXT;
    string_enum["TDEN"] = FrameType::TEXT;
    string_enum["TDOR"] = FrameType::TEXT;
    string_enum["TDRC"] = FrameType::TEXT;
    string_enum["TDRL"] = FrameType::TEXT;
    string_enum["TDTG"] = FrameType::TEXT;
    string_enum["TSSE"] = FrameType::TEXT;
    string_enum["TSOA"] = FrameType::TEXT;
    string_enum["TSOP"] = FrameType::TEXT;
    string_enum["TSOT"] = FrameType::TEXT;

    string_enum["TXXX"] = FrameType::TXXX;

    string_enum["WCOM"] = FrameType::URL;
    string_enum["WCOP"] = FrameType::URL;
    string_enum["WOAF"] = FrameType::URL;
    string_enum["WOAR"] = FrameType::URL;
    string_enum["WOAS"] = FrameType::URL;
    string_enum["WORS"] = FrameType::URL;
    string_enum["WPAY"] = FrameType::URL;
    string_enum["WPUB"] = FrameType::URL;

    string_enum["WXXX"] = FrameType::WXXX;
    string_enum["EQU2"] = FrameType::EQU2;
    string_enum["ETCO"] = FrameType::ETCO;
    string_enum["USLT"] = FrameType::USLT;
    string_enum["SYLT"] = FrameType::SYLT;
    string_enum["COMM"] = FrameType::COMM;
    string_enum["RVA2"] = FrameType::RVA2;
    string_enum["PCNT"] = FrameType::PCNT;
    string_enum["POPM"] = FrameType::POPM;
    string_enum["RBUF"] = FrameType::RBUF;
    string_enum["LINK"] = FrameType::LINK;
    string_enum["POSS"] = FrameType::POSS;
    string_enum["USER"] = FrameType::USER;
    string_enum["OWNE"] = FrameType::OWNE;
    string_enum["COMR"] = FrameType::COMR;
    string_enum["ENCR"] = FrameType::ENCR;
    string_enum["GRID"] = FrameType::GRID;
    string_enum["PRIV"] = FrameType::PRIV;
    string_enum["SEEK"] = FrameType::SEEK;
}

Frame* Frame::CreateFrame(std::string& temp_str, std::fstream& buffer) {

    if (string_enum.find(temp_str) == string_enum.end()) {
        ParseUndefined(buffer);
        return nullptr;
    }

    switch (string_enum[temp_str]) {
        case UFID:
            return ParseUFID(buffer);
        case TEXT:
            return ParseText(buffer);
        case TXXX:
            return ParseTXXX(buffer);
        case URL:
            return ParseURL(buffer);
        case WXXX:
            return ParseWXXX(buffer);
        case ETCO:
            return ParseETCO(buffer);
        case USLT:
            return ParseUSLT(buffer);
        case SYLT:
            return ParseSYLT(buffer);
        case COMM:
            return ParseCOMM(buffer);
        case RVA2:
            return ParseRVA2(buffer);
        case EQU2:
            return ParseEQU2(buffer);
        case PCNT:
            return ParsePCNT(buffer);
        case POPM:
            return ParsePOPM(buffer);
        case RBUF:
            return ParseRBUF(buffer);
        case LINK:
            return ParseLINK(buffer);
        case POSS:
            return ParsePOSS(buffer);
        case USER:
            return ParseUSER(buffer);
        case OWNE:
            return ParseOWNE(buffer);
        case COMR:
            return ParseCOMR(buffer);
        case ENCR:
            return ParseENCR(buffer);;
        case GRID:
            return ParseGRID(buffer);
        case PRIV:
            return ParsePRIV(buffer);
        case SEEK:
            return ParseSEEK(buffer);
        default:
            ParseUndefined(buffer);
            return nullptr;
    }

}

