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

package com.intel.podm.allocation.mappers.localdrive;

import com.intel.podm.business.dto.redfish.RequestedLocalDrive;
import com.intel.podm.business.entities.redfish.base.LocalStorage;

import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Optional;

import static com.google.common.collect.Maps.newHashMap;
import static com.intel.podm.allocation.mappers.Sorter.ascendingWhereNullsLast;
import static com.intel.podm.allocation.mappers.Sorter.contextsAscendingWhereNullsLast;
import static com.intel.podm.allocation.mappers.Sorter.sort;
import static com.intel.podm.allocation.mappers.localdrive.Predicates.byAtLeastCapacityGib;
import static com.intel.podm.allocation.mappers.localdrive.Predicates.byAtLeastMinRpm;
import static com.intel.podm.allocation.mappers.localdrive.Predicates.byExactId;
import static com.intel.podm.allocation.mappers.localdrive.Predicates.byExactInterface;
import static com.intel.podm.allocation.mappers.localdrive.Predicates.byExactSerialNumber;
import static com.intel.podm.allocation.mappers.localdrive.Predicates.byExactType;
import static java.util.Comparator.comparing;
import static java.util.Comparator.naturalOrder;
import static java.util.Comparator.nullsFirst;

public class LocalStorageAllocationMapper {
    public Map<RequestedLocalDrive, LocalStorage> map(List<RequestedLocalDrive> requestedDrives, List<LocalStorage> availableLocalStorage) {
        Map<RequestedLocalDrive, LocalStorage> mapped = newHashMap();

        List<RequestedLocalDrive> requestedDrivesQueue =
                sort(requestedDrives, contextsAscendingWhereNullsLast());
        List<LocalStorage> availableLocalStorageQueue =
                sort(availableLocalStorage, ascendingWhereNullsLast(LocalStorage::getId));

        for (RequestedLocalDrive requestedDrive : requestedDrivesQueue) {
            Optional<LocalStorage> localStorage = findMatchingAvailableDrive(requestedDrive, availableLocalStorageQueue);
            localStorage.ifPresent(storage -> mapped.put(requestedDrive, storage));
            localStorage.ifPresent(availableLocalStorageQueue::remove);
        }
        return mapped;
    }

    private static Optional<LocalStorage> findMatchingAvailableDrive(RequestedLocalDrive requestedDrive, List<LocalStorage> availableLocalStorage) {
        return availableLocalStorage.stream()
                .filter(byExactId(requestedDrive.getResourceContext()))
                .filter(byAtLeastCapacityGib(requestedDrive.getCapacityGib()))
                .filter(byExactType(requestedDrive.getType()))
                .filter(byAtLeastMinRpm(requestedDrive.getMinRpm()))
                .filter(byExactSerialNumber(requestedDrive.getSerialNumber()))
                .filter(byExactInterface(requestedDrive.getInterface()))
                .sorted(withDriveComparator())
                .findFirst();
    }

    private static Comparator<LocalStorage> withDriveComparator() {
        return comparing(LocalStorage::getType, nullsFirst(naturalOrder()))
                .thenComparing(LocalStorage::getCapacityGib, nullsFirst(naturalOrder()))
                .thenComparing(LocalStorage::getRpm, nullsFirst(naturalOrder()))
                .thenComparing(LocalStorage::getSerialNumber, nullsFirst(naturalOrder()))
                .thenComparing(LocalStorage::getInterface, nullsFirst(naturalOrder()));
    }
}
