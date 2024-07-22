#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#define trigPin 9 
#define echoPin 11 
#define buzzer2 2
float duration;
float distance;
float sD;
int time;
//long   lat,lon; // create variable for latitude and longitude object
float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(3,4);//rx,tx
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
TinyGPS gps; // create gps object
const int sswitch = 13;
const int eswitch = 2;
void setup() {
  pinMode(sswitch, INPUT);
   pinMode(eswitch, INPUT);
   pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(buzzer2, OUTPUT);
  Serial.begin(9600); // connect serial
//Serial.println("The GPS Received Signal:");
gpsSerial.begin(9600); // connect gps sensor
lcd.begin(16,2);
}

void message()
{
 while(gpsSerial.available()){ // check for gps data
    if(gps.encode(gpsSerial.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    // display position
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("GPS Signal");
    lcd.setCursor(1,0);
    lcd.print("LAT:");
    lcd.setCursor(5,0);
    lcd.print(lat);
    lcd.setCursor(0,1);
    lcd.print(",LON:");
    lcd.setCursor(5,1);
    lcd.print(lon); 
   }
  }
  String latitude = String(lat,6);
  String longitude = String(lon,6);
  Serial.println(latitude+";"+longitude);
    Serial.println("AT+CMGF=1");  // Sets the SMS mode to text
    delay(1000);
    Serial.println();
    Serial.print("AT+CMGS=\"+910000000000\"\r"); //Mobile number to send location
    delay(1000);
    Serial.print("Emergency alert user requeries your Attention: ");
    Serial.print("https://maps.google.com/maps/place/"+latitude+", "+longitude); // SMS-Message body
    Serial.println(char(26));                //CTRL+Z key combination to send message
    while(1){}  
  delay(1000);
}
void ultrasonic()
{
     digitalWrite(trigPin, LOW);
delayMicroseconds(2); 
// Setting the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW); 
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH); 
// Distance Calculation
distance= duration*0.034/2; 
sD=distance;
time=sD*10;
if (sD <= 90) //Vibrates When Object Distance Exceed By 50cm
{
  digitalWrite(buzzer2, HIGH);
  delay(time);
  digitalWrite(buzzer2,LOW);
  delay(time);
}
else if (sD <= 60)  //Vibrates When Object Distance Exceed By 40cm
{
  digitalWrite(buzzer2, HIGH);
  delay(time);
  digitalWrite(buzzer2,LOW);
  delay(time);
}
else if (sD <= 30)  //Vibrates When Object Distance Excced By 30cm
{
  digitalWrite(buzzer2, HIGH);
  delay(time);
  digitalWrite(buzzer2,LOW);
  delay(time);
}
else if (sD <= 10) //Vibrates When Object Distance Excced By 20cm
{
  digitalWrite(buzzer2, HIGH);
  delay(time);
  digitalWrite(buzzer2,LOW);
  delay(time);
}
else if (sD <10) //Vibrates When Object Distance Excced By 10cm
{
  digitalWrite(buzzer2, HIGH);
  delay(time);
  digitalWrite(buzzer2,LOW);
  delay(time);
}
else if(sD <5)  //Vibrates When Object Distance Is ELss Than 10cm
{
  digitalWrite(buzzer2, LOW);
  delay(time);
  digitalWrite(buzzer2,LOW);
  delay(time);
}
else
{ 
  digitalWrite(buzzer2,LOW);
}
  //Distance Is Displayed On Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
void loop()
{
 boolean Buttonstate1=digitalRead(sswitch);
  boolean Buttonstate2=digitalRead(eswitch);
  Serial.println("Button1 State:");
  Serial.println(Buttonstate1);
   Serial.println("Button2 State:");
   Serial.println(Buttonstate2);
  if(Buttonstate1&&Buttonstate2)
 {
  Serial.println("Both Are Switched on:");
   Serial.println(Buttonstate1);
   Serial.println(Buttonstate2);
   ultrasonic();
   Serial.println("Sending Message..");
   message();   
}
 if(Buttonstate1)
 {
  Serial.println("Ultra-sonic Button Switched On..");
  Serial.println(Buttonstate1); 
  ultrasonic();
 }
 if(Buttonstate2)
 {
  Serial.println("Emergency Button Switched on..");
   Serial.println(Buttonstate2);
   message();
}
}
