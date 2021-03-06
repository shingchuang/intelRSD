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
 *
 * @file command/network/json/get_manager_info.cpp
 *
 * @brief JSON command GetManagerInfo implementation
 * */

#include "agent-framework/command/network/json/get_manager_info.hpp"

using namespace agent_framework::command::network::json;
using namespace agent_framework::model::literals;

GetManagerInfo::GetManagerInfo() :
    CommandJson(Procedure(TAG,
                jsonrpc::PARAMS_BY_NAME,
                jsonrpc::JSON_STRING,
                Manager::MANAGER, jsonrpc::JSON_STRING,
                nullptr)) {}

void GetManagerInfo::method(const Json::Value& params, Json::Value& result) {
    Command* command = get_command();

    network::GetManagerInfo::Request request{};
    network::GetManagerInfo::Response response{};

    request.m_manager = params[Manager::MANAGER].asString();

    command->execute(request, response);

    result = response.m_manager.to_json();
}

void GetManagerInfo::notification(const Json::Value&) { }

static CommandJson::Register<GetManagerInfo> g;
