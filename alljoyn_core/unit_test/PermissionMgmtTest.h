/**
 * @file
 * Helper functions for the PermissionMgmt Test Cases
 */

/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef _ALLJOYN_PERMISSION_MGMT_TEST_H
#define _ALLJOYN_PERMISSION_MGMT_TEST_H

#include <qcc/platform.h>
#include <gtest/gtest.h>
#include <qcc/GUID.h>
#include <qcc/StringSink.h>
#include <qcc/StringSource.h>
#include <qcc/StringUtil.h>

#include <alljoyn/KeyStoreListener.h>
#include <alljoyn/Status.h>
#include <alljoyn/Message.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <qcc/CryptoECC.h>
#include <qcc/CertificateECC.h>
#include <qcc/Log.h>
#include <alljoyn/SecurityApplicationProxy.h>
#include <alljoyn/PermissionPolicy.h>
#include "KeyStore.h"
#include "PermissionMgmtObj.h"
#include "InMemoryKeyStore.h"

namespace ajn {

class TestApplicationStateListener : public ApplicationStateListener {
  public:
    TestApplicationStateListener() : signalApplicationStateReceived(false) { }
    void State(const char* busName, const qcc::KeyInfoNISTP256& publicKeyInfo, PermissionConfigurator::ApplicationState state);
    bool signalApplicationStateReceived;
};

class TestPermissionConfigurationListener : public PermissionConfigurationListener {
  public:
    TestPermissionConfigurationListener() : factoryResetReceived(false), policyChangedReceived(false) { }
    QStatus FactoryReset();
    void PolicyChanged();
    bool factoryResetReceived;
    bool policyChangedReceived;
};

class TestPortListener : public SessionPortListener {
  public:
    qcc::String lastJoiner;
    bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        QCC_UNUSED(sessionPort);
        QCC_UNUSED(joiner);
        QCC_UNUSED(opts);
        return true;
    }
    void SessionJoined(SessionPort sessionPort, SessionId id, const char* joiner) {
        QCC_UNUSED(sessionPort);
        QCC_UNUSED(id);
        lastJoiner = joiner;
    }
};

