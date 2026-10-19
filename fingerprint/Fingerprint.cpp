/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Fingerprint.h"
#include "Session.h"

namespace aidl::android::hardware::biometrics::fingerprint {

Fingerprint::Fingerprint(std::shared_ptr<IFingerprint> stock)
    : mService(std::move(stock)), mController(std::make_shared<PanelController>()) {}

ndk::ScopedAStatus Fingerprint::getSensorProps(std::vector<SensorProps>* out) {
    return mService->getSensorProps(out);
}

ndk::ScopedAStatus Fingerprint::createSession(int32_t sensorId, int32_t userId,
                                              const std::shared_ptr<ISessionCallback>& cb,
                                              std::shared_ptr<ISession>* out) {
    auto callback = ndk::SharedRefBase::make<SessionCallback>(cb, mController);

    std::shared_ptr<ISession> session;
    auto ret = mService->createSession(sensorId, userId, callback, &session);
    if (!ret.isOk()) {
        return ret;
    }

    *out = ndk::SharedRefBase::make<Session>(std::move(session), mController);
    return ret;
}

}  // namespace aidl::android::hardware::biometrics::fingerprint
