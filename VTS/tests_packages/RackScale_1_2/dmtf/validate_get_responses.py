"""
 * @section LICENSE
 *
 * @copyright
 * Copyright (c) 2016 Intel Corporation
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
"""

from cts_core.discovery.api_explorer import ApiExplorer
from cts_core.discovery.discovery_container import DiscoveryContainer
from cts_core.metadata.metadata_manager import MetadataManager
from cts_core.metadata_validation.get.metadata_get_validator import MetadataGetValidator
from cts_framework.tests_helpers  import TestCase
from cts_framework.commons.test_status_override import TestStatusOverride
from cts_framework.tests_helpers.result_status import ResultStatus


class ValidateGetResponses(TestCase):
    TIMEOUT = 600
    DESCRIPTION = """test case validating api get responses against provided metadata"""
    CONFIGURATION_PARAMETERS = [
        TestCase.ConfigurationParameter(parameter_name="ApiEndpoint",
                                        parameter_description="Endpoint to api that will be tested", parameter_type=str,
                                        is_required=True, parameter_default_value=None),
        TestCase.ConfigurationParameter(parameter_name="MetadataLocationDirectory",
                                        parameter_description="Path to directory containing metadata",
                                        parameter_type=str, is_required=True, parameter_default_value=None),
        TestCase.ConfigurationParameter(parameter_name="UseSSL",
                                        parameter_description="defines if VTS shall use ssl to communiacte with api",
                                        parameter_type=bool, is_required=False, parameter_default_value=False),
        TestCase.ConfigurationParameter(parameter_name="CertificateCertFile",
                                        parameter_description="Path to file with certificate in PEM format",
                                        parameter_type=str, is_required=False, parameter_default_value=None),
        TestCase.ConfigurationParameter(parameter_name="CertificateKeyFile",
                                        parameter_description="Path to file with certificate key in PEM format",
                                        parameter_type=str, is_required=False, parameter_default_value=None),
        TestCase.ConfigurationParameter(parameter_name="User",
                                        parameter_description="If specified vts will use specified user to authorize " +
                                                              "using basic auth", parameter_type=str, is_required=False,
                                        parameter_default_value=None),
        TestCase.ConfigurationParameter(parameter_name="Password",
                                        parameter_description="If specified vts will use specified password to " +
                                                              "authorize using basic auth", parameter_type=str,
                                        is_required=False, parameter_default_value=None)]

    def run(self):
        TestStatusOverride.reset()

        metadata_manager = MetadataManager(self.configuration)
        metadata_manager.load_files()
        metadata_container = metadata_manager.load_metadata_properties()

        api_explorer = ApiExplorer("/redfish/v1/", "ServiceRoot.ServiceRoot", metadata_container, self.configuration)

        discovery_container = api_explorer.process_with_resource(DiscoveryContainer())

        status = MetadataGetValidator(metadata_container).validate(discovery_container)


        if status:
            self.set_status(TestStatusOverride.get_joined_status(ResultStatus.PASSED))
        else:
            self.set_status_failed()
