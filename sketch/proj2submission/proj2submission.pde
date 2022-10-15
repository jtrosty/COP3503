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
Textfield SeedValueField;

// UI size and position variables
int counter = 0;
int heightUI = 20;
int barLengthUI = 180;
int shortBarLengthUI = barLengthUI / 3;
int startButtonLength = 50;
int startPosX = 10;
int startPosY = 10;
int dropBoxHeight = 30;

int fontSize = 10;
int toggleLabelOffset = 5;

//----------------------------------------------------------------------------------//

void setup() {
  size(1200, 800, P2D);
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
      uiBackground();
      walkObj.update();
    }
  }
}

//----------------------------------------------------------------------------------//

void resetBackground() {
  background(135, 206, 235);
  stroke(0);
  fill(90);
  rectMode(CORNER);
  rect(0, 0, 200, 800);
}

void uiBackground() {
  stroke(0);
  fill(90);
  rectMode(CORNER);
  rect(0, 0, 200, 800);
  rectMode(CENTER);
}
class RandomWalk {
  RandWalkData data;
  PVector currentPoint = new PVector(0.0f, 0.0f);
  float originX = 200.0f;
  float originY = 0.0f; float rightX = 1200.0f;
  float bottomY = 800.0f;
  HashMap<Float, Integer> visited = new HashMap();

  void setup() {}
  void update() {}
  void draw() {}
  PVector getNextPoint(float x, float y, float spacing, float screenX, float screenY) {
    return currentPoint;
    } 

  void terrain(Float key) {
    int timesVisited = 0; 
    if (visited.containsKey(key)) {
      timesVisited = visited.get(key);
    }
    else {
      visited.put(key, 0);
    }

    if(timesVisited < 4) {
      fill(160, 126, 84);
    }
    else if (timesVisited < 7  && timesVisited > 4) {
      fill(143, 170, 64);
    }
    else if (timesVisited < 10  && timesVisited > 7) {
      fill(135, 135, 135);
    }
    else if (timesVisited >= 10) {
      fill(timesVisited * 20);
    }
    visited.replace(key, timesVisited + 1);
  }

  boolean minClamp(float value, float min) {
    if (value < min) return true;
    return false;
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
}

class HexWalk extends RandomWalk {
  HexWalk(RandWalkData _data, float startX, float startY) {
    data =  _data;
    currentPoint.x = startX;
    currentPoint.y = startY;
    rectMode(CENTER);
  }

  void setup() {

  }

  void draw() {
    if (data.useStroke) {
      stroke(0);
    }
    else {
      noStroke();
    }
    PVector tempVectorKey = CartesianToHex(currentPoint.x, currentPoint.y, data.stepSize, data.stepScale, 700, 400);
    Float tempKey = tempVectorKey.x * 1000.0 + tempVectorKey.y;
    if (data.simTerrain) {
      terrain(tempKey);
    }
    else {
      fill(152, 120, 248);
    }
    drawHex(currentPoint.x, currentPoint.y, data.stepSize);
    data.counter++;
  }

  void drawHex(float x, float y, float radius) {
    beginShape();
    for (int i = 0; i <= 360; i+= 60)
    {
      float xPos = x + cos(radians(i)) * radius;
      float yPos = y + sin(radians(i)) * radius;

      vertex(xPos, yPos);
    }
    endShape();
  }
 //<>//
  void update() {
    currentPoint = getNextPoint(currentPoint.x, currentPoint.y, data.spacing, 1200, 800);
  }

