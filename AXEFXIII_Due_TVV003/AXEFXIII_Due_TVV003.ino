#include <SPI.h>
#include <AxeFxControl.h>

#include "ILI9341_due_config.h"
#include "ILI9341_due.h"
#include "SystemFont5x7.h"
#include "Arial14.h"
#include "Arial_bold_14.h"

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10

// Color set
#define BLACK           0x0000
#define RED             0xF800
#define GREEN           0x07E0
#define BLUE            0x001F
#define BLUE            0x102E
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define ORANGE          0xFD20
#define GREENYELLOW     0xAFE5
#define DARKGREEN       0x03E0
#define WHITE           0xFFFF

uint16_t  color;
uint16_t  colorFONDO = BLACK;

AxeSystem Axe;

unsigned long my_time;

ILI9341_due tft = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);

const int bankUP = 50;
const int bankDOWN = 49;
const int presetUP = 46;
const int presetDOWN = 47;
const int sceneUP = 51;
const int sceneDOWN = 48;
const int P1 = 43;
const int P2 = 39;
const int P3 = 35;
const int P4 = 34;
const int P5 = 45;
const int P6 = 41;
const int P7 = 36;
const int P8 = 37;
const int drive1 = 52;
const int delay1 = 53;
const int reverb1 = 44;
const int pitch1 = 42;
const int tuner = 40;
const int tempoTap = 38;

// variables will change:
int cs_bankUP = 0;  // currrent state
int ps_bankUP = 0;  // previous state
unsigned long bd_bankUP = 0;  // button duration
unsigned long bs_bankUP = 0;  // button start

int cs_bankDOWN = 0;  // currrent state
int ps_bankDOWN = 0;  // previous state
unsigned long bd_bankDOWN = 0;  // button duration
unsigned long bs_bankDOWN = 0;  // button start

int cs_presetUP = 0;  // currrent state
int ps_presetUP = 0;  // previous state
unsigned long bd_presetUP = 0;  // button duration
unsigned long bs_presetUP = 0;  // button start

int cs_presetDOWN = 0;  // currrent state
int ps_presetDOWN = 0;  // previous state
unsigned long bd_presetDOWN = 0;  // button duration
unsigned long bs_presetDOWN = 0;  // button start

int cs_sceneUP = 0;  // currrent state
int ps_sceneUP = 0;  // previous state
unsigned long bd_sceneUP = 0;  // button duration
unsigned long bs_sceneUP = 0;  // button start

int cs_sceneDOWN = 0;  // currrent state
int ps_sceneDOWN = 0;  // previous state
unsigned long bd_sceneDOWN = 0;  // button duration
unsigned long bs_sceneDOWN = 0;  // button start

int cs_P1 = 0;  // currrent state
int ps_P1 = 0;  // previous state
unsigned long bd_P1 = 0;  // button duration
unsigned long bs_P1 = 0;  // button start

int cs_P2 = 0;  // currrent state
int ps_P2 = 0;  // previous state
unsigned long bd_P2 = 0;  // button duration
unsigned long bs_P2 = 0;  // button start

int cs_P3 = 0;  // currrent state
int ps_P3 = 0;  // previous state
unsigned long bd_P3 = 0;  // button duration
unsigned long bs_P3 = 0;  // button start

int cs_P4 = 0;  // currrent state
int ps_P4 = 0;  // previous state
unsigned long bd_P4 = 0;  // button duration
unsigned long bs_P4 = 0;  // button start

int cs_P5 = 0;  // currrent state
int ps_P5 = 0;  // previous state
unsigned long bd_P5 = 0;  // button duration
unsigned long bs_P5 = 0;  // button start

int cs_P6 = 0;  // currrent state
int ps_P6 = 0;  // previous state
unsigned long bd_P6 = 0;  // button duration
unsigned long bs_P6 = 0;  // button start

int cs_P7 = 0;  // currrent state
int ps_P7 = 0;  // previous state
unsigned long bd_P7 = 0;  // button duration
unsigned long bs_P7 = 0;  // button start

int cs_P8 = 0;  // currrent state
int ps_P8 = 0;  // previous state
unsigned long bd_P8 = 0;  // button duration
unsigned long bs_P8 = 0;  // button start

int cs_drive1 = 0;  // currrent state
int ps_drive1 = 0;  // previous state
unsigned long bd_drive1 = 0;  // button duration
unsigned long bs_drive1 = 0;  // button start

int cs_delay1 = 0;  // currrent state
int ps_delay1 = 0;  // previous state
unsigned long bd_delay1 = 0;  // button duration
unsigned long bs_delay1 = 0;  // button start

