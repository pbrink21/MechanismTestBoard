const int onoffledpin = 12;
const int killswitch = 13;

void setup() {
  Serial.begin(9600);
  pinMode(killswitch, INPUT);
  pinMode(onoffledpin, OUTPUT);
}

void loop() {
//kill switch code with led indicator
   if(digitalRead(killswitch)==HIGH){
   digitalWrite(onoffledpin, LOW);
   }else{
     out(2,3,A0,0,1023);
     digitalWrite(onoffledpin, HIGH);
   }
  delay(2);
}

void out(int outpin1, int outpin2, int inpin, int lowval, int upval){
  int sensorValue = analogRead(A0);
  int outputValue = map(sensorValue, lowval, upval, -255, 255);
  if(outputValue>0){
    //forwards
    analogWrite(outpin1, outputValue);
    analogWrite(outpin2, 0);
  }else if(outputValue<0){
    //bakcwards
    analogWrite(outpin1, 0);
    analogWrite(outpin2, outputValue);
  }else{
    //stopped
    digitalWrite(outpin1, LOW);
    digitalWrite(outpin2, LOW);
  }

  //prints everything for troubleshooting purposes
  Serial.print(inpin);
  Serial.print(sensorValue);
  Serial.println(outputValue);
  Serial.print("==========================");
}
