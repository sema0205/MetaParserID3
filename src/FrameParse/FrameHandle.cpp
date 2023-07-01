
#include "../ConvertionFuncs/assistant.h"
#include "../FramesFactory/Frame.h"

#include <vector>

template<class frame_child>
void ParseFrameHeader(frame_child& frame, std::fstream& buffer) {

    char size[5];
    char flags[3];

    buffer.read(size, 4);
    buffer.read(flags, 2);
    frame->SetSize(ConvertToSynchSafe(size));

    auto bitset = GetFrameFlags(flags);
    frame->SetSave(bitset[1]);
    frame->SetFile(bitset[2]);
    frame->SetRead(bitset[3]);
    frame->SetSpecific(bitset[4]);
    frame->SetZip(bitset[5]);
    frame->SetEncoding(bitset[6]);
    frame->SetDesynchronization(bitset[7]);
    frame->SetLength(bitset[8]);
}

void ParseUndefined(std::fstream& buffer) {
    TextFrame* temp = new TextFrame;
    temp->SetId("UNDE");
    ParseFrameHeader(temp, buffer);
    char test[temp->GetSize() + 1];
    buffer.read(test, temp->GetSize());
}

// unique parse for UFID
UFIDFrame* ParseUFID(std::fstream& buffer) {

    UFIDFrame* temp = new UFIDFrame;
    temp->SetId("UFID");
    ParseFrameHeader(temp, buffer);

    std::string header;
    std::string identifier;
    char byte[2];

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    header += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        header += byte;
        bytes_size--;
    }

    while(bytes_size) {

        buffer.read(byte, 1);
        identifier += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {header, identifier};
    temp->SetUFIDVectorValues(vec);
    temp->SetUFIDOwnerHeader(header);
    temp->SetUFIDIdentifier(identifier);

    return temp;
}


