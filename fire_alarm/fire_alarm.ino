#include <LiquidCrystal_I2C.h>
#include<Wire.h>
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketchLiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

#define pinD0 4
#define buzzer2 18
#define SENSOR 13
#define buzzer1 19
#define relay 12
#define ledcblua 5
#define ledmq2 15
#define SPRINKLER_START_DELAY 5000  //5 seconds 
#define SPRINKLER_ON_TIME 3000      //3 seconds Sprinkler on time
unsigned long previousTime = millis();
int sensorValue = 0;
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinD0, INPUT);
  pinMode(SENSOR, INPUT);
  pinMode(ledcblua, OUTPUT);
  pinMode(ledmq2, OUTPUT);

  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
   pinMode(relay, OUTPUT);
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" FIRE ALARM ");
  lcd.setCursor(0,1);
  lcd.print(" an toan ");
}

void loop() {
  // put your main code here, to run repeatedly:
 

  if (digitalRead(pinD0)==LOW){
    digitalWrite(buzzer1, HIGH);
    digitalWrite(ledcblua, HIGH);
     lcd.setCursor(0,1);
    lcd.print(" co lua ");
  
     if (millis() - previousTime > SPRINKLER_START_DELAY)  //We will wait for few seconds before sprinkler can be started once fire is detected.
    {
       
      digitalWrite(relay, HIGH);
      lcd.setCursor(0,1);
    lcd.print(" dap lua ");
      delay(SPRINKLER_ON_TIME);}

  }
  else
  {
    digitalWrite(buzzer1,LOW);
    digitalWrite(ledcblua, LOW);
     digitalWrite(relay, LOW); 
      lcd.setCursor(0,1);
  lcd.print(" an toan ");
   previousTime = millis(); 
   
   
 
    Serial.println("ko lửa");

  }


  //Serial.println(flameD0);
  //delay(20);
delay(500);      // gửi tín hiệu 500ms /1 lần
  sensorValue = analogRead(SENSOR); //(đọc giá trị nồng độ khí gas (analog) của MQ2 và gán vào biến sensorValue)
  Serial.print("Value: "); Serial.println(sensorValue);//in giá trị ra màn hình)
  if (sensorValue > 4000 ){
    digitalWrite(buzzer2, HIGH);
    digitalWrite(ledmq2, HIGH);
    lcd.setCursor(0,1);
    lcd.print(" VUOT CO2 ");
    Serial.println("VUOT MUC CO2");
   
    delay(4400);
  }
  else
  {
    digitalWrite(buzzer2,LOW);
    digitalWrite(ledmq2, LOW);
    Serial.println("BTHG");
  }
  Serial.println("flameD1");
  Serial.print(" ");
  
}
