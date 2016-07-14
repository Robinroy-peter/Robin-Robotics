 ###################################################################
 // ---------------------------------------------------------------------------
// Basic Testing codeed by Robinroy peter.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h>

Servo servo;  // create servo object to control a servo
//plz find servo attach pin is 9..thats defined in setup()
int val;    // variable to read the value from the analog pin

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing ultra_sonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(13,OUTPUT);
  servo.attach(9);
   servo.write(val);
}

void loop() {
  
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(ultra_sonic.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
   digitalWrite(13,LOW);
  if((5<ultra_sonic.ping_cm())&&(ultra_sonic.ping_cm()<30)){
    digitalWrite(13,HIGH);
    servo.write(160-val);
    }
    val = 160-val;
    delay(200);
   }
