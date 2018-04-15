# arduino_point_score
Programm for arduino
Переменные:
int lcd_col = 16; //Количество символов в одном ряду экрана LCD
int sw_st = 0;  //Сторона которая удерживает точку Синие - 1 зеленые - 2
int timer_sw = 10; //Таймер включения
int prev_storona = 0; //Сторона которая владела точкой до начала захвата
int button_blue = 8; //Пин подключения кнопки Синей стороны
int button_green = 9; //Пин подключения кнопки Зеленой стороны
long timer_score_default = 300; //Количество секунд требуемое для удержания точки
long timer_score = timer_score_default; //Количество секунд требуемое для удержания точки
int timer_zahvat_default = 60; //Количество секунд необходимое для захвата точки
//int timer_zahvat = timer_zahvat_default; //Количество секунд необходимое для захвата точки
nt score_blue = 0; //Количество очков синей стороны
int score_green = 0;  //Количество очков зеленой стороны

Функции:
void clean_sim(int a, int b) //Стереть экран до конца с указанной позиции
void say_zahvat_tochki(int a, int b) //Напечатать захват точки с указанной позиции
void say_tochka_zahvachena(int a, int b) //Напечатать точка захвачена с указанной позиции
void say_sinie(int a, int b) //Напечатать синие с указанной позиции
void say_zelenie(int a, int b) //Напечатать зеленые с указанной позиции
void say_neitral(int a, int b) //Напечатать точка нейтральна с указанной позиции
void zahvat(int a) //Функция захвата точки стороной а
void if_btn() //Функция проверки нажатия кнопки