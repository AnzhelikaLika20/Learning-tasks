#include "readers_util.h"

LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_{std::move(reader)}, limit_{limit} {
}

size_t LimitReader::Read(char *buf, size_t len) {
    size_t temp = limit_;
    limit_ = 0;
    return reader_->Read(buf, temp);
}

TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_{std::move(readers)} {
}

size_t TeeReader::Read(char *buf, size_t len) {
    size_t total = len;
    while (current_ < readers_.size()) {
        size_t current_length = readers_[current_]->Read(buf, len);
        len -= current_length;
        buf += current_length;
        current_++;
        if (len <= 0) {
            break;
        }
    }
    return total - len;
}

HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_{std::move(reader)} {
}

size_t HexDecodingReader::Read(char *buf, size_t len) {
    char *temp_buf = new char[3];
    temp_buf[2] = '\0';
    const int hex_const = 16;
    std::string *data = nullptr;
    for (size_t i = 0; i < len; ++i) {
        size_t current_length = reader_->Read(temp_buf, 2);
        if (current_length == 0) {
            len = i;
            break;
        }
        data = new std::string(temp_buf);
        *buf = static_cast<char>(std::stoul(*data, nullptr, hex_const));
        buf += 1;
        delete data;
    }
    delete[] temp_buf;
    return len;
}
