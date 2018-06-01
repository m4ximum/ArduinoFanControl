/**
 * Ventilation control with Arduino UNO, two DHT22 sensors, 5V/240V solid state relay and 230V Fan 
 * Fan runs when humidity from the indoor sensor is higher than the outer sensor
 * 
 * 
 * @author m4ximum
 * @license MIT
 */

#include <DHT_U.h>
#include <time.h>

#define DHTPININ 2      // Indoor DHT
#define DHTPINOUT 4     // Outdoor DHT
#define RELAYPIN 7      // Relay trigger Pin
#define HUMIDITIYLED 12
#define DUSTPOLLUTIONLED 8
#define DHTTYPE DHT22
DHT dhtIn(DHTPININ, DHTTYPE); // Init DHT sensor
DHT dhtOut(DHTPINOUT, DHTTYPE); // Init DHT sensor


//Variables
float humIn;  //humidity Indoor sensor
float tempIn; //temperature Indoor value
float humOut; //humidity Outdoor sensor
float tempOut;//temperature Outdoor value
bool fanRunning = false;
bool debug = true;


void setup()
{
  Serial.begin(9600);
  dhtIn.begin();
  pinMode(RELAYPIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(HUMIDITIYLED, OUTPUT);
  pinMode(DUSTPOLLUTIONLED, OUTPUT);
}

void loop()
{
    delay(2000);
    humIn = dhtIn.readHumidity();
    tempIn = dhtIn.readTemperature();
    humOut = dhtOut.readHumidity();
    tempOut = dhtOut.readTemperature();
    
    if(debug){
      serialOutput(humIn, humOut, tempIn, tempOut);
    }

    if(humIn > humOut){
      startFan();
      digitalWrite(HUMIDITIYLED, HIGH);
      delay(10000); //10sec delay
    }/*else if(fineDustPollution()){
      startFan();
      digitalWrite(DUSTPOLLUTIONLED, HIGH);
    }*/else{
      stopFan();
      digitalWrite(HUMIDITIYLED, LOW);
      digitalWrite(DUSTPOLLUTIONLED, LOW);
    }
    delay(2000);
}

bool fineDustPollution(){
  bool runFan = false;

  return runFan; 
}

void startFan(){
  if(!fanRunning){
    Serial.println("Starting fan");
    digitalWrite(RELAYPIN, HIGH);
    fanRunning = true;  
  }
}

void stopFan(){
  if(fanRunning){
    Serial.println("Stopping Fan");
    digitalWrite(RELAYPIN, LOW);
    fanRunning = false;
  }
}

void serialOutput(float humIn, float humOut, float tempIn, float tempOut){
  Serial.print("Sensor IN -> ");
  Serial.print("Humidity: ");
  Serial.print(humIn);
  Serial.print(" %, Temp: ");
  Serial.print(tempIn);
  Serial.println(" °C");
  Serial.print("Sensor OUT -> ");
  Serial.print("Humidity: ");
  Serial.print(humOut);
  Serial.print(" %, Temp: ");
  Serial.print(tempOut);
  Serial.println(" °C");
}

   

