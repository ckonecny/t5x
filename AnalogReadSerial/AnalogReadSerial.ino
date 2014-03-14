/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int analog0 = analogRead(A0);
  int analog1 = analogRead(A1);
  int analog2 = analogRead(A2);
  int analog3 = analogRead(A3);
  int analog4 = analogRead(A4);
  int analog5 = analogRead(A5);
  int analog6 = analogRead(A6);
  int analog7 = analogRead(A7);
  
  
  // print out the value you read:
  Serial.println("A0:"+String(analog0)+" A1:"+String(analog1)+" A2:"+String(analog2)+" A3:"+String(analog3)+" A4:"+String(analog4)+" A5:"+String(analog5)+" A6:"+String(analog6)+" A7:"+String(analog7));
  delay(300);        // delay in between reads for stability
}