int cs_reverb1 = 0;  // currrent state
int ps_reverb1 = 0;  // previous state
unsigned long bd_reverb1 = 0;  // button duration
unsigned long bs_reverb1 = 0;  // button start

int cs_pitch1 = 0;  // currrent state
int ps_pitch1 = 0;  // previous state
unsigned long bd_pitch1 = 0;  // button duration
unsigned long bs_pitch1 = 0;  // button start

int cs_tuner = 0;  // currrent state
int ps_tuner = 0;  // previous state
unsigned long bd_tuner = 0;  // button duration
unsigned long bs_tuner = 0;  // button start

int cs_tempoTap = 0;  // currrent state
int ps_tempoTap = 0;  // previous state
unsigned long bd_tempoTap = 0;  // button duration
unsigned long bs_tempoTap = 0;  // button start


void setup() {
  Serial.begin(38400);        // start serial for output
  delay(250);

  pinMode(bankUP, INPUT_PULLUP);
  pinMode(bankDOWN, INPUT_PULLUP);
  pinMode(presetUP, INPUT_PULLUP);
  pinMode(presetDOWN, INPUT_PULLUP);
  pinMode(sceneUP, INPUT_PULLUP);
  pinMode(sceneDOWN, INPUT_PULLUP);
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
  pinMode(P4, INPUT_PULLUP);
  pinMode(P5, INPUT_PULLUP);
  pinMode(P6, INPUT_PULLUP);
  pinMode(P7, INPUT_PULLUP);
  pinMode(P8, INPUT_PULLUP);
  pinMode(drive1, INPUT_PULLUP);
  pinMode(delay1, INPUT_PULLUP);
  pinMode(reverb1, INPUT_PULLUP);
  pinMode(pitch1, INPUT_PULLUP);
  pinMode(tuner, INPUT_PULLUP);
  pinMode(tempoTap, INPUT_PULLUP);

  my_time = millis();

  tft.begin();
  tft.setRotation(iliRotation270);
  tft.fillScreen(colorFONDO);
  tft.setFont(Arial_bold_14);

  tft.setTextScale(2);
  tft.fillRect(0, 0, 320, 30, RED);
  tft.setTextColor(WHITE, RED);
  tft.printAt(F("AXE-FX III MIDI CTRL"), 5, 3);

  Axe.begin(Serial1, 1);
  Axe.registerPresetChangeCallback(onPresetChange);
  Axe.registerSystemChangeCallback(onSystemChange);
  Axe.requestPresetDetails();
}

void loop() {
  Axe.update();

  static PresetNumber preset = 0;
  if (preset >= AxeSystem::MAX_PRESETS) {
    preset = 0;
  }
  tft.setTextScale(1);
  tft.setTextColor(WHITE, BLACK);
  // Read the value of the input. It can either be 1 or 0
  cs_bankUP = digitalRead(bankUP);
  cs_bankDOWN = digitalRead(bankDOWN);
  cs_presetUP = digitalRead(presetUP);
  cs_presetDOWN = digitalRead(presetDOWN);
  cs_sceneUP = digitalRead(sceneUP);
  cs_sceneDOWN = digitalRead(sceneDOWN);
  cs_P1 = digitalRead(P1);
  cs_P2 = digitalRead(P2);
  cs_P3 = digitalRead(P3);
  cs_P4 = digitalRead(P4);
  cs_P5 = digitalRead(P5);
  cs_P6 = digitalRead(P6);
  cs_P7 = digitalRead(P7);
  cs_P8 = digitalRead(P8);
  cs_drive1 = digitalRead(drive1);
  cs_delay1 = digitalRead(delay1);
  cs_reverb1 = digitalRead(reverb1);
  cs_pitch1 = digitalRead(pitch1);
  cs_tuner = digitalRead(tuner);
  cs_tempoTap = digitalRead(tempoTap);

  //Serial.println("Reading data ...");

  if (cs_bankUP == LOW) {
    ps_bankUP = 1;
  } else {
    if (ps_bankUP == 1) {
      if (presetNumber >= 375) {
        bankNumber = 0;
      } else {
        bankNumber += 1;
      }
      Axe.sendPresetChange((bankNumber * 8) + 0);
      delay(200);
      ps_bankUP = 0;
    }
  }
  if (cs_bankDOWN == LOW) {
    ps_bankDOWN = 1;
  } else {
    if (ps_bankDOWN == 1) {
      if (presetNumber <= 7) {
        bankNumber = 47;
      } else {
        bankNumber -= 1;
      }
      Axe.sendPresetChange((bankNumber * 8) + 0);
      delay(200);
      ps_bankDOWN = 0;
    }
  }

  if (buttonStateFC1 == LOW) {
    // If button FC1 pushed
    if (prevbuttonStateFC1 == 0) {
      buttonStartFC1 = millis();
      buttonDurationFC1 = buttonStartFC1;
      prevbuttonStateFC1 = 1;
    } else {
      buttonDurationFC1 = millis() - buttonStartFC1;
      prevbuttonStateFC1 = 1;
    }
    tft.printAt("Button FC1 pressed:", 0, 60);
    tft.printAt(String(buttonDurationFC1), 180, 60);
    tft.printAt(" ms.", 220, 60);
  } else {
    if (buttonDurationFC1 > 30 && buttonDurationFC1 < 500) {
      preset += 1;
      Axe.sendPresetChange(preset);
      delay(100);
    }
    // Otherwise
    buttonDurationFC1 = 0;
    prevbuttonStateFC1 = 0;
    buttonStartFC1 = 0;
    tft.printAt("Button FC1 released.                 ", 0, 60);
  }
  if (buttonStateFC3 == LOW) {
    // If button FC3 pushed
    if (prevbuttonStateFC3 == 0) {
      buttonStartFC3 = millis();
      buttonDurationFC3 = buttonStartFC1;
      prevbuttonStateFC3 = 1;
    } else {
      buttonDurationFC3 = millis() - buttonStartFC3;
      prevbuttonStateFC3 = 1;
    }
    tft.printAt("Button FC3 pressed:", 0, 80);
    tft.printAt(String(buttonDurationFC3), 180, 80);
    tft.printAt(" ms.", 220, 80);
  } else {
    if (buttonDurationFC3 > 30 && buttonDurationFC3 < 500) {
      Axe.sendSceneIncrement();
      //delay(200);
      Axe.requestPresetDetails();
      //delay(200);
    }
    // Otherwise
    buttonDurationFC3 = 0;
    prevbuttonStateFC3 = 0;
    buttonStartFC3 = 0;
    tft.printAt("Button FC3 released.                 ", 0, 80);
  }
}

