weather station
===============

Detect temperature, humidity, heat index, atmospheric pressure and altitude unsing a DHT11 sensor and a BMP180 sensor on an arduino uno

---

**DHT**
  * digital humidity and temperature sensor
  * This bad boy detects the humidity and temperature.
  * humidity between 20% and 90%.
  * temperature between 0°C and 50°C.
  * temperature resolution 1°C.
  * between 3 to 5.5 V.
  * if the connexion cable is < 20 m, add a 5K pull-up resistor.
  * sampling period = 1 second.
  * ...see datasheet for pinning

**BMP**
  * barometric pressure sensor
  * The BMP180 sensor is able to detect barometric pressure, altitude and temperature.
  * pressure range 300 to 1100 hPa.
  * pressure resolution 0.01 hPa.
  * between 1.8 to 3.6 V. _(do not connect to the 5V on the board otherwise it will fry the sensor)_
  * temperature resolution 0.5°C. _(more precise than the DHT so use this one for measuring temperature)_
  * SDA = serial data bus (I2C)
  * SCL = serial clock input bus (I2C)
  * ...see datasheet for pinning
