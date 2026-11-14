#include <freeglut.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

struct Color3 {
    float r, g, b;
};

struct Theme {
    const char* name;
    Color3 bgTop;
    Color3 bgBottom;
    Color3 floorColor;
    Color3 gridColor;
    Color3 bobaCup;
    Color3 bobaLid;
    Color3 bobaStraw;
    Color3 donutDough;
    Color3 donutGlaze;
    Color3 consoleBody;
    Color3 consoleAccent;
    Color3 indicatorColor;
};

int currentTheme = 0;
const int THEME_COUNT = 3;

Theme themes[THEME_COUNT] = {
    {
        "Pastel Pink",
        {0.102f, 0.063f, 0.200f},
        {0.220f, 0.110f, 0.360f},
        {0.340f, 0.220f, 0.480f},
        {0.980f, 0.580f, 0.850f},
        {1.000f, 0.660f, 0.840f},
        {1.000f, 0.930f, 0.970f},
        {0.520f, 0.980f, 0.860f},
        {0.980f, 0.840f, 0.620f},
        {1.000f, 0.520f, 0.780f},
        {0.460f, 0.920f, 0.980f},
        {0.720f, 0.480f, 0.980f},
        {0.980f, 0.880f, 0.400f}
    },
    themes[0],
    themes[0]
};

int winWidth = 1080;
int winHeight = 680;

void drawFloorPlatform() {
    const Theme& t = themes[currentTheme];

    glPushMatrix();
    glTranslatef(0.0f, -0.82f, 0.0f);

    glPushMatrix();
    glScalef(6.8f, 0.16f, 3.6f);
    glColor3f(t.floorColor.r, t.floorColor.g, t.floorColor.b);
    glutSolidCube(1.0);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(t.gridColor.r, t.gridColor.g, t.gridColor.b);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    for (float x = -3.4f; x <= 3.41f; x += 0.425f) {
        glVertex3f(x, 0.085f, -1.8f);
        glVertex3f(x, 0.085f, 1.8f);
    }
    for (float z = -1.8f; z <= 1.81f; z += 0.45f) {
        glVertex3f(-3.4f, 0.085f, z);
        glVertex3f(3.4f, 0.085f, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 1.35, 5.9,
        0.0, 0.00, 0.0,
        0.0, 1.00, 0.0
    );

    GLfloat lightPos[] = { 2.5f, 5.0f, 4.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    drawFloorPlatform();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    winWidth = w;
    winHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void initOpenGL() {
    glClearColor(0.102f, 0.063f, 0.200f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.35f, 0.30f, 0.45f, 1.0f };
    GLfloat diffuseLight[] = { 0.95f, 0.92f, 1.00f, 1.0f };
    GLfloat specularLight[] = { 0.85f, 0.85f, 0.95f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat matSpecular[] = { 0.45f, 0.45f, 0.50f, 1.0f };
    GLfloat matShininess[] = { 36.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("BOBA-VERSE 3D - Y2K Pastel Neon World");

    initOpenGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}