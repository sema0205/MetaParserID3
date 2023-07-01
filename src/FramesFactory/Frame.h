#pragma once

#include "../ConvertionFuncs/assistant.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

enum FrameType {
    UFID,
    TEXT,
    TXXX,
    URL,
    WXXX,
    ETCO,
    USLT,
    SYLT,
    COMM,
    RVA2,
    EQU2,
    PCNT,
    POPM,
    RBUF,
    LINK,
    POSS,
    USER,
    OWNE,
    COMR,
    ENCR,
    GRID,
    PRIV,
    SEEK
};

static std::unordered_map<std::string, FrameType> string_enum;

void InitializeEnumMap();

class Frame {
public:
    virtual std::vector<std::string> GetFrameDataSet() = 0;
    virtual void PrintFrameInfo() = 0;
    static Frame* CreateFrame(std::string& temp_str, std::fstream& buffer);

    void SetId(std::string a) {
        frame_id_ = a;
    }

    void SetSize(int a) {
        frame_size_ = a;
    }

    void SetSave(bool a) {
        is_save_frame_ = a;
    }

    void SetFile(bool a) {
        is_file_frame_ = a;
    }

    void SetRead(bool a) {
        is_read_only = a;
    }

    void SetSpecific(bool a) {
        is_specific_group_ = a;
    }

    void SetZip(bool a) {
        is_zipped_ = a;
    }

    void SetEncoding(bool a) {
        is_encode_ = a;
    }

    void SetDesynchronization(bool a) {
        is_desynchronization_ = a;
    }

    void SetLength(bool a) {
        is_length_ = a;
    }

    std::string GetId() {
        return frame_id_;
    }

    int GetSize() {
        return frame_size_;
    }

    bool GetSave() {
        return is_save_frame_;
    }

    bool GetFile() {
        return is_file_frame_;
    }

    bool GetRead() {
        return is_read_only;
    }

    bool GetSpecific() {
        return is_specific_group_;
    }

    bool GetZip() {
        return is_zipped_;
    }

    bool GetEncoding() {
        return is_encode_;
    }

    bool GetDesynchronization() {
        return is_desynchronization_;
    }

    bool GetLength() {
        return is_length_;
    }

private:
    std::string frame_id_;
    int frame_size_;
    bool is_save_frame_;
    bool is_file_frame_;
    bool is_read_only;
    bool is_specific_group_;
    bool is_zipped_;
    bool is_encode_;
    bool is_desynchronization_;
    bool is_length_;
};

class UFIDFrame : public Frame {
public:

    UFIDFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Unique file identifier\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tOwner Identifier: " << owner_header_ << "\n";
        std::cout << "\t\tIdentifier Binary: ";
        for (auto el : identifier_) {
            std::cout << int(el);
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetUFIDOwnerHeader() {
        return owner_header_;
    }

    std::string GetUFIDIdentifier() {
        return identifier_;
    }

    std::vector<std::string> GetUFIDVectorValues() {
        return all_values_;
    }

    void SetUFIDOwnerHeader(std::string& temp) {
        owner_header_ = temp;
    }

    void SetUFIDIdentifier(std::string& temp) {
        identifier_ = temp;
    }

    void SetUFIDVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string owner_header_;
    std::string identifier_;
};


class TextFrame : public Frame {
public:

    TextFrame(){};

