/******************Libraries to use******************/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
#include <SensorFusion.h>

SF sensorFusion;

float pitch, roll, yaw;
float deltaT;
/******************Sample Rate for IMU******************/

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55); //55 is sensor id set during calibration sequence



/********************Setup Program********************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  Serial.println("Orientation Sensor Test with Sensor Fusion Library");

  /*Initialize sensor*/
  if (!bno.begin())
  {
    Serial.print("Sensor not detected");
    while (1);
  }

  int eeAddress = 0; //Define as int as value to be incremented later on
  long bnoID;
  bool foundCalib = false;

  EEPROM.get(eeAddress, bnoID);

  adafruit_bno055_offsets_t calibrationData;
  sensor_t sensor;

  //Checking for sensor id at beginning of program
  bno.getSensor(&sensor);
  if (bnoID != sensor.sensor_id)
  {
    Serial.println("\nCalibration data doesn't exist, run calibration program to save offsets to EEPROM.");
    delay(500);
  }
  else
  {
    Serial.println("\nFound calibration for sensor");
    eeAddress += sizeof(long);
    EEPROM.get(eeAddress, calibrationData);

    Serial.println("\nRestoring calibration offsets");
    bno.setSensorOffsets(calibrationData);

    Serial.println("\nCompleted calibration");
    foundCalib = true;
  }

  bno.setExtCrystalUse(false);

  sensors_event_t event;
  bno.getEvent(&event);
  if (foundCalib) {
    Serial.println("Move sensor slightly to calibrate magnetometers");
    while (!bno.isFullyCalibrated())
    {
      bno.getEvent(&event);
      delay(BNO055_SAMPLERATE_DELAY_MS);
    }
  }
  else
  {
    Serial.println("Please Calibrate Sensor: ");
    while (!bno.isFullyCalibrated())
    {
      bno.getEvent(&event);

      Serial.print("X: ");
      Serial.print(event.orientation.x, 4);
      Serial.print("\tY: ");
      Serial.print(event.orientation.y, 4);
      Serial.print("\tZ: ");
      Serial.print(event.orientation.z, 4);

      /* Optional: Display calibration status */

      /* New line for the next sample */
      Serial.println("");

      /* Wait the specified delay before requesting new data */
      delay(BNO055_SAMPLERATE_DELAY_MS);
    }
  }

  Serial.println("\nFully calibrated!");
  Serial.println("--------------------------------");
  Serial.println("Calibration Results: ");
  adafruit_bno055_offsets_t newCalib;
  bno.getSensorOffsets(newCalib);

  Serial.println("\n\nStoring calibration data to EEPROM...");

  eeAddress = 0;
  bno.getSensor(&sensor);
  bnoID = sensor.sensor_id;
  EEPROM.put(eeAddress, bnoID);
  eeAddress += sizeof(long);
  EEPROM.put(eeAddress, newCalib);
  Serial.println("Data stored to EEPROM.");
  Serial.println("\n--------------------------------\n");
  delay(250);

}
