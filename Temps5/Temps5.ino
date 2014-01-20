#include <OneWire.h>
#include <DallasTemperature.h>

// One wire bus connected to pin 3
#define ONE_WIRE_BUS 3

// Use 9 bit temperature
#define TEMPERATURE_PRECISION 9

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Device addresses (see numbers on cables)
uint8_t sensor[5][8] = {
  { 0x28, 0xB1, 0xD1, 0x23, 0x05, 0x00, 0x00, 0x70 },
  { 0x28, 0x20, 0x07, 0x24, 0x05, 0x00, 0x00, 0xB2 },
  { 0x28, 0xF6, 0x25, 0xEF, 0x04, 0x00, 0x00, 0xB9 },
  { 0x28, 0x91, 0x43, 0x23, 0x05, 0x00, 0x00, 0xF2 },
  { 0x28, 0x91, 0x3F, 0x23, 0x05, 0x00, 0x00, 0xBE }
};

void setup(void) {
  // start serial port
  Serial.begin(115200);

  // Start up the library
  sensors.begin();

  // Set precision to 9 bits
  for (int i=0; i<5; i++) {
    sensors.setResolution(sensor[i], TEMPERATURE_PRECISION);
  }

  // On-board LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

}

void loop(void) { 
  float tempC;

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures();
  delay(10);

  // Turn on LED
  digitalWrite(13, HIGH);

  // Print timestamp in seconds
  Serial.print(millis()/1000L);
  Serial.print(" ");
  
  // Print temperatures
  for (int i=0; i<5; i++) {
    tempC = sensors.getTempC(sensor[i]);
    Serial.print(tempC);
    Serial.print(" ");
  }
  Serial.println("");

  // Turn off LED
  digitalWrite(13, LOW);

  delay(1000);
}

