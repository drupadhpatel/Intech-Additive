#include <GL/glut.h>

// Simple hierarchical solar system: Sun -> Earth -> Moon.
// Uses basic lighting with the Sun as a light source.

// Radii
constexpr float SUN_RADIUS = 1.5f;
constexpr float EARTH_RADIUS = 0.6f;
constexpr float MOON_RADIUS = 0.18f;

// Distances from parent body
constexpr float EARTH_DISTANCE = 5.0f;
constexpr float MOON_DISTANCE = 1.5f;

// Animation speeds (degrees per frame tick)
constexpr float EARTH_ORBIT_SPEED = 0.2f;
constexpr float EARTH_ROTATION_SPEED = 1.5f;
constexpr float MOON_ORBIT_SPEED = 1.5f;
constexpr float MOON_ROTATION_SPEED = 2.5f;

// Animation state
float earthOrbitAngle = 0.0f;
float earthRotationAngle = 0.0f;
float moonOrbitAngle = 0.0f;
float moonRotationAngle = 0.0f;

void initScene() {
    glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Lighting setup: Sun as a point light.
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambient[] = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 0.9f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 0.9f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void drawSphere(float radius, const GLfloat color[3]) {
    glColor3fv(color);
    glutSolidSphere(radius, 32, 24);
}

void drawSolarSystem() {
    // Light position at Sun's location (w=1 => positional light).
    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Draw Sun
    const GLfloat sunColor[] = {1.0f, 0.85f, 0.0f};
    drawSphere(SUN_RADIUS, sunColor);

    // Earth orbit around Sun
    glPushMatrix();
    glRotatef(earthOrbitAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(EARTH_DISTANCE, 0.0f, 0.0f);

    // Earth's self-rotation
    glPushMatrix();
    glRotatef(earthRotationAngle, 0.0f, 1.0f, 0.0f);
    const GLfloat earthColor[] = {0.1f, 0.35f, 0.8f};
    drawSphere(EARTH_RADIUS, earthColor);
    glPopMatrix();

    // Moon orbit around Earth
    glPushMatrix();
    glRotatef(moonOrbitAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(MOON_DISTANCE, 0.0f, 0.0f);
    glRotatef(moonRotationAngle, 0.0f, 1.0f, 0.0f);
    const GLfloat moonColor[] = {0.75f, 0.75f, 0.75f};
    drawSphere(MOON_RADIUS, moonColor);
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 6.0, 18.0, // eye
        0.0, 0.0, 0.0,  // center
        0.0, 1.0, 0.0   // up
    );

    drawSolarSystem();

    glutSwapBuffers();
}

void update(int) {
    earthOrbitAngle = fmodf(earthOrbitAngle + EARTH_ORBIT_SPEED, 360.0f);
    earthRotationAngle = fmodf(earthRotationAngle + EARTH_ROTATION_SPEED, 360.0f);
    moonOrbitAngle = fmodf(moonOrbitAngle + MOON_ORBIT_SPEED, 360.0f);
    moonRotationAngle = fmodf(moonRotationAngle + MOON_ROTATION_SPEED, 360.0f);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 100.0);
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) { // Esc
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("OpenGL Solar System - Hierarchical Modeling");

    initScene();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}


