/*!
 * @section LICENSE
 *
 * @copyright
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @section DESCRIPTION
 * */

#ifndef AGENT_CHASSIS_IPMB_COMMAND_GET_LAN_SELECTOR_SOURCE_SELECTOR_HPP
#define AGENT_CHASSIS_IPMB_COMMAND_GET_LAN_SELECTOR_SOURCE_SELECTOR_HPP

#include <ipmb/command/command.hpp>

/*! Agent namesapce */
namespace agent {
/*! Chassis namesapce */
namespace chassis {
/*! IPMB namesapce */
namespace ipmb {
/*! Command namesapce */
namespace command {

/*! Source Selector */
class SourceSelector final : public Command {
public:
    /*!
     * Unpacks IPMI Message
     * @param msg IPMI Message
     * */
    void unpack(IpmiMessage& msg);

    /*!
     * Packs IPMI Message
     * @param msg IPMI Message
     * */
    void pack(IpmiMessage& msg);

    /*! Copy constructor */
    SourceSelector(const SourceSelector&) = default;
    /*! Assigment construcor */
    SourceSelector& operator=(const SourceSelector&) = default;

    explicit SourceSelector() = default;
    ~SourceSelector();

private:
    static const constexpr uint8_t CMD_RESPONSE_DATA_LENGHT = 3;

    static const constexpr uint8_t OFFSET_CC = 0;
    static const constexpr uint8_t OFFSET_REVISTION = 1;
    static const constexpr uint8_t OFFSET_SOURCE = 2;

    class Response final : public Command::Response {
    public:
        /*!
         * Fill data buffer
         * @param msg IPMI Message
         * */
        void add_data(IpmiMessage& msg);

        void set_revision(const std::uint8_t revision) {
            m_param_revision = revision;
        }

        void set_source(const std::uint8_t source) {
            m_source = source;
        }

    private:
        std::uint8_t m_param_revision{0x11};
        std::uint8_t m_source{};
    };

    Response m_response{};

};

}
}
}
}

#endif /* AGENT_CHASSIS_IPMB_COMMAND_GET_LAN_SELECTOR_SOURCE_SELECTOR_HPP */