  PVector getNextPoint(float x, float y, float spacing, float screenX, float screenY) { //<>//
    int randDir = int((random(6))); //<>//
    PVector result = new PVector(x,y);

    switch (randDir) {
      case 0:
        // Go Up
        // x no change
        x = x;
        y = y + spacing * sqrt(3); 
        break;
      case 1:
        //  Up Rigth
        x = x + (spacing * cos(radians(30)) * sqrt(3));
        y = y + (spacing * sin(radians(30)) * sqrt(3));
        break;
      case 2:
        // Down Rigth
        x = x + (spacing * cos(radians(30)) * sqrt(3));
        y = y - (spacing * sin(radians(30)) * sqrt(3));
        break;
      case 3:
        // Go down
        x = x;
        y = y - (spacing * sqrt(3));
        break;
      case 4:
        // down left
        x = x - (spacing * cos(radians(30)) * sqrt(3));
        y = y - (spacing * sin(radians(30)) * sqrt(3));
        break;
      case 5:
        // Go up Left
        x = x - (spacing * cos(radians(30)) * sqrt(3));
        y = y + (spacing * sin(radians(30)) * sqrt(3));
        break;
    }
    if (data.constrainStep) {
      if (!wasClamp(x, 200 + (sqrt(3) * data.stepSize), screenX - (sqrt(3) * data.stepSize)/2) &&
          !wasClamp(y, 0 + data.stepSize / 2, screenY - (data.stepSize / 2))) {
          return new PVector(x, y);
      }
    }
    else {
          return new PVector(x, y);
    }
    return result;
  }

  PVector CartesianToHex(float xPos, float yPos, float hexRadius, float stepScale, float xOrigin, float yOrigin) {
    float startX = xPos - xOrigin;
    float startY = yPos - yOrigin;

    float col = (2.0/3.0f * startX) / (hexRadius * stepScale);
    float row = (-1.0f/3.0f * startX + 1/sqrt(3.0f) * startY) / (hexRadius * stepScale);
    
    /*===== Convert to Cube Coordinates =====*/
    float x = col;
    float z = row;
    float y = -x - z; // x + y + z = 0 in this system
    
    float roundX = round(x);
    float roundY = round(y);
    float roundZ = round(z); //<>//
    
    float xDiff = abs(roundX - x);
    float yDiff = abs(roundY - y);
    float zDiff = abs(roundZ - z);
     //<>//
    if (xDiff > yDiff && xDiff > zDiff) //<>//
      roundX = -roundY - roundZ;
    else if (yDiff > zDiff)
      roundY = -roundX - roundZ;
    else
      roundZ = -roundX - roundY;
      
    /*===== Convert Cube to Axial Coordinates =====*/
    PVector result = new PVector(roundX, roundZ);
    
    return result;
  }
}

class SquareWalk extends RandomWalk {

  SquareWalk(RandWalkData _data, float startX, float startY) {
    data =  _data;
    currentPoint.x = startX;
    currentPoint.y = startY;
    rectMode(CENTER);
  }

  void setup() {
    rectMode(CENTER);
  }

  void draw() {
    if (data.useStroke) {
      stroke(0);
    }
    else {
      noStroke();
    }
    Float tempKey = currentPoint.x * 1000.0 + currentPoint.y;
    if (data.simTerrain) {
      terrain(tempKey);
    }
    else {
      fill(152, 120, 248);
    }
    square(currentPoint.x, currentPoint.y, data.stepSize);
    data.counter++;
  }

  void update() {
    currentPoint = getNextPoint(currentPoint.x, currentPoint.y, data.spacing, 1200, 800);
  }

