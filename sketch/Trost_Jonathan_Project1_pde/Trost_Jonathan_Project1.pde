import controlP5.*;

ControlP5 UI;
Button StartButton;
Slider IterationsSlider;
Slider StepCountSlider;
Toggle ColorChange;
Toggle ImmediateExecution;

// Screen Control variables
int SCREEN_X = 800;
int SCREEN_Y = 800;
float POINT_X = 400.0;
float POINT_Y = 400.0;

// Walk variables
int iterations = 0;
int stepCount =  0;
float arryPoint[] = {POINT_X, POINT_Y};

// UI size and position variables
int counter = 0;
int heightUI = 30;
int barLengthUI = 380;
int startButtonLength = 50;

int startPosX = 10;
int startPosY = 10;
int sliderPosX = 200;
int togglePosX = 70;

int fontSize = 15;
int toggleLabelOffset = 5;


void setup() {
  size(800, 800);
  UI = new ControlP5(this);
  background(135, 206, 235);
  setUpUI(UI);
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

void setUpUI( ControlP5 ui) {
  StartButton = ui.addButton("Start")
    .setPosition(startPosX, startPosY)
    .setSize(startButtonLength, heightUI)
    ;
  StartButton.getCaptionLabel().setSize(fontSize);
  
  IterationsSlider = ui.addSlider("Iterations")
    .setPosition(sliderPosX, startPosY)
    .setSize(barLengthUI, heightUI)
    .setRange(1000, 500000)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  IterationsSlider.getCaptionLabel().setSize(fontSize);
  IterationsSlider.getValueLabel().setSize(fontSize);

  StepCountSlider = ui.addSlider("Step Count")
    .setPosition(sliderPosX, startPosY + heightUI)
    .setSize(barLengthUI, heightUI)
    .setRange(1,1000)
    .setDecimalPrecision(0)
    .setValue(1)
    ;
  StepCountSlider.getCaptionLabel().setSize(fontSize);
  StepCountSlider.getValueLabel().setSize(fontSize);

  ColorChange = ui.addToggle("Color")
    .setPosition(togglePosX, startPosY)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  ColorChange.getCaptionLabel().setSize(fontSize);
  ColorChange.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

  ImmediateExecution = ui.addToggle("Gradual")
    .setPosition(togglePosX, startPosY + heightUI)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  ImmediateExecution.getCaptionLabel().setSize(fontSize);
  ImmediateExecution.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));
}
