#include <Wire.h>
#include <Adafruit_BME680.h>
#include <PMS.h>
#include <WiFi.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

PMS pms(Serial2);
PMS::DATA data;

Adafruit_BME680 bme; // I2C

const char* WIFI_SSID = "Darshil";
const char* WIFI_PASSWORD = "1234567890";


#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "O1_V2GneSPSShWlBRoZEoY1nUmY8e-BeoAfIMr8XLlUFszDE6gxV1MIGmToiA3c9kN78Xq4QeRoFJ1BWl9H6sQ=="
#define INFLUXDB_ORG "55e78fd6907352a4"
#define INFLUXDB_BUCKET "AIR_Q018"
#define INFLUXDB_MEASUREMENT "atmosphere_data"

// Set timezone. You can refer here: http://bit.ly/3YKh66x
#define TZ_INFO "IST-5:30"

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
Point sensor(INFLUXDB_MEASUREMENT);

void saveConfigCallback() {
  Serial.println("Saving WiFi configuration");
  // Add code here to save custom parameters, if needed
}

void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to the provided WiFi credentials.");

    // If failed to connect, start transmitting its own WiFi
    WiFiManager wifiManager;
    wifiManager.setConfigPortalTimeout(300); // Set Config Portal timeout to 5 minutes (300 seconds)
    wifiManager.setSaveParamsCallback(saveConfigCallback);

    Serial.println("Starting Config Portal for setting new WiFi credentials.");

    if (!wifiManager.startConfigPortal("AutoConnectAP", "AutoConnectPassword")) {
      Serial.println("Failed to connect or configure new WiFi credentials. Rebooting...");
      delay(3000);
      ESP.restart();
    }

    Serial.println("Connected to new WiFi. Updated credentials:");
    Serial.println("SSID: " + WiFi.SSID());
    Serial.println("Password: " + WiFi.psk());
  }

  Serial.println("Connected to WiFi");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  connectToWifi();

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

#ifndef ESP8266
  while (!Serial);
#endif

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
}

void loop() {
  if (pms.read(data)) {
    bme.performReading(); // Perform BME680 sensor reading

    float temperature = bme.temperature;
    float humidity = bme.humidity;
    float pressure = bme.pressure / 100.0;
    float gas = bme.gas_resistance / 1000.0;
    float altitudeBme = bme.readAltitude(SEALEVELPRESSURE_HPA);
    float val1 = data.PM_AE_UG_1_0;
    float val2 = data.PM_AE_UG_2_5;
    float val3 = data.PM_AE_UG_10_0;
    
    gas = round(gas * 100) / 100;

    // Clear fields for reusing the point. Tags will remain untouched
    sensor.clearFields();

    // Store measured values into point
    sensor.addField("ip", WiFi.localIP());
    sensor.addField("temperature", temperature);
    sensor.addField("humidity", humidity);
    sensor.addField("pressure", pressure);
    sensor.addField("gas", gas);
    sensor.addField("altitude", altitudeBme);

    // Store calculated values into point
    sensor.addField("pm1", val1);
    sensor.addField("pm2.5", val2);
    sensor.addField("pm10", val3);

    // Print what we are writing
    Serial.print("Writing: ");
    Serial.println(sensor.toLineProtocol());

    // Check WiFi connection and reconnect if needed
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost. Reconnecting...");
      connectToWifi();
    }

    // Write point to InfluxDB
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB Cloud write failed: ");
      Serial.println(client.getLastErrorMessage());
    }

    Serial.println("Wait 30s");
    delay(30000); // Delay for 30 seconds
  }
}
