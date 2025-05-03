#include "drivers/DHT22Protocol.hpp"

using namespace drivers;


DHT22Data DHT22Protocol::read(uint8_t pin){

    uint8_t data[5] = {0};
    DHT22Data result = {{0}, false};

    //Establishing a connection
    pinMode(pin, OUTPUT);

    digitalWrite(pin, LOW);
    delayMicroseconds(2);

    digitalWrite(pin, HIGH);
    delayMicroseconds(30);

    pinMode(pin, INPUT);

    //Waiting DHT22 Response
    if(!waitForLevel(pin, LOW, 85)) return result;
    if(!waitForLevel(pin, HIGH, 85)) return result;
    if(!waitForLevel(pin, LOW, 85)) return result;

    //Connection completed, collecting data:
    for(int i = 0; i < 40; i++){
        if(waitForLevel(pin, HIGH, 60)) return result; //timeout
        
        unsigned long start =  micros();
        while(digitalRead(pin)){
            if(micros() - start > 90) return result;
        }

        unsigned long pulseDuration = micros() - start;
        
        data[i/8] <<= 1;
        
        if(pulseDuration > 50){
            data[i/8] |= 1; //00000001
        }

    }
    
    //Fill result fields (bytes and success)
    memcpy(result.bytes, data, sizeof(data));
    result.success = verifyChecksum(data);

    return result;
}


bool DHT22Protocol::verifyChecksum(const uint8_t data[5]){

    uint8_t sum = data[0] + data[1] + data[2] + data[3];

    if (sum == data[4]) return true;
    return false;

}


bool DHT22Protocol::waitForLevel(uint8_t pin, uint8_t level, uint32_t timeout_us){
    uint32_t start = micros();

    while(digitalRead(pin) != level){
        if(micros() - start > timeout_us) return false;
    }

    return true;
}

