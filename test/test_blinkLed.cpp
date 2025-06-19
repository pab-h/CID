#ifdef UNIT_TEST

#include <Arduino.h>
#include <unity.h>


void test_blinkLed() {
    
    pinMode(LED_BUILTIN, OUTPUT);

    for(int i = 0; i < 3; i++) {

        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);

    }

    TEST_ASSERT_TRUE(true);

}

void setup() {

    UNITY_BEGIN();

    RUN_TEST(test_blinkLed);

    UNITY_END();

}

void loop() {}

#endif