/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Session.h"

namespace aidl::android::hardware::biometrics::fingerprint {

Session::Session(std::shared_ptr<ISession> session, std::shared_ptr<PanelController> hbm)
    : mSession(std::move(session)), mController(std::move(hbm)) {}

ndk::ScopedAStatus Session::generateChallenge() {
    return mSession->generateChallenge();
}

ndk::ScopedAStatus Session::revokeChallenge(int64_t challenge) {
    return mSession->revokeChallenge(challenge);
}

ndk::ScopedAStatus Session::enroll(const HardwareAuthToken& hat,
                                   std::shared_ptr<ICancellationSignal>* out) {
    return mSession->enroll(hat, out);
}

ndk::ScopedAStatus Session::authenticate(int64_t operationId,
                                         std::shared_ptr<ICancellationSignal>* out) {
    return mSession->authenticate(operationId, out);
}

ndk::ScopedAStatus Session::detectInteraction(std::shared_ptr<ICancellationSignal>* out) {
    return mSession->detectInteraction(out);
}

ndk::ScopedAStatus Session::enumerateEnrollments() {
    return mSession->enumerateEnrollments();
}

ndk::ScopedAStatus Session::removeEnrollments(const std::vector<int32_t>& enrollmentIds) {
    return mSession->removeEnrollments(enrollmentIds);
}

ndk::ScopedAStatus Session::getAuthenticatorId() {
    return mSession->getAuthenticatorId();
}

ndk::ScopedAStatus Session::invalidateAuthenticatorId() {
    return mSession->invalidateAuthenticatorId();
}

ndk::ScopedAStatus Session::resetLockout(const HardwareAuthToken& hat) {
    return mSession->resetLockout(hat);
}

ndk::ScopedAStatus Session::close() {
    mController->disableHighBrightFod();
    return mSession->close();
}

ndk::ScopedAStatus Session::onPointerDown(int32_t pointerId, int32_t x, int32_t y, float minor,
                                          float major) {
    // Illumination must be up before the stock HAL starts capturing.
    mController->enableHighBrightFod();
    return mSession->onPointerDown(pointerId, x, y, minor, major);
}

ndk::ScopedAStatus Session::onPointerUp(int32_t pointerId) {
    auto ret = mSession->onPointerUp(pointerId);
    mController->disableHighBrightFod();
    return ret;
}

ndk::ScopedAStatus Session::onUiReady() {
    return mSession->onUiReady();
}

ndk::ScopedAStatus Session::authenticateWithContext(int64_t operationId,
                                                    const OperationContext& context,
                                                    std::shared_ptr<ICancellationSignal>* out) {
    return mSession->authenticateWithContext(operationId, context, out);
}

ndk::ScopedAStatus Session::enrollWithContext(const HardwareAuthToken& hat,
                                              const OperationContext& context,
                                              std::shared_ptr<ICancellationSignal>* out) {
    return mSession->enrollWithContext(hat, context, out);
}

ndk::ScopedAStatus Session::detectInteractionWithContext(
        const OperationContext& context, std::shared_ptr<ICancellationSignal>* out) {
    return mSession->detectInteractionWithContext(context, out);
}

ndk::ScopedAStatus Session::onPointerDownWithContext(const PointerContext& context) {
    mController->enableHighBrightFod();
    return mSession->onPointerDownWithContext(context);
}

ndk::ScopedAStatus Session::onPointerUpWithContext(const PointerContext& context) {
    auto ret = mSession->onPointerUpWithContext(context);
    mController->disableHighBrightFod();
    return ret;
}

ndk::ScopedAStatus Session::onContextChanged(const OperationContext& context) {
    return mSession->onContextChanged(context);
}

ndk::ScopedAStatus Session::onPointerCancelWithContext(const PointerContext& context) {
    auto ret = mSession->onPointerCancelWithContext(context);
    mController->disableHighBrightFod();
    return ret;
}

ndk::ScopedAStatus Session::setIgnoreDisplayTouches(bool shouldIgnore) {
    return mSession->setIgnoreDisplayTouches(shouldIgnore);
}

}  // namespace aidl::android::hardware::biometrics::fingerprint
