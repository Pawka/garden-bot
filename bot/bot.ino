#include <stdlib.h> 
#include <EEPROM.h>

const int MOISTURE_PIN     = A0; //Moisture sensor pin.
const int PHOTOCELL_PIN    = A1; //Light sensor pin.
const int TEMPERATURE_PIN  = A3; //Temperature sensor pin.

const int MOISTURE_LED_PIN = 12; //Light led when moisture is too low.
const int OUPTUT_LED_PIN   = 13; //Data output indication pin.

const int ADDR_MOISTURE = 0; //Moisture edge value address on EEPROM.
const int ADDR_TIMEOUT  = 1; //Timeout value address on EEPROM (in seconds).

const int READ_TIMEOUT  = 10;


void setup() {                
    pinMode(OUPTUT_LED_PIN, OUTPUT);
    pinMode(MOISTURE_LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    String content = "";
    char character;

    while (Serial.available()) {
        character = Serial.read();
        content.concat(character);
    }

    //If command was received.
    if (content.charAt(3) == ';') {
        String cmd = content.substring(0, 3);
        String value = content.substring(4);

        if (cmd == "NFO") {
            cmdInfo();
        } else if (cmd == "TIM") {
            cmdSetTimeout(value);
        } else if (cmd == "MOI") {
            cmdSetMoisture(value);
        }
    }
    delay(READ_TIMEOUT);
    sendResults();
    delay(getTimeout() - READ_TIMEOUT);
}

/**
 * Write up to 2^16 int values to EEPROM. Only half addresses could be used
 * because single value uses two bytes.
 */
void writeEEPROM(int address, int value) {
    int a = value / 256;
    int b = value % 256;

    EEPROM.write(address * 2, a);
    EEPROM.write(address * 2 + 1, b);
}

/**
 * Read 2 bytes integer value from EEPROM. Only half addresses could be used
 * because single value uses two bytes.
 */
int readEEPROM(int address) {
    int a = EEPROM.read(address * 2);
    int b = EEPROM.read(address * 2 + 1);

    return a * 256 + b;
}

/** CONFIG ********************************************************************/
/**
 * Return moisture edge value.
 */
int getMoistureEdge() {
    int val = readEEPROM(ADDR_MOISTURE);

    //Analog value is between 0 and 1023.
    if (val < 1 || val > 1023) {
        //Default value
        val = 400; 
        setMoistureEdge(val);
    }

    return val;
}

/**
 * Store moisture edge value to memory.
 */
void setMoistureEdge(int value) {
    writeEEPROM(ADDR_MOISTURE, value);
}

/**
 * Return results output timeout in miliseconds.
 */
long getTimeout() {
    long val = readEEPROM(ADDR_TIMEOUT); //Timeout is stored in seconds.

    //Available timeout range.
    if (val < 1 || val > 60) {
        //Default value
        val = 1;
        setTimeout(val);
    }

    //Convert to miliseconds.
    return val * 1000;
}

/**
 * Store timeout value to memory.
 */
void setTimeout(int value) {
    writeEEPROM(ADDR_TIMEOUT, value);
}


/** SENSORS *******************************************************************/
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
    int edge = getMoistureEdge();

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
 * Return temperature value in celcius.
 */
float getTemperature() {
    float temperature = (5.0 * analogRead(TEMPERATURE_PIN) * 100.0) / 1024;

    return temperature;
}


/** INTERFACE *****************************************************************/
/**
 * Send collected sensor values via serial connection.
 */
void sendResults() {
    digitalWrite(OUPTUT_LED_PIN, HIGH);
    int moisture = getMoisture();
    int light = getLight();
    float temperature = getTemperature();

    updateMoistureLed(moisture);
    Serial.print("DAT;"); //Prefix for output data.
    Serial.print(moisture);
    Serial.print(";");
    Serial.print(light);
    Serial.print(";");
    Serial.print(temperature);
    Serial.println("");
    digitalWrite(OUPTUT_LED_PIN, LOW);
}

/**
 * Send current status info to serial.
 */
void cmdInfo() {
    Serial.println("Config");
    Serial.println("--------------------");
    Serial.print("Moisture edge: ");
    Serial.println(getMoistureEdge());
    Serial.print("Timeout:       ");
    Serial.println(getTimeout() / 1000);

    Serial.println("\nStats");
    Serial.println("--------------------");
    Serial.print("Moisture:    ");
    Serial.println(getMoisture());
    Serial.print("Light:       ");
    Serial.println(getLight());
    Serial.print("Temperature: ");
    Serial.println(getTemperature());
}

/**
 * Command to set timeout.
 */
void cmdSetTimeout(String value) {
    setTimeout(value.toInt());
    Serial.print("Timeout set: ");
    Serial.println(getTimeout() / 1000);
}

/**
 * Command to set moisture edge level.
 */
void cmdSetMoisture(String value) {
    setMoistureEdge(value.toInt());
    Serial.print("Moisture set: ");
    Serial.println(getMoistureEdge());
}
