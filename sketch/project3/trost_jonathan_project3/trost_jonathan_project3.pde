import controlP5.*;
ControlP5 cp5;

int width = 1600;
int height = 1000;

float camBounds = 60;
PShape monster;
PShape wireMonster;
CameraControl camControl;
PVector zeroPoint = new PVector(0,0,0);
ShapeUnified wiredMonster;
ShapeUnified halfMonster;
ShapeUnified boxes;


void setup() {
    size(1600, 1000, P3D);
    cp5 = new ControlP5(this);
    //cp5.addSlider("cameraX", -camBounds, camBounds).setPosition(20,30);
    //cp5.addSlider("cameraY", -camBounds, camBounds).setPosition(20,50);
    //cp5.addSlider("cameraZ", -camBounds, camBounds).setPosition(20,70);
    //wiredMonster.shape = loadShape("monster.obj");
    //halfMonster.shape = loadShape("monster.obj");
    camControl = new CameraControl();
    wiredMonster = new ShapeUnified("monster.obj", 75, 0, 0);
    halfMonster = new ShapeUnified("monster.obj", 0, 0, 0);
    boxes = new ShapeUnified(makeCube(), -100, 0, 0);
    camControl.AddLookAtTarget(new PVector(-100, 0, 0));
    camControl.AddLookAtTarget(new PVector(-50, 0, 0));
    camControl.AddLookAtTarget(new PVector(0, 0, 0));
    camControl.AddLookAtTarget(new PVector(75, 0, 0));
}

void draw() {
    background(200);
    perspective(radians(50.0f), width / (float) height, 0.1, 1000);
    // 2 matrixes to setup projection andcamera
    camControl.Update();

    DrawGridLines();
    //triangleFanManual();
    //drawLowResCircle(20, 40);
    pushMatrix();

    translate(-100, 1, 0);
    scale(1, 1, 1);
    shape(boxes.shape);

    translate(5, 0, 0);
    scale(5, 10, 2);
    shape(boxes.shape);

    translate(3, 2, 1);
    scale(1, 2, 20);
    shape(boxes.shape);
    

    popMatrix();

    pushMatrix();
    scale(.5, .5, .5);
    halfMonster.shape.setFill(color(100, 100, 0, 255));
    shape(halfMonster.shape);
    popMatrix();

    pushMatrix();
    translate(-50, 5, 0);
    drawLowResCircle(20, 5);
    translate(10, 0, 0);
    drawLowResCircle(6, 5);
    popMatrix();

    pushMatrix();
    translate(wiredMonster.x,wiredMonster.y, wiredMonster.z);
    wiredMonster.shape.stroke(0, 0, 0);
    wiredMonster.shape.setStroke(true);
    wiredMonster.shape.setStrokeWeight(2);
    wiredMonster.shape.setFill(color(255, 255, 255, 0));
    shape(wiredMonster.shape);
    popMatrix();

    perspective();
    camera();
}

void mouseWheel(MouseEvent event) {
    camControl.Zoom(event.getCount());
}
void keyPressed() {
    camControl.CycleTarget();
}

class CameraControl {

    ArrayList<PVector> targets = new ArrayList<PVector>();
    float theta = PI / 4.0;
    float phi = PI / 4.0;
    float distance = 100;
    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 0;
    float increment = PI / 360.0;
    PVector currentTarget;
    int currIndex = 0;
    CameraControl() {
        targets.add(zeroPoint);
        currentTarget = zeroPoint;
    }

    void Update() {
        cameraX = currentTarget.x + distance * cos(phi) * sin(theta);
        cameraY = currentTarget.y + distance * cos(theta);
        cameraZ = currentTarget.z + distance * sin(theta) * sin(phi);
        phi = map(mouseX, 0.0, width, 0.0, (2 * PI));
        theta = map(mouseY, 0.0, height, 0.0, (PI/ 2));
        //theta = (mouseY / 360) % (PI);
        camera( cameraX, cameraY, cameraZ,
                currentTarget.x, currentTarget.y, currentTarget.z,
                0, -1, 0);
    }

