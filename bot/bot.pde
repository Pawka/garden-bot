
const int MOISTURE_PIN = A0; //Moisture sensor pin

const int TIMEOUT = 1000; //Loop timeout in ms.

void setup() {                
    Serial.begin(9600);
}

void loop() {
    Serial.println(getMoisture());
    delay(TIMEOUT);
}

/**
 *  Return moisture value from sensor
 */
int getMoisture() {
    int moistureValue = analogRead(MOISTURE_PIN);

    return moistureValue;
}
