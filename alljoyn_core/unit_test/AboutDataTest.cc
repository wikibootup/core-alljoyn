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

#include <alljoyn/AboutData.h>
#include <alljoyn/version.h>
#include <gtest/gtest.h>
#include <qcc/String.h>

#include <map>

#include "ajTestCommon.h"

using namespace ajn;

TEST(AboutDataTest, constants) {
    EXPECT_STREQ("AppId", AboutData::APP_ID);
    EXPECT_STREQ("DefaultLanguage", AboutData::DEFAULT_LANGUAGE);
    EXPECT_STREQ("DeviceName", AboutData::DEVICE_NAME);
    EXPECT_STREQ("DeviceId", AboutData::DEVICE_ID);
    EXPECT_STREQ("AppName", AboutData::APP_NAME);
    EXPECT_STREQ("Manufacturer", AboutData::MANUFACTURER);
    EXPECT_STREQ("ModelNumber", AboutData::MODEL_NUMBER);
    EXPECT_STREQ("SupportedLanguages", AboutData::SUPPORTED_LANGUAGES);
    EXPECT_STREQ("Description", AboutData::DESCRIPTION);
    EXPECT_STREQ("DateOfManufacture", AboutData::DATE_OF_MANUFACTURE);
    EXPECT_STREQ("SoftwareVersion", AboutData::SOFTWARE_VERSION);
    EXPECT_STREQ("AJSoftwareVersion", AboutData::AJ_SOFTWARE_VERSION);
    EXPECT_STREQ("HardwareVersion", AboutData::HARDWARE_VERSION);
    EXPECT_STREQ("SupportUrl", AboutData::SUPPORT_URL);
}

TEST(AboutDataTest, VerifyFieldValues) {
    AboutData aboutData;
    //AppId
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::APP_ID));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::APP_ID));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::APP_ID));
    EXPECT_STREQ("ay", aboutData.GetFieldSignature(AboutData::APP_ID));

    //DefaultLanguage
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::DEFAULT_LANGUAGE));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::DEFAULT_LANGUAGE));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::DEFAULT_LANGUAGE));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::DEFAULT_LANGUAGE));

    //DeviceName
    EXPECT_FALSE(aboutData.IsFieldRequired(AboutData::DEVICE_NAME));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::DEVICE_NAME));
    EXPECT_TRUE(aboutData.IsFieldLocalized(AboutData::DEVICE_NAME));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::DEVICE_NAME));

    //DeviceId
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::DEVICE_ID));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::DEVICE_ID));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::DEVICE_ID));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::DEVICE_ID));

    //AppName
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::APP_NAME));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::APP_NAME));
    EXPECT_TRUE(aboutData.IsFieldLocalized(AboutData::APP_NAME));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::APP_NAME));

    //Manufacturer
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::MANUFACTURER));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::MANUFACTURER));
    EXPECT_TRUE(aboutData.IsFieldLocalized(AboutData::MANUFACTURER));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::MANUFACTURER));

    //ModelNumber
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::MODEL_NUMBER));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(AboutData::MODEL_NUMBER));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::MODEL_NUMBER));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::MODEL_NUMBER));

    //SupportedLanguages
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::SUPPORTED_LANGUAGES));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::SUPPORTED_LANGUAGES));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::SUPPORTED_LANGUAGES));
    EXPECT_STREQ("as", aboutData.GetFieldSignature(AboutData::SUPPORTED_LANGUAGES));

    //Description
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::DESCRIPTION));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::DESCRIPTION));
    EXPECT_TRUE(aboutData.IsFieldLocalized(AboutData::DESCRIPTION));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::DESCRIPTION));

    //DateOfManufacture
    EXPECT_FALSE(aboutData.IsFieldRequired(AboutData::DATE_OF_MANUFACTURE));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::DATE_OF_MANUFACTURE));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::DATE_OF_MANUFACTURE));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::DATE_OF_MANUFACTURE));

    //SoftwareVersion
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::SOFTWARE_VERSION));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::SOFTWARE_VERSION));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::SOFTWARE_VERSION));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::SOFTWARE_VERSION));

    //AJSoftwareVersion
    EXPECT_TRUE(aboutData.IsFieldRequired(AboutData::AJ_SOFTWARE_VERSION));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::AJ_SOFTWARE_VERSION));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::AJ_SOFTWARE_VERSION));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::AJ_SOFTWARE_VERSION));

    //HardwareVersion
    EXPECT_FALSE(aboutData.IsFieldRequired(AboutData::HARDWARE_VERSION));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::HARDWARE_VERSION));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::HARDWARE_VERSION));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::HARDWARE_VERSION));

    //SupportUrl
    EXPECT_FALSE(aboutData.IsFieldRequired(AboutData::SUPPORT_URL));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(AboutData::SUPPORT_URL));
    EXPECT_FALSE(aboutData.IsFieldLocalized(AboutData::SUPPORT_URL));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(AboutData::SUPPORT_URL));

    //Unknown field
    EXPECT_FALSE(aboutData.IsFieldRequired("Unknown"));
    EXPECT_FALSE(aboutData.IsFieldAnnounced("Unknown"));
    EXPECT_FALSE(aboutData.IsFieldLocalized("Unknown"));
    EXPECT_TRUE(NULL == aboutData.GetFieldSignature("Unknown"));
}

TEST(AboutDataTest, DefaultLanguageNotSpecified) {
    QStatus status = ER_FAIL;
    AboutData aboutData;
    status = aboutData.SetDeviceName("Device Name");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);

    status = aboutData.SetAppName("Application Name");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);

    status = aboutData.SetManufacturer("Manufacturer Name");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);

    status = aboutData.SetDescription("A description of the application.");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);
}

TEST(AboutDataTest, Constructor) {
    AboutData aboutData("en");
    char* language;
    aboutData.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);
}

TEST(AboutDataTest, CopyConstructor) {
    AboutData aboutData("en");
    char* language;
    aboutData.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    AboutData aboutDataCopy(aboutData);
    aboutDataCopy.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);

    aboutDataCopy.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    //should be able to change each copy independent of one another
    QStatus status = aboutData.SetDeviceName("Device");
    EXPECT_EQ(ER_OK, status);

    status = aboutDataCopy.SetDeviceName("Copy Device");
    EXPECT_EQ(ER_OK, status);

    char* deviceName;
    status = aboutData.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Device", deviceName);

    status = aboutDataCopy.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Copy Device", deviceName);
}

TEST(AboutDataTest, AssignmentOperator) {
    AboutData aboutData("en");
    char* language;
    aboutData.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    // Self assignment
    aboutData = aboutData;
    AboutData aboutDataCopy;
    aboutDataCopy = aboutData;
    aboutDataCopy.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);

    aboutDataCopy.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    //should be able to change each copy independent of one another
    QStatus status = aboutData.SetDeviceName("Device");
    EXPECT_EQ(ER_OK, status);

    status = aboutDataCopy.SetDeviceName("Copy Device");
    EXPECT_EQ(ER_OK, status);

    char* deviceName;
    status = aboutData.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Device", deviceName);

    status = aboutDataCopy.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Copy Device", deviceName);
}

TEST(AboutDataTest, SetAppId) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t originalAppId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(originalAppId, 16u);
    EXPECT_EQ(ER_OK, status);

    uint8_t* appId;
    size_t num;
    status = aboutData.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(originalAppId[i], appId[i]);
    }

    //smaller than 128-bit
    uint8_t appId_64[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    status = aboutData.SetAppId(originalAppId, 8u);
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_APPID_SIZE, status);

    status = aboutData.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(8u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(appId_64[i], appId[i]);
    }

    //larger than 128-bit
    uint8_t appId_256[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                            16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    status = aboutData.SetAppId(appId_256, 32u);
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_APPID_SIZE, status);

    status = aboutData.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(32u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(appId_256[i], appId[i]);
    }
}

