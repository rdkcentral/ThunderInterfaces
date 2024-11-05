/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Metrological has done changes to the original interface definition
 * from Fraunhofer FOKUS
 */
/*
 * Copyright 2014 Fraunhofer FOKUS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

class BufferReader {
private:
    BufferReader() = delete;
    BufferReader(const BufferReader&) = delete;
    BufferReader& operator=(const BufferReader&) = delete;

PUSH_WARNING("-Wshift-count-overflow")
    // Internal implementation of multi-byte reads
    template <typename T>
    bool Read(T* v)
    {
        if ((v != nullptr) && (HasBytes(sizeof(T)) == true)) {
            T tmp = 0;
            for (size_t i = 0; i < sizeof(T); i++) {
                tmp <<= 8;
                tmp += buf_[pos_++];
            }
            *v = tmp;
            return true;
        }
        return false;
    }
POP_WARNING()

public:
    inline BufferReader(const uint8_t* buf, size_t size)
        : buf_(buf)
        , size_(buf != NULL ? size : 0)
        , pos_(0)
    {
    }
    inline ~BufferReader() = default;

public:
    inline bool HasBytes(size_t count) const { return pos_ + count <= size_; }
    inline bool IsEOF() const { return pos_ >= size_; }
    inline const uint8_t* data() const { return buf_; }
    inline size_t size() const { return size_; }
    inline size_t pos() const { return pos_; }

    // Read a value from the stream, performing endian correction,
    // and advance the stream pointer.
    inline bool Read1(uint8_t* v) WARNING_RESULT_NOT_USED { return Read(v); }
    inline bool Read2(uint16_t* v) WARNING_RESULT_NOT_USED { return Read(v); }
    inline bool Read2s(int16_t* v) WARNING_RESULT_NOT_USED { return Read(v); }
    inline bool Read4(uint32_t* v) WARNING_RESULT_NOT_USED { return Read(v); }
    inline bool Read4s(int32_t* v) WARNING_RESULT_NOT_USED { return Read(v); }
    inline bool Read8(uint64_t* v) WARNING_RESULT_NOT_USED { return Read(v); }
    inline bool Read8s(int64_t* v) WARNING_RESULT_NOT_USED { return Read(v); }

    inline bool ReadString(std::string* str, size_t count) WARNING_RESULT_NOT_USED
    {
        if ((str != nullptr) && (HasBytes(count) == true)) {
            str->assign(buf_ + pos_, buf_ + pos_ + count);
            pos_ += count;
            return true;
        }
        return false;
    }
    inline bool ReadVec(std::vector<uint8_t>* vec, size_t count) WARNING_RESULT_NOT_USED
    {
        if ((vec != nullptr) && (HasBytes(count) == true)) {
            vec->clear();
            vec->insert(vec->end(), buf_ + pos_, buf_ + pos_ + count);
            pos_ += count;
            return true;
        }
        return false;
    }

    // These variants read a 4-byte integer of the corresponding signedness and
    // store it in the 8-byte return type.
    inline bool Read4Into8(uint64_t* v) WARNING_RESULT_NOT_USED
    {
        uint32_t tmp;
        if ((v != nullptr) && (Read4(&tmp) == true)) {
            *v = tmp;
            return true;
        }
        return false;
    }
    inline bool Read4sInto8s(int64_t* v) WARNING_RESULT_NOT_USED
    {
        int32_t tmp;
        if ((v != nullptr) && (Read4s(&tmp) == true)) {
            *v = tmp;
            return true;
        }
        return false;
    }

    // Advance the stream by this many bytes.
    inline bool SkipBytes(size_t bytes) WARNING_RESULT_NOT_USED
    {
        if (HasBytes(bytes) == true) {
            pos_ += bytes;
            return true;
        }
        return false;
    }

private:
    const uint8_t* buf_;
    size_t size_;
    size_t pos_;
};
