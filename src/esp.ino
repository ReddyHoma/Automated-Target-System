//Including required libraries for operation
#include <WiFi.h>
#include <PubSubClient.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
 
unsigned long duration = 0;
unsigned long startMilliSeconds = 0;
String expectedUserCredentials = "";
String expectedStartTime = "";

//Initializing WiFi router credentials for connection
const char* ssid = "username";
const char* pass = "password";

//Initializing broker
const char* mqtt_broker = "test.moquitto.org";

const int relayPin = 13;

//Creating a Network Time Protocol Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org", 19800, 60000);

//Creating WiFi Client
WiFiClient esp32_pulley;
PubSubClient client(esp32_pulley);

//Defining functions used 
void connectToWifi();
void reconnectMQTT();
void connecttoMQTT();
void startRelay(unsigned long duration);
void stopRelay();
void publishStatus(const char* status);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
bool isTimeToStart(String startTime);

void setup() 
{
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  connectToWifi();
  
  timeClient.begin();
  
  //MQTT Client setup
  client.setServer(mqtt_broker, 1883);
  client.setCallback(mqtt_callback);

  connecttoMQTT();
}

void loop() 
{
  if(!client.connected()) //Incase of error in connection with broker, reconnects to MQTT
  {
    reconnectMQTT();
  }
  client.loop();
  timeClient.update();
  if (millis()-startMilliSeconds >= duration && duration >0)
  {
    stopRelay();
  }//Checks if usage period has ended
}

void connectToWifi() //Connecting to WiFi using defined credentials
{
  WiFi.begin(ssid,pass);
  while (WiFi.status()!= WL_CONNECTED)
  {
    delay(5000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void connecttoMQTT() //Establishing connection with MQTT Broker
{
  String clientID = "ESP32Pulley - ";
  clientID += WiFi.macAddress(); //Unique client ID for each pulley using MAC Address

  while(!client.connected())
  {
    Serial.print("Attempting MQTT Connection");
    if (client.connect(clientID.c_str()))
    {
      Serial.println("Connected to MQTT Broker");
      client.subscribe("pulley/control/#");
      Serial.println("Subscribed to topic");
    }
    else
    {
      Serial.print("Connection Failed with rc = ");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void reconnectMQTT() //Attempting to reconnect to MQTT Broker in case of any issue
{
  String clientID = "ESP32Pulley - ";
  clientID += WiFi.macAddress();

  while(!client.connected())
  {
    Serial.print("Attempting MQTT Connection");
    if (client.connect(clientID.c_str()))
    {
      Serial.println("Connected");
      client.subscribe("pulley/control/#");
    }
    else
    {
      Serial.print("Failed Connection with rc = ");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void startRelay(unsigned long durationMilliSeconds) //Function starting relay operation
{
  duration = durationMilliSeconds;
  startMilliSeconds = millis();
  digitalWrite(relayPin, HIGH);
  publishStatus("Pulley Started");
}

void stopRelay() //Function to stop relay operation
{
  digitalWrite(relayPin, LOW);
  publishStatus("Pulley Stopped");
  duration = 0;
}

void publishStatus(const char* status) //Publishing pulley status to App
{
  client.publish("pulley/status",status);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) //Dealing with 3 callback functions - Start relay, Stop relay and Publish status to App through MQTT  
{
  Serial.print("Message arrived on topic - ");
  Serial.println(topic);
  Serial.print("Message : ");

  String message;
  for(unsigned int i = 0; i<length; i++)
  {
    message +=(char)payload[i];
  }

  Serial.println(message);

  if (String(topic) == "pulley/control")
  {
    int commaIndex1 = message.indexOf(',');
    int commaIndex2 = message.indexOf(',', commaIndex1 + 1);
    String userCredentials = message.substring(0,commaIndex1);
    String startTime = message.substring(commaIndex1 + 1, commaIndex2);
    String durationString = message.substring(commaIndex2 + 1);
    
    expectedUserCredentials = userCredentials;
    expectedStartTime = startTime;
    duration = durationString.toInt() * 60000;

    if (isTimeToStart(expectedStartTime) && duration>0)
    {
      if(String(topic) == "pulley/control/start")
      {
        startRelay(duration);
      }
      else if(String(topic) == "pulley/control/stop")
      {
        stopRelay();
      }
      else if(String(topic) == "pulley/control/status")
      {
        publishStatus(digitalRead(relayPin) == HIGH? "Pulley Working" : "Pulley Offline");
      }
    }
    else
    {
      Serial.println("Lane not reserved for you. Please recheck your booking.");
    }
  } 
}

bool isTimeToStart(String startDateTime) //Verifies if user is eligible to operate lane at particular current time
{
  timeClient.update();
  unsigned long currentEpochTime = timeClient.getEpochTime();
  setTime(currentEpochTime);

  int dash1Index = startDateTime.indexOf('-');
  int dash2Index = startDateTime.indexOf('-', dash1Index + 1);
  int spaceIndex = startDateTime.indexOf(' ', dash2Index + 1);
  int colonIndex = startDateTime.indexOf(':', spaceIndex + 1);

  int startYear = startDateTime.substring(0, dash1Index).toInt();
  int startMonth = startDateTime.substring(dash1Index + 1, dash2Index).toInt();
  int startDay = startDateTime.substring(dash2Index + 1, spaceIndex).toInt();
  int startHour = startDateTime.substring(spaceIndex + 1, colonIndex).toInt();
  int startMinute = startDateTime.substring(colonIndex + 1).toInt();
  
  int currentYear = year();
  int currentMonth = month();
  int currentDay = day();
  int currentHour = hour();
  int currentMinute = minute();

  if (currentYear == startYear && currentMonth == startMonth && currentDay == startDay && currentHour == startHour && currentMinute == startMinute)
  {
    return true;
  }
  return false;
}
