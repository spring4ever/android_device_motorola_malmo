/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint-service.moto"

#include "Fingerprint.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::android::hardware::biometrics::fingerprint::Fingerprint;
using aidl::android::hardware::biometrics::fingerprint::IFingerprint;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(4);
    ABinderProcess_startThreadPool();

    // The stock HAL is patched to register as "wrapper" instead of "default".
    const std::string stockInstance = std::string(IFingerprint::descriptor) + "/wrapper";
    auto stock = IFingerprint::fromBinder(
            ndk::SpAIBinder(AServiceManager_waitForService(stockInstance.c_str())));
    CHECK(stock != nullptr) << "Failed to get " << stockInstance;

    // Exit when the stock HAL dies so init restarts us against the new instance.
    ndk::ScopedAIBinder_DeathRecipient deathRecipient(AIBinder_DeathRecipient_new([](void*) {
        LOG(ERROR) << "Stock fingerprint HAL died, exiting";
        exit(EXIT_FAILURE);
    }));
    CHECK_EQ(AIBinder_linkToDeath(stock->asBinder().get(), deathRecipient.get(), nullptr),
             STATUS_OK);

    auto fingerprint = ndk::SharedRefBase::make<Fingerprint>(stock);

    const std::string instance = std::string(Fingerprint::descriptor) + "/default";
    binder_status_t status =
            AServiceManager_addService(fingerprint->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << instance << " " << status;

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
