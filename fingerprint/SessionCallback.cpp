/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include "SessionCallback.h"

namespace aidl::android::hardware::biometrics::fingerprint {

SessionCallback::SessionCallback(std::shared_ptr<ISessionCallback> cb,
                                 std::shared_ptr<PanelController> hbm)
    : mCb(std::move(cb)), mController(std::move(hbm)) {}

ndk::ScopedAStatus SessionCallback::onChallengeGenerated(int64_t challenge) {
    return mCb->onChallengeGenerated(challenge);
}

ndk::ScopedAStatus SessionCallback::onChallengeRevoked(int64_t challenge) {
    return mCb->onChallengeRevoked(challenge);
}

ndk::ScopedAStatus SessionCallback::onAcquired(AcquiredInfo info, int32_t vendorCode) {
    return mCb->onAcquired(info, vendorCode);
}

ndk::ScopedAStatus SessionCallback::onError(Error error, int32_t vendorCode) {
    mController->disableHighBrightFod();
    return mCb->onError(error, vendorCode);
}

ndk::ScopedAStatus SessionCallback::onEnrollmentProgress(int32_t enrollmentId,
                                                         int32_t remaining) {
    return mCb->onEnrollmentProgress(enrollmentId, remaining);
}

ndk::ScopedAStatus SessionCallback::onAuthenticationSucceeded(int32_t enrollmentId,
                                                              const HardwareAuthToken& hat) {
    mController->disableHighBrightFod();
    return mCb->onAuthenticationSucceeded(enrollmentId, hat);
}

ndk::ScopedAStatus SessionCallback::onAuthenticationFailed() {
    mController->disableHighBrightFod();
    return mCb->onAuthenticationFailed();
}

ndk::ScopedAStatus SessionCallback::onLockoutTimed(int64_t durationMillis) {
    mController->disableHighBrightFod();
    return mCb->onLockoutTimed(durationMillis);
}

ndk::ScopedAStatus SessionCallback::onLockoutPermanent() {
    mController->disableHighBrightFod();
    return mCb->onLockoutPermanent();
}

ndk::ScopedAStatus SessionCallback::onLockoutCleared() {
    return mCb->onLockoutCleared();
}

ndk::ScopedAStatus SessionCallback::onInteractionDetected() {
    return mCb->onInteractionDetected();
}

ndk::ScopedAStatus SessionCallback::onEnrollmentsEnumerated(
        const std::vector<int32_t>& enrollmentIds) {
    return mCb->onEnrollmentsEnumerated(enrollmentIds);
}

ndk::ScopedAStatus SessionCallback::onEnrollmentsRemoved(
        const std::vector<int32_t>& enrollmentIds) {
    return mCb->onEnrollmentsRemoved(enrollmentIds);
}

ndk::ScopedAStatus SessionCallback::onAuthenticatorIdRetrieved(int64_t authenticatorId) {
    return mCb->onAuthenticatorIdRetrieved(authenticatorId);
}

ndk::ScopedAStatus SessionCallback::onAuthenticatorIdInvalidated(int64_t newAuthenticatorId) {
    return mCb->onAuthenticatorIdInvalidated(newAuthenticatorId);
}

ndk::ScopedAStatus SessionCallback::onSessionClosed() {
    mController->disableHighBrightFod();
    return mCb->onSessionClosed();
}

}  // namespace aidl::android::hardware::biometrics::fingerprint
