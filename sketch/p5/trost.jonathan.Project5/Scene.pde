class Scene
{
  // TODO: Write this class!
  /*
    Things you'll need:
    Some way to store PShapes and their positions
    Some way to store lights--position plus color for the pointLight() function
    Other classes may be helpful here
    A background color for the scene
  */
  int numModels = 0;
  ArrayList<PShape> modelsList = new ArrayList<PShape>();
  ArrayList<PVector> positionList = new ArrayList<PVector>();
  ArrayList<Integer> modelColorList = new ArrayList<Integer>();

  color backgroundColor;

  int numLights = 0;
  ArrayList<PVector> lightPositionList = new ArrayList<PVector>();
  ArrayList<Integer> lightColorList = new ArrayList<Integer>();

  String pathScene = "scenes/";
  String pathModel = "models/";

  Scene(String file) {
    if (file == "testfile") {
      LoadTestScene();
    }
    else {
      LoadScene(file);
    }
  }

  void LoadTestScene() {
    BufferedReader reader = createReader(pathScene + "testfile.txt");
    String currentLine;
    String[] split;
    PVector tempPos;
    color tempColor;
    try {
      currentLine = reader.readLine();
      split = currentLine.split(",");
      modelsList.add(loadShape(pathModel + split[0] + ".obj"));
      tempPos = new PVector(float(split[1]), float(split[3]), float(split[3]));
      positionList.add(tempPos);
      backgroundColor = color(int(split[4]), int(split[5]), int(split[6]));
      numModels = modelsList.size();

      currentLine = reader.readLine();
      split = currentLine.split(",");
      tempPos = new PVector(float(split[0]), float(split[1]), float(split[2]));
      lightPositionList.add(tempPos);
      //tempColor = color(int(split[4]), int(split[5]), int(split[6]));
      lightColorList.add(new Integer(int(split[3])));
      lightColorList.add(new Integer(int(split[4])));
      lightColorList.add(new Integer(int(split[5])));
      numLights = lightColorList.size() / 3;
      
    }
    catch (IOException e) {
      e.printStackTrace();
    }
  }

  void LoadScene(String filename) {
    BufferedReader reader = createReader(pathScene + filename + ".txt");
    String currentLine;
    String[] split;
    PVector tempPos;
    color tempColor;
    try {
      // Background color
      currentLine = reader.readLine();
      split = currentLine.split(","); //<>//
      backgroundColor = color(int(split[0]), int(split[1]), int(split[2])); //<>//

      // Get num of models
      currentLine = reader.readLine();
      numModels = int(currentLine);

      // Get models
      for (int i = 0; i < numModels; i++) {
        currentLine = reader.readLine();
        split = currentLine.split(",");
        modelsList.add(loadShape(pathModel + split[0] + ".obj"));
        tempPos = new PVector(float(split[1]), float(split[2]), float(split[3]));
        positionList.add(tempPos);
        modelColorList.add(new Integer(int(split[4])));
        modelColorList.add(new Integer(int(split[5])));
        modelColorList.add(new Integer(int(split[6])));
      }

      // Get num of lights
      currentLine = reader.readLine();
      numLights = int(currentLine);

      // Get all light data
      for (int i = 0; i < numLights; i++) {
        currentLine = reader.readLine();
        split = currentLine.split(",");
        tempPos = new PVector(float(split[0]), float(split[1]), float(split[2]));
        lightPositionList.add(tempPos);
        lightColorList.add(new Integer(int(split[3])));
        lightColorList.add(new Integer(int(split[4])));
        lightColorList.add(new Integer(int(split[5])));
      }
    }
    catch (IOException e) {
      e.printStackTrace();
    }
  }

  
  void DrawScene()
  {
    // TODO: Draw all the information in this scene
    /*
      Just like using draw() with a regular sketch, things you would need to do
      Clear the screen with background()
      Set up any lights in this scene
      Draw each object in the correct location
    */
    clear(); //<>//
    background(backgroundColor);
    for (int i = 0; i < numLights; i++) {
      PVector pos = lightPositionList.get(i);
      int red =   lightColorList.get(i * 3).intValue();
      int green = lightColorList.get((i * 3) + 1).intValue();
      int blue =  lightColorList.get((i * 3) + 2).intValue();
      pointLight(red, green, blue, pos.x, pos.y, pos.z);
    }
    
    for (int i = 0; i < numModels; i++) {
      pushMatrix();
      translate(positionList.get(i).x, positionList.get(i).y, positionList.get(i).z);
      if (modelColorList.size() != 0) {
        int red =   modelColorList.get(i * 3).intValue();
        int green = modelColorList.get((i * 3) + 1).intValue();
        int blue =  modelColorList.get((i * 3) + 2).intValue();
        modelsList.get(i).setFill(color(red, green, blue));
      }
      shape(modelsList.get(i));
      popMatrix();
    }

  }

  int GetShapeCount() {
    return numModels;
  }

  int GetLightCount() {
    return numLights;
  }
}