TEST(AboutDataTest, SetAppId_using_uuid_string) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    // not a hex digit
    status = aboutData.SetAppId("g00102030405060708090a0b0c0d0e0f");
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_VALUE, status);

    // odd number of characters parsing error
    status = aboutData.SetAppId("00102030405060708090a0b0c0d0e0f");
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_VALUE, status);

    // too few characters
    status = aboutData.SetAppId("0102030405060708090a0b0c0d0e0f");
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_APPID_SIZE, status);

    // too many characters
    status = aboutData.SetAppId("000102030405060708090a0b0c0d0e0f10");
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_APPID_SIZE, status);

    // not valid uuid parsing error
    status = aboutData.SetAppId("000102030405-060708090A0B-0C0D0E0F10");
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_VALUE, status);

    // not valid uuid parsing error
    status = aboutData.SetAppId("00010203-04050607-0809-0A0B-0C0D0E0F");
    EXPECT_EQ(ER_ABOUT_INVALID_ABOUTDATA_FIELD_VALUE, status);

    status = aboutData.SetAppId("000102030405060708090a0b0c0d0e0f");
    EXPECT_EQ(ER_OK, status);

    uint8_t* appId;
    size_t num;
    status = aboutData.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(i, appId[i]);
    }

    AboutData aboutData2("en");

    //use capital hex digits
    status = aboutData2.SetAppId("000102030405060708090A0B0C0D0E0F");
    EXPECT_EQ(ER_OK, status);

    status = aboutData2.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(i, appId[i]);
    }

    AboutData aboutData3("en");

    //use capital hex digits UUID as per RFC 4122
    status = aboutData3.SetAppId("00010203-0405-0607-0809-0A0B0C0D0E0F");
    EXPECT_EQ(ER_OK, status);

    status = aboutData3.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(i, appId[i]);
    }

    AboutData aboutData4("en");

    //use lowercase hex digits UUID as per RFC 4122
    status = aboutData4.SetAppId("00010203-0405-0607-0809-0a0b0c0d0e0f");
    EXPECT_EQ(ER_OK, status);

    status = aboutData4.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(i, appId[i]);
    }
}

TEST(AboutDataTest, SetDeviceName) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");
    char* language;
    status = aboutData.GetDefaultLanguage(&language);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    status = aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    status = aboutData.SetDeviceName("Device");
    EXPECT_EQ(ER_OK, status);

    char* deviceName;
    status = aboutData.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Device", deviceName);

    status = aboutData.SetDeviceName("dispositivo", "es");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetDeviceName(&deviceName, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("dispositivo", deviceName);
}

TEST(AboutDataTest, SetDeviceId) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetDeviceId("avec-awe1213-1234559xvc123");
    EXPECT_EQ(ER_OK, status);

    char* deviceId;
    status = aboutData.GetDeviceId(&deviceId);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("avec-awe1213-1234559xvc123", deviceId);
}

TEST(AboutDataTest, SetAppName) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);

    char* appName;
    status = aboutData.GetAppName(&appName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Application", appName);

    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetAppName(&appName, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("aplicacion", appName);
}

TEST(AboutDataTest, SetManufacturer) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);

    char* manufacturer;
    status = aboutData.GetManufacturer(&manufacturer);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Manufacturer", manufacturer);

    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetManufacturer(&manufacturer, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("manufactura", manufacturer);
}

TEST(AboutDataTest, SetModelNumber) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetModelNumber("xBnc345");
    EXPECT_EQ(ER_OK, status);

    char* modelNumber;
    status = aboutData.GetModelNumber(&modelNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("xBnc345", modelNumber);
}

TEST(AboutDataTest, SetSupportedLanguage)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    size_t numLanguages = aboutData.GetSupportedLanguages();
    const char** languages = new const char*[numLanguages];


    size_t numRetLang = aboutData.GetSupportedLanguages(languages, numLanguages);
    EXPECT_EQ(numLanguages, numRetLang);
    EXPECT_EQ(1u, numLanguages);
    EXPECT_STREQ("en", languages[0]);
    delete [] languages;
    languages = NULL;

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);

    numLanguages = aboutData.GetSupportedLanguages();
    languages = new const char*[numLanguages];

    numRetLang = aboutData.GetSupportedLanguages(languages, numLanguages);
    EXPECT_EQ(numLanguages, numRetLang);
    EXPECT_EQ(2u, numLanguages);
    EXPECT_STREQ("en", languages[0]);
    EXPECT_STREQ("es", languages[1]);
    delete [] languages;
    languages = NULL;
}
//ASACORE-910
TEST(AboutDataTest, SetSupportedLanguage_Duplicate)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);

    // Duplicate language already added from constructor
    status = aboutData.SetSupportedLanguage("en");
    EXPECT_EQ(ER_OK, status);

    // Duplicate language already added, error status should be generated
    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);

    // Even though "en" and "es" languages have been added multiple times only
    // two languages should be reported in the list of SupportedLanguages.
    size_t numRetLang = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, numRetLang);
}

//ASACORE-911
TEST(AboutDataTest, DISABLED_SetSupportedLanguage_Invalid_Tag)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    // Invalid language tag not defined in RFC5646
    status = aboutData.SetSupportedLanguage("abc");
    EXPECT_NE(ER_OK, status);

    status = aboutData.SetSupportedLanguage("232");
    EXPECT_NE(ER_OK, status);

    // Invalid subtag not defined in RFC5646
    status = aboutData.SetSupportedLanguage("en-t324");
    EXPECT_NE(ER_OK, status);

    status = aboutData.SetSupportedLanguage("zh-gfjk");
    EXPECT_NE(ER_OK, status);

    size_t numRetLang = aboutData.GetSupportedLanguages();
    EXPECT_EQ(1u, numRetLang);
}

//ASACORE-907
TEST(AboutDataTest, GetSupportedLanguages)
{
    AboutData aboutData("en");

    size_t numLanguages;
    numLanguages = aboutData.GetSupportedLanguages();
    EXPECT_EQ(1u, numLanguages);
}

TEST(AboutDataTest, SetDescription) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);

    char* description;
    status = aboutData.GetDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("A poetic description of this application", description);

    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetDescription(&description, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Una descripcion poetica de esta aplicacion", description);
}

TEST(AboutDataTest, SetDateOfManufacture) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetDateOfManufacture("2014-01-20");
    EXPECT_EQ(ER_OK, status);

    char* dateOfManufacture;
    status = aboutData.GetDateOfManufacture(&dateOfManufacture);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("2014-01-20", dateOfManufacture);

}

// ASACORE-906
TEST(AboutDataTest, DISABLED_SetDateOfManufacture_Negative) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    // Invalid date should fail
    status = aboutData.SetDateOfManufacture("2014-41-20");
    EXPECT_NE(ER_OK, status);

    status = aboutData.SetDateOfManufacture("201a-02-20");
    EXPECT_NE(ER_OK, status);

    status = aboutData.SetDateOfManufacture("2013-02-29");
    EXPECT_NE(ER_OK, status);

    status = aboutData.SetDateOfManufacture("04/31/2014");
    EXPECT_NE(ER_OK, status);
}

TEST(AboutDataTest, SetSoftwareVersion) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);

    char* softwareVersion;
    status = aboutData.GetSoftwareVersion(&softwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("0.1.2", softwareVersion);
}

TEST(AboutDataTest, SetHardwareVersion) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetHardwareVersion("3.2.1");
    EXPECT_EQ(ER_OK, status);

    char* hardwareVersion;
    status = aboutData.GetHardwareVersion(&hardwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("3.2.1", hardwareVersion);
}

TEST(AboutDataTest, SetSupportUrl) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetSupportUrl("www.example.com");
    EXPECT_EQ(ER_OK, status);

    char* supportUrl;
    status = aboutData.GetSupportUrl(&supportUrl);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("www.example.com", supportUrl);
}