    void AddLookAtTarget(PVector v1) {
        targets.add(v1);
    }

    void CycleTarget() {
        if (currIndex < targets.size() - 1) {
            currIndex++;
        }
        else {
            currIndex = 0;
        }
        currentTarget = targets.get(currIndex);
    }

    void Zoom(float zoom) {
        distance += zoom * 6;
        if (distance < 20) distance = 20;
        if (distance > 200) distance = 200;
    }
}

class ShapeUnified {
    PShape shape;
    float x;
    float y;
    float z;

    ShapeUnified(PShape _shape, float _x, float _y, float _z) {
        shape = _shape;
        x = _x;
        y = _y;
        z = _z;
    }
    ShapeUnified(String file, float _x, float _y, float _z) {
        shape = loadShape(file);
        x = _x;
        y = _y;
        z = _z;
    }
}


PShape makeCube() {
    PShape cube = createShape();
    cube.beginShape(TRIANGLE_STRIP);
    stroke(0);

    //Triangle 1 z plane negative
    cube.fill(255, 0, 0);
    cube.vertex( 0.5,  0.5, -0.5);
    cube.vertex(-0.5,  0.5, -0.5);
    cube.vertex(-0.5, -0.5, -0.5);
    
    //Triangle 2
    cube.fill(0, 255, 0);
    cube.vertex(-0.5, -0.5, -0.5);
    cube.vertex( 0.5, -0.5, -0.5);
    cube.vertex( 0.5,  0.5, -0.5);

    //Triangle 1 x plane positive
    cube.fill(0, 0, 255);
    cube.vertex(0.5,  0.5, -0.5);
    cube.vertex(0.5,  0.5,  0.5);
    cube.vertex(0.5, -0.5, -0.5);

    //Triangle 2
    cube.fill(0, 128, 255);
    cube.vertex(0.5,  0.5,  0.5);
    cube.vertex(0.5, -0.5, -0.5);
    cube.vertex(0.5, -0.5,  0.5);

    //Triangle 1 z positive
    cube.fill(255, 100, 0);
    cube.vertex(0.5,  0.5, 0.5);
    cube.vertex(0.5, -0.5, 0.5);
    cube.vertex(-0.5, -0.5, 0.5);
    
    //Triangle 2
    cube.fill(146, 216, 255);
    cube.vertex(-0.5, -0.5, 0.5);
    cube.vertex(-0.5, 0.5, 0.5);
    cube.vertex(0.5, 0.5, 0.5);

    //Triangle 1 y plane positive
    cube.fill(0, 255, 255);
    cube.vertex( 0.5, 0.5,  0.5);
    cube.vertex(-0.5, 0.5,  0.5);
    cube.vertex(-0.5, 0.5, -0.5);

    //Triangle 2
    cube.fill(255, 0, 255);
    cube.vertex(-0.5, 0.5, -0.5);
    cube.vertex( 0.5, 0.5,  0.5);
    cube.vertex( 0.5, 0.5, -0.5);

    //Triangle 1 x plane negative
    cube.fill(255, 255, 0);
    cube.vertex(-0.5,  0.5, -0.5);
    cube.vertex(-0.5, -0.5, -0.5);
    cube.vertex(-0.5,  0.5,  0.5);
    
    // Triangle 2
    cube.fill(255, 165, 0);
    cube.vertex(-0.5, -0.5, -0.5);
    cube.vertex(-0.5, -0.5,  0.5);

    //Triangle 1 y plane negative
    cube.fill(106, 90, 205);
    cube.vertex(-0.5, -0.5,  0.5);
    cube.vertex( 0.5, -0.5,  0.5);
    cube.vertex(-0.5, -0.5, -0.5);

    //Triangle 2
    cube.fill(50, 50, 50);
    cube.vertex( 0.5, -0.5,  0.5);
    cube.vertex(-0.5, -0.5, -0.5);
    cube.vertex( 0.5, -0.5, -0.5);
/*
    
    //Triangle 2
    cube.vertex(-0.5,  0.5,  0.5);
    fill(255, 0,0 );

    


    */
/*
    //Triangle 1 x plane negative 
    cube.vertex(-0.5, 0.5, -0.5);
    cube.vertex(-0.5, 0.5, 0.5);
    cube.vertex(-0.5, -0.5, 0.5);
    
    //Triangle 2
    cube.vertex(-0.5, -0.5, 0.5);
    cube.vertex(-0.5, 0.5, -0.5);
    //cube.vertex(-0.5, -0.5, -0.5);
    // X plane
    //Triangle 2 x plane
    cube.vertex(0.5, 0.5, 0.5);
    cube.vertex(-0.5, 0.5, 0.5);
    cube.vertex(-0.5, -0.5, 0.5);
    
    //Triangle 2
    cube.vertex(0.5, 0.5, 0.5);
    cube.vertex(-0.5, -0.5, 0.5);
    cube.vertex(0.5, -0.5, 0.5);
    */

    cube.endShape();
    return cube;
}

