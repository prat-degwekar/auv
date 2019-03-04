

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
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void pidtune() {
  // COVFEFE
  Serial.println(F("# in pidtune"));
  char *is = inputString.c_str();
  char *cmd;
  p = strtok(is, " ");
  if (strcmp(p, "y") == 0) {
     Serial.println(F("Yaw command"));
  }
}
