/*
// Copyright (c) 2024 Hewlett Packard Enterprise
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#include "machinecontext.hpp"
#include <fstream>

constexpr std::map<std::string, std::function<void(std::string)>> MachineContext::support_map()
{
    //could be swapped out for JSON input if future expansion required
    
    return {
        //relative path to dt-node, d-bus object property to update
        { "model", [&](auto v){ MachineContext::Asset::model(v); } },
        { "serial-number", [&](auto v){ MachineContext::Asset::serial_number(v); }} 
    };
};

void MachineContext::populateMachineContext()
{
    // walk supported node paths
    for (auto& [nodeRelativePath, nodeUpdate] : support_map())
    {
        std::string node_full_path = node_base_path + nodeRelativePath;
        std::ifstream vpd_stream(node_full_path);
        
        std::string node_value;

        if (!vpd_stream || !std::getline(vpd_stream, node_value))
            continue;

        nodeUpdate(node_value); //update d-bus property w/ mapped function
    }
};