TEST(AboutDataTest, IsValid)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    EXPECT_FALSE(aboutData.IsValid());
    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    EXPECT_FALSE(aboutData.IsValid("es"));

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));
}
//ASACORE-914
TEST(AboutDataTest, IsValid_Negative)
{
    QStatus status = ER_FAIL;
    AboutData aboutData;
    //DefaultLanguage and other required fields are missing
    EXPECT_FALSE(aboutData.IsValid());

    status = aboutData.SetDefaultLanguage("en");
    EXPECT_EQ(ER_OK, status);
    EXPECT_FALSE(aboutData.IsValid());

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    //DeviceId and other required fields are missing
    EXPECT_FALSE(aboutData.IsValid());

    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    //AppName and other required fields are missing
    EXPECT_FALSE(aboutData.IsValid());

    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    //Manufacturer and other required fields are missing
    EXPECT_FALSE(aboutData.IsValid());

    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    //ModelNumber and other required fields are missing
    EXPECT_FALSE(aboutData.IsValid());

    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    //Description and other required fields are missing
    EXPECT_FALSE(aboutData.IsValid());

    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    //SoftwareVersion missing
    EXPECT_FALSE(aboutData.IsValid());;

    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);

    // Now all required fields are set for english
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    // Missing AppName/Manufacture/Description
    EXPECT_FALSE(aboutData.IsValid("es"));

    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    // Missing Manufacture/Description
    EXPECT_FALSE(aboutData.IsValid("es"));

    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    // Missing Description
    EXPECT_FALSE(aboutData.IsValid("es"));

    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));
}

TEST(AboutDataTest, GetAboutData)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacture");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg aboutArg;
    status = aboutData.GetAboutData(&aboutArg);
    EXPECT_EQ(ER_OK, status);

    //printf("*****\n%s\n*****\n", aboutArg.ToString().c_str());

    MsgArg* args;

    aboutArg.GetElement("{sv}", AboutData::APP_ID, &args);
    int8_t* appIdOut;
    size_t appIdNum;
    args->Get("ay", &appIdNum, &appIdOut);
    ASSERT_EQ(16u, appIdNum);
    for (size_t i = 0; i < appIdNum; ++i) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    aboutArg.GetElement("{sv}", AboutData::DEFAULT_LANGUAGE, &args);
    char* defaultLanguage;
    args->Get("s", &defaultLanguage);
    EXPECT_STREQ("en", defaultLanguage);

    aboutArg.GetElement("{sv}", AboutData::DEVICE_ID, &args);
    char* deviceId;
    args->Get("s", &deviceId);
    EXPECT_STREQ("fakeID", deviceId);

    aboutArg.GetElement("{sv}", AboutData::APP_NAME, &args);
    char* appName;
    args->Get("s", &appName);
    EXPECT_STREQ("Application", appName);

    aboutArg.GetElement("{sv}", AboutData::MANUFACTURER, &args);
    char* manufacturer;
    args->Get("s", &manufacturer);
    EXPECT_STREQ("Manufacture", manufacturer);

    aboutArg.GetElement("{sv}", AboutData::MODEL_NUMBER, &args);
    char* modelNumber;
    args->Get("s", &modelNumber);
    EXPECT_STREQ("123456", modelNumber);
}

TEST(AboutDataTest, GetMsgArg_es_language)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacture");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg aboutArg;
    status = aboutData.GetAboutData(&aboutArg, "es");
    EXPECT_EQ(ER_OK, status);

    //printf("*****\n%s\n*****\n", aboutArg.ToString().c_str());

    MsgArg* args;

    aboutArg.GetElement("{sv}", AboutData::APP_ID, &args);
    int8_t* appIdOut;
    size_t appIdNum;
    args->Get("ay", &appIdNum, &appIdOut);
    ASSERT_EQ(16u, appIdNum);
    for (size_t i = 0; i < appIdNum; ++i) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    aboutArg.GetElement("{sv}", AboutData::DEFAULT_LANGUAGE, &args);
    char* defaultLanguage;
    args->Get("s", &defaultLanguage);
    EXPECT_STREQ("en", defaultLanguage);

    aboutArg.GetElement("{sv}", AboutData::DEVICE_ID, &args);
    char* deviceId;
    args->Get("s", &deviceId);
    EXPECT_STREQ("fakeID", deviceId);

    aboutArg.GetElement("{sv}", AboutData::APP_NAME, &args);
    char* appName;
    args->Get("s", &appName);
    EXPECT_STREQ("aplicacion", appName);

    aboutArg.GetElement("{sv}", AboutData::MANUFACTURER, &args);
    char* manufacturer;
    args->Get("s", &manufacturer);
    EXPECT_STREQ("manufactura", manufacturer);

    aboutArg.GetElement("{sv}", AboutData::MODEL_NUMBER, &args);
    char* modelNumber;
    args->Get("s", &modelNumber);
    EXPECT_STREQ("123456", modelNumber);
}

void VerifyAppName(AboutData& aboutData, const char* language, const char* expectedAppName)
{
    MsgArg aboutArg;
    QStatus status = aboutData.GetAboutData(&aboutArg, language);
    EXPECT_EQ(ER_OK, status);
    MsgArg* args;
    aboutArg.GetElement("{sv}", AboutData::APP_NAME, &args);
    char* appName;
    args->Get("s", &appName);
    EXPECT_STREQ(expectedAppName, appName);
}

TEST(AboutDataTest, GetMsgArg_best_language)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    EXPECT_FALSE(aboutData.IsValid());
    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetAppName("en appName");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("en manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("en description");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("de-CH");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("de-CH appName", "de-CH");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("de-CH manufacturer", "de-CH");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("de-CH description", "de-CH");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("de-CH"));

    // Test requesting languages that resolve to the language that happens
    // to be the default language.
    VerifyAppName(aboutData, "EN", "en appName");
    VerifyAppName(aboutData, "EN-US", "en appName");
    VerifyAppName(aboutData, "en-a-bbb-x-a-ccc", "en appName");

    // Test requesting languages that resolve to a language other than
    // the default language.
    VerifyAppName(aboutData, "DE-CH", "de-CH appName");
    VerifyAppName(aboutData, "de-ch-1901", "de-CH appName");

    // Test requesting languages that resolve to nothing and so use the
    // default language.
    VerifyAppName(aboutData, "de", "en appName");
    VerifyAppName(aboutData, "fr", "en appName");
}

static const char* targetLanguages[] = { "en", "de-CH" };
class MyAboutDataTranslator : public Translator {
  public:

    MyAboutDataTranslator()
    {
        appName[0].Set("s", "en appName");
        appName[1].Set("s", "de-CH appName");
        manufacturer[0].Set("s", "en manufacturer");
        manufacturer[1].Set("s", "de-CH manufacturer");
        description[0].Set("s", "en description");
        description[1].Set("s", "de-CH description");
    }

    virtual ~MyAboutDataTranslator() { }

    virtual size_t NumTargetLanguages() {
        return 2;
    }

    virtual void GetTargetLanguage(size_t index, qcc::String& ret) {
        ret.assign(targetLanguages[index]);
    }

    virtual QStatus TranslateToMsgArg(const char* sourceLanguage,
                                      const char* targetLanguage, const char* source, ajn::MsgArg*& msgarg)
    {
        QCC_UNUSED(sourceLanguage);
        size_t i = 0;

        for (i = 0; i < 2; i++) {
            if (strcasecmp(targetLanguage, targetLanguages[i]) == 0) {
                break;
            }
        }
        if (i == 2) {
            return ER_LANGUAGE_NOT_SUPPORTED;
        }

        if (0 == strcmp(source, "AppName")) {
            msgarg = &appName[i];
            return ER_OK;
        }

        if (0 == strcmp(source, "Manufacturer")) {
            msgarg = &manufacturer[i];
            return ER_OK;
        }

        if (0 == strcmp(source, "Description")) {
            msgarg = &description[i];
            return ER_OK;
        }

        return ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD;
    }

  private:
    MsgArg appName[2];
    MsgArg manufacturer[2];
    MsgArg description[2];
};

