# Вариант(ы) 1

## Лабораторная работа 1

<p>
Группа 1. Вывести числа начиная с -100 до 100 по середине экрана без ведущих нулей с шагом в 1 и паузой в 0.15 секунду;

Группа 2. Вывести вещественные числа (1 разряда на целую, 2 на дробную часть, первый разряд под знак) с -2 до 2 с шагом 0.2 и паузой в 1 секунду;

Группа 3. Вывести текст в любом регистре `hello node` текст зациклить с сдвигом на 1 символ раз в 1
секунду.
</p>

```arduino
#include <TM1637Display.h>

#define CLK 13
#define DIO 12

#define SYM_SPACE  0b00000000
#define SYM_MINUS  SEG_G
#define SYM_H      SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
#define SYM_E      SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
#define SYM_L      SEG_D | SEG_E | SEG_F
#define SYM_O      SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F
#define SYM_N      SEG_A | SEG_B | SEG_F | SEG_E | SEG_C
#define SYM_D      SEG_B | SEG_C | SEG_D | SEG_E | SEG_G

const int DELAY_PART1 = 150;
const int DELAY_PART2 = 1000;
const int DELAY_PART3 = 1000;

TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
	display.setBrightness(7);
}


void loop() {
  part1();
  part2();
  part3();
}

void part1() {
  int n = -100;
  while(n != 100) {
    display.showNumberDec(n++);
    delay(DELAY_PART1);
  }
  display.clear();
}

void part2() {
    const uint8_t minus[] = { SYM_MINUS };

    for (int i = -200; i <= 200; i += 20) {
        display.clear();
        display.showNumberDecEx(abs(i), 0b01000000, true, 3, 1);
        if (i < 0) {
            display.setSegments(minus, 1);
        }
        delay(DELAY_PART2);
    }
	
	display.clear();
}

void part3() {
  uint8_t text[] = { 
    SYM_SPACE, SYM_SPACE, SYM_SPACE, SYM_SPACE, 
    SYM_H, SYM_E, SYM_L, SYM_L, SYM_O, 
    SYM_SPACE, SYM_N, SYM_O, SYM_D, SYM_E, 
    SYM_SPACE, SYM_SPACE, SYM_SPACE, SYM_SPACE
  };
  
  uint8_t textBound = sizeof(text) - 4;
  uint8_t i = 0;

  while (true) {
    display.setSegments(text + i); // i - pointer to text[] (.setSegments() consumes first 4 uint8_t[] entries)
    i = ++i % textBound; // i - must be within 'textBound'
    delay(DELAY_PART3);
  }
}
```
</br></br>

## Лабораторная работа 2

<p>
Выводить температуру в цельсияю и влажность на 4-х цифровой экран по очереди с паузой в 2
секунды, вывод в формате значение (2 знака), пояснение (2 знака).
</p>

```arduino
#include <TM1637Display.h>
#include <DHT.h>

#define CLK 1
#define DIO 2

#define DHTPIN 3
#define DHTTYPE DHT22 

#define SYM_C SEG_D | SEG_E | SEG_F | SEG_A
#define SYM_O SEG_A | SEG_B | SEG_F | SEG_G
#define SYM_o SEG_C | SEG_D | SEG_E | SEG_G

TM1637Display display = TM1637Display(CLK, DIO);
DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  display.setBrightness(7);
  dht.begin();
}

void loop() {
  uint8_t segTemperature[] = { SYM_O, SYM_C };
  float temperature = dht.readTemperature();

  display.showNumberDec(temperature, false, 2);
  display.setSegments(segTemperature, 2, 2);
  delay(2000);

  uint8_t segHumidity[] = { SYM_o, SYM_O };
  float humidity = dht.readHumidity();

  display.showNumberDec(humidity, false, 2);
  display.setSegments(segHumidity, 2, 2);
  delay(2000);

  display.clear();
}

```
</br></br>

## Лабораторная работа 3

<p>
Ход работы:

1. Реализовать библиотеку для работы с матричной клавиатурой 4*4
2. Реализовать меню из 3-х пунктов
    1. вычислитель
    2. память
    3. сброс
3. Переключение между пунктами меню на клавиатуре, на экране выводится текущий пункт в
верхней строке и значение из него в нижней.
4. Вход в меню доступен только для пунктов 1 и 3, в первом математическая операция (смотри свой
вариант) и команда записи в память, во втором вывод текущего состояния памяти, в 3-ем при
входе написать выхотите сбросить память и 2 варианта ответа (например A - Да, B - Нет)

Варианты:
1. логическое ИЛИ
2. логическое ИСКЛЮЧАЮЩИЕ ИЛИ
3. логическое И
Пока пользователь находится в основном меню, постаянного опроса клавиатуры не делать,
переключение между пунктами меню осуществлять за счет обработки прерываний клавиатуры. Для
вычислений допустимы следующие действия ввод значения с клавиатуры, загрузка из памяти (должен быть вычитан при старте программы, что бы постаянно не обращаться к ней), для полученного
результата вычислений должна быть возможность сохранить его в память (по желанию пользователя).
</p>

