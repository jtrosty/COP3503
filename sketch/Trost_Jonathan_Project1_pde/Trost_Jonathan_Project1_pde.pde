import controlP5.*;

ControlP5 UI;
Button StartButton;
Slider IterationsSlider;
Slider StepCountSlider;
Toggle ColorChange;
Toggle ImmediateExecution;

int SCREEN_X = 800;
int SCREEN_Y = 800;
float POINT_X = 400.0;
float POINT_Y = 400.0;
boolean play = true;
int iterations = 0;
float arryPoint[] = {POINT_X, POINT_Y};
int stepCount =  0;
int counter = 0;


void setup() {
  size(800, 800);
  UI = new ControlP5(this);
  background(135, 206, 235);
  pixelDensity(displayDensity());
  StartButton = UI.addButton("Start")
    .setPosition(10,10)
    .setSize(50,30)
    ;
  IterationsSlider = UI.addSlider("Iterations")
    .setPosition(200,10)
    .setSize(350, 30)
    .setRange(1000, 500000)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  StepCountSlider = UI.addSlider("Step Count")
    .setPosition(200,40)
    .setSize(350, 30)
    .setRange(1,1000)
    .setDecimalPrecision(0)
    .setValue(1)
    ;
  ColorChange = UI.addToggle("Color")
    .setPosition(70, 10)
    .setSize(50, 30)
    .setValue(true)
    ;
  ImmediateExecution = UI.addToggle("Gradual")
    .setPosition(130, 10)
    .setSize(50, 30)
    .setValue(true)
    ;
}

void draw() {
  stroke(0);
  if (counter < iterations) {
    for (int i = 0; i < stepCount; i++) {
      if (ColorChange.getState()) {
          float mappedColor = map(counter, 0, iterations, 0, 255);
          stroke(mappedColor);
      }

      arryPoint = getNextPoint(arryPoint[0], arryPoint[1], SCREEN_X, SCREEN_Y);
      point(arryPoint[0], arryPoint[1]);
      counter++;
    }
  }
  else {
    // Stop drawing
  }
}

public void controlEvent(ControlEvent event) {
  event.getController().getName();
}

public void Start() {
  clear();
  background(135, 206, 235);
  reset();
  iterations = int(IterationsSlider.getValue());
  if (ImmediateExecution.getState()) {
    stepCount = iterations;
  }
  else {
    stepCount = int(StepCountSlider.getValue());
  }
}

void reset() {
  counter = 0;
  arryPoint[0] = 400.0;
  arryPoint[1] = 400.0;
}

float clamp(float value, float min, float max) {
  if (value > max)          return max;
  else if (value < min)     return min;
  else                      return value;
}

float[] getNextPoint(float x, float y, float screenX, float screenY) {
  int randDir = int((random(4)));
  float result[] = {x, y};
  switch (randDir) {
    case 0:
      // Go Up
      result[1] = clamp(y + 1, 0, screenY);
      break;
    case 1:
      // Go Right
      result[0] = clamp(x + 1, 0, screenX);
      break;
    case 2:
      // Go down
      result[1] = clamp(y - 1, 0, screenY);
      break;
    case 3:
      // Go Left
      result[0] = clamp(x - 1, 0, screenX);
      break;
  }
  return result;
}