TEST(AboutDataTest, GetMsgArg_custom_translator)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);

    MyAboutDataTranslator translator;
    aboutData.SetTranslator(&translator);
    EXPECT_TRUE(aboutData.IsValid());
    EXPECT_TRUE(aboutData.IsValid("de-CH"));

    // Test requesting languages that resolve to the language that happens
    // to be the default language.
    VerifyAppName(aboutData, "EN", "en appName");
    VerifyAppName(aboutData, "EN-US", "en appName");
    VerifyAppName(aboutData, "en-a-bbb-x-a-ccc", "en appName");

    // Test requesting languages that resolve to a language other than
    // the default language.
    VerifyAppName(aboutData, "DE-CH", "de-CH appName");
    VerifyAppName(aboutData, "de-ch-1901", "de-CH appName");

    // Test requesting languages that resolve to nothing and so use the
    // default language.
    VerifyAppName(aboutData, "de", "en appName");
    VerifyAppName(aboutData, "fr", "en appName");
}

TEST(AboutDataTest, GetAnnouncedAboutData)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacture");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    MsgArg announceArg;
    status = aboutData.GetAnnouncedAboutData(&announceArg);
    EXPECT_EQ(ER_OK, status);

    MsgArg* args;

    announceArg.GetElement("{sv}", AboutData::APP_ID, &args);
    int8_t* appIdOut;
    size_t appIdNum;
    args->Get("ay", &appIdNum, &appIdOut);
    ASSERT_EQ(16u, appIdNum);
    for (size_t i = 0; i < appIdNum; ++i) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    announceArg.GetElement("{sv}", AboutData::DEFAULT_LANGUAGE, &args);
    char* defaultLanguage;
    args->Get("s", &defaultLanguage);
    EXPECT_STREQ("en", defaultLanguage);

    announceArg.GetElement("{sv}", AboutData::DEVICE_ID, &args);
    char* deviceId;
    args->Get("s", &deviceId);
    EXPECT_STREQ("fakeID", deviceId);

    announceArg.GetElement("{sv}", AboutData::APP_NAME, &args);
    char* appName;
    args->Get("s", &appName);
    EXPECT_STREQ("Application", appName);

    announceArg.GetElement("{sv}", AboutData::MANUFACTURER, &args);
    char* manufacturer;
    args->Get("s", &manufacturer);
    EXPECT_STREQ("Manufacture", manufacturer);

    announceArg.GetElement("{sv}", AboutData::MODEL_NUMBER, &args);
    char* modelNumber;
    args->Get("s", &modelNumber);
    EXPECT_STREQ("123456", modelNumber);
}

/*
 * ASACORE-1348
 * Unit test added to verify SetField is working as expected when following
 * steps described in bug.
 * 1. Create a new AboutData.
 * 2. Set a new OEM/custom field named "Foo" to value "A" for locale "en"
 * 3. Set a new value for "Foo" as "B" for locale "es"
 * 4. Optionally, verify that both "en" and "es" are added to the list of
 *    supported languages (they are).
 * 5. Optionally, verify that the "Foo" field is localized (IsLocalized). It is.
 * 6. Use GetField to retrieve the "Foo" value for "en". "A" should be returned.
 */
TEST(AboutDataTest, SetField) {
    AboutData aboutData("en");

    MsgArg en_arg("s", "A");
    MsgArg es_arg("s", "B");
    EXPECT_EQ(ER_OK, aboutData.SetField("Foo", en_arg, "en"));
    EXPECT_EQ(ER_OK, aboutData.SetField("Foo", es_arg, "es"));
    const char* languages[2];
    EXPECT_EQ((size_t)2, aboutData.GetSupportedLanguages(languages, 2));
    // order is unknown
    if (languages[0][1] == 's') {
        EXPECT_STREQ(languages[0], "es");
        EXPECT_STREQ(languages[1], "en");
    } else {
        EXPECT_STREQ(languages[0], "en");
        EXPECT_STREQ(languages[1], "es");
    }
    EXPECT_TRUE(aboutData.IsFieldLocalized("Foo"));
    MsgArg* foo_en_arg;
    MsgArg* foo_es_arg;
    EXPECT_EQ(ER_OK, aboutData.GetField("Foo", foo_en_arg, "en"));
    EXPECT_EQ(ER_OK, aboutData.GetField("Foo", foo_es_arg, "es"));
    char* foo_en;
    char* foo_es;
    EXPECT_EQ(ER_OK, foo_en_arg->Get("s", &foo_en));
    EXPECT_EQ(ER_OK, foo_es_arg->Get("s", &foo_es));

    EXPECT_STREQ("A", foo_en);
    EXPECT_STREQ("B", foo_es);
}

TEST(AboutDataTest, SetOEMSpecificField)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    MsgArg arg;
    status = arg.Set("s", "888-555-1234");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg);
    EXPECT_EQ(ER_OK, status);

    status = arg.Set("s", "800-555-4321");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg, "es");
    EXPECT_EQ(ER_OK, status);

    MsgArg* value;
    status = aboutData.GetField("SupportNumber", value);
    EXPECT_EQ(ER_OK, status);

    EXPECT_STREQ("s", value->Signature().c_str());
    const char* supportNumber;
    status = value->Get("s", &supportNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("888-555-1234", supportNumber);

    status = aboutData.GetField("SupportNumber", value, "es");
    EXPECT_EQ(ER_OK, status);

    EXPECT_STREQ("s", value->Signature().c_str());
    status = value->Get("s", &supportNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("800-555-4321", supportNumber);
}
TEST(AboutDataTest, GetMsgArgWithOEMSpecificField)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg arg;
    status = arg.Set("s", "888-555-1234");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg);
    EXPECT_EQ(ER_OK, status);

    status = arg.Set("s", "800-555-4321");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg, "es");
    EXPECT_EQ(ER_OK, status);

    MsgArg aboutArg;
    aboutData.GetAboutData(&aboutArg);

    MsgArg* args;

    aboutArg.GetElement("{sv}", AboutData::APP_ID, &args);
    int8_t* appIdOut;
    size_t appIdNum;
    args->Get("ay", &appIdNum, &appIdOut);
    ASSERT_EQ(16u, appIdNum);
    for (size_t i = 0; i < appIdNum; ++i) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    aboutArg.GetElement("{sv}", AboutData::DEFAULT_LANGUAGE, &args);
    char* defaultLanguage;
    args->Get("s", &defaultLanguage);
    EXPECT_STREQ("en", defaultLanguage);

    aboutArg.GetElement("{sv}", AboutData::DEVICE_ID, &args);
    char* deviceId;
    args->Get("s", &deviceId);
    EXPECT_STREQ("fakeID", deviceId);

    aboutArg.GetElement("{sv}", AboutData::APP_NAME, &args);
    char* appName;
    args->Get("s", &appName);
    EXPECT_STREQ("Application", appName);

    aboutArg.GetElement("{sv}", AboutData::MANUFACTURER, &args);
    char* manufacturer;
    args->Get("s", &manufacturer);
    EXPECT_STREQ("Manufacturer", manufacturer);

    aboutArg.GetElement("{sv}", AboutData::MODEL_NUMBER, &args);
    char* modelNumber;
    args->Get("s", &modelNumber);
    EXPECT_STREQ("123456", modelNumber);

    aboutArg.GetElement("{sv}", "SupportNumber", &args);
    char* supportNumber;
    args->Get("s", &supportNumber);
    EXPECT_STREQ("888-555-1234", supportNumber);
}

TEST(AboutDataTest, InitUsingMsgArgBadSignature) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");
    MsgArg notADictionary("s", "incorrect type.");

    status = aboutData.CreatefromMsgArg(notADictionary);
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, status);
}