```arduino
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include "MatrixKeypad.h"

#define MAX_INT_VALUE 2147483647

const byte ROWS_PINS[4] = { 46, 47, 48, 49 };
const byte COLS_PINS[4] = { 50, 51, 52, 53 };

long memory = 0, num1 = 0, num2 = 0, calcResult = 0;
byte currentStep = 0;
bool resultDisplayed = false;

char pressedKey = NO_PRESS, selectedOperation = NO_PRESS;

LiquidCrystal_I2C lcd(0x27, 16, 2);
MatrixKeypad keypad(ROWS_PINS, COLS_PINS);

void updateDisplay(const String &line1 = "", const String &line2 = "") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}

void resetCalculator() {
    num1 = 0;
    num2 = 0;
    selectedOperation = NO_PRESS;
    calcResult = 0;
    currentStep = 0;
    resultDisplayed = false;
}

void handleNumberInput(long &target, byte digit) {
    if (target < MAX_INT_VALUE / 10) {
        target = target * 10 + digit;
    }
}

void performCalculation() {
    switch (selectedOperation) {
        case '+': calcResult = num1 + num2; break;
        case '-': calcResult = num1 - num2; break;
        case '*': calcResult = num1 * num2; break;
        case '/': calcResult = (num2 != 0) ? num1 / num2 : 0; break;
        default: calcResult = 0; break;
    }
}

void processKeyPress(char key) {
    if (isdigit(key)) {
        if (resultDisplayed) { 
            resetCalculator();
        }
        handleNumberInput((currentStep == 0) ? num1 : num2, key - '0');
        updateDisplay(String(num1), (currentStep == 0) ? "" : String(num2));

    } else if (key == '#') {
        if (resultDisplayed) {
            memory = calcResult;
            EEPROM.put(0, memory);
            updateDisplay("Saved to memory", String(calcResult));
        } else if (currentStep == 1 && num2 == 0) {
            num2 = memory;
            updateDisplay(String(num1), String(num2));
        } else if (currentStep == 0 && num1 == 0) {
            num1 = memory;
            updateDisplay(String(num1), String(selectedOperation));
        } else if (currentStep == 1) {
            performCalculation();
            updateDisplay("= " + String(calcResult), "");
            resultDisplayed = true;
        }

    } else if (key == '*') {
        resetCalculator();
        updateDisplay("A+ B- C* D/ #=", String(memory));
        return;

    } else if (key >= 'A' && key <= 'D' && currentStep == 0) {
        if (resultDisplayed) {
            num1 = calcResult;
            resultDisplayed = false;
        }
        selectedOperation = (key == 'A') ? '+' : (key == 'B') ? '-' : (key == 'C') ? '*' : '/';
        currentStep = 1;
        updateDisplay(String(num1), String(selectedOperation));
    }
}

void setup() {
    lcd.init();
    lcd.backlight();
    EEPROM.get(0, memory);
    updateDisplay("A+ B- C* D/ #=", String(memory));
}

void loop() {
    pressedKey = keypad.scanKey();
    if (pressedKey != NO_PRESS) {
        processKeyPress(pressedKey);
    }
}
```

"Matrix.h"
```h
#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include <Arduino.h>

#define ROWS 4
#define COLUMNS 4
#define NO_PRESS '\0'
#define DEBOUNCE_TIME 50

class MatrixKeypad {
public:
    MatrixKeypad(const byte* rowPins, const byte* colPins);
    ~MatrixKeypad();
    char scanKey();

private:
    const byte* _rowPins;
    const byte* _colPins;
    const char _keyMapping[ROWS * COLUMNS] = {
        '1', '2', '3', 'A',
        '4', '5', '6', 'B',
        '7', '8', '9', 'C',
        '*', '0', '#', 'D'
    };
    unsigned long _lastPressTime = 0;

    void setRowPinsOutput();
    void resetColPins();
};

#endif
```

"Matrix.cpp"
```cpp
#include "MatrixKeypad.h"

MatrixKeypad::MatrixKeypad(const byte* rowPins, const byte* colPins)
    : _rowPins(rowPins), _colPins(colPins) {
    for (byte i = 0; i < ROWS; i++) {
        pinMode(_rowPins[i], OUTPUT);
        digitalWrite(_rowPins[i], HIGH);
    }

    for (byte j = 0; j < COLUMNS; j++) {
        pinMode(_colPins[j], INPUT_PULLUP);
    }
}

MatrixKeypad::~MatrixKeypad() {
    // ������ �� ����� �������, ��� ��� ������� ���������� �����
}

char MatrixKeypad::scanKey() {
    for (byte row = 0; row < ROWS; row++) {
        digitalWrite(_rowPins[row], LOW);

        for (byte col = 0; col < COLUMNS; col++) {
            if (digitalRead(_colPins[col]) == LOW) {
                // �������� �� �������
                if (millis() - _lastPressTime > DEBOUNCE_TIME) {
                    _lastPressTime = millis();
                    while (digitalRead(_colPins[col]) == LOW); // ���� ���������� ������

                    resetColPins(); // ��������������� ���������
                    return _keyMapping[row * COLUMNS + col];
                }
            }
        }

        digitalWrite(_rowPins[row], HIGH); // ���������� ������
    }
    return NO_PRESS; // ���� ������ �� ������
}

void MatrixKeypad::setRowPinsOutput() {
    for (byte i = 0; i < ROWS; i++) {
        pinMode(_rowPins[i], OUTPUT);
        digitalWrite(_rowPins[i], HIGH);
    }
}

void MatrixKeypad::resetColPins() {
    for (byte i = 0; i < COLUMNS; i++) {
        digitalWrite(_colPins[i], HIGH);
    }
}

```