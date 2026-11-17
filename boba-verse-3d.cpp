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

bool isWireframe = false;

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

void drawBobaCup() {
    const Theme& t = themes[currentTheme];

    glPushMatrix();
    glTranslatef(0.0f, -0.52f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(t.bobaLid.r, t.bobaLid.g, t.bobaLid.b);
    glutSolidTorus(0.06, 0.23, 16, 28);
    glPopMatrix();

    const float pearlPos[9][3] = {
        { -0.11f, -0.26f,  0.08f },
        {  0.10f, -0.27f,  0.07f },
        {  0.00f, -0.28f, -0.10f },
        { -0.04f, -0.18f,  0.13f },
        {  0.13f, -0.16f, -0.05f },
        { -0.13f, -0.14f, -0.06f },
        {  0.02f, -0.10f,  0.03f },
        { -0.07f, -0.34f, -0.01f },
        {  0.07f, -0.34f,  0.02f }
    };
    glColor3f(0.08f, 0.05f, 0.09f);
    for (int i = 0; i < 9; i++) {
        glPushMatrix();
        glTranslatef(pearlPos[i][0], pearlPos[i][1], pearlPos[i][2]);
        glutSolidSphere(0.065, 14, 14);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.42f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(t.bobaLid.r, t.bobaLid.g, t.bobaLid.b);
    glutSolidTorus(0.045, 0.41, 16, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.43f, 0.0f);
    glScalef(1.0f, 0.36f, 1.0f);
    glColor3f(t.bobaLid.r, t.bobaLid.g, t.bobaLid.b);
    glutSolidSphere(0.40, 24, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.10f, 0.56f, 0.02f);
    glRotatef(-16.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.065f, 0.78f, 0.065f);
    glColor3f(t.bobaStraw.r, t.bobaStraw.g, t.bobaStraw.b);
    glutSolidCube(1.0);
    glPopMatrix();

    if (!isWireframe) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
        glColor4f(t.bobaCup.r, t.bobaCup.g, t.bobaCup.b, 0.62f);
    }
    else {
        glColor3f(t.bobaCup.r, t.bobaCup.g, t.bobaCup.b);
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.42f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.41, 1.00, 28, 12);
    glPopMatrix();

    if (!isWireframe) {
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
}

void drawDonut() {
    const Theme& t = themes[currentTheme];

    glPushMatrix();
    glColor3f(t.donutDough.r, t.donutDough.g, t.donutDough.b);
    glutSolidTorus(0.17, 0.36, 22, 36);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.035f);
    glColor3f(t.donutGlaze.r, t.donutGlaze.g, t.donutGlaze.b);
    glutSolidTorus(0.155, 0.36, 20, 36);
    glPopMatrix();

    const float sprinkleAngles[10] = {
        0.0f, 36.0f, 72.0f, 108.0f, 144.0f,
        180.0f, 216.0f, 252.0f, 288.0f, 324.0f
    };
    const float sprinkleColors[5][3] = {
        {1.0f, 0.95f, 0.45f},
        {0.45f, 0.96f, 1.0f},
        {0.98f, 0.98f, 1.0f},
        {0.62f, 1.0f, 0.72f},
        {0.82f, 0.55f, 1.0f}
    };

    for (int i = 0; i < 10; i++) {
        float rad = sprinkleAngles[i] * 3.14159265f / 180.0f;
        float radiusRing = (i % 2 == 0) ? 0.38f : 0.33f;
        float sx = std::cos(rad) * radiusRing;
        float sy = std::sin(rad) * radiusRing;

        glPushMatrix();
        glTranslatef(sx, sy, 0.185f);
        glRotatef(sprinkleAngles[i] + 35.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(sprinkleColors[i % 5][0], sprinkleColors[i % 5][1], sprinkleColors[i % 5][2]);
        if (i % 2 == 0) {
            glScalef(0.08f, 0.03f, 0.03f);
            glutSolidCube(1.0);
        }
        else {
            glutSolidSphere(0.028, 10, 10);
        }
        glPopMatrix();
    }
}

void drawRetroConsole() {
    const Theme& t = themes[currentTheme];

    glPushMatrix();
    glScalef(0.86f, 0.94f, 0.58f);
    glColor3f(t.consoleBody.r, t.consoleBody.g, t.consoleBody.b);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.16f, 0.295f);
    glScalef(0.66f, 0.42f, 0.04f);
    glColor3f(0.10f, 0.07f, 0.20f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.16f, 0.318f);
    glScalef(0.54f, 0.32f, 0.02f);
    glColor3f(0.45f, 1.00f, 0.88f);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(t.consoleAccent.r, t.consoleAccent.g, t.consoleAccent.b);
    glPushMatrix();
    glTranslatef(-0.20f, -0.22f, 0.305f);
    glScalef(0.18f, 0.06f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.20f, -0.22f, 0.305f);
    glScalef(0.06f, 0.18f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.14f, -0.25f, 0.305f);
    glScalef(0.08f, 0.08f, 0.05f);
    glColor3f(1.0f, 0.45f, 0.78f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25f, -0.18f, 0.305f);
    glScalef(0.08f, 0.08f, 0.05f);
    glColor3f(1.0f, 0.90f, 0.42f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.28f, 0.56f, -0.05f);
    glScalef(0.05f, 0.24f, 0.05f);
    glColor3f(t.consoleAccent.r, t.consoleAccent.g, t.consoleAccent.b);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.28f, 0.70f, -0.05f);
    glColor3f(1.0f, 0.55f, 0.85f);
    glutSolidSphere(0.055, 12, 12);
    glPopMatrix();
}

void drawBitmapText(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

void drawTextOverlay() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, winWidth, 0, winHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.05f, 0.03f, 0.12f, 0.65f);

    glBegin(GL_QUADS);
    glVertex2f(14.0f, (float)winHeight - 14.0f);
    glVertex2f(420.0f, (float)winHeight - 14.0f);
    glVertex2f(420.0f, (float)winHeight - 72.0f);
    glVertex2f(14.0f, (float)winHeight - 72.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(14.0f, 14.0f);
    glVertex2f((float)winWidth - 14.0f, 14.0f);
    glVertex2f((float)winWidth - 14.0f, 48.0f);
    glVertex2f(14.0f, 48.0f);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(1.0f, 0.72f, 0.92f);
    drawBitmapText(26.0f, (float)winHeight - 36.0f, "BOBA-VERSE 3D  //  Y2K PASTEL STUDIO", GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.95f, 0.95f, 1.0f);
    drawBitmapText(26.0f, (float)winHeight - 58.0f, "Scene : Floor Grid + Boba Cup + Donut + Retro Console", GLUT_BITMAP_HELVETICA_12);

    glColor3f(0.92f, 0.86f, 1.0f);
    drawBitmapText(26.0f, 27.0f, "Objek 3D: Boba Cup, Donut, & Retro Cube Console", GLUT_BITMAP_HELVETICA_12);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
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

    glPushMatrix();
    glTranslatef(-1.85f, 0.05f, 0.0f);
    glRotatef(12.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-18.0f, 0.0f, 1.0f, 0.0f);
    drawBobaCup();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
    drawDonut();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.85f, 0.05f, 0.0f);
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
    drawRetroConsole();
    glPopMatrix();

    drawTextOverlay();

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