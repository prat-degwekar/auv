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
  Serial.println(F("\n"));
  Serial.println(F("Axis\tP\tI\tD"));
  Serial.println(F("\n"));
  Serial.println(F("Yaw:\t"));
  Serial.println(pid_p_gain_yaw);
  Serial.println(F("\t"));
  Serial.println(pid_i_gain_yaw);
  Serial.println(F("\t"));
  Serial.println(pid_d_gain_yaw);
  Serial.println(F("\n"));
  Serial.println(F("Pitch:\t"));
  Serial.println(pid_p_gain_pitch);
  Serial.println(F("\t"));
  Serial.println(pid_i_gain_pitch);
  Serial.println(F("\t"));
  Serial.println(pid_d_gain_pitch);
  Serial.println(F("\n"));
  Serial.println(F("Roll:\t"));
  Serial.println(pid_p_gain_roll);
  Serial.println(F("\t"));
  Serial.println(pid_i_gain_roll);
  Serial.println(F("\t"));
  Serial.println(pid_d_gain_roll);
  Serial.println(F("\n"));
  Serial.println(F("Depth:\t"));
  Serial.println(pid_p_gain_depth);
  Serial.println(F("\t"));
  Serial.println(pid_i_gain_depth);
  Serial.println(F("\t"));
  Serial.println(pid_d_gain_depth);
  Serial.println(F("\n"));
}

void pidtune() {
  Serial.println(F("# in pidtune\n"));
  char *is = inputString.c_str();
  char *cmd, *par1, *par2;
  cmd = strtok(is, " ");
  par1 = strtok(NULL, " ");
  par2 = strtok(NULL, "\n");
  if (strcmp(cmd, "y") == 0) {
    Serial.println(F("Yaw command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_yaw = atof(par2);
    } else if (strcmp(par1, "i")) {
      pid_i_gain_yaw = atof(par2);
    } else if (strcmp(par1, "d")) {
      pid_d_gain_yaw = atof(par2);
    }
  } else if (strcmp(cmd, "p") == 0) {
    Serial.println(F("Pitch command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_pitch = atof(par2);
    } else if (strcmp(par1, "i")) {
      pid_i_gain_pitch = atof(par2);
    } else if (strcmp(par1, "d")) {
      pid_d_gain_pitch = atof(par2);
    }
  } else if (strcmp(cmd, "r") == 0) {
    Serial.println(F("Roll command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_roll = atof(par2);
    } else if (strcmp(par1, "i")) {
      pid_i_gain_roll = atof(par2);
    } else if (strcmp(par1, "d")) {
      pid_d_gain_roll = atof(par2);
    }
  } else if (strcmp(cmd, "d") == 0) {
    Serial.println(F("Depth command"));
    if (strcmp(par1, "p") == 0) {
      pid_p_gain_depth = atof(par2);
    } else if (strcmp(par1, "i")) {
      pid_i_gain_depth = atof(par2);
    } else if (strcmp(par1, "d")) {
      pid_d_gain_depth = atof(par2);
    }
  } else {
    Serial.println(F("Invalid command to pidtune, returning"));
    // return;
  }
  pidStatus();
}