void onPresetChange(AxePreset preset) {

  const size_t sz = 150;
  char buf[sz];

  //Preset/scene names with % in them will not print to debug properly
  //AxeSystem has notified that all requested information has arrived!

  tft.setTextScale(2);
  tft.setTextColor(WHITE, RED);
  tft.cursorToXY(100, 3);
  tft.print("P");
  tft.cursorToXY(120, 3);
  String my_preset = "";
  if ((preset.getPresetNumber() + 1) < 10) {
    my_preset = my_preset + "00" + (preset.getPresetNumber() + 1) + " ";
  } else if (((preset.getPresetNumber() + 1) >= 10) && ((preset.getPresetNumber() + 1) < 100)) {
    my_preset = my_preset + "0" + (preset.getPresetNumber() + 1) + " ";
  } else {
    my_preset = my_preset + preset.getPresetNumber() + 1 + " ";
  }
  tft.print(my_preset);
  tft.cursorToXY(230, 3);
  tft.print("S");
  tft.cursorToXY(250, 3);
  tft.print(preset.getSceneNumber());

  tft.setTextScale(1);
  tft.setTextColor(WHITE, BLACK);
  //You can print directly to a Print object
  tft.cursorToXY(0, 120);
  tft.print("P: ");
  Serial.print("Preset name: ");
  preset.printPresetName(Serial, true);
  preset.printPresetName(tft, true);

  Serial.print("Scene number: ");
  Serial.println(preset.getSceneNumber());

  //Or you can get the name into a buffer
  Serial.print("Scene name: ");
  preset.copySceneName(buf, sz);
  Serial.println(buf);
  tft.cursorToXY(0, 140);
  tft.print("S: ");
  tft.print(buf);

  Serial.print("Looper status: ");
  snprintf(buf, sz,
           "record[%d] play[%d] overdub[%d] once[%d] reverse[%d] halfspeed[%d]",
           Axe.getLooper().isRecord(),
           Axe.getLooper().isPlay(),
           Axe.getLooper().isOverdub(),
           Axe.getLooper().isOnce(),
           Axe.getLooper().isReverse(),
           Axe.getLooper().isHalfSpeed()
          );
  Serial.println(buf);

  const size_t tagSz = 10;
  char tag[tagSz];

  snprintf(buf, sz, "Effects[%d]: ", preset.getEffectCount());
  Serial.println(buf);

  for (EffectIndex index = 0; index < preset.getEffectCount(); index++) {
    AxeEffect effect = preset.getEffectAt(index);
    effect.copyEffectTag(tag, tagSz);
    char engaged = effect.isBypassed() ? ' ' : 'X';
    snprintf(buf, sz, "%s(ch:%c) [%c]", tag, effect.getChannelChar(), engaged);
    Serial.println(buf);
  }
}

void onSystemChange() {
  my_time = millis();
}
