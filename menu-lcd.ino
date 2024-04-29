#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>
#include <Wire.h>

// Custom variables
#define TABLE_NUM_BIN 1111

// PINS
#define PIN_D0 16
#define PIN_D1 5
#define PIN_D2 4
#define PIN_D3 0  // DO NOT USE / prevent EPROM flash
// NB: j'aurais du la souder celle la !!!!
#define PIN_D4 2  // DO NOT USE / builtin led ?
#define PIN_D5 14
#define PIN_D6 12
#define PIN_D7 13
#define PIN_D8 15
#define PIN_RX 3  // DO NOT USE / USB com
#define PIN_TX 1  // DO NOT USE / USB com

// LCD display
#define LCD_SDA PIN_D2
#define LCD_SCL PIN_D1
#define LCD_BRIGHT_PIN PIN_D7
#define LCD_BRIGHTNESS 64
LiquidCrystal_I2C lcd(0x27, 20, 4);
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};

// 4 digits (7 segments)
#define DIGIT_CLK PIN_D5
#define DIGIT_DIO PIN_D6
TM1637Display display(DIGIT_CLK, DIGIT_DIO);
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
const uint8_t seg_chenille[][4] = {
  {SEG_A, SEG_A, SEG_A, SEG_A},
  {SEG_B, SEG_B, SEG_B, SEG_B},
  {SEG_C, SEG_C, SEG_C, SEG_C},
  {SEG_D, SEG_D, SEG_D, SEG_D},
  {SEG_E, SEG_E, SEG_E, SEG_E},
  {SEG_F, SEG_F, SEG_F, SEG_F}
};

void delayChenille(unsigned long ms) {
  unsigned long tend = millis() + ms;
  do {
    display.setSegments(seg_chenille[(millis()/200)%6], 4, 0);
    delay(50);
  } while(millis() < tend);
}

void simulateBoot() {
  display.setSegments(data);
  lcd.clear();
  delayChenille(1000);
  lcd.setCursor(0, 0);
  lcd.print("Booting CED/OS v0.99");
  delayChenille(1000);
  lcd.setCursor(0, 1);
  //         12345678901234567890
  lcd.print("ESP2688/D1MINI....");
  delayChenille(700);
  lcd.print("OK");
  delayChenille(300);
  lcd.setCursor(0, 2);
  //         12345678901234567890
  lcd.print("8D7S:TM1637+I2C...");
  delayChenille(700);
  lcd.print("OK");
  delayChenille(300);
  lcd.setCursor(0, 3);
  //         12345678901234567890
  lcd.print("LCD/HD44780+I2C...");
  delayChenille(700);
  lcd.print("OK");
  delayChenille(1000);
  display.clear();
}

void setup() {
  // INIT LCD
  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  lcd.createChar(3, heart);
  analogWriteRange(255);
  analogWrite(LCD_BRIGHT_PIN, LCD_BRIGHTNESS);
  
  // 4 digit brightness
  display.setBrightness(1, true);

  // Fun self test
  simulateBoot();

  // Table number on display
  display.showNumberDec(TABLE_NUM_BIN, true);
}

void displayPage1() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("CEDRIC ");
  lcd.write(3);
  lcd.print(" MARIE");
  lcd.setCursor(0, 2);
  lcd.print(" MARIAGE 27/04/2024");
}

void displayPage2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //         12345678901234567890
  lcd.print("       ENTREE");
  lcd.setCursor(0, 1);
  lcd.print("Foie gras et magret,");
  lcd.setCursor(0, 2);
  lcd.print("compotee de figues");
  lcd.setCursor(0, 3);
  lcd.print("et pain d'epices");
}

void displayPage3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //         12345678901234567890
  lcd.print("     INTERLUDE");
  lcd.setCursor(0, 1);
  lcd.print("    Trou lorrain");
  lcd.setCursor(0, 2);
  lcd.print("Eau de vie mirabelle");
  lcd.setCursor(0, 3);
  lcd.print("et sorbet mirabelle");
}

void displayPage4() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //         12345678901234567890
  lcd.print("   PLAT PRINCIPAL");
  lcd.setCursor(0, 1);
  lcd.print("Veau sauce morilles");
  lcd.setCursor(0, 2);
  lcd.print("Ecrase de PdT");
  lcd.setCursor(0, 3);
  lcd.print("Legumes glaces");
}

void displayPage5() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //         12345678901234567890
  lcd.print("PLATEAU DE FROMAGES");
  lcd.setCursor(0, 1);
  lcd.print("Crottin de chevre");
  lcd.setCursor(0, 2);
  lcd.print("Brie de Meaux, Comte");
  lcd.setCursor(0, 3);
  lcd.print("Munster, Fourme");
}

void displayPage6() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //         12345678901234567890
  lcd.print("      DESSERTS");
  lcd.setCursor(0, 1);
  lcd.print("Entremet 3 chocolats");
  lcd.setCursor(0, 2);
  lcd.print("Entremet fraise");
  lcd.setCursor(0, 3);
  lcd.print("Chou caramel vanille");
}

void loop() {
  displayPage1();
  delay(6000);
  displayPage2();
  delay(6000);
  displayPage3();
  delay(6000);
  displayPage4();
  delay(6000);
  displayPage5();
  delay(6000);
  displayPage6();
  delay(6000);
}
