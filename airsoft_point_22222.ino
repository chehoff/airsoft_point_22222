// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
unsigned long prev_ms = 0;
int print_sw_1 = 0;
int sw_st = 0;
int timer_sw = 10;
int storona = 0;
int prev_storona = 0;
int button_blue = 8;
int button_green = 9;
long timer_1 = 300;
int timer_2 = 60;
int score_blue = 0;
int score_green = 0;
LiquidCrystal_I2C lcd(0x3F,16,2);
byte ch[8] = {
  B00000,
  B00000,
  B10001,
  B10001,
  B01111,
  B00001,
  B00001,
  B00000
};
byte k[8] = {
  B00000,
  B00000,
  B10010,
  B10100,
  B11000,
  B10100,
  B10010,
  B00000
};
byte n[8] = {
  B00000,
  B00000,
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B00000
};
byte t[8] = {
  B00000,
  B00000,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};
byte l[8] = {
  B00000,
  B00000,
  B01111,
  B00101,
  B00101,
  B10101,
  B01001,
  B00000
};
byte v[8] = {
  B00000,
  B00000,
  B11100,
  B10010,
  B11100,
  B10010,
  B11100,
  B00000
};
byte z[8] = {
  B00000,
  B00000,
  B11110,
  B00001,
  B00110,
  B00001,
  B11110,
  B00000
};
byte bl[8] = {
  B00000,
  B00000,
  B10001,
  B10001,
  B11101,
  B10011,
  B11101,
  B00000
};
void setup() {
  pinMode(button_blue, INPUT);
  pinMode(button_green, INPUT);
  lcd.begin(16, 2);
  lcd.init();
  lcd.createChar(16, ch);
  lcd.createChar(1, k);
  lcd.createChar(2, n);
  lcd.createChar(3, t);
  lcd.createChar(4, l);
  lcd.createChar(5, v);
  lcd.createChar(6, z);
  lcd.createChar(7, bl);
  lcd.backlight();
}

// the loop routine runs over and over again forever:
void loop() {
dbl_btn_clk();
if(sw_st==1){
    if (print_sw_1 == 1){
      print_sw_1 = 0;}
if (storona == 0){
    lcd.setCursor(0,0);
    say_neitral(0,0);
  } else {
    say_tochka_zahvachena(0,0);
    nabor_ochkov(storona);
  }
  if((digitalRead(button_blue)==HIGH)&&(storona != 1)){
    prev_storona = storona;
    zahvat(1);
  }
  if((digitalRead(button_green)==HIGH)&&(storona != 2)){
    prev_storona = storona;
    zahvat(2);
  }
  } else {
    if(print_sw_1 == 0){
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      say_sinie(0,0);
      say_zelenie(9,0);
      lcd.setCursor(2,1);
      lcd.print(score_blue);
      lcd.setCursor(12,1);
      lcd.print(score_green);
      print_sw_1 = 1;
    }
  }
  delay(505);
}
void zahvat(int a){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  say_zahvat_tochki(2,0);
  while(timer_2>0){
    dbl_btn_clk();
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(7, 1);
    lcd.print(timer_2);
    timer_2--;
    delay(1000);
    if ((digitalRead(button_blue)==HIGH)&&(prev_storona==1)){
      timer_2 = 60;
      return;
    } else if ((digitalRead(button_green)==HIGH)&&(prev_storona==2)){
      timer_2 = 60;
      return;
    }
  }
  storona = a;
  timer_2 = 60;
  timer_1 = 300;
  prev_ms = millis();
}
void say_zahvat_tochki(int a, int b){
  lcd.setCursor (a, b);
for (int i = a; i < 16-a; ++i)
{
  lcd.print(' ');
}
  lcd.setCursor(a, b);
  lcd.print("3ax");
  lcd.print(char(5));
  lcd.print("a");
  lcd.print(char(3));
  lcd.print(" ");
  lcd.print(char(3));
  lcd.print("o");
  lcd.print(char(0));
  lcd.print(char(1));
  lcd.print("u");
}

void say_tochka_zahvachena(int a, int b){
  lcd.setCursor(a, b);
  lcd.print("To");
  lcd.print(char(0));
  lcd.print(char(1));
  lcd.print("a");
  lcd.print(" ");
  lcd.print(char(6));
  lcd.print("ax");
  lcd.print(char(5));
  lcd.print("a");
  lcd.print(char(0));
  lcd.print("e");
  lcd.print(char(2));
  lcd.print("a:");
}
void say_sinie(int a, int b){
  lcd.setCursor(a, b);
  lcd.print("Cu");
  lcd.print(char(2));
  lcd.print("ue");
}
void say_neitral(int a, int b){
  lcd.setCursor(a, b);
  lcd.print("To");
  lcd.print(char(0));
  lcd.print(char(1));
  lcd.print("a ");
  lcd.print(char(2));
  lcd.print("eu");
  lcd.print(char(3));
  lcd.print("pa");
  lcd.print(char(4));
  lcd.print("b");
  lcd.print(char(2));
  lcd.print("a");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
void say_zelenie(int a, int b){
  lcd.setCursor(a, b);
  lcd.print("3e");
  lcd.print(char(4));
  lcd.print("e");
  lcd.print(char(2));
  lcd.print(char(7));
  lcd.print("e");
}
void nabor_ochkov(int a){
  say_tochka_zahvachena(0,0);
  if(a == 1){
    lcd.setCursor(0,1);
    lcd.print("                ");
    say_sinie(0,1);
    lcd.setCursor(9,1);
    lcd.print(score_blue);
    lcd.setCursor(13,1);
    lcd.print("   ");
    lcd.setCursor(12,1);
    lcd.print(timer_1);
    if((millis()-prev_ms)>=1000){
      timer_1--;
      prev_ms = millis();
    }
    if (timer_1 < 0){
      score_blue++;
      timer_1 = 300;
      prev_ms = millis();
    }
  } else if (a == 2){   
    lcd.setCursor(0,1);
    lcd.print("                ");
    say_zelenie(0,1);
    lcd.setCursor(9,1);
    lcd.print(score_green);
    lcd.setCursor(13,1);
    lcd.print(timer_1);
    if((millis()-prev_ms)>=1000){
      timer_1--;
      prev_ms = millis();
    }
    if (timer_1 < 0){
      score_green++;
      timer_1 = 300;
      prev_ms = millis();
    }
  } else {
    lcd.print("Neitral");
  }
}
void dbl_btn_clk(){
  if((digitalRead(button_blue)==HIGH)&&(digitalRead(button_green)==HIGH)){
  if (timer_sw==0){
    if(sw_st==1){
      sw_st = 0;
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(8,0);
      lcd.print("Ok");
      delay(5000);
    } else {
      sw_st = 1;
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(8,0);
      lcd.print("Ok");
      delay(5000);
    }
    timer_sw = 10;
  } else {
    timer_sw--;
  }
} else {
  timer_sw = 10;
}
return;
}

