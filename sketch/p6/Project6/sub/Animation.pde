// Snapshot in time of some amount of data
class KeyFrame
{
  // Where does this thing occur in the animation?
  public float time;

  
  // Because translation and vertex positions are the same thing, this can
  // be reused for either. An array of one is perfectly viable.
  public ArrayList<PVector> points = new ArrayList<PVector>();
}

class Animation
{
  // Animations start at zero, and end... here
  float animDuration = 0.0;
  int numOfKeyFrames = 0;
  int numOfDataPoints = 0;
  float x, y, z;
  float rotationX, rotationY, rotationZ;
  float scaleX, scaleY, scaleZ;
  float r, g, b, a;

  int getNumOfKeyFrames() {
    return keyFrames.size();
  }

  float GetDuration() {
    return keyFrames.get(keyFrames.size()-1).time;
  }

  void addKeyFrame(float _time, ArrayList<PVector> _points) {
    KeyFrame newKeyFrame = new KeyFrame();
    newKeyFrame.time = _time;
    newKeyFrame.points = _points;
    keyFrames.add(newKeyFrame);
  }
  
  void setDuration(float _time) {
    animDuration = _time;
  }
  
  ArrayList<KeyFrame> keyFrames = new ArrayList<KeyFrame>();
}