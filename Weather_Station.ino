#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 2
#define DHTTYPE DHT11

float temperature = 0;
float humidity = 0;
float pressure = 0;
float heatIndex = 0;
float altitude = 0;
float seaLevelPressure = 0;
int units = 'a';
bool DHT_OK = true;
bool BMP_OK = true;

const float m_to_ft = 3.28084;

Adafruit_BMP085 bmp;
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(9600);
  if(!bmp.begin()) {
    Serial.println("\nCould not find a valid BMP180 sensor. Check the wiring! Continuing without BMP180...");
    BMP_OK = false;
  }
  
  dht.begin();
  if(isnan(dht.readHumidity()) || isnan(dht.readTemperature())) {
    Serial.println("Could not find a valid DHT11 sensor. Check the wiring");
    DHT_OK = false;
  }
  
  if(!BMP_OK && !DHT_OK) {
    Serial.println("Could not find either BMP180 or DHT11 sensor! Check wiring... reset to try again.");
    while(1) {}
  }
  
  Serial.print("DHT11 & BMP180\nm: metric (*C, m)\ni: imperial (*F, ft)\nPlease select desired units by either sending a m or a i\n");
  //Attendre que l'utilisateur specifie les unites voulues
  while(1) {
    while(Serial.available() > 0) {
      units = Serial.read();
    }
    if((units == 'm') or (units == 'i')) {
      break;
    }
  }
  
  switch((int)units) {
    case'm':
      Serial.print("Metric units selected!\n");
      break;
    case'i':
      Serial.print("Imperial units selected!\n");
      break;
    default:
      Serial.print("Wrong character! Defaulting to metric units...\n");
      break;
  }
  
  if(BMP_OK) {
    Serial.print("Please enter sea level pressure in kPa. (1 kPa = 1000 Pa = 10 hPa = 10 mBar)\n Note: Must be between 90 and 110.\n");
    while(1) {
      while(Serial.available() > 0) {
        seaLevelPressure = Serial.parseFloat();
      }
      if((seaLevelPressure >= 90) && (seaLevelPressure <= 110)) {
        Serial.print("Sea level pressure entered is : ");
        Serial.print(seaLevelPressure, 3);
        Serial.print(" kPa\n");
        break;
      }
    }
  }
} //End of void setup()

void loop() {
  delay(2000); //ajouter un delai de 2 secondes pour permettre un changement des donnees du sensor
  printWeatherData();
} // End of void loop()

void printWeatherData() {
  if(DHT_OK) {
    humidity = dht.readHumidity();
  }
  if(BMP_OK) {
    temperature = bmp.readTemperature();
    pressure = bmp.readPressure();
    altitude = bmp.readAltitude(seaLevelPressure * 1000);
  }
  else if(DHT_OK) {
    temperature = dht.readTemperature();
  }
  
  if(units == 'i') {
    temperature = dht.convertCtoF(temperature);
    heatIndex = dht.computeHeatIndex(temperature, humidity, true);
  }
  else {
    heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  }
  
  //Affichage des donnees meteo
  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.print((units == 'm') ? " *C":" *F");
  
  Serial.print("\tHumidity : ");
  Serial.print(humidity, 1);
  Serial.print(" %\t");
  
  Serial.print("Heat index : ");
  Serial.print(heatIndex, 1);
  Serial.print((units == 'm') ? " *C":" *F");
  
  Serial.print("\tPressure : ");
  Serial.print(pressure / 1000, 3);
  Serial.print(" kPa");
  Serial.print("\t");
  
  Serial.print("Altitude : ");
  Serial.print((units == 'm') ? altitude : (altitude * m_to_ft), 1);
  Serial.println((units == 'm') ? " m":" ft");
}
