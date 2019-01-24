#include <ESP8266WiFi.h>
#include <ESP8266SMTP.h>

const int sensor = 4; // pin for reed switch sensor... actually pin 2 but nodemcu is mislabeled ¯\_(ツ)_/¯
int state; // 0 (close) or 1 (open) reed switch


void setup()
{
  pinMode(sensor, INPUT_PULLUP);
  
  Serial.begin(74880);
  delay(2000);
   
}

void loop()
{
  state = digitalRead(sensor); // read sensor
  
  if (state == HIGH) {                                                   // someone opened your mailbox

     const char* ssID = "****your_network_name****";                     // WIFI network name
     const char* password = "****your_network_password****";             // WIFI network password (not very secure, but you can encrypt)
     
     WiFi.begin(ssID, password);
     delay(8000);    
     Serial.print(F("Connection Status is now: "));
     Serial.println(WiFi.status());
    
     SMTP.setEmail("****your_gmail_address****")                        // your gmail email address (for added security, use a dummy gmail)(will need to turn on "use less secure apps" in gmail settings)
    .setPassword("****your_gmail_password****")                         // your gmail password (not very secure, but you can encrypt)
    .Subject("You've Got Mail!")
    .setFrom("ESP8266_SMTP")
    .setForGmail();                                                     // simply sets port to 465 and setServer("smtp.gmail.com");           
  
    if(SMTP.Send("****your_receiving_address****", "You need to go get your mail now.")) {
      Serial.println(F("Message sent"));
    } else {
      Serial.print(F("Error sending message: "));
      Serial.println(SMTP.getError());
    } 

    delay(30000);
    WiFi.disconnect(true);                                              // disconect WIFI to save battery
    delay(30000);
    Serial.print(F("Connection Status is now: "));
    Serial.println(WiFi.status());
  }
    
  else {
      // nothing to see here
    }
}
