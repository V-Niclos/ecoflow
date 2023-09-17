#include <unity.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <ClsRelayOnOff.h>

using namespace fakeit;

#define PIN0 1

#define SETUP_RELAY() \
    ClsRelayOnOff relay; \
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn(); \
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn(); \
    relay.setup(0, PIN0, "TestRelay0",ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);


void test_relay_setup() {
    SETUP_RELAY()
    Verify(Method(ArduinoFake(), pinMode).Using(PIN0, OUTPUT),
           Method(ArduinoFake(), digitalWrite).Using(PIN0, HIGH)).Once();
}

void test_relay_open_close() {
    SETUP_RELAY()
    ArduinoFake().ClearInvocationHistory();

    // Test setOpen
    relay.setOpen();
    Verify(Method(ArduinoFake(), digitalWrite).Using(PIN0, LOW)).Once();

    // Test setClose
    relay.setClose();
    Verify(Method(ArduinoFake(), digitalWrite).Using(PIN0, HIGH)).Once();

    // Test getIsOpen
    When(Method(ArduinoFake(), digitalRead).Using(PIN0)).Return(ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
    uint8_t is_open = relay.getIsOpen();
    TEST_ASSERT_EQUAL(0, is_open);

    When(Method(ArduinoFake(), digitalRead).Using(PIN0)).Return(ClsRelayOnOff::eOnOff_OPENCLOSE_OPEN);
    is_open = relay.getIsOpen();
    TEST_ASSERT_EQUAL(1, is_open);
}

void test_relay_get_json() {

    SETUP_RELAY()

    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
    String json = relay.getJson();
    TEST_ASSERT_EQUAL_STRING(
        "{\"Lines\": [{\"RelayId\":\"0\", \"RelayPin\":\"1\", \"RelayName\":\"TestRelay0\", \"PrgIsOpen\":\"0\"}"
        "{\"RelayId\":\"0\", \"RelayPin\":\"1\", \"RelayName\":\"TestRelay0\", \"PrgIsOpen\":\"0\"}"
        "{\"RelayId\":\"0\", \"RelayPin\":\"1\", \"RelayName\":\"TestRelay0\", \"PrgIsOpen\":\"0\"}"
        "]}",
        json.c_str());


    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(ClsRelayOnOff::eOnOff_OPENCLOSE_OPEN);
    json = relay.getJson();
    TEST_ASSERT_EQUAL_STRING(
        "{\"Lines\": [{\"RelayId\":\"0\", \"RelayPin\":\"1\", \"RelayName\":\"TestRelay0\", \"PrgIsOpen\":\"1\"}"
        "{\"RelayId\":\"0\", \"RelayPin\":\"1\", \"RelayName\":\"TestRelay0\", \"PrgIsOpen\":\"1\"}"
        "{\"RelayId\":\"0\", \"RelayPin\":\"1\", \"RelayName\":\"TestRelay0\", \"PrgIsOpen\":\"1\"}"
        "]}",
        json.c_str());
}


void test_relay_get_html() {
        SETUP_RELAY()

    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(ClsRelayOnOff::eOnOff_OPENCLOSE_CLOSE);
    String html = relay.getHtmlStatus();
    TEST_ASSERT_EQUAL_STRING(
        "<hr/><h5>Relays type on off</h5><p><b>0 TestRelay0 </b><span class=\"led red\"></span><p>",
        html.c_str());


    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(ClsRelayOnOff::eOnOff_OPENCLOSE_OPEN);
    html = relay.getHtmlStatus();
    TEST_ASSERT_EQUAL_STRING(
        "<hr/><h5>Relays type on off</h5><p><b>0 TestRelay0 </b><span class=\"led green\"></span><p>",
        html.c_str());
}

void test_relays() {
    RUN_TEST(test_relay_setup);
    RUN_TEST(test_relay_open_close);
    RUN_TEST(test_relay_get_json);
    RUN_TEST(test_relay_get_html);
}