// unique parse for Text
TextFrame* ParseText(std::fstream& buffer) {

    TextFrame* temp = new TextFrame;
    ParseFrameHeader(temp, buffer);

    std::string code;
    std::string text;
    char byte[2];

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    code += byte;
    bytes_size--;

    while (bytes_size) {
        buffer.read(byte, 1);
        text += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {code, text};
    temp->SetTextVectorValues(vec);
    temp->SetTextEncoding(code);
    temp->SetTextInformation(text);

    return temp;
}

TXXXFrame* ParseTXXX(std::fstream& buffer) {

    TXXXFrame* temp = new TXXXFrame;
    ParseFrameHeader(temp, buffer);

    std::string code;
    std::string description;
    std::string value;
    char byte[2];

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    code += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        description += byte;
        bytes_size--;
    }

    while(bytes_size) {
        buffer.read(byte, 1);
        value += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {code, description, value};
    temp->SetTXXXVectorValues(vec);
    temp->SetTXXXEncoding(code);
    temp->SetTXXXDescription(description);
    temp->SetTXXXValue(value);

    return temp;
}

URLFrame* ParseURL(std::fstream& buffer) {

    URLFrame* temp = new URLFrame;
    ParseFrameHeader(temp, buffer);

    std::string url_link;
    char byte[2];
    int bytes_size = temp->GetSize();

    while (bytes_size) {
        buffer.read(byte, 1);
        url_link += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {url_link};
    temp->SetURLVectorValues(vec);
    temp->SetURLOwnerHeader(url_link);

    return temp;
}

WXXXFrame* ParseWXXX(std::fstream& buffer) {

    WXXXFrame* temp = new WXXXFrame;
    ParseFrameHeader(temp, buffer);

    std::string code;
    std::string description;
    std::string value;
    char byte[2];

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    code += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        description += byte;
        bytes_size--;
    }

    while(bytes_size) {

        buffer.read(byte, 1);
        value += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {code, description, value};
    temp->SetWXXXVectorValues(vec);
    temp->SetWXXXEncoding(code);
    temp->SetWXXXDescription(description);
    temp->SetWXXXValue(value);

    return temp;
}

ETCOFrame* ParseETCO(std::fstream& buffer) {

    ETCOFrame* temp = new ETCOFrame;
    ParseFrameHeader(temp, buffer);

    std::vector<std::string> vec;
    char situation[2];
    char time[5];
    int bytes_size = temp->GetSize();

    while (bytes_size >= 5) {
        std::string situation_time_str;

        buffer.read(situation, 1);
        situation_time_str += situation;
        bytes_size--;

        buffer.read(time, 4);
        situation_time_str += time;
        bytes_size -= 4;

        vec.push_back(situation_time_str);
    }

    if (bytes_size > 0) {
        std::string left_bytes;
        while (bytes_size) {
            buffer.read(situation, 1);
            left_bytes += situation;
            bytes_size--;
        }
        vec.push_back(left_bytes);
    }

    temp->SetETCOVectorValues(vec);

    return temp;
}

USLTFrame* ParseUSLT(std::fstream& buffer) {

    USLTFrame* temp = new USLTFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char language[4];

    std::string code_str;
    std::string language_str;
    std::string description;
    std::string info;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    bytes_size--;
    buffer.read(language, 3);
    bytes_size -= 3;

    code_str = byte;
    language_str = language;

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        description += byte;
        bytes_size--;
    }

    while (bytes_size > 0) {
        buffer.read(byte, 1);
        info += byte[0];
        if (byte[0] == '\n') {
            bytes_size -= 2;
        } else {
            bytes_size--;
        }
    }

    std::vector<std::string> vec = {code_str, language_str, description, info};
    temp->SetUSLTVectorValues(vec);
    temp->SetUSLTEncoding(code_str);
    temp->SetUSLTLanguage(language_str);
    temp->SetUSLTDescription(description);
    temp->SetUSLTTextInfo(info);

    return temp;
}

SYLTFrame* ParseSYLT(std::fstream& buffer) {

    SYLTFrame* temp = new SYLTFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char add_4_bytes_time[5];
    char language[4];

    std::string code_str;
    std::string language_str;
    std::string format_time_str;
    std::string type_values_str;
    std::string description;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    bytes_size--;
    code_str = byte;

    buffer.read(language, 3);
    bytes_size -= 3;
    language_str = language;

    buffer.read(byte, 1);
    bytes_size--;
    format_time_str = byte;

    buffer.read(byte, 1);
    bytes_size--;
    type_values_str = byte;

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        description += byte;
        bytes_size--;
    }

    std::vector<std::string> vec;
    vec.push_back(code_str);
    vec.push_back(language_str);
    vec.push_back(format_time_str);
    vec.push_back(type_values_str);
    vec.push_back(description);

    std::string temp_str;

    if (bytes_size) {
        buffer.read(byte, 1);
        temp_str += byte;
        bytes_size--;
    }

    while (bytes_size) {

        while (byte[0] != '\000' && bytes_size > 0) {
            buffer.read(byte, 1);
            temp_str += byte;
            bytes_size--;
        }

        buffer.read(add_4_bytes_time, 4);
        bytes_size -= 4;
        temp_str += add_4_bytes_time;
        if (bytes_size >= 4) {
            buffer.read(add_4_bytes_time, 4);
            temp_str += add_4_bytes_time;
            vec.push_back(temp_str);
            bytes_size -= 4;
            temp_str = "";
            if (bytes_size) {
                buffer.read(byte, 1);
                temp_str += byte;
                bytes_size--;
            }
        }
    }

    temp->SetSYLTVectorValues(vec);
    temp->SetSYLTEncoding(code_str);
    temp->SetSYLTLanguage(language_str);
    temp->SetSYLTFormatTime(format_time_str);
    temp->SetSYLTValuesType(type_values_str);
    temp->SetSYLTDescription(description);

    return temp;
}

COMMFrame* ParseCOMM(std::fstream& buffer) {

    COMMFrame* temp = new COMMFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char language[4];

    std::string code_str;
    std::string language_str;
    std::string description;
    std::string info;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    bytes_size--;
    buffer.read(language, 3);
    bytes_size -= 3;

    code_str = byte;
    language_str = language;

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        description += byte;
        bytes_size--;
    }

    while (bytes_size) {
        buffer.read(byte, 1);
        info += byte;
        bytes_size--;
    }


    std::vector<std::string> vec = {code_str, language_str, description, info};
    temp->SetCOMMVectorValues(vec);
    temp->SetCOMMEncoding(code_str);
    temp->SetCOMMLanguage(language_str);
    temp->SetCOMMDescription(description);
    temp->SetCOMMTextInfo(info);

    return temp;
}

