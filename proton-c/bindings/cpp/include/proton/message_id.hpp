#ifndef MESSAGE_ID_HPP
#define MESSAGE_ID_HPP

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

#include "proton/types.hpp"
#include "proton/scalar.hpp"

namespace proton {

class encoder;
class decoder;

/// An AMQP message ID.
///
/// It can contain one of the following types:
///
///  - uint64_t
///  - std::string
///  - proton::uuid
///  - proton::binary
///
class message_id : public restricted_scalar {
  public:
    message_id(uint64_t x = 0) { scalar_ = x; }
    message_id(const uuid& x) { scalar_ = x; }
    message_id(const binary& x) { scalar_ = x; }
    message_id(const std::string& x) { scalar_ = x; }
    message_id(const char *x) { scalar_ = std::string(x); }

    /// @name Assignment operators
    ///
    /// Assign a C++ value, deduce the AMQP type()
    ///
    /// @{
    message_id& operator=(uint64_t x) { scalar_ = x; return *this; }
    message_id& operator=(const uuid& x) { scalar_ = x; return *this; }
    message_id& operator=(const binary& x) { scalar_ = x; return *this; }
    message_id& operator=(const std::string& x) { scalar_ = x; return *this; }
    /// char* is encoded as std::string
    message_id& operator=(const char *x) { scalar_ = std::string(x); return *this; }
    /// @}

    /// @name Get methods
    ///
    /// get(T&) extracts the value if the types match exactly and
    /// throws conversion_error otherwise.
    ///
    /// @{
    void get(uint64_t& x) const { scalar_.get(x); }
    void get(uuid& x) const { scalar_.get(x); }
    void get(binary& x) const { scalar_.get(x); }
    void get(std::string& x) const { scalar_.get(x); }
    /// @}

    /// Return the value as type T.
    template<class T> T get() const { T x; get(x); return x; }

    friend PN_CPP_EXTERN encoder operator<<(encoder, const message_id&);
    friend PN_CPP_EXTERN decoder operator>>(decoder, message_id&);

  private:
    message_id(const pn_atom_t& a): restricted_scalar(a) {}

  friend class message;
};

}
#endif // MESSAGE_ID_HPP
