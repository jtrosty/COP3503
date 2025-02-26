// VertexAnimation Project - Student Version
import java.io.*;
import java.util.*;
import queasycam.*;

CameraControl camControl;
float camBounds = 200;
int width = 1600;
int height = 1000;

/*========== Monsters ==========*/
Animation monsterAnim;
ShapeInterpolator monsterForward = new ShapeInterpolator();
ShapeInterpolator monsterReverse = new ShapeInterpolator();
ShapeInterpolator monsterSnap = new ShapeInterpolator();

/*========== Sphere ==========*/
Animation sphereAnim; // Load from file
Animation spherePos; // Create manually
ShapeInterpolator sphereForward = new ShapeInterpolator();
PositionInterpolator spherePosition = new PositionInterpolator();

// TODO: Create animations for interpolators
ArrayList<PositionInterpolator> cubes = new ArrayList<PositionInterpolator>();
ArrayList<PShape> boxes = new ArrayList<PShape>();

void setup()
{
  pixelDensity(displayDensity());
  size(1200, 800, P3D);

  /* ========= Camera ===========*/
  camControl = new CameraControl();

  /*====== Load Animations ======*/
  monsterAnim = ReadAnimationFromFile("monster.txt");
  sphereAnim = ReadAnimationFromFile("sphere.txt");

  monsterForward.SetAnimation(monsterAnim);
  monsterReverse.SetAnimation(monsterAnim);
  monsterSnap.SetAnimation(monsterAnim);  
  monsterSnap.SetFrameSnapping(true);

  sphereForward.SetAnimation(sphereAnim);

  /*====== Create Animations For Cubes ======*/
  // When initializing animations, to offset them
  // you can "initialize" them by calling Update()
  // with a time value update. Each is 0.1 seconds
  // ahead of the previous one
  Animation cubePos = new Animation();
  // Create and set keyframes
  ArrayList<PVector> cubeFrame0 = new ArrayList<PVector>();
  ArrayList<PVector> cubeFrame1 = new ArrayList<PVector>();
  ArrayList<PVector> cubeFrame2 = new ArrayList<PVector>();
  ArrayList<PVector> cubeFrame3 = new ArrayList<PVector>();
  cubeFrame0.add(new PVector(0, 0, 0));
  cubeFrame1.add(new PVector(0, 0, 100));
  cubeFrame2.add(new PVector(0, 0));
  cubeFrame3.add(new PVector(0, 0, -100));
  cubePos.addKeyFrame(0.5, cubeFrame0);
  cubePos.addKeyFrame(1.0, cubeFrame1);
  cubePos.addKeyFrame(1.5, cubeFrame2);
  cubePos.addKeyFrame(2.0, cubeFrame3);
  cubePos.setDuration(2.0);
  int numOfCubes = 11;

  for (int i = 0; i < 11; i++) {
    cubes.add(new PositionInterpolator());
    cubes.get(i).SetAnimation(cubePos);
    cubes.get(i).setStartTime((2.0 / float(numOfCubes)) * float(i));
    noStroke();
    if (i % 2 == 1) {
      cubes.get(i).SetFrameSnapping(true);
      fill(255, 255, 0);
    }
    else {
      fill(255, 0, 0);
    }
    boxes.add(createShape(BOX, 10));
  }
  
  /*====== Create Animations For Spheroid ======*/
  Animation spherePos = new Animation();
  // Create and set keyframes
  ArrayList<PVector> frame0 = new ArrayList<PVector>();
  ArrayList<PVector> frame1 = new ArrayList<PVector>();
  ArrayList<PVector> frame2 = new ArrayList<PVector>();
  ArrayList<PVector> frame3 = new ArrayList<PVector>();
  frame0.add(new PVector(-100, 0, 100));
  frame1.add(new PVector(-100, 0, -100));
  frame2.add(new PVector(100, 0, -100));
  frame3.add(new PVector(100, 0, 100));
  spherePos.addKeyFrame(1.0, frame0);
  spherePos.addKeyFrame(2.0, frame1);
  spherePos.addKeyFrame(3.0, frame2);
  spherePos.addKeyFrame(4.0, frame3);
  spherePos.setDuration(4.0);
  spherePosition.SetAnimation(spherePos);
  

}

