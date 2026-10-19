/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/biometrics/fingerprint/BnFingerprint.h>

#include "PanelController.h"

namespace aidl::android::hardware::biometrics::fingerprint {

class Fingerprint : public BnFingerprint {
  public:
    explicit Fingerprint(std::shared_ptr<IFingerprint> stock);

    ndk::ScopedAStatus getSensorProps(std::vector<SensorProps>* out) override;
    ndk::ScopedAStatus createSession(int32_t sensorId, int32_t userId,
                                     const std::shared_ptr<ISessionCallback>& cb,
                                     std::shared_ptr<ISession>* out) override;

  private:
    std::shared_ptr<IFingerprint> mService;
    std::shared_ptr<PanelController> mController;
};

}  // namespace aidl::android::hardware::biometrics::fingerprint
