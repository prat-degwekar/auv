/** PID Gain & Limit Settings **/

// Roll

float pid_p_gain_roll = 0.00;
float pid_i_gain_roll = 0.00;
float pid_d_gain_roll = 0.00;
int pid_max_roll = 100;

// Pitch

float pid_p_gain_pitch = 2.00;
float pid_i_gain_pitch = 0.00;
float pid_d_gain_pitch = 0.01;
int pid_max_pitch = 100;

// Yaw

float pid_p_gain_yaw = 2.00;
float pid_i_gain_yaw = 0.00;
float pid_d_gain_yaw = 0.01;
int pid_max_yaw = 100;

// Depth
float pid_p_gain_depth = 3.00;
float pid_i_gain_depth = 0.00;
float pid_d_gain_depth = 0.01;
int pid_max_depth = 180;

// PID Variables
float pid_i_mem_roll = 0.0;
float pid_last_error_roll = 0.0;
float pid_output_roll;

float pid_i_mem_pitch = 0.0;
float pid_last_error_pitch = 0.0;
float pid_output_pitch;

float pid_i_mem_yaw = 0.0;
float pid_last_error_yaw = 0.0;
float pid_output_yaw;

float pid_i_mem_depth = 0.0;
float pid_last_error_depth = 0.0;
float pid_output_depth;

float pid_error_temp = 0; // Error calculation - recycled over and over for computing YPR each

String inputString = "";     // a String to hold incoming data
bool stringComplete = false; // whether the string is complete
// void loop() {
//   // print the string when a newline arrives:
//   if (stringComplete) {
//     Serial.println(inputString);
//     // clear the string:
//     inputString = "";
//     stringComplete = false;
//   }
// }
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

void (*resetFunc)(void) = 0;

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;

    if (inChar == '\n') {
      stringComplete = true;
      return;
    }
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
  }
}
void pidStatus() {
  Serial.println(F("### Current Status"));
  Serial.println(F("Axis\tP\tI\tD"));
  Serial.print(F("Yaw:\t"));
  Serial.print(pid_p_gain_yaw);
  Serial.print(F("\t"));
  Serial.print(pid_i_gain_yaw);
  Serial.print(F("\t"));
  Serial.println(pid_d_gain_yaw);
  Serial.print(F("Pitch:\t"));
  Serial.print(pid_p_gain_pitch);
  Serial.print(F("\t"));
  Serial.print(pid_i_gain_pitch);
  Serial.print(F("\t"));
  Serial.println(pid_d_gain_pitch);
  Serial.print(F("Roll:\t"));
  Serial.print(pid_p_gain_roll);
  Serial.print(F("\t"));
  Serial.print(pid_i_gain_roll);
  Serial.print(F("\t"));
  Serial.println(pid_d_gain_roll);
  Serial.print(F("Depth:\t"));
  Serial.print(pid_p_gain_depth);
  Serial.print(F("\t"));
  Serial.print(pid_i_gain_depth);
  Serial.print(F("\t"));
  Serial.println(pid_d_gain_depth);
  Serial.print(F("Stable depth: "));
  Serial.println(stable_depth);
}

void pidtune() {
  Serial.println(F("# in pidtune\n"));
  char *is = inputString.c_str();
  char *cmd, *par1, *par2;
  cmd = strtok(is, " ");
  par1 = strtok(NULL, " ");
  par2 = strtok(NULL, "\r");
  if (strcmp(cmd, "y") == 0) {
    Serial.println(F("Yaw command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_yaw = atof(par2);
    } else if (strcmp(par1, "i") == 0) {
      pid_i_gain_yaw = atof(par2);
    } else if (strcmp(par1, "d") == 0) {
      pid_d_gain_yaw = atof(par2);
    }
  } else if (strcmp(cmd, "p") == 0) {
    Serial.println(F("Pitch command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_pitch = atof(par2);
    } else if (strcmp(par1, "i") == 0) {
      pid_i_gain_pitch = atof(par2);
    } else if (strcmp(par1, "d") == 0) {
      pid_d_gain_pitch = atof(par2);
    }
  }else if (strcmp(cmd, "r") == 0) {
    Serial.println(F("Roll command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_roll = atof(par2);
    } else if (strcmp(par1, "i") == 0) {
      pid_i_gain_roll = atof(par2);
    } else if (strcmp(par1, "d") == 0) {
      pid_d_gain_roll = atof(par2);
    }
  } else if (strcmp(cmd, "d") == 0) {
    Serial.println(F("Depth command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_depth = atof(par2);
    } else if (strcmp(par1, "i") == 0) {
      pid_i_gain_depth = atof(par2);
    } else if (strcmp(par1, "d") == 0) {
      pid_d_gain_depth = atof(par2);
    }
  } else if (strcmp(cmd, "sd") == 0) {
    Serial.println(F("Stable depth"));
    if (strcmp(par1, "s") == 0) {
      stable_depth = atof(par2);
    }
  } else if (strcmp(cmd, "rst") == 0) {
    resetFunc();
  } else {
    Serial.println(F("Invalid command to pidtune, returning"));
    // return;
  }
  pidStatus();
}