TEST(AboutDataTest, InitUsingMsgArg)
{
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg arg;
    status = arg.Set("s", "888-555-1234");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg);
    EXPECT_EQ(ER_OK, status);

    status = arg.Set("s", "800-555-4321");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg, "es");
    EXPECT_EQ(ER_OK, status);

    MsgArg aboutArg;
    aboutData.GetAboutData(&aboutArg);

    AboutData aboutDataInit("en");
    status = aboutDataInit.CreatefromMsgArg(aboutArg);
    EXPECT_EQ(ER_OK, status);

    uint8_t* appIdOut;
    size_t numOut;
    status = aboutDataInit.GetAppId(&appIdOut, &numOut);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, numOut);
    for (size_t i = 0; i < numOut; i++) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    char* deviceId;
    status = aboutDataInit.GetDeviceId(&deviceId);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("fakeID", deviceId);

    char* appName;
    status = aboutDataInit.GetAppName(&appName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Application", appName);

    char* manufacturer;
    status = aboutDataInit.GetManufacturer(&manufacturer);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Manufacturer", manufacturer);

    char* modelNumber;
    status = aboutDataInit.GetModelNumber(&modelNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("123456", modelNumber);

    char* description;
    status = aboutDataInit.GetDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("A poetic description of this application", description);

    MsgArg* value;
    status = aboutDataInit.GetField("SupportNumber", value);
    EXPECT_EQ(ER_OK, status);

    EXPECT_STREQ("s", value->Signature().c_str());
    const char* supportNumber;
    status = value->Get("s", &supportNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("888-555-1234", supportNumber);

    size_t number_languages = aboutDataInit.GetSupportedLanguages();
    EXPECT_EQ(2u, number_languages);
    //TODO complete the test for language and other required
}

TEST(AboutDataTest, UTF8_test)
{
    char str[] = "привет";
    QStatus status = ER_FAIL;
    AboutData aboutData("en");

    status = aboutData.SetAppName(str, "ru");
    EXPECT_EQ(ER_OK, status);

    char* ruOut;
    status = aboutData.GetAppName(&ruOut, "ru");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ(str, ruOut);
}

TEST(AboutDataTest, CreateFromXml_from_qcc_string) {
    QStatus status = ER_FAIL;
    AboutData aboutData;
    qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "</AboutData>";
    status = aboutData.CreateFromXml(xml);
    EXPECT_EQ(ER_OK, status);

    // originalAppId is the string 000102030405060708090A0B0C0D0E0C converted to an array of bytes
    uint8_t originalAppId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 12 };
    uint8_t* appId;
    size_t num;
    status = aboutData.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(originalAppId[i], appId[i]) << i << ": " << originalAppId[i] << " = " << appId[i];
    }

    char* defaultLanguage;
    status = aboutData.GetDefaultLanguage(&defaultLanguage);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("en", defaultLanguage);

    char* deviceName;
    status = aboutData.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("My Device Name", deviceName);

    status = aboutData.GetDeviceName(&deviceName, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Nombre de mi dispositivo", deviceName);

    char* deviceId;
    status = aboutData.GetDeviceId(&deviceId);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("baddeviceid", deviceId);

    char* appName;
    status = aboutData.GetAppName(&appName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("My Application Name", appName);

    status = aboutData.GetAppName(&appName, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Mi Nombre de la aplicación", appName);

    char* manufacturer;
    status = aboutData.GetManufacturer(&manufacturer);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Company", manufacturer);

    status = aboutData.GetManufacturer(&manufacturer, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Empresa", manufacturer);

    size_t numLanguages = aboutData.GetSupportedLanguages();
    const char** languages = new const char*[numLanguages];

    size_t numRetLang = aboutData.GetSupportedLanguages(languages, numLanguages);
    EXPECT_EQ(numLanguages, numRetLang);
    EXPECT_EQ(2u, numLanguages);
    EXPECT_STREQ("en", languages[0]);
    EXPECT_STREQ("es", languages[1]);
    delete [] languages;
    languages = NULL;

    char* description;
    status = aboutData.GetDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("A detailed description provided by the application.", description);

    status = aboutData.GetDescription(&description, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Una descripción detallada proporcionada por la aplicación.", description);

    char* modelNumber;
    status = aboutData.GetModelNumber(&modelNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Wxfy388i", modelNumber);

    char* dateOfManufacture;
    status = aboutData.GetDateOfManufacture(&dateOfManufacture);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("2014-01-08", dateOfManufacture);

    char* softwareVersion;
    status = aboutData.GetSoftwareVersion(&softwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("1.0.0", softwareVersion);

    char* ajSoftwareVersion;
    status = aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    char* hardwareVersion;
    status = aboutData.GetHardwareVersion(&hardwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("1.0.0", hardwareVersion);

    char* supportUrl;
    status = aboutData.GetSupportUrl(&supportUrl);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("www.example.com", supportUrl);

    MsgArg* value;
    status = aboutData.GetField("UserDefinedTag", value);
    EXPECT_EQ(ER_OK, status);

    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* userDefined;
    status = value->Get("s", &userDefined);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Can only accept strings anything other than strings must be done using the AboutData Class SetField method", userDefined);

    status = aboutData.GetField("UserDefinedTag", value, "es");
    EXPECT_EQ(ER_OK, status);

    EXPECT_STREQ("s", value->Signature().c_str());
    status = value->Get("s", &userDefined);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField", userDefined);
}
/*
 * This test is identical to AboutDataTest.CreateFromXml_from_qcc_string except
 * the xml string is passed in as a const char* not a qcc::String
 */
TEST(AboutDataTest, CreateFromXml_from_char_string) {
    QStatus status = ER_FAIL;
    AboutData aboutData;
    const char* xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "</AboutData>";
    status = aboutData.CreateFromXml(xml);
    EXPECT_EQ(ER_OK, status);

    // originalAppId is the string 000102030405060708090A0B0C0D0E0C converted to an array of bytes
    uint8_t originalAppId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 12 };
    uint8_t* appId;
    size_t num;
    status = aboutData.GetAppId(&appId, &num);
    EXPECT_EQ(ER_OK, status);
    ASSERT_EQ(16u, num);
    for (size_t i = 0; i < num; i++) {
        EXPECT_EQ(originalAppId[i], appId[i]) << i << ": " << originalAppId[i] << " = " << appId[i];
    }

    char* defaultLanguage;
    status = aboutData.GetDefaultLanguage(&defaultLanguage);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("en", defaultLanguage);

    char* deviceName;
    status = aboutData.GetDeviceName(&deviceName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("My Device Name", deviceName);

    status = aboutData.GetDeviceName(&deviceName, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Nombre de mi dispositivo", deviceName);

    char* deviceId;
    status = aboutData.GetDeviceId(&deviceId);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("baddeviceid", deviceId);

    char* appName;
    status = aboutData.GetAppName(&appName);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("My Application Name", appName);

    status = aboutData.GetAppName(&appName, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Mi Nombre de la aplicación", appName);

    char* manufacturer;
    status = aboutData.GetManufacturer(&manufacturer);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Company", manufacturer);

    status = aboutData.GetManufacturer(&manufacturer, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Empresa", manufacturer);

    size_t numLanguages = aboutData.GetSupportedLanguages();
    const char** languages = new const char*[numLanguages];

    size_t numRetLang = aboutData.GetSupportedLanguages(languages, numLanguages);
    EXPECT_EQ(numLanguages, numRetLang);
    EXPECT_EQ(2u, numLanguages);
    EXPECT_STREQ("en", languages[0]);
    EXPECT_STREQ("es", languages[1]);
    delete [] languages;
    languages = NULL;

    char* description;
    status = aboutData.GetDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("A detailed description provided by the application.", description);

    status = aboutData.GetDescription(&description, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Una descripción detallada proporcionada por la aplicación.", description);

    char* modelNumber;
    status = aboutData.GetModelNumber(&modelNumber);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Wxfy388i", modelNumber);

    char* dateOfManufacture;
    status = aboutData.GetDateOfManufacture(&dateOfManufacture);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("2014-01-08", dateOfManufacture);

    char* softwareVersion;
    status = aboutData.GetSoftwareVersion(&softwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("1.0.0", softwareVersion);

    char* ajSoftwareVersion;
    status = aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    char* hardwareVersion;
    status = aboutData.GetHardwareVersion(&hardwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("1.0.0", hardwareVersion);

    char* supportUrl;
    status = aboutData.GetSupportUrl(&supportUrl);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("www.example.com", supportUrl);
}

/*
 * ASACORE-1603 prevent the CreateFromXml function from segfaulting
 * The CreateFromXml will continue parsing and will not report an error.
 * Users will have to use the IsValid method to check if the AboutData contains
 * all valid fields.
 */
TEST(AboutDataTest, CreateFromXml_missing_required_field) {
    AboutData aboutData;
    qcc::String xml =
        "<AboutData>"
        "  <Daemonrealm></Daemonrealm>"
        "  <DateOfManufacture>2199-10-01</DateOfManufacture>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <HardwareVersion>355.499. b</HardwareVersion>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Passcode>000000</Passcode>"
        "  <SoftwareVersion>12.20.44 build 44454</SoftwareVersion>"
        "  <SupportUrl>http://ask.allseenaliance.org</SupportUrl>"
        "  <AppName>OnboardingServiceApp</AppName>"
        "  <AppName lang='en'>OnboardingServiceApp</AppName>"
        "  <AppName lang='es'>OnboardingServiceApp</AppName>"
        "  <AppName lang='fr'>OnboardingServiceApp</AppName>"
        "  <Description>This is an Alljoyn Application</Description>"
        "  <Description lang='en'>This is an Alljoyn Application</Description>"
        "  <Description lang='es'>Esta es una Alljoyn aplicacion</Description>"
        "  <Description lang='fr'>C'est une Alljoyn application</Description>"
        "  <DeviceName>My device name</DeviceName>"
        "  <DeviceName lang='en'>My device name</DeviceName>"
        "  <DeviceName lang='es'>Mi nombre de dispositivo</DeviceName>"
        "  <DeviceName lang='fr'>Mon nom de l'appareil</DeviceName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang='en'>Company</Manufacturer>"
        "  <Manufacturer lang='es'>Empresa</Manufacturer>"
        "  <Manufacturer lang='fr'>Entreprise</Manufacturer>"
        "  <scan_file>/tmp/wifi_scan_results</scan_file>"
        "  <error_file>/tmp/state/alljoyn-onboarding-lasterror</error_file>"
        "  <state_file>/tmp/state/alljoyn-onboarding</state_file>"
        "  <connect_cmd>/etc/init.d/alljoyn-onboarding connect</connect_cmd>"
        "  <offboard_cmd>/etc/init.d/alljoyn-onboarding offboard</offboard_cmd>"
        "  <configure_cmd>/etc/init.d/alljoyn-onboarding configure %s %s %s</configure_cmd>"
        "  <scan_cmd>/usr/sbin/wifi_scan</scan_cmd>"
        "</AboutData>";
    EXPECT_EQ(ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD, aboutData.CreateFromXml(xml));
    EXPECT_FALSE(aboutData.IsValid());

    uint8_t* appId;
    size_t num;
    // no AppId present in the Xml
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetAppId(&appId, &num));

    char* defaultLanguage;
    EXPECT_EQ(ER_OK, aboutData.GetDefaultLanguage(&defaultLanguage));
    EXPECT_STREQ("en", defaultLanguage);

    char* deviceName;
    EXPECT_EQ(ER_OK, aboutData.GetDeviceName(&deviceName));
    EXPECT_STREQ("My device name", deviceName);

    EXPECT_EQ(ER_OK, aboutData.GetDeviceName(&deviceName, "es"));
    EXPECT_STREQ("Mi nombre de dispositivo", deviceName);

    EXPECT_EQ(ER_OK, aboutData.GetDeviceName(&deviceName, "fr"));
    EXPECT_STREQ("Mon nom de l'appareil", deviceName);

    // No DeviceId present in the Xml
    char* deviceId;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetDeviceId(&deviceId));

    char* appName;
    EXPECT_EQ(ER_OK, aboutData.GetAppName(&appName));
    EXPECT_STREQ("OnboardingServiceApp", appName);

    EXPECT_EQ(ER_OK, aboutData.GetAppName(&appName, "es"));
    EXPECT_STREQ("OnboardingServiceApp", appName);

    EXPECT_EQ(ER_OK, aboutData.GetAppName(&appName, "fr"));
    EXPECT_STREQ("OnboardingServiceApp", appName);

    char* manufacturer;
    EXPECT_EQ(ER_OK, aboutData.GetManufacturer(&manufacturer));
    EXPECT_STREQ("Company", manufacturer);

    EXPECT_EQ(ER_OK, aboutData.GetManufacturer(&manufacturer, "es"));
    EXPECT_STREQ("Empresa", manufacturer);

    EXPECT_EQ(ER_OK, aboutData.GetManufacturer(&manufacturer, "fr"));
    EXPECT_STREQ("Entreprise", manufacturer);

    size_t numLanguages = aboutData.GetSupportedLanguages();
    const char** languages = new const char*[numLanguages];

    size_t numRetLang = aboutData.GetSupportedLanguages(languages, numLanguages);
    EXPECT_EQ(numLanguages, numRetLang);
    ASSERT_EQ(3u, numLanguages);
    EXPECT_STREQ("en", languages[0]);
    EXPECT_STREQ("es", languages[1]);
    EXPECT_STREQ("fr", languages[2]);
    delete [] languages;
    languages = NULL;

    char* description;
    EXPECT_EQ(ER_OK, aboutData.GetDescription(&description));
    EXPECT_STREQ("This is an Alljoyn Application", description);

    EXPECT_EQ(ER_OK, aboutData.GetDescription(&description, "es"));
    EXPECT_STREQ("Esta es una Alljoyn aplicacion", description);

    EXPECT_EQ(ER_OK, aboutData.GetDescription(&description, "fr"));
    EXPECT_STREQ("C'est une Alljoyn application", description);

    char* modelNumber;
    EXPECT_EQ(ER_OK, aboutData.GetModelNumber(&modelNumber));
    EXPECT_STREQ("Wxfy388i", modelNumber);

    char* dateOfManufacture;
    EXPECT_EQ(ER_OK, aboutData.GetDateOfManufacture(&dateOfManufacture));
    EXPECT_STREQ("2199-10-01", dateOfManufacture);

    char* softwareVersion;
    EXPECT_EQ(ER_OK, aboutData.GetSoftwareVersion(&softwareVersion));
    EXPECT_STREQ("12.20.44 build 44454", softwareVersion);

    char* ajSoftwareVersion;
    EXPECT_EQ(ER_OK, aboutData.GetAJSoftwareVersion(&ajSoftwareVersion));
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    char* hardwareVersion;
    EXPECT_EQ(ER_OK, aboutData.GetHardwareVersion(&hardwareVersion));
    EXPECT_STREQ("355.499. b", hardwareVersion);

    char* supportUrl;
    EXPECT_EQ(ER_OK, aboutData.GetSupportUrl(&supportUrl));
    EXPECT_STREQ("http://ask.allseenaliance.org", supportUrl);

    MsgArg* value;
    EXPECT_EQ(ER_OK, aboutData.GetField("Passcode", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* passcode;
    EXPECT_EQ(ER_OK, value->Get("s", &passcode));
    EXPECT_STREQ("000000", passcode);

    EXPECT_EQ(ER_OK, aboutData.GetField("scan_file", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* scan_file;
    EXPECT_EQ(ER_OK, value->Get("s", &scan_file));
    EXPECT_STREQ("/tmp/wifi_scan_results", scan_file);

    // "  <error_file>/tmp/state/alljoyn-onboarding-lasterror</error_file>"
    EXPECT_EQ(ER_OK, aboutData.GetField("error_file", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* error_file;
    EXPECT_EQ(ER_OK, value->Get("s", &error_file));
    EXPECT_STREQ("/tmp/state/alljoyn-onboarding-lasterror", error_file);

    //"  <state_file>/tmp/state/alljoyn-onboarding</state_file>"
    EXPECT_EQ(ER_OK, aboutData.GetField("state_file", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* state_file;
    EXPECT_EQ(ER_OK, value->Get("s", &state_file));
    EXPECT_STREQ("/tmp/state/alljoyn-onboarding", state_file);

    //"  <connect_cmd>/etc/init.d/alljoyn-onboarding connect</connect_cmd>"
    EXPECT_EQ(ER_OK, aboutData.GetField("connect_cmd", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* connect_cmd;
    EXPECT_EQ(ER_OK, value->Get("s", &connect_cmd));
    EXPECT_STREQ("/etc/init.d/alljoyn-onboarding connect", connect_cmd);

    //"  <offboard_cmd>/etc/init.d/alljoyn-onboarding offboard</offboard_cmd>"
    EXPECT_EQ(ER_OK, aboutData.GetField("offboard_cmd", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* offboard_cmd;
    EXPECT_EQ(ER_OK, value->Get("s", &offboard_cmd));
    EXPECT_STREQ("/etc/init.d/alljoyn-onboarding offboard", offboard_cmd);

    //"  <configure_cmd>/etc/init.d/alljoyn-onboarding configure %s %s %s</configure_cmd>"
    EXPECT_EQ(ER_OK, aboutData.GetField("configure_cmd", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* configure_cmd;
    EXPECT_EQ(ER_OK, value->Get("s", &configure_cmd));
    EXPECT_STREQ("/etc/init.d/alljoyn-onboarding configure %s %s %s", configure_cmd);

    //"  <scan_cmd>/usr/sbin/wifi_scan</scan_cmd>"
    EXPECT_EQ(ER_OK, aboutData.GetField("scan_cmd", value));
    EXPECT_STREQ("s", value->Signature().c_str()) << value->ToString();
    const char* scan_cmd;
    EXPECT_EQ(ER_OK, value->Get("s", &scan_cmd));
    EXPECT_STREQ("/usr/sbin/wifi_scan", scan_cmd);

}

TEST(AboutDataTest, CreateFromXml_missing_default_language) {
    AboutData aboutData;
    qcc::String xml =
        "<AboutData>"
        "  <Daemonrealm></Daemonrealm>"
        "  <DateOfManufacture>2199-10-01</DateOfManufacture>"
        "  <HardwareVersion>355.499. b</HardwareVersion>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Passcode>000000</Passcode>"
        "  <SoftwareVersion>12.20.44 build 44454</SoftwareVersion>"
        "  <SupportUrl>http://ask.allseenaliance.org</SupportUrl>"
        "  <AppName>OnboardingServiceApp</AppName>"
        "  <AppName lang='en'>OnboardingServiceApp</AppName>"
        "  <AppName lang='es'>OnboardingServiceApp</AppName>"
        "  <AppName lang='fr'>OnboardingServiceApp</AppName>"
        "  <Description>This is an Alljoyn Application</Description>"
        "  <Description lang='en'>This is an Alljoyn Application</Description>"
        "  <Description lang='es'>Esta es una Alljoyn aplicacion</Description>"
        "  <Description lang='fr'>C'est une Alljoyn application</Description>"
        "  <DeviceName>My device name</DeviceName>"
        "  <DeviceName lang='en'>My device name</DeviceName>"
        "  <DeviceName lang='es'>Mi nombre de dispositivo</DeviceName>"
        "  <DeviceName lang='fr'>Mon nom de l'appareil</DeviceName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang='en'>Company</Manufacturer>"
        "  <Manufacturer lang='es'>Empresa</Manufacturer>"
        "  <Manufacturer lang='fr'>Entreprise</Manufacturer>"
        "</AboutData>";
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, aboutData.CreateFromXml(xml));

    EXPECT_FALSE(aboutData.IsValid());

    uint8_t* appId;
    size_t num;
    // no AppId present in the Xml
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetAppId(&appId, &num));

    char* defaultLanguage;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetDefaultLanguage(&defaultLanguage));

    char* deviceName;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetDeviceName(&deviceName));
    EXPECT_EQ(ER_OK, aboutData.GetDeviceName(&deviceName, "en"));
    EXPECT_STREQ("My device name", deviceName);

    EXPECT_EQ(ER_OK, aboutData.GetDeviceName(&deviceName, "es"));
    EXPECT_STREQ("Mi nombre de dispositivo", deviceName);

    EXPECT_EQ(ER_OK, aboutData.GetDeviceName(&deviceName, "fr"));
    EXPECT_STREQ("Mon nom de l'appareil", deviceName);

    // No DeviceId present in the Xml
    char* deviceId;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetDeviceId(&deviceId));

    char* appName;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetAppName(&appName));
    EXPECT_EQ(ER_OK, aboutData.GetAppName(&appName, "en"));
    EXPECT_STREQ("OnboardingServiceApp", appName);

    EXPECT_EQ(ER_OK, aboutData.GetAppName(&appName, "es"));
    EXPECT_STREQ("OnboardingServiceApp", appName);

    EXPECT_EQ(ER_OK, aboutData.GetAppName(&appName, "fr"));
    EXPECT_STREQ("OnboardingServiceApp", appName);

    char* manufacturer;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetManufacturer(&manufacturer));
    EXPECT_EQ(ER_OK, aboutData.GetManufacturer(&manufacturer, "en"));
    EXPECT_STREQ("Company", manufacturer);

    EXPECT_EQ(ER_OK, aboutData.GetManufacturer(&manufacturer, "es"));
    EXPECT_STREQ("Empresa", manufacturer);

    EXPECT_EQ(ER_OK, aboutData.GetManufacturer(&manufacturer, "fr"));
    EXPECT_STREQ("Entreprise", manufacturer);

    size_t numLanguages = aboutData.GetSupportedLanguages();
    const char** languages = new const char*[numLanguages];

    size_t numRetLang = aboutData.GetSupportedLanguages(languages, numLanguages);
    EXPECT_EQ(numLanguages, numRetLang);
    ASSERT_EQ(3u, numLanguages);
    EXPECT_STREQ("en", languages[0]);
    EXPECT_STREQ("es", languages[1]);
    EXPECT_STREQ("fr", languages[2]);
    delete [] languages;
    languages = NULL;

    char* description;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetDescription(&description));
    EXPECT_EQ(ER_OK, aboutData.GetDescription(&description, "en"));
    EXPECT_STREQ("This is an Alljoyn Application", description);

    EXPECT_EQ(ER_OK, aboutData.GetDescription(&description, "es"));
    EXPECT_STREQ("Esta es una Alljoyn aplicacion", description);

    EXPECT_EQ(ER_OK, aboutData.GetDescription(&description, "fr"));
    EXPECT_STREQ("C'est une Alljoyn application", description);

    char* modelNumber;
    EXPECT_EQ(ER_OK, aboutData.GetModelNumber(&modelNumber));
    EXPECT_STREQ("Wxfy388i", modelNumber);

    char* dateOfManufacture;
    EXPECT_EQ(ER_OK, aboutData.GetDateOfManufacture(&dateOfManufacture));
    EXPECT_STREQ("2199-10-01", dateOfManufacture);

    char* softwareVersion;
    EXPECT_EQ(ER_OK, aboutData.GetSoftwareVersion(&softwareVersion));
    EXPECT_STREQ("12.20.44 build 44454", softwareVersion);

    char* ajSoftwareVersion;
    EXPECT_EQ(ER_OK, aboutData.GetAJSoftwareVersion(&ajSoftwareVersion));
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    char* hardwareVersion;
    EXPECT_EQ(ER_OK, aboutData.GetHardwareVersion(&hardwareVersion));
    EXPECT_STREQ("355.499. b", hardwareVersion);

    char* supportUrl;
    EXPECT_EQ(ER_OK, aboutData.GetSupportUrl(&supportUrl));
    EXPECT_STREQ("http://ask.allseenaliance.org", supportUrl);

    MsgArg* value;
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, aboutData.GetField("Passcode", value));
}

class AboutDataTestAboutData : public AboutData {
  public:
    static const char* TEST_FIELDABC;

    AboutDataTestAboutData() : AboutData() {
        // test field abc is required, is announced, not localized
        SetNewFieldDetails(TEST_FIELDABC, REQUIRED | ANNOUNCED, "s");
    }
    AboutDataTestAboutData(const char* defaultLanguage) : AboutData(defaultLanguage) {
        SetNewFieldDetails(TEST_FIELDABC, REQUIRED | ANNOUNCED, "s");
    }

    QStatus SetTestFieldABC(const char* testFieldABC)
    {
        QStatus status = ER_OK;
        MsgArg arg;
        status = arg.Set(GetFieldSignature(TEST_FIELDABC), testFieldABC);
        if (status != ER_OK) {
            return status;
        }
        status = SetField(TEST_FIELDABC, arg);
        return status;
    }

    QStatus GetTestFieldABC(char** testFieldABC)
    {
        QStatus status;
        MsgArg* arg;
        status = GetField(TEST_FIELDABC, arg);
        if (status != ER_OK) {
            return status;
        }
        status = arg->Get(GetFieldSignature(TEST_FIELDABC), testFieldABC);
        return status;
    }
};

const char* AboutDataTestAboutData::TEST_FIELDABC = "TestFieldABC";

TEST(AboutDataTest, SetNewField) {
    QStatus status = ER_FAIL;
    AboutDataTestAboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_FALSE(aboutData.IsValid());
    status = aboutData.SetTestFieldABC("Mary had a little lamb.");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    MsgArg announceArg;
    status = aboutData.GetAnnouncedAboutData(&announceArg);
    EXPECT_EQ(ER_OK, status);

    MsgArg* args;

    announceArg.GetElement("{sv}", AboutDataTestAboutData::APP_ID, &args);
    int8_t* appIdOut;
    size_t appIdNum;
    args->Get("ay", &appIdNum, &appIdOut);
    ASSERT_EQ(16u, appIdNum);
    for (size_t i = 0; i < appIdNum; ++i) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    announceArg.GetElement("{sv}", AboutDataTestAboutData::DEFAULT_LANGUAGE, &args);
    char* defaultLanguage;
    args->Get("s", &defaultLanguage);
    EXPECT_STREQ("en", defaultLanguage);

    announceArg.GetElement("{sv}", AboutDataTestAboutData::DEVICE_ID, &args);
    char* deviceId;
    args->Get("s", &deviceId);
    EXPECT_STREQ("fakeID", deviceId);

    announceArg.GetElement("{sv}", AboutDataTestAboutData::APP_NAME, &args);
    char* appName;
    args->Get("s", &appName);
    EXPECT_STREQ("Application", appName);

    announceArg.GetElement("{sv}", AboutDataTestAboutData::MANUFACTURER, &args);
    char* manufacturer;
    args->Get("s", &manufacturer);
    EXPECT_STREQ("Manufacturer", manufacturer);

    announceArg.GetElement("{sv}", AboutDataTestAboutData::MODEL_NUMBER, &args);
    char* modelNumber;
    args->Get("s", &modelNumber);
    EXPECT_STREQ("123456", modelNumber);

    announceArg.GetElement("{sv}", AboutDataTestAboutData::TEST_FIELDABC, &args);
    char* testFieldabc;
    args->Get("s", &testFieldabc);
    EXPECT_STREQ("Mary had a little lamb.", testFieldabc);
}

bool hasField(const char** fields, size_t count, const char* fieldName) {
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(fieldName, fields[i]) == 0) {
            return true;
        }
    }
    return false;
}

TEST(AboutDataTest, GetFields) {
    QStatus status = ER_FAIL;
    AboutDataTestAboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    EXPECT_FALSE(aboutData.IsValid());
    status = aboutData.SetTestFieldABC("Mary had a little lamb.");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    size_t count = aboutData.GetFields();
    // The 8 fields set above + 3 implicitly created fields: AJSoftwareVersion,
    // SupportedLanguages, and DefaultLanguage.
    EXPECT_EQ(11u, count);

    const char** fields = new const char*[count];
    EXPECT_EQ(count, aboutData.GetFields(fields, count));

    EXPECT_TRUE(hasField(fields, count, "AJSoftwareVersion"));
    EXPECT_TRUE(hasField(fields, count, "AppId"));
    EXPECT_TRUE(hasField(fields, count, "DefaultLanguage"));
    EXPECT_TRUE(hasField(fields, count, "DeviceId"));
    EXPECT_TRUE(hasField(fields, count, "ModelNumber"));
    EXPECT_TRUE(hasField(fields, count, "SoftwareVersion"));
    EXPECT_TRUE(hasField(fields, count, "SupportedLanguages"));
    EXPECT_TRUE(hasField(fields, count, "TestFieldABC"));
    EXPECT_TRUE(hasField(fields, count, "AppName"));
    EXPECT_TRUE(hasField(fields, count, "Description"));
    EXPECT_TRUE(hasField(fields, count, "Manufacturer"));

    delete [] fields;
}

TEST(AboutDataTest, caseInsensitiveLanguageTag) {
    QStatus status = ER_FAIL;
    AboutData aboutData("en");
    char* language;
    status = aboutData.GetDefaultLanguage(&language);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("en", language);
    /* set the device name in english the default name tag all lowercase "en" */
    status = aboutData.SetDeviceName("Device");
    EXPECT_EQ(ER_OK, status);

    /* set the device name in spanish the default name tag all lowercase "es" */
    status = aboutData.SetDeviceName("dispositivo", "es");
    EXPECT_EQ(ER_OK, status);

    size_t num_langs;
    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    /*
     * Case insensitive Setting
     * the number of langauges should remain 2
     */
    status = aboutData.SetDeviceName("Device", "EN");
    EXPECT_EQ(ER_OK, status);

    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    status = aboutData.SetDeviceName("Device", "En");
    EXPECT_EQ(ER_OK, status);

    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    status = aboutData.SetDeviceName("Device", "eN");
    EXPECT_EQ(ER_OK, status);

    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    status = aboutData.SetDeviceName("dispositivo", "ES");
    EXPECT_EQ(ER_OK, status);

    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    status = aboutData.SetDeviceName("dispositivo", "Es");
    EXPECT_EQ(ER_OK, status);

    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    status = aboutData.SetDeviceName("dispositivo", "eS");
    EXPECT_EQ(ER_OK, status);

    num_langs = aboutData.GetSupportedLanguages();
    EXPECT_EQ(2u, num_langs);

    /*
     * Case insensitive Getting of the language-tag
     */
    char* deviceName;
    status = aboutData.GetDeviceName(&deviceName, "EN");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Device", deviceName);

    deviceName = NULL;
    status = aboutData.GetDeviceName(&deviceName, "En");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Device", deviceName);

    deviceName = NULL;
    status = aboutData.GetDeviceName(&deviceName, "eN");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Device", deviceName);

    deviceName = NULL;
    status = aboutData.GetDeviceName(&deviceName, "ES");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("dispositivo", deviceName);

    deviceName = NULL;
    status = aboutData.GetDeviceName(&deviceName, "Es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("dispositivo", deviceName);

    deviceName = NULL;
    status = aboutData.GetDeviceName(&deviceName, "eS");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("dispositivo", deviceName);
}

//TEST(AboutDataTest, SetSupportUrlEmpty) {
//    QStatus status = ER_FAIL;
//    AboutData aboutData("en");
//
//    char* supportUrl;
//    status = aboutData.GetSupportUrl(&supportUrl);
//    EXPECT_EQ(ER_OK, status);
//    EXPECT_STREQ("www.example.com", supportUrl);
//}
