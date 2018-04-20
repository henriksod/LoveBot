#define MSG_SIZE 8
#define AXIS_THRESH 32
#define AXIS_STICK(BYTE, THRESH) ((BYTE > (128 + THRESH)) || (BYTE < (128 - THRESH)))
#define AXIS_TRIGGER(BYTE, THRESH) (BYTE > THRESH)

byte incomingBytes[MSG_SIZE];

/* Tömmer listan som innehåller meddelandet från datorn */
void clearBytes() {
    for (int i = 0; i < 2; i++) {
      incomingBytes[i] = 0;
    }
    for (int i = 2; i < MSG_SIZE; i++) {
      incomingBytes[i] = 128;  
    }
}

/* Tömmer seriella bufferten */
void clearBuffer() {
    while (Serial.available() > 0) {
      char t = Serial.read();  
    }
}

/* Anropas för att invänta nästa meddelande från datorn */
void waitForMsg() {
  while (Serial.available() < MSG_SIZE) {
    delay(10);
  }
}

/* Anropas för att läsa in meddelandet från datorn till */
void readData() {
  for (int i = 0; i < MSG_SIZE; i++) {
    incomingBytes[i] = Serial.read();  
  }
}

/* MUFFINS OCH REGNBÅGAR */
void sendAck(const char* msg) {
  Serial.write(msg);
  Serial.write("&");
}

/* Här sker anropningen av era egna funktioner utifrån
 * meddelandet från datorn.
 */
void processData() {
  int axisRot = 1;
  
  if (incomingBytes[0] & 1) {
      // A 
  } if (incomingBytes[0] & 2) {
      // B
  } if (incomingBytes[0] & 4) {
      // X
  } if (incomingBytes[0] & 8) {
      // Y
  } if (incomingBytes[0] & 16) {
      // R1
  } if (incomingBytes[0] & 32) {
      // R3
  } if (incomingBytes[0] & 64) {
      // L1    
  } if (incomingBytes[0] & 128) {
      // UNMAPPED
  } if (incomingBytes[1] & 1) {
      // DPAD UP
  } if (incomingBytes[1] & 2) {
      // DPAD DOWN
  } if (incomingBytes[1] & 4) {
      // DPAD LEFT
  } if (incomingBytes[1] & 8) {
      // DPAD RIGHT
  } if (incomingBytes[1] & 16) {
      // START
  } if (incomingBytes[1] & 32) {
      // SELECT
  } if (incomingBytes[1] & 64) {
      // L3
  } if (incomingBytes[1] & 128) {
      //Serial.println("UNMAPPED");
  }
  
  //Axis 1 (L2)
  if (AXIS_TRIGGER(incomingBytes[2], AXIS_THRESH)) {

  }
  
  //Axis 2 (R2)
  if (AXIS_TRIGGER(incomingBytes[3], AXIS_THRESH)) {

  }
  
  //Axis 3 (LY)
  if (AXIS_STICK(incomingBytes[4], AXIS_THRESH)) {

  }
  
  //Axis 4 (LX)
  if (AXIS_STICK(incomingBytes[5], AXIS_THRESH)) {
    
  }
  
  //Axis 5 (RY)
  if (AXIS_STICK(incomingBytes[6], AXIS_THRESH)) {

  }
  
  //Axis 6 (RX)
  if (AXIS_STICK(incomingBytes[7], AXIS_THRESH)) {
    
  }
}

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

}

void loop() {
        //Clear data from last loop
        clearBytes();

        waitForMsg();
        // Recieve data
        if (Serial.available() >= MSG_SIZE) {
            // read the incoming byte:
            readData();
            //replyData();
        }
        
        //Call corresponding functions
        processData();
        sendAck("Hello I am data");

        clearBuffer();
}
