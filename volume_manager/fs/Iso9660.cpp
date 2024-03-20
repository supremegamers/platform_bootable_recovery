/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <sys/mount.h>
#include <utils/Errors.h>
#include "Iso9660.h"
#include "Utils.h"

namespace android {
namespace volmgr {
namespace iso9660 {

status_t Mount(const std::string& source, const std::string& target,
        int ownerUid, int ownerGid ) {
    int rc;
    unsigned long flags;
    char mountData[256];

    const char* c_source = source.c_str();
    const char* c_target = target.c_str();

    flags = MS_NODEV | MS_NOEXEC | MS_NOSUID | MS_DIRSYNC | MS_RDONLY;

    snprintf(mountData, sizeof(mountData),
            "utf8,uid=%d,gid=%d", ownerUid, ownerGid);

    rc = mount(c_source, c_target, "iso9660", flags, mountData);
    if (rc != 0) {
        rc = mount(c_source, c_target, "udf", flags, mountData);
    }

    return rc;
}

}  // namespace iso9660
}  // namespace volmgr
}  // namespace android