class BasePermissionMgmtTest : public testing::Test, public BusObject,
    public ProxyBusObject::PropertiesChangedListener {
  public:


    static const char* INTERFACE_NAME;
    static const char* NOTIFY_INTERFACE_NAME;
    static const char* ONOFF_IFC_NAME;
    static const char* TV_IFC_NAME;

    BasePermissionMgmtTest(const char* path) : BusObject(path),
        adminBus("PermissionMgmtTestAdmin", false),
        serviceBus("PermissionMgmtTestService", false),
        servicePort(0),
        consumerBus("PermissionMgmtTestConsumer", false),
        remoteControlBus("PermissionMgmtTestRemoteControl", false),
        adminAdminGroupGUID("00112233445566778899AABBCCDDEEFF"),
        consumerAdminGroupGUID("AABBCCDDEEFF00112233445566778899"),
        serviceGUID(),
        consumerGUID(),
        remoteControlGUID(),
        status(ER_OK),
        serviceKeyListener(NULL),
        adminKeyListener(NULL),
        consumerKeyListener(NULL),
        remoteControlKeyListener(NULL),
        canTestStateSignalReception(false),
        currentTVChannel(1),
        volume(1),
        channelChangedSignalReceived(false),
        propertiesChangedSignalReceived(false),
        testASL(),
        testPCL()
    {
    }

    virtual void SetUp();

    virtual void TearDown();

    virtual void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void EnableSecurity(const char* keyExchange);
    bool GetFactoryResetReceived() const;
    void SetFactoryResetReceived(bool flag);
    bool GetPolicyChangedReceived() const;
    void SetPolicyChangedReceived(bool flag);

    void CreateOnOffAppInterface(BusAttachment& bus, bool addService);
    void CreateTVAppInterface(BusAttachment& bus, bool addService);
    void CreateAppInterfaces(BusAttachment& bus, bool addService);
    void GenerateCAKeys();

    BusAttachment adminBus;
    BusAttachment serviceBus;
    SessionPort servicePort;
    TestPortListener servicePortListener;
    BusAttachment consumerBus;
    BusAttachment remoteControlBus;
    qcc::GUID128 adminAdminGroupGUID;
    qcc::GUID128 consumerAdminGroupGUID;
    qcc::GUID128 serviceGUID;
    qcc::GUID128 consumerGUID;
    qcc::GUID128 remoteControlGUID;
    qcc::KeyInfoNISTP256 adminAdminGroupAuthority;
    qcc::KeyInfoNISTP256 consumerAdminGroupAuthority;
    QStatus status;

    QStatus InterestInChannelChangedSignal(BusAttachment* bus);
    void ChannelChangedSignalHandler(const InterfaceDescription::Member* member,
                                     const char* sourcePath, Message& msg);
    void SetApplicationStateSignalReceived(bool flag);
    bool GetApplicationStateSignalReceived() const;
    void SetChannelChangedSignalReceived(bool flag);
    bool GetChannelChangedSignalReceived() const;
    void SetPropertiesChangedSignalReceived(bool flag);
    bool GetPropertiesChangedSignalReceived() const;

    void OnOffOn(const InterfaceDescription::Member* member, Message& msg);
    void OnOffOff(const InterfaceDescription::Member* member, Message& msg);
    void TVUp(const InterfaceDescription::Member* member, Message& msg);

    void TVDown(const InterfaceDescription::Member* member, Message& msg);
    void TVChannel(const InterfaceDescription::Member* member, Message& msg);
    typedef enum {
        SEND_SIGNAL_UNICAST = 0,
        SEND_SIGNAL_SESSIONCAST = 1,
        SEND_SIGNAL_BROADCAST = 2
    } SignalSendMethod;
    void TVChannelChanged(const InterfaceDescription::Member* member, Message& msg, SignalSendMethod sendMethod);
    void TVMute(const InterfaceDescription::Member* member, Message& msg);
    void TVInputSource(const InterfaceDescription::Member* member, Message& msg);
    QStatus Get(const char* ifcName, const char* propName, MsgArg& val);
    QStatus Set(const char* ifcName, const char* propName, MsgArg& val);
    const qcc::String& GetAuthMechanisms() const;

    AuthListener* serviceKeyListener;
    AuthListener* adminKeyListener;
    AuthListener* consumerKeyListener;
    AuthListener* remoteControlKeyListener;
    InMemoryKeyStoreListener adminKeyStoreListener;
    InMemoryKeyStoreListener serviceKeyStoreListener;
    InMemoryKeyStoreListener consumerKeyStoreListener;
    InMemoryKeyStoreListener remoteControlKeyStoreListener;
    void DetermineStateSignalReachable();
    bool canTestStateSignalReception;
    QStatus SetupBus(BusAttachment& bus);
    QStatus TeardownBus(BusAttachment& bus);
    QStatus JoinSessionWithService(BusAttachment& initiator, SessionId& sessionId);

  private:
    void RegisterKeyStoreListeners();

    uint32_t currentTVChannel;
    uint32_t volume;
    bool channelChangedSignalReceived;
    bool propertiesChangedSignalReceived;
    qcc::String authMechanisms;
    TestApplicationStateListener testASL;
    TestPermissionConfigurationListener testPCL;
};

class PermissionMgmtTestHelper {
  public:
    static QStatus SetCAFlagOnCert(BusAttachment& issuerBus, qcc::CertificateX509& certificate);
    static QStatus CreateAllInclusiveManifest(Manifest& manifest);
    static QStatus SignManifest(BusAttachment& issuerBus, const std::vector<uint8_t>& subjectThumbprint, Manifest& manifest);
    static QStatus SignManifest(BusAttachment& issuerBus, const qcc::CertificateX509& subjectCertificate, Manifest& manifest);
    static QStatus SignManifests(BusAttachment& issuerBus, const qcc::CertificateX509& subjectCertificate, std::vector<Manifest>& manifests);
    static QStatus CreateIdentityCertChain(BusAttachment& caBus, BusAttachment& issuerBus, const qcc::String& serial, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::String& alias, uint32_t expiredInSecs, qcc::IdentityCertificate* certChain, size_t chainCount);
    static QStatus CreateIdentityCert(BusAttachment& issuerBus, const qcc::String& serial, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::String& alias, uint32_t expiredInSecs, qcc::IdentityCertificate& cert, bool setEmptyAKI = false);
    static QStatus CreateIdentityCert(BusAttachment& issuerBus, const qcc::String& serial, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::String& alias, uint32_t expiredInSecs, qcc::String& der);

