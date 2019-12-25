//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

#ifndef TextSecureKit_Constants_h
#define TextSecureKit_Constants_h

typedef NS_ENUM(NSInteger, TSWhisperMessageType) {
    TSUnknownMessageType = 0,
    TSEncryptedWhisperMessageType = 1,
    TSIgnoreOnIOSWhisperMessageType = 2, // on droid this is the prekey bundle message irrelevant for us
    TSPreKeyWhisperMessageType = 3,
    TSUnencryptedWhisperMessageType = 4,
    TSUnidentifiedSenderMessageType = 6,
};

#pragma mark Server Address

#define textSecureHTTPTimeOut 10

#define kLegalTermsUrlString @"https://vinci.my/terms.html"

#define textSecureAccountsAPI @"v1/accounts"
#define textSecureAttributesAPI @"v1/accounts/attributes/"

#define textSecureMessagesAPI @"v1/messages/"
#define textSecureKeysAPI @"v2/keys"
#define textSecureSignedKeysAPI @"v2/keys/signed"
#define textSecureDirectoryAPI @"v1/directory"
#define textSecureAttachmentsAPI @"v1/attachments"
#define textSecureDeviceProvisioningCodeAPI @"v1/devices/provisioning/code"
#define textSecureDeviceProvisioningAPIFormat @"v1/provisioning/%@"
#define textSecureDevicesAPIFormat @"v1/devices/%@"
#define textSecureProfileAPIFormat @"v1/profile/%@"
#define textSecureSetProfileNameAPIFormat @"v1/profile/name/%@"
#define textSecureProfileAvatarFormAPI @"v1/profile/form/avatar"
#define textSecure2FAAPI @"v1/accounts/pin"
#define textSecureRegistrationLockV2API @"v1/accounts/registration_lock"

#define SignalApplicationGroup @"group.id.vinci.corp.messenger"

// Vinci
//#define textSecureWebSocketAPI @"wss://secret.noosphere.foundation:443/v1/websocket/"
//#define textSecureServerURL @"https://secret.noosphere.foundation:443/"
//#define textSecureCDNServerURL @"https://secret.noosphere.foundation:443/"
//
//#define textSecureServiceReflectorHost @"europe-west1-signal-cdn-reflector.cloudfunctions.net"
//#define textSecureCDNReflectorHost @"europe-west1-signal-cdn-reflector.cloudfunctions.net"
//#define contactDiscoveryURL @"https://secret.noosphere.foundation:443/cds"
//#define keyBackupURL @"https://secret.noosphere.foundation:443/cds"
//#define storageServiceURL @"https://secret.noosphere.foundation:443/cds"
//#define kUDTrustRoot @"BWiWgIeU3+YDJ+EPePZtFMkJx7SMGvI+zuW/lwwagGhC"
//
//#define serviceCensorshipPrefix @"service"
//#define cdnCensorshipPrefix @"cdn"
//#define contactDiscoveryCensorshipPrefix @"directory"
//#define keyBackupCensorshipPrefix @"backup"
//
//#define contactDiscoveryEnclaveName @"cd6cfc342937b23b1bdd3bbf9721aa5615ac9ff50a75c5527d441cd3276826c9"
//#define contactDiscoveryMrEnclave contactDiscoveryEnclaveName
//
//#define keyBackupEnclaveName @"281b2220946102e8447b1d72a02b52d413c390780bae3e3a5aad27398999e7a3"
//#define keyBackupMrEnclave @"94029382f0a8947a72df682e6972f58bbb6dda2f5ec51ab0974bd40c781b719b"
//#define keyBackupServiceId @"281b2220946102e8447b1d72a02b52d413c390780bae3e3a5aad27398999e7a3"

#endif

NS_ASSUME_NONNULL_END

