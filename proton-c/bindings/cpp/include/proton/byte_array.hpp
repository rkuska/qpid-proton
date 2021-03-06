#ifndef BYTE_ARRAY_HPP
#define BYTE_ARRAY_HPP
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <proton/config.hpp>
#include <proton/comparable.hpp>

#include <algorithm>

namespace proton {

/// Used to represent fixed-sized data types that don't have a natural C++ representation
/// as an array of bytes.
template <size_t N> class byte_array : private comparable<byte_array<N> > {
  public:
    /// Initially all 0.
    byte_array() : bytes_() {}

    /// Returns N
    static size_t size() { return N; }

    char* begin() { return bytes_; }
    char* end() { return bytes_+N; }
    char& operator[](size_t i) { return bytes_[i]; }

    const char* begin() const { return bytes_; }
    const char* end() const { return bytes_+N; }
    const char& operator[](size_t i) const { return bytes_[i]; }

    friend bool operator==(const byte_array& x, const byte_array& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }

    friend bool operator<(const byte_array& x, const byte_array& y) {
        return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

  private:
    char bytes_[N];
};

}

#endif // BYTE_ARRAY_HPP