void draw()
{
  lights();
  background(0);
  perspective(radians(50.0f), width / (float) height, 0.1, 1000);
  camControl.Update();
  DrawGrid();

  float playbackSpeed = 0.005f;

  // TODO: Implement your own camera

  /*====== Draw Forward Monster ======*/
  pushMatrix();
  translate(-40, 0, 0);
  monsterForward.fillColor = color(128, 200, 54);
  monsterForward.Update(playbackSpeed);
  shape(monsterForward.currentShape);
  popMatrix();

  /*====== Draw Reverse Monster ======*/
  pushMatrix();
  translate(40, 0, 0);
  monsterReverse.fillColor = color(220, 80, 45);
  monsterReverse.Update(-playbackSpeed);
  shape(monsterReverse.currentShape);
  popMatrix();
  
  /*====== Draw Snapped Monster ======*/
  pushMatrix();
  translate(0, 0, -60);
  monsterSnap.fillColor = color(160, 120, 85);
  monsterSnap.Update(playbackSpeed);
  shape(monsterSnap.currentShape);
  popMatrix();
  
  /*====== Draw Spheroid ======*/
  spherePosition.Update(playbackSpeed);
  sphereForward.fillColor = color(39, 110, 190);
  sphereForward.Update(playbackSpeed);
  PVector pos = spherePosition.currentPosition;
  pushMatrix();
  translate(pos.x, pos.y, pos.z);
  shape(sphereForward.currentShape);
  popMatrix();

  
  /*====== TODO: Update and draw cubes ======*/
  // For each interpolator, update/draw
  PVector posCube;
  
  for (int i = 0; i < 11; i++) {
    pushMatrix();
    translate(100 - (i * 20), 0, 0);
    cubes.get(i).Update(playbackSpeed);
    posCube = cubes.get(i).currentPosition;
    if (i % 2 == 0) {
      fill(255, 0, 0);
    }
    else {
      fill(255, 255, 0);
    }
    translate(posCube.x, posCube.y, posCube.z);
    shape(boxes.get(i));
    popMatrix();
  }

  camera();
  perspective();
}

void mouseWheel(MouseEvent event) {
    camControl.Zoom(event.getCount());
}

void keyPressed() {
    camControl.CycleTarget();
}

// Create and return an animation object
Animation ReadAnimationFromFile(String fileName) {
  Animation animation = new Animation();
  String currentLine;
  String[] split;

  // The BufferedReader class will let you read in the file data
  try {
    BufferedReader reader = createReader(fileName);
    currentLine = reader.readLine();
    animation.numOfKeyFrames = int(currentLine);
    currentLine = reader.readLine();
    animation.numOfDataPoints = int(currentLine);

    for (int i = 0; i < animation.numOfKeyFrames; i++) {
      // Get line
      currentLine = reader.readLine();
      float tempTime = float(currentLine);
      ArrayList<PVector> pointsKeyFrame = new ArrayList<PVector>();

      for (int j = 0; j < animation.numOfDataPoints; j++) {
        currentLine = reader.readLine();
        split = currentLine.split(" ");
        pointsKeyFrame.add(new PVector(float(split[0]), float(split[1]), float(split[2])));
      }
      animation.addKeyFrame(tempTime, pointsKeyFrame);
      if (i == animation.numOfKeyFrames -1) {
        animation.setDuration(tempTime);
      }
    }
  }
  catch (FileNotFoundException ex) {
    println("File not found: " + fileName);
  }
  catch (IOException ex) {
    ex.printStackTrace();
  }

  return animation;
}

void DrawGrid() {
  // TODO: Draw the grid
  // Dimensions: 200x200 (-100 to +100 on X and Z)
    int numOfLines = 20;
    float startOfLines = -100;
    float increment = 10;

    strokeWeight(1);
    stroke(50);
    for (int i = 0; i <= numOfLines; i++) {
        line( startOfLines + (i * increment), 0.0, startOfLines, startOfLines + (increment * i), 0.0, -startOfLines);
        line( startOfLines, 0.0, startOfLines + (i * increment), -startOfLines, 0.0, startOfLines + (increment * i));
        //line(-500, -500 + (i * 100), 500, 0, 0);
    }
    strokeWeight(5);
    stroke(255, 0, 0);
    line(startOfLines, 0, 0, -startOfLines, 0, 0);
    /*
    stroke(0, 255, 0);
    line(0, startOfLines, 0, 0,-startOfLines, 0);
    */
    stroke(0, 0, 255);
    line(0, 0, startOfLines, 0, 0, -startOfLines);

    strokeWeight(1);

}
