#include <LiquidCrystal.h>

int incomingByte;
byte inputByte_0;
byte inputByte_1;
byte inputByte_2;
byte inputByte_3;
byte inputByte_4;
LiquidCrystal lcd(8,9,4,5,6,7);

void setup() {
  Serial.begin(115200);
  Serial.println("AfterLCD started");
  // put your setup code here, to run once:
  
  lcd.begin(16,2);
  lcd.print("AfterLCD v0.1");
  lcd.setCursor(0,1);
  lcd.print("@ijat.my");

  Serial.println("Waiting to receive data");
}

void loop() {
  
  if (Serial.available()) 
  {
    /* //Read buffer
    inputByte_0 = Serial.read();
    delay(100);    
    inputByte_1 = Serial.read();
    delay(100);      
    inputByte_2 = Serial.read();
    delay(100);      
    inputByte_3 = Serial.read();
    delay(100);
    inputByte_4 = Serial.read(); */

    //if (!Test()) {
      lcd.clear();
      while (Serial.available() > 0) {
        byte b = Serial.read();
        if (b == 10) {
          lcd.setCursor(0,1);
          continue;
        }
        lcd.write(b);
      }
    //}
  }

  
  

}

bool Test() {
//Check for start of Message
  if(inputByte_0 == 16)
  {
       //Detect Command type
       switch (inputByte_1) 
       {
          case 127:
             //Set PIN and value
             switch (inputByte_2)
            {
              case 4:
                if(inputByte_3 == 255)
                {
                  Serial.println("Serial error - 1");
                  lcd.clear();
                  lcd.print("Fail[E1]");
                  return false;
                  break;
                }
                else
                {
                  Serial.println("Serial error - 2");
                  lcd.clear();
                  lcd.print("Fail\n[E2]");
                  return false;
                  break;
                }
              break;
            } 
            break;
          case 128:
            Serial.println("Sent confirmation to PC");
            Serial.print("HELLO FROM ARDUINO");
            break;
        } 
        //Clear Message bytes
        inputByte_0 = 0;
        inputByte_1 = 0;
        inputByte_2 = 0;
        inputByte_3 = 0;
        inputByte_4 = 0;
        //Let the PC know we are ready for more data
        lcd.clear();
        lcd.print("Ready");
        Serial.println("Ready to receive next data");
        return true;
  }
}

