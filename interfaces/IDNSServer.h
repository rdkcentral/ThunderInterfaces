/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
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

#pragma once
#include "Module.h"

namespace Thunder {
namespace Exchange {

    // This interface gives access to DNS Zone information
    struct EXTERNAL IDNS : virtual public Core::IUnknown {
        enum { ID = ID_DNS_SERVER };

        struct Record {

            // RFC 1035 section 3.2.2
            enum type : uint8_t {
                INVALID       =   0,

                RECORD_A      =   1, // a host address
                RECORD_NS     =   2, // an authoritative name server
                RECORD_MD     =   3, // a mail destination( Obsolete - use MX)
                RECORD_MF     =   4, // a mail forwarder (Obsolete - use MX)
                RECORD_CNAME  =   5, // the canonical name for an alias
                RECORD_SOA    =   6, // marks the start of a zone of authority
                RECORD_MB     =   7, // a mailbox domain name (EXPERIMENTAL)
                RECORD_MG     =   8, // a mail group member (EXPERIMENTAL)
                RECORD_MR     =   9, // a mail rename domain name (EXPERIMENTAL)
                RECORD_NULL   =  10, // a null RR (EXPERIMENTAL)
                RECORD_WKS    =  11, // a well known service description
                RECORD_PTR    =  12, // a domain name pointer
                RECORD_HINFO  =  13, // host information
                RECORD_MINFO  =  14, // mailbox or mail list information
                RECORD_MX     =  15, // mail exchange
                RECORD_TXT    =  16, // text strings

                // RFC 1035 section 3.2.3 (superset)          
                REQUEST_AXFR  = 252, // a request for a transfer of an entire zone
                REQUEST_MAILB = 253, // a request for mailbox - related records(MB, MG or MR)
                REQUEST_MAILA = 254, // a request for mail agent RRs(Obsolete - see MX)
                REQUEST_ALL   = 255
            };

            type Type;
            string Designator;
            string Value;
        };

        ~IDNS() override = default;

        virtual Core::hresult FindByType(const Record::type kind, const string& designator, Record& entry /* @out */) = 0;
        virtual Core::hresult FindByIndex(const uint8_t index, const string& designator, Record& entry /* @out */) = 0;
        virtual Core::hresult Add(const Record& entry) = 0;
        virtual Core::hresult Remove(const Record& record) = 0;
    };


}
}

