abstract class Interpolator
{
  Animation animation;
  
  // Where we at in the animation?
  float currentTime = 0;
  int numOfFrames;
  
  // To interpolate, or not to interpolate... that is the question
  boolean snapping = false;
  
  void SetAnimation(Animation anim)
  {
    animation = anim;
    numOfFrames = anim.numOfKeyFrames;
  }

  void setStartTime(float startTime) {
    currentTime = startTime;
  }
  
  void SetFrameSnapping(boolean snap)
  {
    snapping = snap;
  }
  PVector linearInterpolate(PVector start, PVector end, float ratio) {
    float x = ((end.x - start.x) * ratio) + start.x;
    float y = ((end.y - start.y) * ratio) + start.y;
    float z = ((end.z - start.z) * ratio) + start.z;
    return new PVector(x, y, z);
  }

  void UpdateTime(float time)
  {
    // Check to see if the time is out of bounds (0 / Animation_Duration)
    // If so, adjust by an appropriate amount to loop correctly
    currentTime += time;
    if (time > 0.0) {
      if ( currentTime > animation.animDuration) {
        currentTime =  currentTime - animation.animDuration;
      }
    }  
    else {
      if (currentTime < 0.0) {
        currentTime = currentTime + animation.animDuration;
      }
    }
  }
  
  // Implement this in derived classes
  // Each of those should call UpdateTime() and pass the time parameter
  // Call that function FIRST to ensure proper synching of animations
  abstract void Update(float time);
}

class ShapeInterpolator extends Interpolator { 
  // The result of the data calculations - either snapping or interpolating
  PShape currentShape;
  
  // Changing mesh colors
  color fillColor;
  
  PShape GetShape() {
    return currentShape;
  }
  
  void Update(float time) {
    // TODO: Create a new PShape by interpolating between two existing key frames
    // using linear interpolation
    // Get key frames
    UpdateTime(time);
    int nextIndex = 0; //<>//
    int prevIndex = 0;
    if (time > 0) {
      for (int i = 0; i < numOfFrames; i++) {
        // Logic to calculate the current index and the next index
        if (currentTime < animation.keyFrames.get(i).time ) {
            nextIndex = i;
            if (nextIndex == 0) {
              prevIndex = animation.keyFrames.size() - 1;
            }
            else {
              prevIndex = i - 1;
            }
          break;
        }
      }
    }
    else {
      for (int i = numOfFrames - 1; i >= 0 ; i--) {
        // Logic to calculate the current index and the next index
        if (currentTime > animation.keyFrames.get(i).time ) {
            nextIndex = i;
            prevIndex = i + 1;
          break;
        }
        if (i == 0) {
          nextIndex = numOfFrames - 1;
          prevIndex = 0;
          break;
        }
      }
    }

    KeyFrame prevFrame = animation.keyFrames.get(prevIndex);
    KeyFrame nextFrame = animation.keyFrames.get(nextIndex);
    float timeRatio = 0.0;
    float timeBetweenFrames = 0.0;

    if (time > 0) {
      timeBetweenFrames = nextFrame.time - prevFrame.time;
      if (timeBetweenFrames < 0) {
        timeBetweenFrames = nextFrame.time;
      }
      
      if ( prevFrame.time > nextFrame.time) {
        timeRatio = (currentTime / timeBetweenFrames);
      }
      else {
        timeRatio = ((currentTime - prevFrame.time) / timeBetweenFrames);
      }
    }
    else {
      timeBetweenFrames = prevFrame.time - nextFrame.time;
      if (timeBetweenFrames < 0) {
        timeBetweenFrames = prevFrame.time;
        timeRatio = ((timeBetweenFrames - currentTime) / timeBetweenFrames);
      }
      else {
        timeRatio = ((timeBetweenFrames - (currentTime - nextFrame.time)) / timeBetweenFrames);
      }
    }

    // We have the frames time ot interperolate and make a shape. 
    currentShape = createShape();
    currentShape.beginShape(TRIANGLE); 
    currentShape.fill(fillColor);
    currentShape.noStroke();
    for (int i = 0; i < animation.numOfDataPoints; i++) {
      PVector pointStart = prevFrame.points.get(i);
      PVector pointEnd = nextFrame.points.get(i);
      PVector result = linearInterpolate(pointStart, pointEnd, timeRatio);
      if (snapping) {
        currentShape.vertex(pointStart.x, pointStart.y, pointStart.z);
      }
      else {
        currentShape.vertex(result.x, result.y, result.z);
      }
    }
    currentShape.endShape();

  }
}

class PositionInterpolator extends Interpolator {
  PVector currentPosition;
  
  void Update(float time) {
    // The same type of process as the ShapeInterpolator class... except
    // this only operates on a single point
    UpdateTime(time);
    int nextIndex = 0; //<>//

    int prevIndex = 0;
    if (time > 0) {
      for (int i = 0; i < animation.getNumOfKeyFrames(); i++) {
        // Logic to calculate the current index and the next index
        if (currentTime < animation.keyFrames.get(i).time ) {
            nextIndex = i;
            if (nextIndex == 0) {
              prevIndex = animation.keyFrames.size() - 1;
            }
            else {
              prevIndex = i - 1;
            }
          break;
        }
      }
    }
    else {
      for (int i = animation.getNumOfKeyFrames() - 1; i >= 0 ; i--) {
        // Logic to calculate the current index and the next index
        if (currentTime > animation.keyFrames.get(i).time ) {
            nextIndex = i;
            prevIndex = i + 1;
          break;
        }
        if (i == 0) {
          nextIndex = numOfFrames - 1;
          prevIndex = 0;
          break;
        }
      }
    }

    KeyFrame prevFrame = animation.keyFrames.get(prevIndex);
    KeyFrame nextFrame = animation.keyFrames.get(nextIndex);
    float timeRatio = 0.0;
    float timeBetweenFrames = 0.0;

    if (time > 0) {
      timeBetweenFrames = nextFrame.time - prevFrame.time;
      if (timeBetweenFrames < 0) {
        timeBetweenFrames = nextFrame.time;
      }
      
      if ( prevFrame.time > nextFrame.time) {
        timeRatio = (currentTime / timeBetweenFrames);
      }
      else {
        timeRatio = ((currentTime - prevFrame.time) / timeBetweenFrames);
      }
    }
    else {
      timeBetweenFrames = prevFrame.time - nextFrame.time;
      if (timeBetweenFrames < 0) {
        timeBetweenFrames = prevFrame.time;
        timeRatio = ((timeBetweenFrames - currentTime) / timeBetweenFrames);
      }
      else {
        timeRatio = ((timeBetweenFrames - (currentTime - nextFrame.time)) / timeBetweenFrames);
      }
    }

    // We have the frames time ot interperolate and make a shape. 
    PVector pointStart = prevFrame.points.get(0);
    PVector pointEnd = nextFrame.points.get(0);
    PVector result = linearInterpolate(pointStart, pointEnd, timeRatio);
    if (snapping) {
      currentPosition = pointStart;
    }
    else {
      currentPosition = result;
    }
  }
}
