/*!
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
 * @file manager.hpp
 *
 *
 * @brief manager
 * */

#ifndef AGENT_FRAMEWORK_MODULE_MODEL_MANAGER_HPP
#define AGENT_FRAMEWORK_MODULE_MODEL_MANAGER_HPP

#include "agent-framework/module-ref/model/attributes/model_attributes.hpp"
#include "agent-framework/module-ref/model/resource.hpp"
#include "agent-framework/module-ref/enum/common.hpp"

namespace agent_framework {
namespace model {

/*! Manager */
class Manager : public Resource {
public:
    using NetworkServices = attribute::Array<attribute::NetworkService>;

    explicit Manager(const std::string& parent_uuid = {});
    ~Manager();

    Manager(const Manager&) = default;
    Manager& operator=(const Manager&) = default;
    Manager(Manager&&) = default;
    Manager& operator=(Manager&&) = default;

    /*!
     * @brief construct an object of class Manager from JSON
     *
     * @param json the Json::Value deserialized to object
     *
     * @return the newly constructed Manager object
     */
    static Manager from_json(const Json::Value& json);

    /*!
     * @brief transform the object to JSon
     *
     * @return the object serialized to Json::Value
     */
    Json::Value to_json() const;

    /**
     * @brief Get collection name
     * @return collection name
     */
    static enums::CollectionName get_collection_name() {
        return Manager::collection_name;
    }

    /*!
     * @brief Get component name
     * @return component name
     * */
    static enums::Component get_component() {
        return Manager::component;
    }

    /*!
     * @brief Get serial console
     * @return serial console
     * */
    const attribute::SerialConsole& get_serial_console() const {
        return m_serial_console;
    }

    /*!
     * @brief Set serial console
     * @param[in] serial_console Manager serial console
     * */
    void set_serial_console(const attribute::SerialConsole& serial_console) {
        m_serial_console = serial_console;
    }

    /*!
    * @brief Get connection data
    * @return connection data
     * */
    const attribute::ConnectionData& get_connection_data() const {
        return m_connection_data;
    }

    /*!
     * @brief Set connection data
     * @param[in] connection_data Manager connection data
     * */
    void set_connection_data(const attribute::ConnectionData& connection_data) {
        m_connection_data = connection_data;
    }

    /*!
     * @brief Get network services
     * @return network services
     * */
    const NetworkServices& get_network_services() const {
        return m_network_services;
    }

    /*!
     * @brief setter for network_services attribute
     *
     * @param network_services of type NetworkServices
     */
    void set_network_services(const NetworkServices& network_services) {
        m_network_services = network_services;
    }

    /*!
     * @brief adds network service
     *
     * @param network_service of type NetworkService
     */
    void add_network_service(const attribute::NetworkService& network_service) {
        m_network_services.add_entry(network_service);
    }

    /*!
     * @brief Set firmware version
     * @param[in] firmware_version Manager firmeware version
     * */
    void set_firmware_version(const OptionalField<std::string>& firmware_version) {
        m_firmware_version = firmware_version;
    }

    /*!
     * @brief Get firmware version
     * @return Firmware version
     */
    const OptionalField<std::string>& get_firmware_version() const {
        return m_firmware_version;
    }

    /*!
     * @brief Set IPv4 address
     * @param[in] ipv4_address Manager IPv4 address
     * */
    void set_ipv4_address(const OptionalField<std::string>& ipv4_address) {
        m_ipv4_address = ipv4_address;
    }

    /*!
     * @brief Get IPv4 address
     * @return IPv4 address
     */
    const OptionalField<std::string>& get_ipv4_address() const {
        return m_ipv4_address;
    }

    /*!
    * @brief Set slot
    * @param[in] slot Manager slot
    * */
    void set_slot(const std::uint32_t slot) {
        m_slot = slot;
    }

    /*!
     * @brief Get slot
     * @return slot
     */
    std::uint32_t get_slot() const {
        return m_slot;
    }

    /*!
    * @brief Set Manager GUID
    * @param[in] guid Manager GUID
    * */
    void set_guid(const OptionalField<std::string>& guid) {
        m_guid = guid;
    }

    /*!
     * @brief Get Manager GUID
     * @return Manager GUID
     */
    const OptionalField<std::string>& get_guid() const {
        return m_guid;
    }

    /*!
    * @brief Set presence
    * @param[in] presence Manager presence
    * */
    void set_presence(const bool presence) {
        m_presence = presence;
    }

    /*!
     * @brief Get presence
     * @return presence
     */
    bool get_presence() const {
        return m_presence;
    }


    /*!
     * @brief Get manager type (obligatory)
     * @return type of the manager as enum
     */
    const OptionalField<enums::ManagerInfoType>& get_manager_type() const {
        return m_type;
    }
    /*!
     * @brief Set manager type (obligatory)
     * @param[in] manager_type type of the manager
     */
    void set_manager_type(const OptionalField<enums::ManagerInfoType>& manager_type) {
        m_type = manager_type;
    }

    /*!
     * @brief Get manager model (optional)
     * @return manager model or NIL if not set
     */
    const OptionalField<std::string>& get_manager_model() const {
        return m_model;
    }
    /*!
     * @brief Set manager model (optional)
     * @param[in] manager_model manager model or NIL to remove value
     */
    void set_manager_model(const OptionalField<std::string>& manager_model) {
        m_model = manager_model;
    }

    /*!
     * @brief Get UUID of the chassis being a manager’s physical location (optional)
     * @return parent location or NIL if not set
     */
    const OptionalField<std::string>& get_location() const {
        return m_location;
    }
    /*!
     * @brief Set UUID of the chassis being a manager’s physical location (optional)
     * @param[in] location parent location or NIL to remove value
     */
    void set_location(const OptionalField<std::string>& location) {
        m_location = location;
    }


    /*!
     * @brief Get graphical console (obligatory)
     * @return graphical console
     */
    const attribute::GraphicalConsole& get_graphical_console() const {
        return m_graphical_console;
    }
    /*!
     * @brief Set graphical console (obligatory)
     * @param[in] graphical_console Manager graphical console
     * */
    void set_graphical_console(const attribute::GraphicalConsole& graphical_console) {
        m_graphical_console = graphical_console;
    }

    /*!
     * @brief Get command shell (obligatory)
     * @return command shell
     */
    const attribute::CommandShell& get_command_shell() const {
        return m_command_shell;
    }
    /*!
     * @brief Set command shell (obligatory)
     * @param[in] command_shell command shell to be set
     * */
    void set_command_shell(const attribute::CommandShell& command_shell) {
        m_command_shell = command_shell;
    }


private:
    attribute::Status m_status{};
    OptionalField<enums::ManagerInfoType> m_type{enums::ManagerInfoType::ManagementController};
    OptionalField<std::string> m_model{};
    OptionalField<std::string> m_location{};
    OptionalField<std::string> m_firmware_version{};
    OptionalField<std::string> m_ipv4_address{};
    std::uint32_t m_slot{};
    OptionalField<std::string> m_guid{};
    NetworkServices m_network_services{};
    attribute::GraphicalConsole m_graphical_console{};
    attribute::SerialConsole m_serial_console{};
    attribute::CommandShell m_command_shell{};
    attribute::ConnectionData m_connection_data{};
    bool m_presence{false};

    static const enums::CollectionName collection_name;
    static const enums::Component component;
};

}
}

#endif /* _AGENT_FRAMEWORK_MODULE_MODEL_MANAGER_HPP */
