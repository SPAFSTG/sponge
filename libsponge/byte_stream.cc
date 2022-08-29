#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity):streamcapacity(capacity) {  }

size_t ByteStream::write(const string &data) {
    if (remaining_capacity() == 0)
        return 0;
    size_t n = data.size(), r = remaining_capacity();
    size_t write_size = (r <= n) ? r : n;
    for (size_t i = 0; i < write_size; i++) {
        stream.push_back(data[i]);
    }
    writtenlen += write_size;
    return write_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t peeklen = len >= buffer_size() ? buffer_size() : len;
    string str;
    str.assign(stream.begin(), stream.begin() + peeklen);
    return str;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t poplen = len >= buffer_size() ? buffer_size() : len;
    for (size_t i = 0; i < poplen; i++) {
        stream.pop_front();
    }
    readlen += poplen;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string str = peek_output(len);
    pop_output(len);
    return str;
}

void ByteStream::end_input() { ended_input = true; }

bool ByteStream::input_ended() const { return ended_input; }

size_t ByteStream::buffer_size() const { return stream.size(); }

bool ByteStream::buffer_empty() const { return stream.size()==0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

size_t ByteStream::bytes_written() const { return writtenlen; }

size_t ByteStream::bytes_read() const { return readlen; }

size_t ByteStream::remaining_capacity() const { return streamcapacity - stream.size(); }