RVA2Frame* ParseRVA2(std::fstream& buffer) {

    RVA2Frame* temp = new RVA2Frame;
    ParseFrameHeader(temp, buffer);

    char info[4];
    char byte[2];

    std::string identifier;
    std::string channel_type;
    std::string peak_bits;
    std::string peak_volume;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    identifier += byte[0];
    bytes_size--;

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        identifier += byte[0];
        bytes_size--;
    }

    buffer.read(info, 3);
    bytes_size -= 3;

    channel_type = info[0];
    peak_bits = info[1];
    peak_volume = info[2];

    while (bytes_size) {
        buffer.read(byte, 1);
        peak_volume += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {identifier, channel_type, peak_bits, peak_volume};
    temp->SetRVA2VectorValues(vec);
    temp->SetRVA2Identifier(identifier);
    temp->SetRVA2ChannelType(channel_type);
    temp->SetRVA2PeakBits(peak_bits);
    temp->SetRVA2PeakVolume(peak_volume);

    return temp;
}

EQU2Frame* ParseEQU2(std::fstream& buffer) {

    EQU2Frame* temp = new EQU2Frame;
    ParseFrameHeader(temp, buffer);

    char info[4];
    char byte[2];
    char two_byte[3];

    std::string method_;
    std::string identifier_;
    std::string info_;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    bytes_size--;
    method_ += byte[0];

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        identifier_ += byte[0];
        bytes_size--;
    }

    while (bytes_size) {
        buffer.read(two_byte, 2);
        info_ += two_byte[1];
        info_ += two_byte[2];
        bytes_size -= 2;
    }

    std::vector<std::string> vec = {method_, identifier_, info_};
    temp->SetEQU2VectorValues(vec);
    temp->SetEQU2Method(method_);
    temp->SetEQU2Identifier(identifier_);
    temp->SetEQU2Info(info_);

    return temp;
}

PCNTFrame* ParsePCNT(std::fstream& buffer) {

    PCNTFrame* temp = new PCNTFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    std::string counter;

    int bytes_size = temp->GetSize();

    while(bytes_size) {
        buffer.read(byte, 1);
        counter += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {counter};
    temp->SetPCNTVectorValues(vec);
    temp->SetPCNTIdentifier(counter);

    return temp;
}

POPMFrame* ParsePOPM(std::fstream& buffer) {

    POPMFrame* temp = new POPMFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    std::string email;
    std::string rating;
    std::string counter;

    int bytes_size = temp->GetSize();

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        email += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    bytes_size--;
    rating = byte;

    while (bytes_size) {
        buffer.read(byte, 1);
        counter += byte;
        bytes_size--;
    }

    std::vector<std::string> vec = {email, rating, counter};
    temp->SetPOPMVectorValues(vec);
    temp->SetPOPMEmail(email);
    temp->SetPOPMRating(rating);
    temp->SetPOPMCounter(counter);

    return temp;
}

RBUFFrame* ParseRBUF(std::fstream& buffer) {

    RBUFFrame* temp = new RBUFFrame;
    ParseFrameHeader(temp, buffer);

    char buf[4];
    char flag[2];
    char move[5];
    std::string buf_;
    std::string flag_;
    std::string move_;

    int bytes_size = temp->GetSize();


    buffer.read(buf, 3);
    buf_ += buf[0];
    buf_ += buf[1];
    buf_ += buf[2];
    bytes_size -= 3;

    if (bytes_size >= 1) {
        buffer.read(flag, 1);
        flag_ = flag;
    }

    if (bytes_size >= 4) {
        buffer.read(move, 4);
        move_ += move[0];
        move_ += move[1];
        move_ += move[2];
        move_ += move[3];
    }

    std::vector<std::string> vec;

    if (!buf_.empty()) {
        vec.push_back(buf_);
    }

    if (!flag_.empty()) {
        vec.push_back(flag_);
    }

    if (!move_.empty()) {
        vec.push_back(move_);
    }


    temp->SetRBUFVectorValues(vec);
    temp->SetRBUFBufferSize(buf_);
    temp->SetRBUFFlagsInfo(flag_);
    temp->SetRBUFMoveNext(move_);

    return temp;
}

LINKFrame* ParseLINK(std::fstream& buffer) {

    LINKFrame* temp = new LINKFrame;
    ParseFrameHeader(temp, buffer);

    char frame_name[5];
    char byte[2];
    std::string name;
    std::string url;
    std::string add;

    int bytes_size = temp->GetSize();

    buffer.read(frame_name, 4);
    name += frame_name[0];
    name += frame_name[1];
    name += frame_name[2];
    name += frame_name[3];
    bytes_size -= 4;

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        url += byte[0];
        bytes_size--;
    }

    while (bytes_size) {
        buffer.read(byte, 1);
        add += byte[0];
        bytes_size--;
    }

    std::vector<std::string> vec;
    vec.push_back(name);
    vec.push_back(url);

    if (!add.empty()) {
        vec.push_back(add);
    }

    temp->SetLINKVectorValues(vec);
    temp->SetLINKIdentifierName(name);
    temp->SetLINKUrlInfo(url);
    temp->SetLINKAddInfo(add);

    return temp;
}

