const int onoffledpin = 12;
const int killswitch = 13;
const int syncSwitch = 11;

void setup() {
  Serial.begin(9600);
  pinMode(killswitch, INPUT);
  pinMode(onoffledpin, OUTPUT);
  pinMode(syncSwitch, INPUT);
}

void loop() {
//kill switch code with led indicator
   if(digitalRead(killswitch)==HIGH){
    //doesn't run other code when board is switched off
   digitalWrite(onoffledpin, LOW);
   }else{
    //PUT ALL RUNNING CODE HERE so the kill switch does what its supposed to 
    if(digitalRead(syncSwitch)==HIGH){
     //makes them both spin at the same speed
     out(2,3,A0,0,1023);
     out(4,5,A0,0,1023);
    }else{
      //makes them both spin at the rate their potentiometers are spinning
      out(2,3,A0,0,1023);
      out(4,5,A1,0,1023);
    }
     digitalWrite(onoffledpin, HIGH);
   }
  delay(2);
}

/*the function "out" is the function that does all the things
    to output the values from the POT to the MC. it accepts 5 
    inputs, in this order: 
    -positive output: white wire in PWM standard, when signal 
      goes through this one it will move forward
    -negative output: black wire in PWM standard, when signal
      goes through this one it will move backward
    -analog input: the port the potentiometer will send values
      into
    -lower value: this is the lowest value your potentiometer
      will output, what you want the POT to be outputting when
      the MC is going backwards as fast as possible
    -upper value: opposite of lower value, what you want the POT
      to be outputting when the MC is going forwards AFAP 
*/

void out(int outpin1, int outpin2, int inpin, int lowval, int upval){
  int sensorValue = analogRead(A0);
  /*lowval and upval are the ranges of potentiometers because
  //some are sketchy and dont output normal values
  //maps possible potentiometer values to values accepted
  //by the PWM motor controllers 
  */
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
