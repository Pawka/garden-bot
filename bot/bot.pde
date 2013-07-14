
const int MOISTURE_PIN     = A0; //Moisture sensor pin.
const int PHOTOCELL_PIN    = A1; //Light sensor pin.

const int MOISTURE_LED_PIN = 12; //Light led when moisture is too low.
const int OUPTUT_LED_PIN   = 13; //Data output indication pin.

const int TIMEOUT          = 1000; //Loop timeout in ms.

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
    int value = analogRead(MOISTURE_PIN);

    return 1023 - value;
}

/**
 * Light on/off moisture LED by current value.
 */
void updateMoistureLed(int currentValue) {
    int edge = 400; //@todo read from memory.

    if (currentValue < edge) {
        digitalWrite(MOISTURE_LED_PIN, HIGH);
    } else {
        digitalWrite(MOISTURE_LED_PIN, LOW);
    }
}

/**
 * Return light value from sensor.
 */
int getLight() {
    int value = analogRead(PHOTOCELL_PIN);

    return value;
}

/**
 * Send collected sensor values via serial connection.
 */
void sendResults() {
    digitalWrite(OUPTUT_LED_PIN, HIGH);
    int moisture = getMoisture();
    int light = getLight();

    updateMoistureLed(moisture);
    Serial.print(moisture);
    Serial.print(";");
    Serial.print(light);
    Serial.println("");
    digitalWrite(OUPTUT_LED_PIN, LOW);
}
