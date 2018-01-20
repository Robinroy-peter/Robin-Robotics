/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Designed By Robinroy Peter Computer Science University of jaffna
 ****************************************************/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SD.h>


int getFingerprintIDez();
const int chipSelect = 53;
const int buttonPin = 22;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
File dataFile;
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
LiquidCrystal_I2C lcd(0x27,20,4); 
SoftwareSerial mySerial(10, 11);
int myInts[10];
int num =0;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup()  
{
  Serial.begin(9600);
  Serial.println("fingertest");
  pinMode(buttonPin, INPUT);
  pinMode(13, OUTPUT);
////////////////////lcd///////////////////
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Attendents System");
  lcd.setCursor(7,1);
  lcd.print("Dep. CS");
   lcd.setCursor(5,2);
  lcd.print("Fac.Science");
   lcd.setCursor(3,3);
  lcd.print("Robinroy peter");
  delay(1000);
  //////////////////lcd/////////////////////////////
  // set the data rate for the sensor serial port
  finger.begin(57600);
  //////////////////////sd/////////////////
    Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(53, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  /*if (SD.exists("example.txt")) {
    Serial.println("Old txt deleted");
    SD.remove("example.txt");
  } else {
    Serial.println("example.txt doesn't exist.");
  }*/
  dataFile = SD.open("example.txt",FILE_WRITE);
  if (dataFile) {
    Serial.println("example.txt: ");

    // read from the file until there's nothing else in it:
    //dataFile.println("Attendens");
    // close the file:
    dataFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  /////////////////sd/////////////////////
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
{ 
    buttonState = digitalRead(buttonPin);
  //int u =getFingerprintIDez();
  //Serial.println(getFingerprintIDez());
//if(u != -1){
dataFile = SD.open("example.txt",FILE_WRITE);
  if (dataFile) {
    Serial.println("example.txt: ");

    // read from the file until there's nothing else in it:
    int u =getFingerprintIDez();
    if(u != -1){
      dataFile.println(u);
      lcd.clear();
      lcd.setCursor(7,1);
      lcd.print(u);
      lcd.setCursor(7,2);
      lcd.print("Done");
      delay(200);
    }
    // close the file:
    dataFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
   // }

 delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #");Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}

/*void DataStore(int y){
 File dataFile = SD.open("example.txt");
  if (dataFile) {
    Serial.println("example.txt: "+y);

    // read from the file until there's nothing else in it:
    dataFile.println(y);
    // close the file:
    dataFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}*/
