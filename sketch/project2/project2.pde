import controlP5.*;


int SCREEN_X = 1200;
int SCREEN_Y = 800;
float POINT_X = (float) (SCREEN_X / 2);
float POINT_Y = (float) (SCREEN_Y / 2);
boolean play = true;

// Walk variables
float arryPoint[] = {POINT_X, POINT_Y};


void setup() {
  size(1200, 800);
  pixelDensity(displayDensity());

  resetBackground();

  ControlP5 UI;
  UI = new ControlP5(this);
  RandWalkData data = new RandWalkData();
  UserControls userControls = new UserControls(UI, data);
}

void resetBackground() {
  background(135, 206, 235);
  fill(90);
  rect(0, 0, 200, 800);
}

void draw() {
  stroke(0);
  /*
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
  */
}

class RandomWalk {
  Update();
  Draw();
  RandWalkData data;

  RandWalkData(RandWalkData _data) {
    data =  _data;
  }
}

class SquareWalk extends RandomWalk {

}

class HexagonWalk extends RandomWalk {

}

public void controlEvent(ControlEvent event) {
  event.getController().getName();
}


void reset() {
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

class RandWalkData {
  int maxSteps = 100;
  int stepRate = 1;
  int stepSize = 10;
  float stepScale = 1.0f;
  boolean constrainStep = false;
  boolean simTerrain = false;
  boolean useStroke = false;
  boolean useRandSeed = false;
  int randSeed = 0;

  // I don't think I need this
  // TODO: Delete
  int tempMaxSteps = 100;
  int tempStepRate = 1;
  int tempStepSize = 10;
  float tempStepScale = 1.0f;
  boolean tempConstrainStep = false;
  boolean tempSimTerratin = false;
  boolean tempUseStroke = false;
  boolean tempUseRandSeed = false;
  int     tempRandSeed = 0;
}

class UserControls {
  Button StartButton;
  DropdownList Shape;
  Slider MaxSteps;
  Slider StepRate;
  Slider StepSize;
  Slider StepScale;
  Toggle ConstrainStep;
  Toggle SimulateTerrain;
  Toggle UseStroke;
  Toggle UseRandomSeed;
  Textfield SeedValue;
  ControlP5 ui;
  RandWalkData data;

  // UI size and position variables
  int counter = 0;
  int heightUI = 30;
  int barLengthUI = 180;
  int shortBarLengthUI = barLengthUI / 3;
  int startButtonLength = 50;

  int startPosX = 10;
  int startPosY = 10;
  int dropBoxHeight = 30;

  int fontSize = 15;
  int toggleLabelOffset = 5;
  
  // User control run variables and temps

  // Constructor
  UserControls(ControlP5 _ui, RandWalkData _data) {
    ui = _ui;
    data = _data;
    setUpUI();
  }

  public void Start() {
    clear();
    resetBackground();
    data.maxSteps = int(MaxSteps.getValue());
    data.stepRate = int(StepRate.getValue());
    data.stepSize = int(StepSize.getValue());
    data.stepScale = int(StepScale.getValue());
    constrainStep = ConstrainStep.getState();
    simTerrain = SimulateTerrain.getState();
    useStroke = UseStroke.getState();
    useRandSeed = UseRandomSeed.getState();
    randSeed = int(SeedValue.getValue());
  }

  void setUpUI() {
    StartButton = ui.addButton("Start")
      .setPosition(startPosX, startPosY)
      .setSize(startButtonLength, heightUI)
      ;
    StartButton.getCaptionLabel().setSize(fontSize);

    Shape = ui.addDropdownList("Shape")
      .setPosition(startPosX, startPosY + heightUI + 20)
      .setSize(barLengthUI, heightUI * 3)
      .addItem("Square", 0)
      .addItem("Hexagon", 1)
      ;
    
    MaxSteps = ui.addSlider("Maximum Steps")
      .setPosition(startPosX, 200)
      .setSize(barLengthUI, heightUI)
      .setRange(100, 500000)
      .setDecimalPrecision(0)
      .setValue(1000)
      ;
    MaxSteps.getCaptionLabel().setSize(fontSize);
    MaxSteps.getValueLabel().setSize(fontSize);

    StepRate = ui.addSlider("Step Rate")
      .setPosition(startPosX, 250)
      .setSize(barLengthUI, heightUI)
      .setRange(1, 1000)
      .setDecimalPrecision(0)
      .setValue(1000)
      ;
    StepRate.getCaptionLabel().setSize(fontSize);
    StepRate.getValueLabel().setSize(fontSize);

    StepSize = ui.addSlider("Step Size")
      .setPosition(startPosX, 300)
      .setSize(shortBarLengthUI, heightUI)
      .setRange(10, 30)
      .setDecimalPrecision(0)
      .setValue(1000)
      ;
    StepSize.getCaptionLabel().setSize(fontSize);
    StepSize.getValueLabel().setSize(fontSize);

    StepScale = ui.addSlider("Step Scale")
      .setPosition(startPosX, 350)
      .setSize(shortBarLengthUI, heightUI)
      .setRange(1.0,1.5)
      .setDecimalPrecision(2)
      .setValue(1)
      ;
    StepScale.getCaptionLabel().setSize(fontSize);
    StepScale.getValueLabel().setSize(fontSize);

    ConstrainStep = ui.addToggle("ConstrainStep")
      .setPosition(startPosX, 450)
      .setSize(heightUI, heightUI)
      .setValue(true)
      ;
    ConstrainStep.getCaptionLabel().setSize(fontSize);
    ConstrainStep.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

    SimulateTerrain = ui.addToggle("Simulate Terrain")
      .setPosition(startPosX, 500)
      .setSize(heightUI, heightUI)
      .setValue(true)
      ;
    SimulateTerrain.getCaptionLabel().setSize(fontSize);
    SimulateTerrain.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

    UseStroke = ui.addToggle("Use Stroke")
      .setPosition(startPosX, 550)
      .setSize(heightUI, heightUI)
      .setValue(true)
      ;
    UseStroke.getCaptionLabel().setSize(fontSize);
    UseStroke.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

    UseRandomSeed = ui.addToggle("Use Random Seed")
      .setPosition(startPosX, 600)
      .setSize(heightUI, heightUI)
      .setValue(true)
      ;
    UseRandomSeed.getCaptionLabel().setSize(fontSize);
    UseRandomSeed.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

    SeedValue = ui.addTextfield("Seed Value")
      .setPosition(startPosX, 650)
      .setSize(heightUI, heightUI)
      ;
    SeedValue.getCaptionLabel().setSize(fontSize);
    SeedValue.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));
  }
}
