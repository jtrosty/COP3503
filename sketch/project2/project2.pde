import controlP5.*;
import java.util.Map;

int SCREEN_X = 1200;
int SCREEN_Y = 800;
float POINT_X = (float) (SCREEN_X / 2);
float POINT_Y = (float) (SCREEN_Y / 2);
boolean play = false;

// Walk variables
float arryPoint[] = {POINT_X, POINT_Y};

// Make objects
ControlP5 UI;
RandWalkData data = new RandWalkData();
RandomWalk walkObj = new RandomWalk();

// User Controls 
Button StartButton;
DropdownList ShapeList;
Slider MaxSteps;
Slider StepRate;
Slider StepSize;
Slider StepScale;
Toggle ConstrainStep;
Toggle SimulateTerrain;
Toggle UseStroke;
Toggle UseRandomSeed;
Textfield SeedValue;

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

//----------------------------------------------------------------------------------//

void setup() {
  size(1200, 800);
  pixelDensity(displayDensity());
  //pixelDensity(2);
  resetBackground(); 
  UI = new ControlP5(this);
  setUpUI();
}

void draw() {
  if (data.counter < data.maxSteps && (play == true)) {
    for (int i = 0; i < data.stepRate; i++) {
      walkObj.draw();
      walkObj.update();
    }
  }
}

//----------------------------------------------------------------------------------//

void resetBackground() {
  background(135, 206, 235);
  fill(90);
  rect(0, 0, 200, 800);
}

class RandomWalk {
  RandWalkData data;
  float currentPoint[] = {0.0f, 0.0f};
  float originX = 200.0f;
  float originY = 0.0f;
  float rightX = 1200.0f;
  float bottomY = 800.0f;
  HashMap<Vector2d, Integer> visited;

  void update() {}
  void draw() {}

}

float clamp(float value, float min, float max) {
  if (value > max)          return max;
  else if (value < min)     return min;
  else                      return value;
}

boolean wasClamp(float value, float min, float max) {
  if (value > max)          return true;
  else if (value < min)     return true;
  else                      return false;
}

class Vector2d {
  float x;
  float y;
  Vector2d(float _x, float _y) {
    x = _x;
    y = _y;
  }
}

class SquareWalk extends RandomWalk {

  SquareWalk(RandWalkData _data, float startX, float startY) {
    data =  _data;
    currentPoint[0] = startX;
    currentPoint[1] = startY;
    rectMode(CENTER);
  }

  void draw() {
    stroke(255);
    fill(0);
    if (visited.containsKery(Vector2d(currentPoint[0], currentPoint[1]))) {
      int timesVisited = visited.get(Vector2d(currentPoint[0], currentPoint[1]));
      timesVisited++;
      if (timesVisited > 1){
        fill(180);
      }
    }
    else {
      visited.put(Vector2d(currentPoint[0], currentPoint[1]), 0);
      fill(0);
    }
    square(currentPoint[0], currentPoint[1], data.stepSize);
    data.counter++;
  }

  void update() {
    currentPoint = getNextPoint(currentPoint[0], currentPoint[1], data.spacing, 1200, 800);
  }

  float[] getNextPoint(float x, float y, float spacing, float screenX, float screenY) {
    int randDir = int((random(4)));
    float result[] = {x, y};

    switch (randDir) {
      case 0:
        // Go Up
        if(!wasClamp(y - spacing, 0 + data.stepSize, screenY - (data.stepSize / 2))) {
          result[1] = y - spacing;
        }
        break;
      case 1:
        // Go Right
        if(!wasClamp(x + spacing, 200 + data.stepSize, screenX - (data.stepSize / 2))) {
          result[0] = x + spacing;
        }
        break;
      case 2:
        // Go down
        if(!wasClamp(y + spacing, 0 + data.stepSize, screenY - (data.stepSize / 2))) {
          result[1] = y + spacing;
        }
        break;
      case 3:
        // Go Left
        if(!wasClamp(x - spacing, 200 + data.stepSize, screenX - (data.stepSize / 2))) {
          result[0] = x - spacing;
        }
        break;
    }
    return result;
  }

}