POSSFrame* ParsePOSS(std::fstream& buffer) {

    POSSFrame* temp = new POSSFrame;
    ParseFrameHeader(temp, buffer);

    char format_time[5];
    char byte[2];
    std::string info;

    int bytes_size = temp->GetSize();

    std::vector<std::string> vec;

    while (bytes_size) {
        buffer.read(format_time, 4);
        info += format_time;
        bytes_size -= 4;

        buffer.read(byte, 1);
        info += byte;
        bytes_size--;

        vec.push_back(info);
    }

    temp->SetPOSSVectorValues(vec);

    return temp;
}

USERFrame* ParseUSER(std::fstream& buffer) {

    USERFrame* temp = new USERFrame;
    ParseFrameHeader(temp, buffer);

    char language[4];
    char byte[2];
    std::string encode;
    std::string lang;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    encode = byte[0];
    bytes_size--;

    buffer.read(language, 3);
    lang += language[0];
    lang += language[1];
    lang += language[2];
    bytes_size -= 3;

    std::string text;

    while (bytes_size) {
        buffer.read(byte, 1);
        text += byte[0];
        bytes_size--;
    }

    std::vector<std::string> vec = {encode, lang, text};
    temp->SetUSERVectorValues(vec);
    temp->SetUSEREncode(encode);
    temp->SetUSERLanguage(lang);
    temp->SetUSERTextInfo(text);

    return temp;
}

OWNEFrame* ParseOWNE(std::fstream& buffer) {

    OWNEFrame* temp = new OWNEFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char date[9];

    std::string encode;
    std::string paid_price;
    std::string date_price;
    std::string seller_info;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    bytes_size--;
    encode += byte[0];

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        paid_price += byte[0];
        bytes_size--;
    }

    buffer.read(date, 8);
    date_price += date;
    bytes_size -= 8;

    while (bytes_size) {
        buffer.read(byte, 1);
        seller_info += byte[0];
        bytes_size--;
    }

    std::vector<std::string> vec = {encode, paid_price, date_price, seller_info};
    temp->SetOWNEVectorValues(vec);
    temp->SetOWNEEncode(encode);
    temp->SetOWNEPaidPrice(paid_price);
    temp->SetOWNEDatePrice(date_price);
    temp->SetOWNESeller(seller_info);

    return temp;
}

COMRFrame* ParseCOMR(std::fstream& buffer) {

    COMRFrame* temp = new COMRFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char date[9];
    std::string text_encoding_;
    std::string price_info_;
    std::string date_info_;
    std::string contact_url_;
    std::string type_get_;
    std::string seller_name_;
    std::string description_;
    std::string type_image_;
    std::string logo_seller_;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    text_encoding_ = byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        price_info_ += byte;
        bytes_size--;
    }

    buffer.read(date, 8);
    date_info_ += date;
    bytes_size -= 8;

    buffer.read(byte, 1);
    contact_url_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        contact_url_ += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    type_get_ = byte;
    bytes_size--;

    buffer.read(byte, 1);
    seller_name_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        seller_name_ += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    description_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        description_ += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    type_image_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        type_image_ += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    logo_seller_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        logo_seller_ += byte;
        bytes_size--;
    }

    std::vector<std::string> vec;
    vec.push_back(text_encoding_);
    vec.push_back(price_info_);
    vec.push_back(date_info_);
    vec.push_back(contact_url_);
    vec.push_back(type_get_);
    vec.push_back(seller_name_);
    vec.push_back(description_);
    vec.push_back(type_image_);

    if (!logo_seller_.empty()) {
        vec.push_back(logo_seller_);
    }

    temp->SetCOMRVectorValues(vec);
    temp->SetCOMREncode(text_encoding_);
    temp->SetCOMRPriceInfo(price_info_);
    temp->SetCOMRDateInfo(date_info_);
    temp->SetCOMRContactUrl(contact_url_);
    temp->SetCOMRTypeGet(type_get_);
    temp->SetCOMRSellerName(seller_name_);
    temp->SetCOMRDescription(description_);
    temp->SetCOMRTypeImage(type_image_);
    temp->SetCOMRSellerLogo(logo_seller_);

    return temp;
}

