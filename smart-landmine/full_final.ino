#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 5
#define RST_PIN 9
#define RELAY 3 //connect the relay to number 3 pin
#define BUZZER 2 // connect the buzzer to 2 pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
int btn = 4;
int btnrd;
int rahbar=LOW;
int samir=LOW;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(btn, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader for scanning ...");
  Serial.println();

}
void loop() 
{
  btnrd=digitalRead(btn);
  Serial.println(btnrd);
  //delay(150);
  if(btnrd==HIGH)
  {
    samir=HIGH;
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "70 D7 07 1B") // enter your own card number after copying it from serial monitor
  {
    rahbar= HIGH;
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    digitalWrite(RELAY, LOW);
    //delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    
  }
 
 else   {
    Serial.println(" Access denied");
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
  }
   
    }
  if(btnrd==LOW)
  {
    if(rahbar==HIGH&&samir==HIGH)
     {
     //delay(500);
    digitalWrite(RELAY, LOW);
    //delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    //delay(1000000000);
    rahbar=LOW;
    samir=LOW;
    }
 if(rahbar==LOW&&samir==HIGH) {
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
    // delay(100000000000);
    rahbar=LOW;
    samir=LOW;  
  }
    }  
    
      
 
}
