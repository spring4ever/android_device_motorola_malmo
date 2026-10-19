/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <android-base/file.h>
#include <android-base/logging.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <display/drm/sde_drm.h>

#include <mutex>

namespace aidl::android::hardware::biometrics::fingerprint {

enum HBM_STATE { OFF = 0, ON = 2 };

class PanelController {
  public:
    void enableHighBrightFod();
    void disableHighBrightFod();

  private:
    void setHbmState(int state);

    std::mutex mMutex;
    int mHbmState = OFF;
};

}  // namespace aidl::android::hardware::biometrics::fingerprint
