/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/biometrics/fingerprint/BnSessionCallback.h>

#include "PanelController.h"

namespace aidl::android::hardware::biometrics::fingerprint {

using ::aidl::android::hardware::keymaster::HardwareAuthToken;

class SessionCallback : public BnSessionCallback {
  public:
    SessionCallback(std::shared_ptr<ISessionCallback> cb, std::shared_ptr<PanelController> hbm);

    ndk::ScopedAStatus onChallengeGenerated(int64_t challenge) override;
    ndk::ScopedAStatus onChallengeRevoked(int64_t challenge) override;
    ndk::ScopedAStatus onAcquired(AcquiredInfo info, int32_t vendorCode) override;
    ndk::ScopedAStatus onError(Error error, int32_t vendorCode) override;
    ndk::ScopedAStatus onEnrollmentProgress(int32_t enrollmentId, int32_t remaining) override;
    ndk::ScopedAStatus onAuthenticationSucceeded(int32_t enrollmentId,
                                                 const HardwareAuthToken& hat) override;
    ndk::ScopedAStatus onAuthenticationFailed() override;
    ndk::ScopedAStatus onLockoutTimed(int64_t durationMillis) override;
    ndk::ScopedAStatus onLockoutPermanent() override;
    ndk::ScopedAStatus onLockoutCleared() override;
    ndk::ScopedAStatus onInteractionDetected() override;
    ndk::ScopedAStatus onEnrollmentsEnumerated(const std::vector<int32_t>& enrollmentIds) override;
    ndk::ScopedAStatus onEnrollmentsRemoved(const std::vector<int32_t>& enrollmentIds) override;
    ndk::ScopedAStatus onAuthenticatorIdRetrieved(int64_t authenticatorId) override;
    ndk::ScopedAStatus onAuthenticatorIdInvalidated(int64_t newAuthenticatorId) override;
    ndk::ScopedAStatus onSessionClosed() override;

  private:
    std::shared_ptr<ISessionCallback> mCb;
    std::shared_ptr<PanelController> mController;
};

}  // namespace aidl::android::hardware::biometrics::fingerprint
