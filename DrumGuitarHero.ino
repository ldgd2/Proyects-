#include "UnoJoy.h"

#define PIEZO_THRESHOLD 50 // Umbral de sensibilidad del piezoeléctrico, ajusta según sea necesario
#define BUTTON_THRESHOLD 800 // Umbral para los botones pulsadores, ajusta según sea necesario

// Definición de los pines para los botones y los sensores
#define TRIANGLE_PIEZO_PIN A0    //Pad Amarillo
#define CIRCLE_PIEZO_PIN A1     //Pad Rojo
#define SQUARE_PIEZO_PIN A2     //Pad Azul
#define CROSS_PIEZO_PIN A3      //Pad Verde
#define L1_PIEZO_PIN A4         //Pad Naranja

#define DPAD_UP_BUTTON_PIN 2    //Arriba
#define DPAD_DOWN_BUTTON_PIN 3  //Abajo
#define START_BUTTON_PIN 4     //start
#define SELECT_BUTTON_PIN 5    //Select
#define L3_BUTTON_PIN 6       //Pedal

void setup() {
  setupPins();
  setupUnoJoy();
}

void loop() {
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void) {
  // Configurar pines digitales para los botones pulsadores como entradas con pull-up
  pinMode(DPAD_UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DPAD_DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(L3_BUTTON_PIN, INPUT_PULLUP);
}

dataForController_t getControllerData(void) {
  dataForController_t controllerData = getBlankDataForController();

  // Leer los valores de los pines analógicos para los sensores piezoeléctricos
  int trianglePiezoValue = analogRead(TRIANGLE_PIEZO_PIN);
  int circlePiezoValue = analogRead(CIRCLE_PIEZO_PIN);
  int squarePiezoValue = analogRead(SQUARE_PIEZO_PIN);
  int crossPiezoValue = analogRead(CROSS_PIEZO_PIN);
  int l1PiezoValue = analogRead(L1_PIEZO_PIN);

  // Verificar si se supera el umbral y establecer el estado de los botones correspondientes
  if (trianglePiezoValue >= PIEZO_THRESHOLD) {
    controllerData.triangleOn = true;
  }
  if (circlePiezoValue >= PIEZO_THRESHOLD) {
    controllerData.circleOn = true;
  }
  if (squarePiezoValue >= PIEZO_THRESHOLD) {
    controllerData.squareOn = true;
  }
  if (crossPiezoValue >= PIEZO_THRESHOLD) {
    controllerData.crossOn = true;
  }
  if (l1PiezoValue >= PIEZO_THRESHOLD) {
    controllerData.l1On = true;
  }

  // Leer el estado de los botones pulsadores y establecer el estado correspondiente
  if (digitalRead(DPAD_UP_BUTTON_PIN) == LOW) {
    controllerData.dpadUpOn = true;
  }
  if (digitalRead(DPAD_DOWN_BUTTON_PIN) == LOW) {
    controllerData.dpadDownOn = true;
  }
  if (digitalRead(START_BUTTON_PIN) == LOW) {
    controllerData.startOn = true;
  }
  if (digitalRead(SELECT_BUTTON_PIN) == LOW) {
    controllerData.selectOn = true;
  }
  if (digitalRead(L3_BUTTON_PIN) == LOW) {
    controllerData.l3On = true;
  }

  return controllerData;
}
