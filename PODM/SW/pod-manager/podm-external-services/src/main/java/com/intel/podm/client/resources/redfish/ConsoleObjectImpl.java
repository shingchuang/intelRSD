/*
 * Copyright (c) 2015 Intel Corporation
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

package com.intel.podm.client.resources.redfish;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.intel.podm.client.api.resources.redfish.ConsoleObject;
import com.intel.podm.common.types.GeneralConnectType;

import java.util.List;

@JsonIgnoreProperties(ignoreUnknown = true)
public class ConsoleObjectImpl implements ConsoleObject {
    @JsonProperty("ServiceEnabled")
    private Boolean serviceEnabled;

    @JsonProperty("MaxConcurrentSessions")
    private Integer maxConcurrentSessions;

    @JsonProperty("ConnectTypesSupported")
    private List<GeneralConnectType> connectTypesSupported;

    @Override
    public Boolean isServiceEnabled() {
        return serviceEnabled;
    }

    @Override
    public Integer getMaxConcurrentSessions() {
        return maxConcurrentSessions;
    }

    @Override
    public List<GeneralConnectType> getConnectTypesSupported() {
        return connectTypesSupported;
    }
}