void triangleFanManual() {
    colorMode(HSB, 360, 100, 100);
    beginShape(TRIANGLE_FAN);
    fill(0, 100, 100);
    vertex(-30, 0, 0);
    fill(120, 100, 100);
    vertex(0, -50, 0);
    fill(240, 100, 100);
    vertex(30, 0, 0);
    endShape();

    colorMode(HSB, 360, 100, 100);
    stroke(0);
    
    beginShape(TRIANGLE_FAN);
    fill(0, 100, 100);
    vertex(0, 0, 20);
    fill(60, 100, 100);
    vertex(0, 20, 0);
    fill(120, 100, 100);
    vertex(0, 40, 0);
    fill(180, 100, 100);
    vertex(0, 60, 20);
    fill(240, 100, 100);
    vertex(0, 40, 40);
    fill(300, 100, 100);
    vertex(0, 20, 40);
    fill(360, 100, 100);
    vertex(0, 0, 20);
    endShape();
}

void drawLowResCircle(float numOfVertices, float radius) {
    float incrementRad = (2 * PI) / numOfVertices;
    float increment = 360 / numOfVertices;
    float value = 0;
    float startCoordinate = 100;
    colorMode(HSB, 360, 100, 100);
    
    beginShape(TRIANGLE_FAN);
    strokeWeight(1);
    stroke(1);
    for (float i = 0; i < numOfVertices; i++) {
        fill(value, 100, 100);
        vertex(radius * cos((i * incrementRad)), radius * sin((i * incrementRad)), 0);
        value += increment;
    }
    fill(value, 100, 100);
    vertex(radius * cos(0), 0,  radius * sin(0));
    endShape();
    colorMode(RGB);
}

void makeTriangle() {
    beginShape();
    fill(255, 0, 0);
    vertex(-30, 0, 0);
    fill(0, 255, 0);
    vertex(0, -50, 0);
    fill(0, 0, 255);
    vertex(30, 0, 0);
    endShape();
}

void DrawGridLines() {
    int numOfLines = 20;
    float startX = -100;
    float increment = 10;

    strokeWeight(1);
    stroke(50);
    for (int i = 0; i <= numOfLines; i++) {
        line( startX + (i * increment), 0.0, startX, startX + (increment * i), 0.0, -startX);
        line( startX, 0.0, startX + (i * increment), -startX, 0.0, startX + (increment * i));
        //line(-500, -500 + (i * 100), 500, 0, 0);
    }
    strokeWeight(5);
    stroke(255, 0, 0);
    line(startX, 0, 0, -startX, 0, 0);
    stroke(0, 255, 0);
    line(0, startX, 0, 0,-startX, 0);
    stroke(0, 0, 255);
    line(0, 0, startX, 0, 0, -startX);

    strokeWeight(1);

}
