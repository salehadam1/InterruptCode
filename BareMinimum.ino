const int ir = 20; //interrupt pin 
int coun;

// Variables will change:
int IRState;             // the current reading from the input pin
int lastIrState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;  // the debounce time; increase if the output flickers


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ir, INPUT);
  attachInterrupt(digitalPinToInterrupt(ir), count,RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  //print the count number in the serial
  Serial.println(coun);
  delay(1000);
}

void count()
{
  // read the state of the IR into a local variable:
  int reading = digitalRead(ir);

  / If the IR changed, due to noise or pressing:
  if (reading != lastIrState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the IR state has changed:
    if (reading != IRState) {
      IRState = reading;

      // only count one if the new IR state is HIGH
      if (IRState == HIGH) {
        coun = coun + 1;
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastIrState:
  lastIrState = reading; 
}