  PVector getNextPoint(float x, float y, float spacing, float screenX, float screenY) {
    int randDir = int((random(4)));
    PVector result = new PVector(x, y);

    switch (randDir) {
      case 0:
        // Go Up
          y = y - spacing;
        break;
      case 1:
        // Go Right
          x = x + spacing;
        break;
      case 2:
        // Go down
          y = y + spacing;
        break;
      case 3:
        // Go Left
          x = x - spacing;
        break;
    }

    if (data.constrainStep) {
      if (!wasClamp(x, 200 + data.stepSize/2, screenX - (data.stepSize / 2)) &&  
         (!wasClamp(y, 0 + data.stepSize/2, screenY - (data.stepSize / 2)))) {
          return new PVector(x, y);
      }
    }
    else {
      return new PVector(x, y);
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
  String tempString = SeedValueField.getText();
  if (tempString.isEmpty()) {
    data.useRandSeed = false;
    UseRandomSeed.setState(false);
  }
  else {
    data.randSeed = Integer.parseInt(tempString);
  }
  data.shapeType = ShapeList.getId();
  data.counter = 0;
  data.spacing = int(float(data.stepSize) * data.stepScale);
  if (ShapeList.getValue() == 0) {
    walkObj = new SquareWalk(data, 700, 400);
  }
  else {
    walkObj = new HexWalk(data, 700, 400);
  }
  walkObj.setup();
  if (data.useRandSeed) {
    randomSeed(data.randSeed);
  }
  else {
  }
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
    .setSize(barLengthUI, heightUI * 10)
    .setBarHeight(heightUI * 2)
    .addItem("Square", 0)
    .addItem("Hexagon", 1)
    .setItemHeight(heightUI * 2);
    ;
  ShapeList.setValue(1);
  ShapeList.getCaptionLabel().setSize(fontSize);
  ShapeList.getValueLabel().setSize(fontSize);
  
  MaxSteps = UI.addSlider("Maximum Steps")
    .setPosition(startPosX, 200)
    .setSize(barLengthUI, heightUI)
    .setRange(100, 500000)
    .setDecimalPrecision(0)
    ;
  MaxSteps.setValue(10000);
  MaxSteps.getCaptionLabel().setSize(fontSize);
  MaxSteps.getValueLabel().setSize(fontSize);
  MaxSteps.getCaptionLabel().align(ControlP5.LEFT, ControlP5.TOP_OUTSIDE);

  StepRate = UI.addSlider("Step Rate")
    .setPosition(startPosX, 250)
    .setSize(barLengthUI, heightUI)
    .setRange(1, 1000)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  StepRate.getCaptionLabel().setSize(fontSize);
  StepRate.getValueLabel().setSize(fontSize);
  StepRate.getCaptionLabel().align(ControlP5.LEFT, ControlP5.TOP_OUTSIDE);

  StepSize = UI.addSlider("Step Size")
    .setPosition(startPosX, 300)
    .setSize(shortBarLengthUI, heightUI)
    .setRange(10, 30)
    .setDecimalPrecision(0)
    .setValue(1000)
    ;
  StepSize.getCaptionLabel().setSize(fontSize);
  StepSize.getValueLabel().setSize(fontSize);
  StepSize.getCaptionLabel().align(ControlP5.LEFT, ControlP5.TOP_OUTSIDE);

  StepScale = UI.addSlider("Step Scale")
    .setPosition(startPosX, 350)
    .setSize(shortBarLengthUI, heightUI)
    .setRange(1.0,1.5)
    .setDecimalPrecision(2)
    .setValue(1)
    ;
  StepScale.getCaptionLabel().setSize(fontSize);
  StepScale.getValueLabel().setSize(fontSize);
  StepScale.getCaptionLabel().align(ControlP5.LEFT, ControlP5.TOP_OUTSIDE);

  ConstrainStep = UI.addToggle("Constrain Step")
    .setPosition(startPosX, 400)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  ConstrainStep.getCaptionLabel().setSize(fontSize);
  ConstrainStep.getCaptionLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE);

  SimulateTerrain = UI.addToggle("Simulate Terrain")
    .setPosition(startPosX, 450)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  SimulateTerrain.getCaptionLabel().setSize(fontSize);
  SimulateTerrain.getCaptionLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE);

  UseStroke = UI.addToggle("Use Stroke")
    .setPosition(startPosX, 500)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  UseStroke.getCaptionLabel().setSize(fontSize);
  UseStroke.getCaptionLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE);

  UseRandomSeed = UI.addToggle("Use Random Seed")
    .setPosition(startPosX, 550)
    .setSize(heightUI, heightUI)
    .setValue(true)
    ;
  UseRandomSeed.getCaptionLabel().setSize(fontSize);
  UseRandomSeed.getCaptionLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE);

  SeedValueField = UI.addTextfield("Seed Value")
    .setPosition(startPosX + 100, 550)
    .setSize(heightUI * 3, heightUI)
    .setText("0");
    ;
  SeedValueField.getCaptionLabel().setSize(fontSize);
  SeedValueField.setInputFilter(ControlP5.INTEGER);
  SeedValueField.getCaptionLabel().align(ControlP5.LEFT, ControlP5.BOTTOM_OUTSIDE);
}
