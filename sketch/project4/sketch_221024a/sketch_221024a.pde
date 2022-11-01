
import controlP5.*;
ControlP5 cp5;

int width = 1600;
int height = 1000;

float camBounds = 60;
CameraControl camControl;
PVector zeroPoint = new PVector(0,0,0);
Terrain terrain = new Terrain();
LoadImage loadImage = new LoadImage();

void setup() {
    size(1600, 1000, P3D);
    cp5 = new ControlP5(this);
    //cp5.addSlider("cameraX", -camBounds, camBounds).setPosition(20,30);
    //cp5.addSlider("cameraY", -camBounds, camBounds).setPosition(20,50);
    //cp5.addSlider("cameraZ", -camBounds, camBounds).setPosition(20,70);
    //wiredMonster.shape = loadShape("monster.obj");
    //halfMonster.shape = loadShape("monster.obj");
    camControl = new CameraControl();
    camControl.AddLookAtTarget(new PVector(0, 0, 0));
}

void draw() {
    background(200);
    perspective(radians(50.0f), width / (float) height, 0.1, 1000);
    camControl.Update();
    DrawGridLines();
    loadImage.load();
    terrain.generateIndexList();
    terrain.generateVerticesList();
    terrain.test_DrawVertices();
    terrain.drawTriangles();
    terrain.adjustHeight(loadImage.getImage());
    
    perspective(); //<>// //<>// //<>//
    camera();
}

// Controls

void mouseWheel(MouseEvent event) {
    camControl.Zoom(event.getCount());
}
void keyPressed() {
    //camControl.CycleTarget();
}

class LoadImage {
    PImage theImage;
    String filename;

    void load() {
        theImage = loadImage("terrain0.png");
    }
    
    PImage getImage() {
        return theImage;
    }
}

class Terrain {
    int rows = 10;
    int cols = 10;
    int gridSize = 50;
    ArrayList<PVector> verticesList = new ArrayList<PVector>();
    ArrayList<Integer> triangleIndex = new ArrayList<Integer>();

    void adjustHeight(PImage image) {
        float xIndex = 0;
        float yIndex = 0;
        color imageColor;
        float red = 0.0;
        float heightFromColor = 0.0;
        float maxHeight = 5.0;
        int vertexIndex = 0; 

        for (int j = 0; j < rows; j++) {
            for (int i = 0; i < cols; i++) {
                xIndex = map(i, 0, cols + 1, 0, image.width);
                yIndex = map(j, 0, rows + 1, 0, image.height);

                imageColor = image.get((int)xIndex, (int)yIndex);
                red = imageColor >> 16 & 0xFF; // Bit shift method to get the red color
                heightFromColor = map(red, 0, 255, 0.0, 1.0);

                vertexIndex = i * (cols + 1) + j;
                verticesList.get(vertexIndex).z = maxHeight * heightFromColor;
            }
        }
    }

    void generateIndexList() {
        int verticesInRow = cols + 1;

        for (int j = 0; j < rows; j++) {
            int rowModifier = j * (cols + 1);
            for (int i = 0; i < cols; i++) {
                // Form both triangles for a square
                // Triangle 1
                triangleIndex.add(rowModifier + i);
                triangleIndex.add(rowModifier + i + 1);
                triangleIndex.add(rowModifier + i + verticesInRow);
                // Triangle 2 
                triangleIndex.add(rowModifier + i + 1);
                triangleIndex.add(rowModifier + i + verticesInRow + 1);
                triangleIndex.add(rowModifier + i + verticesInRow);
            }
        }
    }

    void generateVerticesList() {
        float start = -gridSize / 2.0;
        float end = gridSize / 2.0;
        float incrementRow = gridSize / rows;
        float incrementCol = gridSize / cols;

        for (float row = start; row <= end; row += incrementRow) {
            for (float col = start; col <= end; col += incrementCol) {
                PVector newPvect = new PVector(row, col, 0);
                verticesList.add(newPvect);
            }
        }
    }

    void drawTriangles() {
        int indexesPerRow = 3 * cols * 2;
        beginShape(TRIANGLES);
        for (int i = 0; i < triangleIndex.size(); i++) {
            if ( i % indexesPerRow == 0) {
                endShape();
                beginShape(TRIANGLES);
            }
            int vertIndex = triangleIndex.get(i);
            PVector vert = verticesList.get(vertIndex);
            vertex(vert.x, vert.y, vert.z);
        }
        endShape();
    }

    void test_DrawVertices() {
        float numOfEle = verticesList.size();
        float colorIncrement = 360 / numOfEle;
        colorMode(HSB, 360);
        strokeWeight(3);

        for (int i = 0; i < numOfEle; i++) {
            stroke(i * colorIncrement, i * colorIncrement, 100);
            point(verticesList.get(i).x, verticesList.get(i).y, verticesList.get(i).z);
        }
        colorMode(RGB, 255, 255, 255);
    }
}


class CameraControl {

    ArrayList<PVector> targets = new ArrayList<PVector>();
    float theta = PI / 4.0;
    float phi = PI / 4.0;
    float distance = 100;
    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 0;
    float deltaX = 0;
    float deltaY = 0;
    float minZoom = 10.0;
    float maxZoom = 200.0;
    float scaleMouseControl = 0.005;
    float increment = PI / 180.0;
    PVector currentTarget;
    int currIndex = 0;
    CameraControl() {
        targets.add(zeroPoint);
        currentTarget = zeroPoint;
    }

    void Update() {
        camera( cameraX, cameraY, cameraZ,
                currentTarget.x, currentTarget.y, currentTarget.z,
                0, -1, 0);
        if (cp5.isMouseOver()) {
          return;
        }
        else if (mousePressed == true) {
          deltaX = (mouseX - pmouseX) * scaleMouseControl;
          deltaY = (mouseY - pmouseY) * scaleMouseControl;
          phi = phi + deltaX;
          theta = theta + deltaY;
          cameraX = currentTarget.x + distance * cos(phi) * sin(theta);
          cameraY = currentTarget.y + distance * cos(theta);
          cameraZ = currentTarget.z + distance * sin(theta) * sin(phi);
          
          //theta = (mouseY / 360) % (PI);
          camera( cameraX, cameraY, cameraZ,
                currentTarget.x, currentTarget.y, currentTarget.z,
                0, -1, 0);
        }
        else {
          camera( cameraX, cameraY, cameraZ,
                currentTarget.x, currentTarget.y, currentTarget.z,
                0, -1, 0);
        }
          
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
        if (distance < minZoom) distance = minZoom;
        if (distance > maxZoom) distance = maxZoom;
    }
}

void DrawGridLines() {
    int numOfLines = 20;
    float startX = -100;
    float increment = 10;

    strokeWeight(1);
    stroke(50);
    /*
    for (int i = 0; i <= numOfLines; i++) {
        line( startX + (i * increment), startX, 0.0, startX + (i * increment), -startX, 0.0);
        line( startX, startX + (i * increment) , 0.0, -startX, startX + (increment * i), 0.0);
        //line(-500, -500 + (i * 100), 500, 0, 0);
    }
    */
    strokeWeight(5);
    stroke(255, 0, 0);
    line(startX, 0, 0, -startX, 0, 0);
    stroke(0, 255, 0);
    line(0, startX, 0, 0,-startX, 0);
    stroke(0, 0, 255);
    line(0, 0, startX, 0, 0, -startX);

    strokeWeight(1);
}
