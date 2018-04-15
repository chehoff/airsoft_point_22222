//Для работы необходима установка библиотеки LiquidCrystal_I2C
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int lcd_col = 16; //Количество символов в одном ряду экрана LCD
unsigned long prev_ms = 0; //ХЗ что это
int print_sw_1 = 0; //ХЗ что это
int sw_st = 0;  //Сторона которая удерживает точку Синие - 1 зеленые - 2
int timer_sw = 10; //Таймер включения
//int storona = 0; //Текущая сторона владеющая точкой
int prev_storona = 0; //Сторона которая владела точкой до начала захвата
int button_blue = 8; //Пин подключения кнопки Синей стороны
int button_green = 9; //Пин подключения кнопки Зеленой стороны
long timer_score_default = 300; //Количество секунд требуемое для удержания точки
long timer_score = timer_score_default; //Количество секунд требуемое для удержания точки
int timer_zahvat_default = 60; //Количество секунд необходимое для захвата точки
//int timer_zahvat = timer_zahvat_default; //Количество секунд необходимое для захвата точки
int score_blue = 0; //Количество очков синей стороны
int score_green = 0;  //Количество очков зеленой стороны
LiquidCrystal_I2C lcd(0x3F,lcd_col,2); // Инициация дисплея
byte ch[8] = {  //Инициирование буквы "ч"
  B00000,
  B00000,
  B10001,
  B10001,
  B01111,
  B00001,
  B00001,
  B00000
};
byte k[8] = { //Инициирование буквы "к"
  B00000,
  B00000,
  B10010,
  B10100,
  B11000,
  B10100,
  B10010,
  B00000
};
byte n[8] = { //Инициирование буквы "н"
  B00000,
  B00000,
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B00000
};
byte t[8] = { //Инициирование буквы "т"
  B00000,
  B00000,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};
byte l[8] = {//Инициирование буквы "л"
  B00000,
  B00000,
  B01111,
  B00101,
  B00101,
  B10101,
  B01001,
  B00000
};
byte v[8] = {//Инициирование буквы "в"
  B00000,
  B00000,
  B11100,
  B10010,
  B11100,
  B10010,
  B11100,
  B00000
};
byte z[8] = { //Инициирование буквы "з"
  B00000,
  B00000,
  B11110,
  B00001,
  B00110,
  B00001,
  B11110,
  B00000
};
byte bl[8] = {  //Инициирование буквы "ы"
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
  pinMode(button_blue, INPUT); //Инициируем кнопку синих
  pinMode(button_green, INPUT); //Инициируем кнопку зеленых
  lcd.begin(lcd_col,2);
  lcd.init();
  lcd.createChar(16, ch);  //Инициируем алфавит
  lcd.createChar(1, k);
  lcd.createChar(2, n);
  lcd.createChar(3, t);
  lcd.createChar(4, l);
  lcd.createChar(5, v);
  lcd.createChar(6, z);
  lcd.createChar(7, bl);
  lcd.backlight();  //Включаем подсветку
}


void loop() 
{
if(sw_st!=0) //Если точка кому-то принадлежит
  {
    say_tochka_zahvachena(0,0); //Написать что она захвачена
    if(sw_st == 1)  //Если Синие
    {
      say_sinie(0,1); //Написать синие
      clean_sim(9,1);
      lcd.setCursor(9,1);
      lcd.print(score_blue);  //И количество очков
    } else {
      say_zelenie(0,1); //Написать зеленые
      clean_sim(9,1);
      lcd.setCursor(9,1);
      lcd.print(score_green); //И количество очков
    }
    if(timer_score>0) //Если таймер больше 0
    {
      timer_score--;  //Уменьшить таймер на 1
      lcd.setCursor(12,1);
      lcd.print(timer_score); //напечатать количество секунд до захвата
    } else {  //Если таймер 0
      if(sw_st == 1){ //Если удерживают синие
        score_blue++; //Приплюсовать им 1 очко
        timer_score = timer_score_default;  //Сбросить таймер
      } else {  //Если удерживают зеленые
        score_green++;//Приплюсовать им 1 очко
        timer_score = timer_score_default;//Сбросить таймер
      }
    }
    delay(1000);
    if_btn();  //Проверить нажатие кнопки
  } else {
    say_neitral(0,0); //Напечатать точка нейтральна
    if_btn();  //Проверить нажатие кнопки
    delay(1000);
  }
}
void zahvat(int st){
  lcd.clear();
  int prev_st = sw_st;
  say_zahvat_tochki(2,0);
  int timer = timer_zahvat_default;
  while(timer>0){
    if((digitalRead(button_blue)==HIGH)&&(prev_st==1)){
      return;
    }
    if((digitalRead(button_green)==HIGH)&&(prev_st==2)){
      return;
    }
    clean_sim(7,1);
    lcd.setCursor(7, 1);
    lcd.print(timer);
    delay(1000);
    timer--;
  }
  sw_st = st;
}
void clean_sim(int a, int b){
  lcd.setCursor (a, b);
  char Str[lcd_col-a];
  for(int i = 0; i < lcd_col-a; i++){
    Str[i]=' ';
  }
  lcd.print(Str);
}
void say_zahvat_tochki(int a, int b){
  clean_sim(a, b);
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
  clean_sim(a, b);
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
  clean_sim(a, b);
  lcd.setCursor(a, b);
  lcd.print("Cu");
  lcd.print(char(2));
  lcd.print("ue");
}
void say_neitral(int a, int b){
  lcd.clear();
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
  clean_sim(a, b);
  lcd.setCursor(a, b);
  lcd.print("3e");
  lcd.print(char(4));
  lcd.print("e");
  lcd.print(char(2));
  lcd.print(char(7));
  lcd.print("e");
}
void if_btn(){
  if ((digitalRead(button_blue)==HIGH)||(digitalRead(button_green)==HIGH)){
    if ((digitalRead(button_blue)==HIGH)&&(sw_st!=1)){
      zahvat(1);
    } else if ((digitalRead(button_green)==HIGH)&&(sw_st!=2)){
      zahvat(2);
    }
  }
}

