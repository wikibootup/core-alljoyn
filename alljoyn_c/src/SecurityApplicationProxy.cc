/**
 * @file
 * This file implements the SecurityApplicationProxy, which is responsible
 * for Security 2.0 configuration of remote applications.
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

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/AuthListener.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/PermissionPolicy.h>
#include <alljoyn/SecurityApplicationProxy.h>
#include <alljoyn/Session.h>
#include <alljoyn_c/BusAttachment.h>
#include <alljoyn_c/PermissionConfigurator.h>
#include <alljoyn_c/SecurityApplicationProxy.h>
#include <qcc/Debug.h>
#include <qcc/String.h>
#include <qcc/KeyInfoECC.h>
#include <qcc/StringUtil.h>
#include "KeyInfoHelper.h"
#include "XmlManifestConverter.h"
#include "XmlManifestTemplateConverter.h"
#include "CertificateUtilities.h"

#define QCC_MODULE "ALLJOYN_C"

using namespace qcc;
using namespace ajn;
using namespace std;

/*
 * The "signedManifestXml" variable must be freed by the caller using delete[].
 */
static QStatus SignManifest(const IdentityCertificate& identityCertificate,
                            const ECCPrivateKey& privateKey,
                            AJ_PCSTR unsignedManifestXml,
                            AJ_PSTR* signedManifestXml);

static QStatus BuildSignedManifest(const IdentityCertificate& identityCertificate,
                                   const ECCPrivateKey& privateKey,
                                   AJ_PCSTR unsignedManifestXml,
                                   Manifest& manifest);

alljoyn_sessionport AJ_CALL alljoyn_securityapplicationproxy_getpermissionmanagementsessionport()
{
    return ALLJOYN_SESSIONPORT_PERMISSION_MGMT;
}

alljoyn_securityapplicationproxy AJ_CALL alljoyn_securityapplicationproxy_create(alljoyn_busattachment bus,
                                                                                 AJ_PCSTR appBusName,
                                                                                 alljoyn_sessionid sessionId)
{
    QCC_DbgTrace(("%s", __FUNCTION__));

    BusAttachment* busAttachment = (BusAttachment*)bus;
    SessionId id = (SessionId)sessionId;

    return (alljoyn_securityapplicationproxy) new SecurityApplicationProxy(*busAttachment, appBusName, id);
}

void AJ_CALL alljoyn_securityapplicationproxy_destroy(alljoyn_securityapplicationproxy proxy)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    delete (SecurityApplicationProxy*)proxy;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_claim(alljoyn_securityapplicationproxy proxy,
                                                       AJ_PCSTR caKey,
                                                       AJ_PCSTR identityCertificateChain,
                                                       const uint8_t* groupId,
                                                       size_t groupSize,
                                                       AJ_PCSTR groupAuthority,
                                                       AJ_PCSTR* manifestsXmls, size_t manifestsCount)
{
    QStatus status;
    size_t identCertCount = 0;
    KeyInfoNISTP256 caPublicKey;
    KeyInfoNISTP256 groupPublicKey;
    GUID128 groupGuid;
    SecurityApplicationProxy* securityApplicationProxy = (SecurityApplicationProxy*)proxy;
    CertificateX509* identityCerts = nullptr;

    status = GetGroupId(groupId, groupSize, groupGuid);

    if (ER_OK == status) {
        status = KeyInfoHelper::PEMToKeyInfoNISTP256(caKey, caPublicKey);
    }

    if (ER_OK == status) {
        status = KeyInfoHelper::PEMToKeyInfoNISTP256(groupAuthority, groupPublicKey);
    }

    if (ER_OK == status) {
        status = ExtractCertificates(identityCertificateChain, &identCertCount, &identityCerts);
    }

    if (ER_OK == status) {
        status = securityApplicationProxy->Claim(caPublicKey,
                                                 groupGuid,
                                                 groupPublicKey,
                                                 identityCerts, identCertCount,
                                                 manifestsXmls, manifestsCount);
    }

    delete[] identityCerts;

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_getmanifesttemplate(alljoyn_securityapplicationproxy proxy, AJ_PSTR* manifestXml)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ((SecurityApplicationProxy*)proxy)->GetManifestTemplate(manifestXml);
}

