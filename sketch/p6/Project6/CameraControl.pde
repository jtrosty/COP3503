class CameraControl {
    ArrayList<PVector> targets = new ArrayList<PVector>();
    PVector zeroPoint = new PVector(0, 0, 0);
    float theta = PI / 4.0;
    float phi = PI / 4.0;
    float distance = 250;
    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 0;
    float increment = PI / 360.0;
    PVector currentTarget;
    int currIndex = 0;
    float thetaClampMax = radians(179);
    float thetaClampMin = radians(1);

    CameraControl() {
        targets.add(zeroPoint);
        currentTarget = zeroPoint;
    }

    void Update() {
        phi = -map(mouseX, 0.0, width, 0.0, (2 * PI));
        theta = map(mouseY, 0.0, height, 0.0, (PI));

        cameraX = currentTarget.x + distance * cos(phi) * sin(theta);
        cameraY = currentTarget.y + -distance * cos(theta);
        cameraZ = currentTarget.z + distance * sin(theta) * sin(phi);
        theta = clampTheta(theta);

        camera( cameraX, cameraY, cameraZ,
                currentTarget.x, currentTarget.y, currentTarget.z,
                0, 1, 0); }


    float clampTheta(float theta) {
        if (theta > thetaClampMax)      return thetaClampMax;
        else if (theta < thetaClampMin) return thetaClampMin;
        else                            return theta;
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
        distance += zoom * 10;
        if (distance < 20) distance = 20;
        if (distance > 300) distance = 300;
    }
}