/*
class HexagonWalk extends RandomWalk {

}
*/


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
  int counter = maxSteps;
  // 0 will be square, 1 will be hex
  int shapeType = -1;
  int spacing = 0;


  // I don't think I need this
  // TODO: Delete
  /*
  int tempMaxSteps = 100;
  int tempStepRate = 1;
  int tempStepSize = 10;
  float tempStepScale = 1.0f;
  boolean tempConstrainStep = false;
  boolean tempSimTerratin = false;
  boolean tempUseStroke = false;
  boolean tempUseRandSeed = false;
  int     tempRandSeed = 0;
  */
}

// User control run variables and temps

public void Start() {
  clear();
  resetBackground();
  data.maxSteps = int(MaxSteps.getValue());
  data.stepRate = int(StepRate.getValue());
  data.stepSize = int(StepSize.getValue());
  data.stepScale = StepScale.getValue();
  data.constrainStep = ConstrainStep.getState();
  data.simTerrain = SimulateTerrain.getState();
  data.useStroke = UseStroke.getState();
  data.useRandSeed = UseRandomSeed.getState();
  data.randSeed = int(SeedValue.getValue());
  data.shapeType = ShapeList.getId();
  data.counter = 0;
  data.spacing = int(float(data.stepSize) * data.stepScale);
  walkObj = new SquareWalk(data, 700, 400);
  play = true;
}

void setUpUI() {
  StartButton = UI.addButton("Start")
    .setPosition(startPosX, startPosY)
    .setSize(startButtonLength, heightUI)
    ;
  StartButton.getCaptionLabel().setSize(fontSize);

  ShapeList = UI.addDropdownList("Shape List")
    .setPosition(startPosX, startPosY + heightUI + 20)
    .setSize(barLengthUI, heightUI * 3)
    .addItem("Square", 0)
    .addItem("Hexagon", 1)
    ;
  
  MaxSteps = UI.addSlider("Maximum Steps")
    .setPosition(startPosX, 200)
    .setSize(barLengthUI, heightUI)
    .setRange(100, 500000)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  MaxSteps.getCaptionLabel().setSize(fontSize);
  MaxSteps.getValueLabel().setSize(fontSize);

  StepRate = UI.addSlider("Step Rate")
    .setPosition(startPosX, 250)
    .setSize(barLengthUI, heightUI)
    .setRange(1, 1000)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  StepRate.getCaptionLabel().setSize(fontSize);
  StepRate.getValueLabel().setSize(fontSize);

  StepSize = UI.addSlider("Step Size")
    .setPosition(startPosX, 300)
    .setSize(shortBarLengthUI, heightUI)
    .setRange(10, 30)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  StepSize.getCaptionLabel().setSize(fontSize);
  StepSize.getValueLabel().setSize(fontSize);

  StepScale = UI.addSlider("Step Scale")
    .setPosition(startPosX, 350)
    .setSize(shortBarLengthUI, heightUI)
    .setRange(1.0,1.5)
    .setDecimalPrecision(2)
    .setValue(1)
    ;
  StepScale.getCaptionLabel().setSize(fontSize);
  StepScale.getValueLabel().setSize(fontSize);

  ConstrainStep = UI.addToggle("ConstrainStep")
    .setPosition(startPosX, 450)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  ConstrainStep.getCaptionLabel().setSize(fontSize);
  ConstrainStep.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

  SimulateTerrain = UI.addToggle("Simulate Terrain")
    .setPosition(startPosX, 500)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  SimulateTerrain.getCaptionLabel().setSize(fontSize);
  SimulateTerrain.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

  UseStroke = UI.addToggle("Use Stroke")
    .setPosition(startPosX, 550)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  UseStroke.getCaptionLabel().setSize(fontSize);
  UseStroke.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

  UseRandomSeed = UI.addToggle("Use Random Seed")
    .setPosition(startPosX, 600)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  UseRandomSeed.getCaptionLabel().setSize(fontSize);
  UseRandomSeed.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));

  SeedValue = UI.addTextfield("Seed Value")
    .setPosition(startPosX, 650)
    .setSize(heightUI, heightUI)
    ;
  SeedValue.getCaptionLabel().setSize(fontSize);
  SeedValue.getCaptionLabel().setPadding(heightUI + toggleLabelOffset, -((heightUI * 3) / 4));
}