    void PrintFrameInfo() override {
        std::cout << "Text information\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tInformation: " << information_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetTextEncoding() {
        return text_encoding_;
    }

    std::string GetTextInformation() {
        return information_;
    }

    std::vector<std::string> GetTextVectorValues() {
        return all_values_;
    }

    void SetTextEncoding(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetTextInformation(std::string& temp) {
        information_ = temp;
    }

    void SetTextVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string information_;
};

class TXXXFrame : public Frame {
public:

    TXXXFrame() {};

    void PrintFrameInfo() override {
        std::cout << "User defined text information frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tDescription: " << description_ << "\n";
        std::cout << "\t\tValue: " << value_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetTXXXOwnerHeader() {
        return text_encoding_;
    }

    std::string GetTXXXIdentifier() {
        return description_;
    }

    std::string GetTXXXValue() {
        return value_;
    }

    std::vector<std::string> GetTXXXVectorValues() {
        return all_values_;
    }

    void SetTXXXEncoding(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetTXXXDescription(std::string& temp) {
        description_ = temp;
    }

    void SetTXXXValue(std::string& temp) {
        value_ = temp;
    }

    void SetTXXXVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string description_;
    std::string value_;
};

class URLFrame : public Frame {
public:

    URLFrame() {};

    void PrintFrameInfo() override {
        std::cout << "URL link frames\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tURL: " << url_link_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetURLOwnerHeader() {
        return url_link_;
    }

    std::vector<std::string> GetURLVectorValues() {
        return all_values_;
    }

    void SetURLOwnerHeader(std::string& temp) {
        url_link_ = temp;
    }

    void SetURLVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string url_link_;
};

class WXXXFrame : public Frame {
public:

    WXXXFrame() {};

    void PrintFrameInfo() override {
        std::cout << "User defined text information frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tDescription: " << description_ << "\n";
        std::cout << "\t\tURL: " << value_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetWXXXOwnerHeader() {
        return text_encoding_;
    }

    std::string GetWXXXIdentifier() {
        return description_;
    }

    std::string GetWXXXValue() {
        return value_;
    }

    std::vector<std::string> GetWXXXVectorValues() {
        return all_values_;
    }

    void SetWXXXEncoding(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetWXXXDescription(std::string& temp) {
        description_ = temp;
    }

    void SetWXXXValue(std::string& temp) {
        value_ = temp;
    }

    void SetWXXXVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string description_;
    std::string value_;
};

class ETCOFrame : public Frame {
public:

    ETCOFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Event timing codes\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tTime stamp format: " << int(all_values_[0][0]) << "\n";
        std::cout << "\t\tEnd of initial silence: " << int(all_values_[1][0]) << "\n";
        std::cout << "\t\tMain Part start: " << int(all_values_[2][0]) << "\n";

        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::vector<std::string> GetETCOVectorValues() {
        return all_values_;
    }

    void SetETCOVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
};


class USLTFrame : public Frame {
public:

    USLTFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Unsynchronised lyrics/text transcription\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tLanguage: " << language_[0] << language_[1] << language_[2] << "\n";
        std::cout << "\t\tContent descriptor: " << quick_description_ << "\n";
        std::cout << "\t\tLyrics/text: " << full_text_info_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetUSLTEncoding() {
        return text_encoding_;
    }

    std::string GetUSLTLanguage() {
        return language_;
    }

    std::string GetUSLTDescription() {
        return quick_description_;
    }

    std::string GetUSLTTextInfo() {
        return full_text_info_;
    }

    std::vector<std::string> GetUSLTVectorValues() {
        return all_values_;
    }

    void SetUSLTEncoding(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetUSLTLanguage(std::string& temp) {
        language_ = temp;
    }

    void SetUSLTDescription(std::string& temp) {
        quick_description_ = temp;
    }

    void SetUSLTTextInfo(std::string& temp) {
        full_text_info_ = temp;
    }

    void SetUSLTVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string language_;
    std::string quick_description_;
    std::string full_text_info_;
};

class SYLTFrame : public Frame {
public:

    SYLTFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Synchronised lyrics/text\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tLanguage: " << language_[0] << language_[1] << language_[2] << "\n";
        std::cout << "\t\tTime stamp format: " << int(format_time_[0])<< "\n";
        std::cout << "\t\tContent type: " << int(type_values_[0])<< "\n";
        std::cout << "\t\tContent descriptor: " << description_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetSYLTEncoding() {
        return text_encoding_;
    }

    std::string GetSYLTLanguage() {
        return language_;
    }

    std::string GetSYLTFormatTime() {
        return format_time_;
    }

    std::string GetSYLTValuesType() {
        return type_values_;
    }

    std::string GetSYLTDescription() {
        return description_;
    }

    std::vector<std::string> GetSYLTVectorValues() {
        return all_values_;
    }

    void SetSYLTEncoding(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetSYLTLanguage(std::string& temp) {
        language_ = temp;
    }

    void SetSYLTFormatTime(std::string& temp) {
        format_time_ = temp;
    }

    void SetSYLTValuesType(std::string& temp) {
        type_values_ = temp;
    }

    void SetSYLTDescription(std::string& temp) {
        description_ = temp;
    }

    void SetSYLTVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string language_;
    std::string format_time_;
    std::string type_values_;
    std::string description_;
};


class COMMFrame : public Frame {
public:

    COMMFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Comments\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tLanguage: " << language_[0] << language_[1] << language_[2] << "\n";
        std::cout << "\t\tShort content descrip.: " << quick_description_ << "\n";
        std::cout << "\t\tThe actual text: " << full_text_info_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetCOMMEncoding() {
        return text_encoding_;
    }

    std::string GetCOMMLanguage() {
        return language_;
    }

    std::string GetCOMMDescription() {
        return quick_description_;
    }

    std::string GetCOMMTextInfo() {
        return full_text_info_;
    }

    std::vector<std::string> GetCOMMVectorValues() {
        return all_values_;
    }

    void SetCOMMEncoding(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetCOMMLanguage(std::string& temp) {
        language_ = temp;
    }

    void SetCOMMDescription(std::string& temp) {
        quick_description_ = temp;
    }

    void SetCOMMTextInfo(std::string& temp) {
        full_text_info_ = temp;
    }

    void SetCOMMVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string language_;
    std::string quick_description_;
    std::string full_text_info_;
};

class RVA2Frame : public Frame {
public:

    RVA2Frame() {};

    void PrintFrameInfo() override {
        std::cout << "Relative volume adjustment (2)\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tIdentification: " << identifier << "\n";
        std::cout << "\t\tType of channel: " << int(channel_type[0]) << "\n";
        std::cout << "\t\tVolume adjustment: " << int(peak_volume[0]) << "\n";
        std::cout << "\t\tBits representing peak: " << int(peak_volume[1]) << "\n";
        std::cout << "\t\tPeak volume: " << int(peak_volume[3]) << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetRVA2Identifier() {
        return identifier;
    }

    std::string GetRVA2ChannelType() {
        return channel_type;
    }

    std::string GetRVA2PeakBits() {
        return peak_bits;
    }

    std::string GetRVA2PeakVolume() {
        return peak_volume;
    }

    std::vector<std::string> GetRVA2VectorValues() {
        return all_values_;
    }

    void SetRVA2Identifier(std::string& temp) {
        identifier = temp;
    }

    void SetRVA2ChannelType(std::string& temp) {
        channel_type = temp;
    }

    void SetRVA2PeakBits(std::string& temp) {
        peak_bits = temp;
    }

    void SetRVA2PeakVolume(std::string& temp) {
        peak_volume = temp;
    }

    void SetRVA2VectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string identifier;
    std::string channel_type;
    std::string peak_bits;
    std::string peak_volume;
};

class EQU2Frame : public Frame {
public:

    EQU2Frame() {};

    void PrintFrameInfo() override {
        std::cout << "Equalisation (2)\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tInterpolation method: " << int(method_[0]) << "\n";
        std::cout << "\t\tIdentification: " << identifier_ << "\n";

        int it = 0;
        while (it < info_.size()) {
            std::cout << "\t\tFrequency: " << int(info_[it]) << " ";
            it += 2;
            std::cout << "Volume adjustment: " << int(info_[it]) << "\n";
            it += 2;
        }

        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string SetEQU2Method() {
        return method_;
    }

    std::string SetEQU2Identifier() {
        return identifier_;
    }

    std::string SetEQU2Info() {
        return info_;
    }

    std::vector<std::string> GetRVA2VectorValues() {
        return all_values_;
    }

    void SetEQU2Method(std::string& temp) {
        method_ = temp;
    }

    void SetEQU2Identifier(std::string& temp) {
        identifier_ = temp;
    }

    void SetEQU2Info(std::string& temp) {
        info_ = temp;
    }

    void SetEQU2VectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string method_;
    std::string identifier_;
    std::string info_;
};


class PCNTFrame : public Frame {
public:

    PCNTFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Play counter\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tCounter: " << int(counter_[0]) << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetPCNTIdentifier() {
        return counter_;
    }

    std::vector<std::string> GetPCNTVectorValues() {
        return all_values_;
    }

    void SetPCNTIdentifier(std::string& temp) {
        counter_ = temp;
    }

    void SetPCNTVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string counter_;
};

class POPMFrame : public Frame {
public:

    POPMFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Popularimeter\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tEmail to user: " << email_ << "\n";
        std::cout << "\t\tRating: " << int(rating_[0]) << "\n";
        std::cout << "\t\tCounter: " << int(counter_[0]) << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetPOPMEmail() {
        return email_;
    }

    std::string GetPOPMRating() {
        return rating_;
    }

    std::string GetPOPMCounter() {
        return counter_;
    }

    void SetPOPMEmail(std::string& temp) {
        email_ = temp;
    }

    void SetPOPMRating(std::string& temp) {
        rating_ = temp;
    }

    void SetPOPMCounter(std::string& temp) {
        counter_ = temp;
    }

    void SetPOPMVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string email_;
    std::string rating_;
    std::string counter_;
};

class RBUFFrame : public Frame {
public:

    RBUFFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Recommended buffer size\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tBuffer size: " << int(buffer_size_[2]) << "\n";
        std::cout << "\t\tEmbedded info flag: " << int(flags_info_[0]) << "\n";
        std::cout << "\t\tOffset to next tag: " << int(move_next_[0]) << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetRBUFBufferSize() {
        return buffer_size_;
    }

    std::string GetRBUFFlagsInfo() {
        return flags_info_;
    }

    std::string GetRBUFMoveNext() {
        return move_next_;
    }

    void SetRBUFBufferSize(std::string& temp) {
        buffer_size_ = temp;
    }

    void SetRBUFFlagsInfo(std::string& temp) {
        flags_info_ = temp;
    }

    void SetRBUFMoveNext(std::string& temp) {
        move_next_ = temp;
    }

    void SetRBUFVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string buffer_size_;
    std::string flags_info_;
    std::string move_next_;
};

class LINKFrame : public Frame {
public:

    LINKFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Linked information\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tFrame identifier: " << identifier_name_ << "\n";
        std::cout << "\t\tURL: " << url_info_ << "\n";
        std::cout << "\t\tID and additional data: " << additional_info_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetLINKIdentifierName() {
        return identifier_name_;
    }

    std::string GetLINKUrlInfo() {
        return url_info_;
    }

    std::string GetLINKAddInfo() {
        return additional_info_;
    }

    void SetLINKIdentifierName(std::string& temp) {
        identifier_name_ = temp;
    }

    void SetLINKUrlInfo(std::string& temp) {
        url_info_ = temp;
    }

    void SetLINKAddInfo(std::string& temp) {
        additional_info_ = temp;
    }

    void SetLINKVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string identifier_name_;
    std::string url_info_;
    std::string additional_info_;
};

class POSSFrame : public Frame {
public:

    POSSFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Position synchronisation frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tTime stamp format: " << int(all_values_[0][0]) << "\n";
        std::cout << "\t\tPosition: " << int(all_values_[0][1]) << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    void SetPOSSVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
};


class USERFrame : public Frame {
public:

    USERFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Terms of use frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tLanguage: " << language_ << "\n";
        std::cout << "\t\tThe actual text : " << text_info_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetUSEREncode() {
        return text_encoding_;
    }

    std::string GetUSERLanguage() {
        return language_;
    }

    std::string GetUSERTextInfo() {
        return text_info_;
    }

    void SetUSEREncode(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetUSERLanguage(std::string& temp) {
        language_ = temp;
    }

    void SetUSERTextInfo(std::string& temp) {
        text_info_ = temp;
    }

    void SetUSERVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string language_;
    std::string text_info_;
};

class OWNEFrame : public Frame {
public:

    OWNEFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Ownership frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tPrice paid: " << paid_price_ << "\n";
        std::cout << "\t\tDate of purch.: " << date_price_ << "\n";
        std::cout << "\t\tSeller: " << seller_ << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetOWNEEncode() {
        return text_encoding_;
    }

    std::string GetOWNEPaidPrice() {
        return paid_price_;
    }

    std::string GetOWNEDatePrice() {
        return date_price_;
    }

    std::string GetOWNESeller() {
        return seller_;
    }

    void SetOWNEEncode(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetOWNEPaidPrice(std::string& temp) {
        paid_price_ = temp;
    }

    void SetOWNEDatePrice(std::string& temp) {
        date_price_ = temp;
    }

    void SetOWNESeller(std::string& temp) {
        seller_ = temp;
    }

    void SetOWNEVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string paid_price_;
    std::string date_price_;
    std::string seller_;
};

class COMRFrame : public Frame {
public:

    COMRFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Commercial frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tText encoding: " << EncodingType(text_encoding_) << "\n";
        std::cout << "\t\tPrice string: " << price_info_ << "\n";
        std::cout << "\t\tValid until: " << date_info_ << "\n";
        std::cout << "\t\tContact URL: " << contact_url_ << "\n";
        std::cout << "\t\tReceived as: " << int(type_get_[0]) << "\n";
        std::cout << "\t\tName of seller: " << seller_name_ << "\n";
        std::cout << "\t\tDescription: " << description_ << "\n";
        std::cout << "\t\tPicture MIME type: " << type_image_ << "\n";
        std::cout << "\t\tSeller logo: ";
        int it = 0;
        while(it < logo_seller_.size()) {
            std::cout << int(logo_seller_[it]);
            it++;
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetCOMREncode() {
        return text_encoding_;
    }

    std::string GetCOMRPriceInfo() {
        return price_info_;
    }

    std::string GetCOMRDateInfo() {
        return date_info_;
    }

    std::string GetCOMRContactUrl() {
        return contact_url_;
    }

    std::string GetCOMRTypeGet() {
        return type_get_;
    }

    std::string GetCOMRSellerName() {
        return seller_name_;
    }

    std::string GetCOMRDescription() {
        return description_;
    }

    std::string GetCOMRTypeImage() {
        return type_image_;
    }

    std::string GetCOMRSellerLogo() {
        return logo_seller_;
    }

    void SetCOMREncode(std::string& temp) {
        text_encoding_ = temp;
    }

    void SetCOMRPriceInfo(std::string& temp) {
        price_info_ = temp;
    }

    void SetCOMRDateInfo(std::string& temp) {
        date_info_ = temp;
    }

    void SetCOMRContactUrl(std::string& temp) {
        contact_url_ = temp;
    }

    void SetCOMRTypeGet(std::string& temp) {
        type_get_ = temp;
    }

    void SetCOMRSellerName(std::string& temp) {
        seller_name_ = temp;
    }

    void SetCOMRDescription(std::string& temp) {
        description_ = temp;
    }

    void SetCOMRTypeImage(std::string& temp) {
        type_image_ = temp;
    }

    void SetCOMRSellerLogo(std::string& temp) {
        logo_seller_ = temp;
    }

    void SetCOMRVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string text_encoding_;
    std::string price_info_;
    std::string date_info_;
    std::string contact_url_;
    std::string type_get_;
    std::string seller_name_;
    std::string description_;
    std::string type_image_;
    std::string logo_seller_;
};


class ENCRFrame : public Frame {
public:

    ENCRFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Encryption method registration\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tOwner identifier: " << identifier_ << "\n";
        std::cout << "\t\tMethod symbol: " << int(method_symbol_[0]) << "\n";
        std::cout << "\t\tEncryption data: ";
        int it = 0;
        while(it < encoding_data_.size()) {
            std::cout << int(encoding_data_[it]);
            it++;
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetENCROwnerIdentifier() {
        return identifier_;
    }

    std::string GetENCRMethodSymbol() {
        return method_symbol_;
    }

    std::string GetENCREncodingData() {
        return encoding_data_;
    }

    void SetENCROwnerIdentifier(std::string& temp) {
        identifier_ = temp;
    }

    void SetENCRMethodSymbol(std::string& temp) {
        method_symbol_ = temp;
    }

    void SetENCREncodingData(std::string& temp) {
        encoding_data_ = temp;
    }

    void SetENCRVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string identifier_;
    std::string method_symbol_;
    std::string encoding_data_;
};


class GRIDFrame : public Frame {
public:

    GRIDFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Group identification registration\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tOwner identifier: " << identifier_ << "\n";
        std::cout << "\t\tGroup symbol: " << int(method_symbol_[0]) << "\n";
        std::cout << "\t\tGroup dependent data: ";
        int it = 0;
        while(it < group_data_.size()) {
            std::cout << int(group_data_[it]);
            it++;
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetGRIDOwnerIdentifier() {
        return identifier_;
    }

    std::string GetGRIDMGroupSymbol() {
        return method_symbol_;
    }

    std::string GetGRIDGroupData() {
        return group_data_;
    }

    void SetGRIDOwnerIdentifier(std::string& temp) {
        identifier_ = temp;
    }

    void SetGRIDGroupSymbol(std::string& temp) {
        method_symbol_ = temp;
    }

    void SetGRIDGroupData(std::string& temp) {
        group_data_ = temp;
    }

    void SetGRIDVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string identifier_;
    std::string method_symbol_;
    std::string group_data_;
};


class PRIVFrame : public Frame {
public:

    PRIVFrame() {};

    void PrintFrameInfo() override {
        std::cout << "Private frame\n";
        std::cout << "\tType: " << GetId() << "\n";
        std::cout << "\t\tOwner identifier : " << identifier_ << "\n";
        std::cout << "\t\tThe private data: ";
        int it = 0;
        while(it < private_data_.size()) {
            std::cout << int(private_data_[it]);
            it++;
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetPRIVOwnerIdentifier() {
        return identifier_;
    }

    std::string GetPRIVPrivateData() {
        return private_data_;
    }

    void SetPRIVOwnerIdentifier(std::string& temp) {
        identifier_ = temp;
    }

    void SetPRIVPrivateData(std::string& temp) {
        private_data_ = temp;
    }

    void SetPRIVVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string identifier_;
    std::string private_data_;
};

class SEEKFrame : public Frame {
public:

    SEEKFrame() {};

    void PrintFrameInfo() override {
        std::cout << "ok";
        std::cout << "\n";
    }

    std::vector<std::string> GetFrameDataSet() override {
        return all_values_;
    }

    std::string GetSEEKChangeMove() {
        return change_move_;
    }

    void SetSEEKChangeMove(std::string& temp) {
        change_move_ = temp;
    }

    void SetSEEKVectorValues(std::vector<std::string>& temp) {
        all_values_ = temp;
    }

private:
    std::vector<std::string> all_values_;
    std::string change_move_;
};