    static QStatus CreateIdentityCert(BusAttachment& issuerBus, const qcc::String& serial, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::String& alias, qcc::String& der);

    static QStatus CreateMembershipCert(const qcc::String& serial, BusAttachment& signingBus, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::GUID128& guild, bool delegate, uint32_t expiredInSecs, qcc::MembershipCertificate& cert, bool setEmptyAKI = false);
    static QStatus CreateMembershipCert(const qcc::String& serial, BusAttachment& signingBus, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::GUID128& guild, bool delegate, uint32_t expiredInSecs, qcc::String& der);
    static QStatus CreateMembershipCert(const qcc::String& serial, BusAttachment& signingBus, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::GUID128& guild, bool delegate, qcc::String& der);
    static QStatus CreateMembershipCert(const qcc::String& serial, BusAttachment& signingBus, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::GUID128& guild, qcc::String& der);
    static bool IsPermissionDeniedError(QStatus status, Message& msg);
    static QStatus ReadClaimResponse(Message& msg, qcc::ECCPublicKey* pubKey);
    static QStatus GenerateManifest(PermissionPolicy::Rule** retRules, size_t* count);

    static QStatus RetrieveDSAPublicKeyFromKeyStore(BusAttachment& bus, qcc::ECCPublicKey* publicKey);

    static QStatus LoadCertificateBytes(Message& msg, qcc::CertificateX509& cert);
    static QStatus InstallMembership(const qcc::String& serial, BusAttachment& bus, const qcc::String& remoteObjName, BusAttachment& signingBus, const qcc::String& subject, const qcc::ECCPublicKey* subjectPubKey, const qcc::GUID128& guild);
    static QStatus InstallMembershipChain(BusAttachment& topBus, BusAttachment& secondBus, const qcc::String& serial0, const qcc::String& serial1, const qcc::String& remoteObjName, const qcc::String& secondSubject, const qcc::ECCPublicKey* secondPubKey, const qcc::String& targetSubject, const qcc::ECCPublicKey* targetPubKey, const qcc::GUID128& guild, bool setEmptyAKI = false);
    static QStatus InstallMembershipChain(BusAttachment& caBus, BusAttachment& intermediateBus, BusAttachment& targetBus, qcc::String& leafSerial, const qcc::GUID128& sgID);
    static QStatus RetrievePublicKeyFromMsgArg(MsgArg& arg, qcc::ECCPublicKey* pubKey);
    static QStatus GetPeerPublicKey(BusAttachment& bus, ProxyBusObject& remoteObj, qcc::ECCPublicKey* pubKey);
    static QStatus ExerciseOn(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus ExerciseOff(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus ExerciseTVUp(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus ExerciseTVDown(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus ExerciseTVChannel(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus ExerciseTVMute(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus ExerciseTVInputSource(BusAttachment& bus, ProxyBusObject& remoteObj);
    static QStatus JoinPeerSession(BusAttachment& initiator, BusAttachment& responder, SessionId& sessionId);
    static QStatus GetGUID(BusAttachment& bus, qcc::GUID128& guid);
    static QStatus GetPeerGUID(BusAttachment& bus, qcc::String& peerName, qcc::GUID128& peerGuid);
    static QStatus GetTVVolume(BusAttachment& bus, ProxyBusObject& remoteObj, uint32_t& volume);
    static QStatus SetTVVolume(BusAttachment& bus, ProxyBusObject& remoteObj, uint32_t volume);
    static QStatus GetTVCaption(BusAttachment& bus, ProxyBusObject& remoteObj, size_t& propertyCount);
    static void CallDeprecatedSetPSK(DefaultECDHEAuthListener* authListener, const uint8_t* pskBytes, size_t pskLength);
    static void UnwrapStrings(const std::vector<std::string>& strings, std::vector<AJ_PCSTR>& unwrapped);
};

}
#endif