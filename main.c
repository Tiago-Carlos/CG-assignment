#include <glut.h>
#include <stdio.h>

GLfloat horzangle = -45.0, vertangle = 30.0, distance = -6.0;
GLfloat escalaX = 1.0, escalaY = 1.0, escalaZ = 1.0, ordem = 1.0;
GLfloat teste = 0;

static int arm1 = -30, arm2 = 60, head = 0, all = 0;

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
    // Lines X, Y e Z
    // Red = Y
    // Green = Z
    // Blue = X
    // glVertex(X, Y, Z)

    glColor3f(0.0f, 0.0f, 0.5f);
    glPushMatrix();
        // esfera 1
        glTranslatef(2.0f, 0.0f, 2.0f);
        glutSolidSphere(0.8, 16, 16);
    glPopMatrix();
    
    glPushMatrix();
        // esfera 2
        glTranslatef(-2.0f, 0.0f, 2.0f);
        glutSolidSphere(0.8, 16, 16);
    glPopMatrix();

    glPushMatrix();
        // esfera 3
        glTranslatef(-2.0f, 0.0f, -2.0f);
        glutSolidSphere(0.8, 16, 16);
    glPopMatrix();

    glPushMatrix();
        // esfera 4
        glTranslatef(2.0f, 0.0f, -2.0f);
        glutSolidSphere(0.8, 16, 16);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 0.03, 0.0);

    glRotatef((GLfloat)all, 0.0, 1.0, 0.0);

    glPushMatrix();
        // Base
        glScalef(1.0, 0.2, 1.0);
        glutSolidCube(0.25);
    glPopMatrix();

    glTranslatef(0.0, 0.05, 0.0);
    glRotatef((GLfloat)arm1, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.19, 0.0);

    glPushMatrix();
        // arm 1
        glColor3f(0.0f, 0.5f, 0.5f);
        glScalef(0.25, 1.5, 0.25);
        glutSolidCube(0.25);
    glPopMatrix();

    glTranslatef(0.0, 0.19 , 0.0);
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

void ChangeSize(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, width / height, 1.0, 10.0);
}

//Tratamento do pressionar das teclas no teclado
void KeyboardSpecialOptions(unsigned char key, int x, int y)
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

void main(int argc, char* argv[]) {
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
    init();
    glutMainLoop();
}
