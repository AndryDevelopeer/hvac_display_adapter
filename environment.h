#pragma once

#define SERIAL_SPEED 115200

// эта херня у него вобще не подключена
// the pin must support external interrupts
#define DISPLAY_EMULATOR_CE 2 // это типо ресет?

// ============================================ это все что нужно ======================================================
// это походу на дисплей
// нужно сбрасывать дисплей при инициализации
//#define DISPLAY_RST 9 D4 Блок дополнительного дисплея аудиосистемы HVAC (SUB DISP RST)
#define DISPLAY_CLOCK 3 // D5 PUR Блок дополнительного дисплея аудиосистемы HVAC (SUB DISP CLOCK) резистор 220 Ом
#define DISPLAY_DATA 4 // D6 ORN Блок дополнительного дисплея аудиосистемы HVAC (SUB DISP DATA) резистор 220 Ом
#define DISPLAY_CE 5 // D7 BLU Блок дополнительного дисплея аудиосистемы HVAC (SUB DISP CE) резистор 220 Ом

// это с климата
#define HVAC_CLOCK 7 // E4 RED Блок климат-контроля (DISP CLK) резистор 220 Ом
#define HVAC_DATA 8 //E5 YEL Блок климат-контроля (AC SO) резистор 220 Ом

// clock module
#define RTC_CLOCK A1 // CLK
#define RTC_DATA A2 // DATA
#define RTC_CE A3 // RST
#define RTC_BUTTON 11 // set time button
// ============================================ это все что нужно ======================================================

// дальше хз для чего
#define REVERSING_PIN A0 // D10 LT GRN Блок дополнительного дисплея аудиосистемы HVAC (SUB DISP LCD BL+) ? или D9 BL-?

// вот эта шляпа вобще ненужна, надо посмотреть что оно не ломает двухзонный вывод климата
#define ONE_WIRE_PIN 6 // датчик температуры? он вроде как на другом дисплее
#define TEMP_SENSOR_ADDRESS {0x28, 0x2F, 0x17, 0x3D, 0x26, 0x20, 0x01, 0xAE} // это походу просто адрес датчика

// походу это для доп кнопок на руле, если только есть доп кнопки слева
#define AUDIO_SW_PIN 9 // вроде как вобще не используется, похоже что включение от магнитолы?
#define HFT_SW_PIN 10 // что то для кнопок на руле? B6 B7?
