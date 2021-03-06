#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP
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

#include "proton/duration.hpp"

namespace proton {
/// A timestamp in milliseconds since the epoch 00:00:00 (UTC), 1 January 1970.
class timestamp : private comparable<timestamp> {
  public:
    typedef int64_t numeric_type;
    PN_CPP_EXTERN static timestamp now();

    explicit timestamp(numeric_type ms = 0) : ms_(ms) {}
    timestamp& operator=(numeric_type ms) { ms_ = ms; return *this; }
    numeric_type milliseconds() const { return ms_; }
    numeric_type ms() const { return ms_; }

  private:
    numeric_type ms_;
};

inline bool operator==(timestamp x, timestamp y) { return x.ms() == y.ms(); }
inline bool operator<(timestamp x, timestamp y) { return x.ms() < y.ms(); }

inline timestamp operator+(timestamp ts, duration d) { return timestamp(ts.ms() + d.ms()); }
inline timestamp operator+(duration d, timestamp ts) { return ts + d; }

PN_CPP_EXTERN std::ostream& operator<<(std::ostream&, timestamp);

}
#endif // TIMESTAMP_HPP
