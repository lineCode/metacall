//
// Copyright (c) 2011 Alex Yatskov
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

#include "metacall.hpp"
#include "mc_buffer.hpp"

namespace metacall {


//
// Buffer
//

Buffer::Buffer(const void* data, int count) {
    setData(data, count);
}

Buffer::Buffer() {

}

void Buffer::addToBack(const void* data, int bytes) {
    data_.insert(
        data_.end(),
        static_cast<const byte*>(data),
        static_cast<const byte*>(data) + bytes
    );
}

void Buffer::addToFront(const void* data, int bytes) {
    data_.insert(
        data_.begin(),
        static_cast<const byte*>(data),
        static_cast<const byte*>(data) + bytes
    );
}

int Buffer::removeFromFront(void* data, int bytes) {
    bytes = std::min(static_cast<size_t>(bytes), data_.size());
    if (data != NULL) {
        memcpy(data, &data_[0], bytes);
    }
    data_.erase(data_.begin(), data_.begin() + bytes);
    return bytes;
}

int Buffer::removeFromBack(void* data, int bytes) {
    bytes = std::min(static_cast<size_t>(bytes), data_.size());
    if (data != NULL) {
        memcpy(data, &data_[data_.size() - bytes], bytes);
    }
    data_.erase(data_.end() - bytes, data_.end());
    return bytes;
}

void Buffer::clear() {
    data_.clear();
}

void Buffer::setData(const void* data, int bytes) {
    data_.assign(
        static_cast<const byte*>(data),
        static_cast<const byte*>(data) + bytes
    );
}

const void* Buffer::data() const {
    return &data_[0];
}

void* Buffer::data() {
    return &data_[0];
}

int Buffer::bytes() const {
    return data_.size();
}


}