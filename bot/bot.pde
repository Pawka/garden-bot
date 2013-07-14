
const int MOISTURE_PIN = A0; //Moisture sensor pin.
const int OUPTUT_LED_PIN = 13; //Data output indication pin.
const int MOISTURE_LED_PIN = 12; //Light led when moisture is too low.

const int TIMEOUT = 1000; //Loop timeout in ms.

void setup() {                
    pinMode(OUPTUT_LED_PIN, OUTPUT);
    pinMode(MOISTURE_LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    sendResults();
    delay(TIMEOUT);
}

/**
 *  Return moisture value from sensor
 */
int getMoisture() {
    int moistureValue = analogRead(MOISTURE_PIN);

    return moistureValue;
}

/**
 * Light on/off moisture LED by current value.
 */
void updateMoistureLed(int currentValue) {
    int edge = 300; //@todo read from memory.

    if (currentValue >= edge) {
        digitalWrite(MOISTURE_LED_PIN, HIGH);
    } else {
        digitalWrite(MOISTURE_LED_PIN, LOW);
    }
}

/**
 * Send collected sensor values via serial connection.
 */
void sendResults() {
    digitalWrite(OUPTUT_LED_PIN, HIGH);
    int moisture = getMoisture();
    updateMoistureLed(moisture);
    Serial.println(moisture);
    digitalWrite(OUPTUT_LED_PIN, LOW);
}
