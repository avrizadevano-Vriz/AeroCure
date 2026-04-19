#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>


// ---------------- DHT11 ----------------
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(9600);
  dht.begin();


  lcd.init();
  lcd.backlight();


  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}


void loop() {


  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();


  // check if sensor failed
  if (isnan(humidity) || isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error   ");
    lcd.setCursor(0, 1);
    lcd.print("Check DHT11    ");


    Serial.println("DHT11 failed read");
    delay(2000);
    return;
  }


  // -------- LCD DISPLAY --------
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C ");


  lcd.print("H:");
  lcd.print(humidity);


  lcd.setCursor(0, 1);


  if (humidity > 70) {
    lcd.print("MOLD RISK HIGH ");
  }
  else if (humidity > 50) {
    lcd.print("MOLD RISK MED  ");
  }
  else {
    lcd.print("MOLD RISK LOW  ");
  }


  // -------- SERIAL DEBUG --------
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" Humidity: ");
  Serial.println(humidity);


  delay(2000);
}
—-------------------------------------------------------------------------final code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>


// ---------------- DHT11 ----------------
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);


// ---------------- THERMISTOR ----------------
const int thermistorPin = A0;
const float SERIES_RESISTOR = 10000.0;
const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMP = 25.0;
const float B_COEFFICIENT = 3950.0;


// ---------------- LED PINS ----------------
const int greenLED = 8;
const int yellowLED = 9;
const int redLED = 10;


void setup() {
  Serial.begin(9600);


  dht.begin();


  lcd.init();
  lcd.backlight();


  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);


  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}


void loop() {


  // -------- DHT11 --------
  float humidity = dht.readHumidity();
  float dhtTemp = dht.readTemperature();


  // -------- THERMISTOR --------
  int analogValue = analogRead(thermistorPin);


  float resistance = SERIES_RESISTOR / (1023.0 / analogValue - 1.0);


  float temp = resistance / NOMINAL_RESISTANCE;
  temp = log(temp);
  temp /= B_COEFFICIENT;
  temp += 1.0 / (NOMINAL_TEMP + 273.15);
  temp = 1.0 / temp;
  temp -= 273.15;


  // -------- ERROR CHECK --------
  if (isnan(humidity) || isnan(dhtTemp)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT11 ERROR");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring");


    Serial.println("DHT11 FAILED READ");


    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);


    delay(2000);
    return;
  }


  // -------- MOLD LOGIC --------
  String status;


  if (humidity > 70) {
    status = "HIGH RISK";
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }
  else if (humidity > 50 && (temp >= 21 && temp <= 30)) {
    status = "MODERATE";
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  else {
    status = "LOW RISK";
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  }


  // -------- LCD DISPLAY --------
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C ");


  lcd.print("H:");
  lcd.print(humidity, 0);


  lcd.setCursor(0, 1);
  lcd.print(status);


  // -------- SERIAL DEBUG --------
  Serial.print("Thermistor Temp: ");
  Serial.print(dhtTemp);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Wall Temperature: ");
  Serial.print(temp);
  Serial.print(" | Status: ");
  Serial.println(status);


  delay(2000);
}