ENCRFrame* ParseENCR(std::fstream& buffer) {

    ENCRFrame* temp = new ENCRFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char date[9];
    std::string identifier_;
    std::string method_symbol_;
    std::string encoding_data_;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    identifier_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        identifier_ += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    method_symbol_ = byte;
    bytes_size--;

    while(bytes_size) {
        buffer.read(byte, 1);
        encoding_data_ += byte;
        bytes_size--;
    }

    std::vector<std::string> vec;
    vec.push_back(identifier_);
    vec.push_back(method_symbol_);

    if (!encoding_data_.empty()) {
        vec.push_back(encoding_data_);
    }

    temp->SetENCRVectorValues(vec);
    temp->SetENCROwnerIdentifier(identifier_);
    temp->SetENCRMethodSymbol(method_symbol_);
    temp->SetENCREncodingData(encoding_data_);

    return temp;
}

GRIDFrame* ParseGRID(std::fstream& buffer) {

    GRIDFrame* temp = new GRIDFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    char date[9];
    std::string identifier_;
    std::string group_symbol_;
    std::string group_data_;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    identifier_ += byte;
    bytes_size--;

    while(byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        identifier_ += byte;
        bytes_size--;
    }

    buffer.read(byte, 1);
    group_symbol_ = byte;
    bytes_size--;

    while(bytes_size) {
        buffer.read(byte, 1);
        group_data_ += byte;
        bytes_size--;
    }

    std::vector<std::string> vec;
    vec.push_back(identifier_);
    vec.push_back(group_symbol_);

    if (!group_data_.empty()) {
        vec.push_back(group_data_);
    }

    temp->SetGRIDVectorValues(vec);
    temp->SetGRIDOwnerIdentifier(identifier_);
    temp->SetGRIDGroupSymbol(group_symbol_);
    temp->SetGRIDGroupData(group_data_);

    return temp;
}

PRIVFrame* ParsePRIV(std::fstream& buffer) {

    PRIVFrame* temp = new PRIVFrame;
    ParseFrameHeader(temp, buffer);

    char byte[2];
    std::string identifier_;
    std::string private_data;

    int bytes_size = temp->GetSize();

    buffer.read(byte, 1);
    identifier_ += byte[0];
    bytes_size--;

    while (byte[0] != '\000' && bytes_size > 0) {
        buffer.read(byte, 1);
        identifier_ += byte[0];
        bytes_size--;
    }

    while (bytes_size) {
        buffer.read(byte, 1);
        private_data += byte;
        bytes_size--;
    }

    std::vector<std::string> vec;
    vec.push_back(identifier_);

    if (!private_data.empty()) {
        vec.push_back(private_data);
    }

    temp->SetPRIVVectorValues(vec);
    temp->SetPRIVOwnerIdentifier(identifier_);
    temp->SetPRIVPrivateData(private_data);

    return temp;
}

SEEKFrame* ParseSEEK(std::fstream& buffer) {

    SEEKFrame* temp = new SEEKFrame;
    ParseFrameHeader(temp, buffer);

    char info_block[5];
    std::string change_move_;

    int bytes_size = temp->GetSize();

    buffer.read(info_block, 4);
    change_move_ = info_block;

    std::vector<std::string> vec;
    vec.push_back(change_move_);

    temp->SetSEEKVectorValues(vec);
    temp->SetSEEKChangeMove(change_move_);

    return temp;
}
