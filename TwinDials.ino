/*
 This sketch was written by Philc, and maybe amended and used freely, enjoy!!!!
 
 Animated Dials for ESP32 and ILI9341 320 x 240 display, using Arduino_GFX_Library.
 The sketch uses font sizes 1 and 2. 
*/

#include <Arduino_GFX_Library.h>
  
#define TFT_DC 2 //9
#define TFT_CS 15 //10
#define TFT_RST 4 //8

#define TFT_SCK    18
#define TFT_MOSI   23
#define TFT_MISO   19

//Define Chip Select Pins, and Rotation
#define TS_CS 21  //7
#define SD_CS 5
#define ROTATION 3

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define DARK_GREY 0x4A89
#define MEDIUM_GREY 0x8492
#define LIGHT_GREY 0xD6BA
#define LIGHT_GREEN 0x970E

//****Create data bus, and object class to interact with ILI9341 screen*****
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 tft = Arduino_ILI9341(&bus, TFT_RST);

int speed = 0;
  
void setup(){
  Serial.begin(115200);  
  //*****Deselect all SPI Devices, only needed if SD and Touchscreen used*****
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);
  pinMode(21, OUTPUT);  //was 7
  digitalWrite(21, HIGH);  //was 7
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  //*****2 lines below were used for Touchscreen testing with LED--ignore--*****
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  
  tft.begin();
  tft.setRotation(ROTATION); 
   
  tft.fillScreen(BLACK);

  myDialsSetup();
}
  
void loop() {
  dialsUpdate();
}

String oldSpeed = "000";            //Used to clear previous speed
int myRev = 0, myRevTemp = 0;
void dialsUpdate(){
  String mySpeed = "";
  int tempSpeed = 0, revTrack = 0;
  tft.setTextSize(2);  
    for(int a = 131; a <= 410; a++){
       if(a % 2 == 0){
         tempSpeed = ((a - 130)/2);
         if(tempSpeed <= 9){
           mySpeed = " " + String(tempSpeed) + " ";
           tft.setTextColor(BLACK);
           tft.setCursor(65, 125);
           tft.print(oldSpeed);

           tft.setTextColor(WHITE);
           tft.setCursor(65, 125);
           tft.print(mySpeed);
           oldSpeed = mySpeed;
         }else if(tempSpeed >= 10 && tempSpeed < 100){
           mySpeed = String(tempSpeed) + " ";
           tft.setTextColor(BLACK);
           tft.setCursor(65, 125);
           tft.print(oldSpeed);

           tft.setTextColor(WHITE);
           tft.setCursor(65, 125);
           tft.print(mySpeed);
           oldSpeed = mySpeed;
         }else{        
           mySpeed = String(tempSpeed);
           tft.setTextColor(BLACK);
           tft.setCursor(65, 125);
           tft.print(oldSpeed);

           tft.setTextColor(WHITE);
           tft.setCursor(65, 125);
           tft.print(mySpeed);
           oldSpeed = mySpeed;                
         }
       
       //  Serial.print("Speed = "); Serial.println(mySpeed); //used for debugging!!!
       }
      delay(30);     
      if (a % 10 != 0){ //tl = 8;
        tft.fillArc(80, 80, 73, 63, a - 1, a, BLUE);
      }else{
        tft.fillArc(80, 80, 73, 63, a - 1, a, BLACK);
      }
      
      myRevTemp = a - 40;
      revTrack = myRevTemp - 90;
      if(myRevTemp % 31 != 0){
        if(revTrack > 0 && revTrack <= 94){
          tft.fillArc(tft.width() - 80, 80, 73, 63, myRevTemp - 1, myRevTemp, WHITE);
        }else if(revTrack >= 94 && revTrack <= 187){
          tft.fillArc(tft.width() - 80, 80, 73, 63, myRevTemp - 1, myRevTemp, BLUE);
        }
        else{
          tft.fillArc(tft.width() - 80, 80, 73, 63, myRevTemp - 1, myRevTemp, RED);
        }
      }else{
        tft.fillArc(tft.width() - 80, 80, 73, 63, myRevTemp - 1, myRevTemp, BLACK);
      }

     /*2 lines below were used for debugging!!!!
      Serial.print("The values of a and myTempRev: ");Serial.print(a);
      Serial.print("     ");Serial.println(myRevTemp); 
     */  
   } 

  delay(20);

   for(int a = 410; a >= 130; a--){
    myRev = a - 39;
    if(a % 2 == 0){
         tempSpeed = ((a - 130)/2);
         if(tempSpeed <= 9){
           mySpeed = " " + String(tempSpeed) + " ";
           tft.setTextColor(BLACK);
           tft.setCursor(65, 125);
           tft.print(oldSpeed);

           tft.setTextColor(WHITE);
           tft.setCursor(65, 125);
           tft.print(mySpeed);
           oldSpeed = mySpeed;
         }else if(tempSpeed >= 10 && tempSpeed < 100){
           mySpeed = String(tempSpeed) + " ";
           tft.setTextColor(BLACK);
           tft.setCursor(65, 125);
           tft.print(oldSpeed);

           tft.setTextColor(WHITE);
           tft.setCursor(65, 125);
           tft.print(mySpeed);
           oldSpeed = mySpeed;
         }else{        
           mySpeed = String(tempSpeed);
           tft.setTextColor(BLACK);
           tft.setCursor(65, 125);
           tft.print(oldSpeed);

           tft.setTextColor(WHITE);
           tft.setCursor(65, 125);
           tft.print(mySpeed);
           oldSpeed = mySpeed;                
         }

         /*line below used for debugging!!!       
         Serial.print("Speed = "); Serial.println(mySpeed);
         */
       }
      delay(30);     
        if (a % 10 != 0){ //tl = 8;
          //tft.fillArc(80, 80, 73, 63, a - 1, a, BLUE);
          tft.fillArc(80, 80, 73, 63, a - 1, a, BLACK);
        }else{
          tft.fillArc(80, 80, 73, 63, a - 1, a, BLACK);
          if(a == 130){
            tft.fillArc(80, 80, 73, 58, 129, 130, WHITE);
          }
        }
        tft.fillArc(tft.width() - 80, 80, 73, 63, myRev - 1, myRev, BLACK);
   }
}

void myDialsSetup(){
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.setCursor(65, 35);
  tft.print("MPH");

  tft.setCursor(tft.width() - 95, 35);
  tft.print("RPM");

  tft.setTextColor(WHITE);
  tft.setCursor(65, 125);
  tft.print("000");

  tft.setTextSize(1);
  tft.setCursor(45, 115);
  tft.print("0");

  tft.setCursor(tft.width() - 94, 53);
  tft.print("x1000");
  
  tft.setCursor(tft.width() - 82, 126);
  tft.print("0");

  tft.setTextColor(RED);
  tft.setCursor(105, 115);
  tft.print("140");

  tft.setCursor(tft.width() - 32, 86);
  tft.print("9");

  tft.fillArc(80, 80, 73, 58, 129, 130, WHITE);
  tft.fillArc(80, 80, 73, 58, 410, 411, RED);

  tft.fillArc(tft.width() - 80, 80, 73, 58, 89, 90, WHITE);
  tft.fillArc(tft.width() - 80, 80, 73, 58, 11, 12, RED);
  
  tft.drawCircle(80, 80, 75, BLUE);
  tft.drawCircle(tft.width()-80, 80, 75, BLUE);

  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(20, 200);
  tft.print("ESP32 and ILI9341 Dials");
}
