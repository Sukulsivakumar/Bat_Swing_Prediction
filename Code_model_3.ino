float distance1;
float distance2;
float distance3;
const int sensorPin[] = {A0,A1,A2};
float distance[3];
const int AVERAGE_OF =50;
const float MCU_VOLTAGE = 5.0;
const int blue = 3;
const int green = 5;
const int red = 7;

unsigned long previousMillis = 0;  // Store the last time the counter was updated
unsigned long interval = 1000;     // Interval in milliseconds (1 second)


bool label = false;

void setup() {
   Serial.begin(9600);
}

void loop() {

  int seconds = 0;  // Initialize the seconds counter
  setblue(255);
  // POINT - 1
  readDistance(0);                             //read sensor 1
  distance1 = distance[0];
    //distance1 = random(1,20);
  Serial.print("D1 : ");
  Serial.println(distance1);

  if(distance1 >= 2 && distance1 <= 15){    // condition - 1
    setblue(255);
    while(true){                          // LOOP - 1
      // POINT - 2
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        seconds++;
        Serial.print("Seconds: ");
        Serial.println(seconds);  
        }
      readDistance(1);                    //read sensor 2;
      distance2 = distance[1];
        //distance2 = random(16,20);
      Serial.print("D2 : ");
      Serial.println(distance2);
      
      if ((distance2 >= 2 && distance2 <= 15)&& (seconds<=5)){  // condition - 2
        while(true){                     // LOOP - 2
          // POINT - 3
          unsigned long currentMillis = millis();
          if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;  
            seconds++;
            Serial.print("Seconds: ");
            Serial.println(seconds);  
            }
          readDistance(2);                //read sensor 3
          distance3 = distance[2];
            //distance3 = random(1,20);
          Serial.print("D3 : ");
          Serial.println(distance3);
  
          if(( distance3 >= 2 && distance3 <= 15) && (seconds<=5) ){ // condition - 3
            Serial.println("Pass");
            setColor(255,0);
            setColor(0, 255);
            delay(10000);
            setColor(0,0);
            setColor(0,0); 
            label = true;
            seconds=0;
          }
          else if(seconds >5){
              Serial.println("Fail");
              setColor(0,255);
              setColor(255, 0);
              delay(10000);
              setColor(0,0);
              setColor(0,0); 
              label = true;
            }

          if(label){break;}    // Break Loop - 2
          delay(100);
        }
        }
        else if(seconds >5){
          Serial.println("Fail");
            setColor(0,255);
            setColor(255,0);
            delay(10000);
            setColor(0,0);
            setColor(0,0); 
            label = true;
          }
        
      if(label){break;}    // Break Loop - 1
      delay(100);
    }
  }
  delay(100);
}

void readDistance(int sensor){
  float voltage_temp_average=0;
  for(int i=0; i < AVERAGE_OF; i++){
      int sensorValue = analogRead(sensorPin[sensor] );
      delay(1);      
      voltage_temp_average +=sensorValue * (MCU_VOLTAGE / 1023.0);
    }
  voltage_temp_average /= AVERAGE_OF;
  distance[sensor] = 33.9 + -69.5*(voltage_temp_average) + 62.3*pow(voltage_temp_average,2) + -25.4*pow(voltage_temp_average,3) + 3.83*pow(voltage_temp_average,4);
}
void setblue(int blueValue){
  analogWrite(blue, blueValue);
}
void setColor(int redValue, int greenValue) {
  analogWrite(red, redValue);
  analogWrite(green, greenValue);
}
