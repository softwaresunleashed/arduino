#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <WiFiClient.h>
#include <aREST.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//------------------------------------------
//WIFI
const char* ssid = "Home_Wireless";
const char* password = "+9211hacker";

aREST rest = aREST();

int temperature;

//------------------------------------------
//HTTP
// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

 
// Data wire is plugged into pin 2 on the ESP8266 MCU Node
// ‘5’ refers to GPIO05 which is pin 2(refer to ESP8266 pinout)
#define ONE_WIRE_BUS 5
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just lcMaxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");
  Serial.println("");
  
  // trigger wi-fi connection
  WiFi.begin(ssid, password);

  // wait for wifi connection to complete.
  Serial.print("Connecting to SSID -- " + ssid);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // expose the two measurement variable(temperature) to the aREST API
  // so they can be accessed from outside
  rest.variable("temperature",&temperature);

  // set the name & ID of the board:
  rest.set_id("1");
  rest.set_name("sensor_module");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Start up the temperature sensor library
  sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); 

  // Send the command to get temperatures
  temperature = sensors.getTempCByIndex(0);

  // check if a client is connected to the ESP8266, and handle the request
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}







//
//
////DS18B20
//#define D5 5
//#define ONE_WIRE_BUS D5 //Pin to which is attached a temperature sensor
//#define ONE_WIRE_MAX_DEV 15 //The maximum number of devices = 15
//
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature DS18B20(&oneWire);
//int numberOfDevices; //Number of temperature devices found
//DeviceAddress devAddr[ONE_WIRE_MAX_DEV];  //An array device temperature sensors
//float tempDev[ONE_WIRE_MAX_DEV]; //Saving the last measurement of temperature
//float tempDevLast[ONE_WIRE_MAX_DEV]; //Previous temperature measurement
//long lastTemp; //The last measurement
//const int durationTemp = 5000; //The frequency of temperature measurement
//
////------------------------------------------
////WIFI
//const char* ssid = "Home_Wireless";
//const char* password = "+9211hacker";
//
////------------------------------------------
////HTTP
//ESP8266WebServer server(80);
//
////------------------------------------------
////Convert device id to String
//String GetAddressToString(DeviceAddress deviceAddress){
//  String str = "";
//  for (uint8_t i = 0; i < 8; i++){
//    if( deviceAddress[i] < 16 ) str += String(0, HEX);
//    str += String(deviceAddress[i], HEX);
//  }
//  return str;
//}
//
////Setting the temperature sensor
//void SetupDS18B20(){
//  DS18B20.begin();
//
//  Serial.print("Parasite power is: "); 
//  if( DS18B20.isParasitePowerMode() ){ 
//    Serial.println("ON");
//  }else{
//    Serial.println("OFF");
//  }
//  
//  numberOfDevices = DS18B20.getDeviceCount();
//  Serial.print( "Device count: " );
//  Serial.println( numberOfDevices );
//
//  lastTemp = millis();
//  DS18B20.requestTemperatures();
//
//  // Loop through each device, print out address
//  for(int i=0;i<numberOfDevices; i++){
//    // Search the wire for address
//    if( DS18B20.getAddress(devAddr[i], i) ){
//      //devAddr[i] = tempDeviceAddress;
//      Serial.print("Found device ");
//      Serial.print(i, DEC);
//      Serial.print(" with address: " + GetAddressToString(devAddr[i]));
//      Serial.println();
//    }else{
//      Serial.print("Found ghost device at ");
//      Serial.print(i, DEC);
//      Serial.print(" but could not detect address. Check power and cabling");
//    }
//
//    //Get resolution of DS18b20
//    Serial.print("Resolution: ");
//    Serial.print(DS18B20.getResolution( devAddr[i] ));
//    Serial.println();
//
//    //Read temperature from DS18b20
//    float tempC = DS18B20.getTempC( devAddr[i] );
//    Serial.print("Temp C: ");
//    Serial.println(tempC);
//  }
//}
//
////Loop measuring the temperature
//void TempLoop(long now){
//  Serial.print( "Entered Temp Loop..." );
//  
//  if( now - lastTemp > durationTemp ){ //Take a measurement at a fixed time (durationTemp = 5000ms, 5s)
//    for(int i=0; i<numberOfDevices; i++){
//      float tempC = DS18B20.getTempC( devAddr[i] ); //Measuring temperature in Celsius
//      tempDev[i] = tempC; //Save the measured value to the array
//    }
//    DS18B20.setWaitForConversion(false); //No waiting for measurement
//    DS18B20.requestTemperatures(); //Initiate the temperature measurement
//    lastTemp = millis();  //Remember the last time measurement
//  }
//}
//
////------------------------------------------
//void HandleRoot(){
//  String message = "Number of devices: ";
//  message += numberOfDevices;
//  message += "\r\n<br>";
//  char temperatureString[6];
//
//  message += "<table border='1'>\r\n";
//  message += "<tr><td>Device id</td><td>Temperature</td></tr>\r\n";
//  for(int i=0;i<numberOfDevices;i++){
//    dtostrf(tempDev[i], 2, 2, temperatureString);
//    Serial.print( "Sending temperature: " );
//    Serial.println( temperatureString );
//
//    message += "<tr><td>";
//    message += GetAddressToString( devAddr[i] );
//    message += "</td>\r\n";
//    message += "<td>";
//    message += temperatureString;
//    message += "</td></tr>\r\n";
//    message += "\r\n";
//  }
//  message += "</table>\r\n";
//  
//  server.send(200, "text/html", message );
//}
//
//void HandleNotFound(){
//  String message = "File Not Found\n\n";
//  message += "URI: ";
//  message += server.uri();
//  message += "\nMethod: ";
//  message += (server.method() == HTTP_GET)?"GET":"POST";
//  message += "\nArguments: ";
//  message += server.args();
//  message += "\n";
//  for (uint8_t i=0; i<server.args(); i++){
//    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//  }
//  server.send(404, "text/html", message);
//}
//
//
////------------------------------------------
//void setup() {
//  //Setup Serial port speed
//  Serial.begin(115200);
//
//  //Setup WIFI
//  WiFi.begin(ssid, password);
//  Serial.println("");
//
//  //Wait for WIFI connection
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());
//
//  server.on("/", HandleRoot);
//  server.onNotFound( HandleNotFound );
//  server.begin();
//  Serial.println("HTTP server started at ip " + WiFi.localIP().toString() );
//
//  //Setup DS18b20 temperature sensor
//  SetupDS18B20();
//
//}
//
//void loop() {
//  long t = millis();
//  
//  server.handleClient();
//  TempLoop( t );
//}