void AJ_CALL alljoyn_securityapplicationproxy_manifesttemplate_destroy(AJ_PSTR manifestXml)
{
    SecurityApplicationProxy::DestroyManifestTemplate(manifestXml);
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_getapplicationstate(alljoyn_securityapplicationproxy proxy, alljoyn_applicationstate* applicationState)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    PermissionConfigurator::ApplicationState state;

    QStatus status = ((SecurityApplicationProxy*)proxy)->GetApplicationState(state);

    if (ER_OK == status) {
        *applicationState = (alljoyn_applicationstate)state;
    }

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_getclaimcapabilities(alljoyn_securityapplicationproxy proxy, alljoyn_claimcapabilities* capabilities)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    PermissionConfigurator::ClaimCapabilities claimCapabilities;

    QStatus status = ((SecurityApplicationProxy*)proxy)->GetClaimCapabilities(claimCapabilities);

    if (ER_OK == status) {
        *capabilities = (alljoyn_claimcapabilities)claimCapabilities;
    }

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_getclaimcapabilitiesadditionalinfo(alljoyn_securityapplicationproxy proxy, alljoyn_claimcapabilitiesadditionalinfo* additionalInfo)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    PermissionConfigurator::ClaimCapabilityAdditionalInfo claimCapabilitiesAdditionalInfo;

    QStatus status = ((SecurityApplicationProxy*)proxy)->GetClaimCapabilityAdditionalInfo(claimCapabilitiesAdditionalInfo);

    if (ER_OK == status) {
        *additionalInfo = (alljoyn_claimcapabilitiesadditionalinfo)claimCapabilitiesAdditionalInfo;
    }

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_updatepolicy(alljoyn_securityapplicationproxy proxy, AJ_PCSTR policyXml)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ((SecurityApplicationProxy*)proxy)->UpdatePolicy(policyXml);
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_updateidentity(alljoyn_securityapplicationproxy proxy,
                                                                AJ_PCSTR identityCertificateChain,
                                                                AJ_PCSTR* manifestsXmls,
                                                                size_t manifestsCount)
{
    QCC_DbgTrace(("%s", __FUNCTION__));

    QStatus status;
    size_t certCount = 0;
    SecurityApplicationProxy* securityApplicationProxy = (SecurityApplicationProxy*)proxy;
    CertificateX509* certs = nullptr;

    status = ExtractCertificates(identityCertificateChain, &certCount, &certs);

    if (ER_OK == status) {
        status = securityApplicationProxy->UpdateIdentity(certs,
                                                          certCount,
                                                          manifestsXmls,
                                                          manifestsCount);
    }

    delete[] certs;

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_installmembership(alljoyn_securityapplicationproxy proxy, AJ_PCSTR membershipCertificateChain)
{
    QCC_DbgTrace(("%s", __FUNCTION__));

    QStatus status;
    size_t certCount = 0;
    SecurityApplicationProxy* securityApplicationProxy = (SecurityApplicationProxy*)proxy;
    CertificateX509* certs = nullptr;

    status = ExtractCertificates(membershipCertificateChain, &certCount, &certs);

    if (ER_OK == status) {
        status = securityApplicationProxy->InstallMembership(certs, certCount);
    }

    delete[] certs;

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_reset(alljoyn_securityapplicationproxy proxy)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ((SecurityApplicationProxy*)proxy)->Reset();
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_startmanagement(alljoyn_securityapplicationproxy proxy)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ((SecurityApplicationProxy*)proxy)->StartManagement();
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_endmanagement(alljoyn_securityapplicationproxy proxy)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ((SecurityApplicationProxy*)proxy)->EndManagement();
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_resetpolicy(alljoyn_securityapplicationproxy proxy)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ((SecurityApplicationProxy*)proxy)->ResetPolicy();
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_geteccpublickey(alljoyn_securityapplicationproxy proxy, AJ_PSTR* eccPublicKey)
{
    QCC_DbgTrace(("%s", __FUNCTION__));

    QStatus status;
    String publicKeyString;
    ECCPublicKey publicKey;
    SecurityApplicationProxy* securityApplicationProxy = (SecurityApplicationProxy*)proxy;

    *eccPublicKey = nullptr;

    status = securityApplicationProxy->GetEccPublicKey(publicKey);

    if (ER_OK == status) {
        status = CertificateX509::EncodePublicKeyPEM(&publicKey, publicKeyString);
    }

    if (ER_OK == status) {
        *eccPublicKey = CreateStringCopy(publicKeyString);

        if (nullptr == *eccPublicKey) {
            status = ER_OUT_OF_MEMORY;
        }
    }

    return status;
}

void AJ_CALL alljoyn_securityapplicationproxy_eccpublickey_destroy(AJ_PSTR eccPublicKey)
{
    DestroyStringCopy(eccPublicKey);
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_signmanifest(AJ_PCSTR unsignedManifestXml,
                                                              AJ_PCSTR identityCertificatePem,
                                                              AJ_PCSTR signingPrivateKeyPem,
                                                              AJ_PSTR* signedManifest)
{
    QStatus status;
    IdentityCertificate identityCertificate;
    ECCPrivateKey privateKey;

    status = identityCertificate.LoadPEM(identityCertificatePem);

    if (ER_OK == status) {
        status = CertificateX509::DecodePrivateKeyPEM(signingPrivateKeyPem, &privateKey);
    }

    if (ER_OK == status) {
        status = SignManifest(identityCertificate, privateKey, unsignedManifestXml, signedManifest);
    }

    return status;
}

void AJ_CALL alljoyn_securityapplicationproxy_manifest_destroy(AJ_PSTR signedManifestXml)
{
    DestroyStringCopy(signedManifestXml);
}

/*
 * The "signedManifestXml" variable must be freed by the caller using delete[].
 */
QStatus SignManifest(const IdentityCertificate& identityCertificate,
                     const ECCPrivateKey& privateKey,
                     AJ_PCSTR unsignedManifestXml,
                     AJ_PSTR* signedManifestXml)
{
    string signedManifest;
    Manifest manifest;
    QStatus status = BuildSignedManifest(identityCertificate,
                                         privateKey,
                                         unsignedManifestXml,
                                         manifest);

    if (ER_OK == status) {
        status = XmlManifestConverter::ManifestToXml(manifest, signedManifest);
    }

    if (ER_OK == status) {
        *signedManifestXml = CreateStringCopy(signedManifest);

        if (nullptr == *signedManifestXml) {
            status = ER_OUT_OF_MEMORY;
        }
    }

    return status;
}

QStatus BuildSignedManifest(const IdentityCertificate& identityCertificate,
                            const ECCPrivateKey& privateKey,
                            AJ_PCSTR unsignedManifestXml,
                            Manifest& manifest)
{
    vector<PermissionPolicy::Rule> rules;
    QStatus status = XmlManifestTemplateConverter::GetInstance()->XmlToRules(unsignedManifestXml, rules);

    if (ER_OK == status) {
        status = manifest->SetRules(rules.data(), rules.size());
    }

    if (ER_OK == status) {
        status = manifest->ComputeThumbprintAndSign(identityCertificate, &privateKey);
    }

    return status;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_computemanifestdigest(AJ_PCSTR unsignedManifestXml,
                                                                       AJ_PCSTR identityCertificatePem,
                                                                       uint8_t** digest,
                                                                       size_t* digestSize)
{
    CertificateX509 identityCertificate;
    Manifest manifest;
    vector<PermissionPolicy::Rule> rules;

    QStatus status = XmlManifestTemplateConverter::GetInstance()->XmlToRules(unsignedManifestXml, rules);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not convert manifest XML to rules"));
        return status;
    }

    status = manifest->SetRules(rules.data(), rules.size());
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not set manifest rules"));
        return status;
    }

    status = identityCertificate.LoadPEM(identityCertificatePem);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not load identity certificate"));
        return status;
    }

    vector<uint8_t> digestVector;
    status = manifest->ComputeThumbprintAndDigest(identityCertificate, digestVector);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not ComputeThumbprintAndDigest"));
        return status;
    }

    *digest = new (std::nothrow) uint8_t[digestVector.size()];
    if (nullptr == *digest) {
        QCC_LogError(ER_OUT_OF_MEMORY, ("Out of memory allocating digest"));
        return ER_OUT_OF_MEMORY;
    }

    memcpy(*digest, digestVector.data(), digestVector.size());
    *digestSize = digestVector.size();

    return ER_OK;
}

void AJ_CALL alljoyn_securityapplicationproxy_digest_destroy(uint8_t* digest)
{
    delete[] digest;
}

QStatus AJ_CALL alljoyn_securityapplicationproxy_setmanifestsignature(AJ_PCSTR unsignedManifestXml,
                                                                      AJ_PCSTR identityCertificatePem,
                                                                      const uint8_t* signature,
                                                                      size_t signatureSize,
                                                                      AJ_PSTR* signedManifestXml)
{
    if ((2 * ECC_COORDINATE_SZ) != signatureSize) {
        return ER_BAD_ARG_4;
    }

    CertificateX509 identityCertificate;
    Manifest manifest;
    vector<PermissionPolicy::Rule> rules;

    QStatus status = XmlManifestTemplateConverter::GetInstance()->XmlToRules(unsignedManifestXml, rules);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not convert manifest XML to rules"));
        return status;
    }

    status = manifest->SetRules(rules.data(), rules.size());
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not set manifest rules"));
        return status;
    }

    status = identityCertificate.LoadPEM(identityCertificatePem);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not load identity certificate"));
        return status;
    }

    status = manifest->SetSubjectThumbprint(identityCertificate);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not set subject thumbprint"));
        return status;
    }

    ECCSignature eccSig;
    /* TODO ASACORE-3006: Need Import/Export methods for ECCSignature */
    memcpy(eccSig.r, signature, ECC_COORDINATE_SZ);
    memcpy(eccSig.s, signature + ECC_COORDINATE_SZ, ECC_COORDINATE_SZ);

    status = manifest->SetSignature(eccSig);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not set manifest signature"));
        return status;
    }

    std::string signedManifest;

    status = XmlManifestConverter::ManifestToXml(manifest, signedManifest);
    if (ER_OK != status) {
        QCC_LogError(status, ("Could not convert signed manifest to XML"));
        return status;
    }

    *signedManifestXml = CreateStringCopy(signedManifest);

    if (nullptr == *signedManifestXml) {
        QCC_LogError(ER_OUT_OF_MEMORY, ("Out of memory copying manifest XML"));
        return ER_OUT_OF_MEMORY;
    }

    return ER_OK;
}