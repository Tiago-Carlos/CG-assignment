#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdio>

GLfloat horzangle = 0.0, vertangle = 0.0, distance = -6.0;
GLfloat escalaX = 1.0, escalaY = 1.0, escalaZ = 1.0, ordem = 1.0;
GLfloat teste = 0;

static int arm1 = -30, arm2 = 60, head = 0, all = 0;

#define	checkImageWidth 64
#define	checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

void makeCheckImage(void)
{
    int i, j, c;

    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
            checkImage[i][j][0] = (GLubyte)c;
            checkImage[i][j][1] = (GLubyte)c;
            checkImage[i][j][2] = (GLubyte)c;
            checkImage[i][j][3] = (GLubyte)255;
        }
    }
}

class Ball {
    double radius;
    double maximumHeight;
    double x;
    double y;
    double z;
    int direction;
public:
    Ball(double r, double h, double x, double z) :
        radius(r), maximumHeight(h), direction(-1),
        y(h), x(x), z(z) {
    }
    void update() {
        y += direction * 0.05;
        if (y > maximumHeight) {
            y = maximumHeight; direction = -1;
        }
        else if (y < radius) {
            y = radius; direction = 1;
        }
        glPushMatrix();
            glColor3f(0.0f, 0.0f, 0.5f);
            glTranslated(x, y, z);
            glutSolidSphere(radius, 30, 30);
        glPopMatrix();
    }
};
Ball balls[] = {
  Ball(1, 3, 2, 2),
  Ball(0.5, 2, -2, 2),
  Ball(0.8, 4, -2, -2)
};

void init() {
    GLfloat light_diffuse[] = { 1, 1, 1, 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 75.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.126f, 0.126f, 0.128f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_NORMALIZE);

    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
#ifdef GL_VERSION_1_1
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#endif
}

void RenderScene(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -0.5f, distance);
    glRotatef(vertangle, 1.0f, 0.0f, 0.0f);
    glRotatef(horzangle, 0.0f, 1.0f, 0.0f);
    glScalef(escalaX, escalaY, escalaZ);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_FLAT);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
#ifdef GL_VERSION_1_1
    glBindTexture(GL_TEXTURE_2D, texName);
#endif
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 0.0, 2.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 0.0, -1.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 0.0, -1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, 0.0, 2.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //checkerboard.draw();
    // Lines X, Y e Z
    // Red = Y
    // Green = Z
    // Blue = X
    // glVertex(X, Y, Z)
    for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
        balls[i].update();
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 0.03, 0.0);

    glRotatef((GLfloat)all, 0.0, 1.0, 0.0);

    glPushMatrix();
    // Base
    glScalef(1.0, 0.2, 1.0);
    glutSolidCube(0.25);
    glPopMatrix();

    glRotatef((GLfloat)arm1, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.16, 0.0);

    glPushMatrix();
    // arm 1
    glColor3f(0.0f, 0.5f, 0.5f);
    glScalef(0.25, 1.5, 0.25);
    glutSolidCube(0.25);
    glPopMatrix();

    glTranslatef(0.0, 0.19, 0.0);
    glRotatef((GLfloat)arm2, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.18, 0.0);

    glPushMatrix();
    // arm 2
    glColor3f(0.5f, 0.5f, 0.0f);
    glScalef(0.25, 1.5, 0.25);
    glutSolidCube(0.24);
    glPopMatrix();

    glTranslatef(0.0, 0.18, 0.0);
    glRotatef((GLfloat)head, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.05, 0.0);

    glPushMatrix();
    // Lamp
    glScalef(1.0, 1.0, 1.0);
    glutSolidCube(0.10);
    glTranslatef(0.0, 0.0, 0.15);
    glutSolidCube(0.20);
    glPopMatrix();

    glTranslatef(0.0, 0.0, 0.31);

    glPushMatrix();
        glutWireSphere(0.05, 8, 8);
        GLfloat light_position[] = { 0, 0, 0.35, 1 };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        GLfloat light_spot[] = { 0, 0, 1 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glutSwapBuffers();
}
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

void ChangeSize(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, width / height, 1.0, 10.0);
}

//Tratamento do pressionar das teclas no teclado
void KeyboardSpecialOptions(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        vertangle -= 5;
        printf("up\n");
        RenderScene();
        break;
    case GLUT_KEY_DOWN:
        vertangle += 5;
        printf("down\n");
        RenderScene();
        break;
    case GLUT_KEY_LEFT:
        horzangle -= 5;
        printf("left\n");
        RenderScene();
        break;
    case GLUT_KEY_RIGHT:
        horzangle += 5;
        printf("right\n");
        RenderScene();
        break;
    case GLUT_KEY_F1:
        head = 0;
        printf("F1\n");
        RenderScene();
        break;
    case GLUT_KEY_F2:
        escalaY += ordem * 0.1;
        printf("F2\n");
        RenderScene();
        break;
    case GLUT_KEY_F3:
        escalaZ += ordem * 0.1;
        printf("F3\n");
        RenderScene();
        break;
    case GLUT_KEY_F4:
        ordem = -ordem;
        printf("F4\n");
        RenderScene();
        break;
    case GLUT_KEY_F5:
        teste += ordem * 0.01;
        printf("%f", teste);
        printf("\n");
        RenderScene();
        break;
    }
    glutPostRedisplay();
}

void KeyboardOptions(unsigned char key, int x, int y)
{
    switch (key) {
    case 'a':
        arm2 += 5;
        printf("%i", arm2);
        printf("\n");
        RenderScene();
        break;
    case 's':
        arm1 += 5;
        printf("%i", arm1);
        printf("\n");
        RenderScene();
        break;
    case 'A':
        arm2 -= 5;
        printf("%i", arm2);
        printf("\n");
        RenderScene();
        break;
    case 'S':
        arm1 -= 5;
        printf("%i", arm1);
        printf("\n");
        RenderScene();
        break;
    case 'd':
        head += 5;
        printf("%i", head);
        printf("\n");
        RenderScene();
        break;
    case 'D':
        head -= 5;
        printf("%i", head);
        printf("\n");
        RenderScene();
        break;
    case 'f':
        all += 5;
        printf("%i", all);
        printf("\n");
        RenderScene();
        break;
    case 'F':
        all -= 5;
        printf("%i", all);
        printf("\n");
        RenderScene();
        break;
    case 27:
        exit(0);
    default:
        break;
    }
    glutPostRedisplay();
}

//Tratamento dos botoes do mouse
void MouseOptions(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            distance += 0.2;
            printf("%f", distance);
            printf("\n");
            RenderScene();
        }
    }

    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) {
            distance -= 0.2;
            printf("%f", distance);
            printf("\n");
            RenderScene();
        }
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lampida!");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyboardSpecialOptions);
    glutKeyboardFunc(KeyboardOptions);
    glutMouseFunc(MouseOptions);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}