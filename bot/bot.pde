
const int MOISTURE_PIN = A0; //Moisture sensor pin.
const int OUPTUT_LED_PIN = 13; //Data output indication pin.
const int MOUSTURE_LED_PIN = 12; //Light led when moisture is too low.

const int TIMEOUT = 1000; //Loop timeout in ms.

void setup() {                
    pinMode(OUPTUT_LED_PIN, OUTPUT);
    pinMode(MOUSTURE_LED_PIN, OUTPUT);
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
 * Send collected sensor values via serial connection.
 */
void sendResults() {
    digitalWrite(OUPTUT_LED_PIN, HIGH);
    Serial.println(getMoisture());
    digitalWrite(OUPTUT_LED_PIN, LOW);
}
