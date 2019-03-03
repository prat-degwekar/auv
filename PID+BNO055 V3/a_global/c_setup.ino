Adafruit_BNO055 bno = Adafruit_BNO055(55); //55 is sensor id initalized during calibration

void setup()
{
 
Serial.begin(9600);
  /**************************************Sensor Initialization Sequence**************************************/

  /****************************** BNO055 Sensor ******************************/

  Serial.println("Sensor initialization");

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

  /******************************************* MS5837 Sensor ********************************************/

  depthSensor.setModel(MS5837::MS5837_02BA);
  depthSensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

  
  /************************************** Motor Pin Initialization **************************************/
   left.attach(4);
   right.attach(5);
   front.attach(6);
   back.attach(7);
 



  /************************************ Stable Position Calculation ************************************/
  euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  for(int i=1; i<=100;i++)
  {
    bno055_timer = micros();
    euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    depthSensor.read();
    stable_roll = stable_roll + euler.x();
    stable_pitch = stable_pitch + euler.y();
    stable_yaw = stable_yaw + euler.z();
    stable_depth = stable_depth + (depthSensor.depth()*1000);
    while(micros() - bno055_timer <= BNO055_SAMPLERATE_DELAY_MS);    
  }
  /*****Starting postition stabilized******/
  stable_roll = stable_roll/100;
  stable_pitch = stable_pitch/100;
  stable_yaw = stable_yaw/100;
  stable_depth = stable_depth/100;

  /********************************** Thruster Initialization Sequence **********************************/
  motor_arm(0);
  Serial.println("armed");
  delay(5000);
}
