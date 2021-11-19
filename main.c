#include <glut.h>
#include <stdio.h>

GLfloat horzangle = -45.0, vertangle = 30.0, distance = -6.0;
GLfloat escalaX = 1.0, escalaY = 1.0, escalaZ = 1.0, ordem = 1.0;
GLfloat teste = 0;

static int arm1 = -30, arm2 = 60, head = 0;

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
    // Lines X, Y e Z
    // Red = Y
    // Green = Z
    // Blue = X
    // glVertex(X, Y, Z)
    glBegin(GL_LINES);
    // GlColor3f(red, green, blue)
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex3f(1.0f, 0.0f, 2.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(-1.0f, 0.0f, 2.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 0.03, 0.0);

    glPushMatrix();
    // Base
    glScalef(1.0, 0.2, 1.0);
    glutWireCube(0.25);
    glPopMatrix();

    glTranslatef(0.0, 0.05, 0.0);
    glRotatef((GLfloat)arm1, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.19, 0.0);

    glPushMatrix();
    // arm 1
    glScalef(0.25, 1.5, 0.25);
    glutWireCube(0.25);
    glPopMatrix();

    glTranslatef(0.0, 0.19 , 0.0);
    glRotatef((GLfloat)arm2, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.18, 0.0);

    glPushMatrix();
    // arm 2
    glScalef(0.25, 1.5, 0.25);
    glutWireCube(0.24);
    glPopMatrix();

    glTranslatef(0.0, 0.18, 0.0);
    glRotatef((GLfloat)head, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.05, 0.0);

    glPushMatrix();
    // Lamp
    glScalef(1.0, 1.0, 1.0);
    glutWireCube(0.10);
    glTranslatef(0.0, 0.0, 0.15);
    glutWireCube(0.20);
    glPopMatrix();

    //glFlush();
    glutSwapBuffers();
}

void ChangeSize(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, width / height, 1.0, 10.0);
}

// Funcao de cada tecla
void LeftKey(void) {
    horzangle += 5;
    printf("left\n");
    RenderScene();
}

void RightKey(void) {
    horzangle -= 5;
    printf("right\n");
    RenderScene();
}

void UpKey(void) {
    vertangle += 5;
    printf("up\n");
    RenderScene();
}

void DownKey(void) {
    vertangle -= 5;
    printf("down\n");
    RenderScene();
}

void F1Key(void) {
    head = 0;
    printf("F1\n");
    RenderScene();
}

void F2Key(void) {
    escalaY += ordem * 0.1;
    printf("F2\n");
    RenderScene();
}

void F3Key(void) {
    escalaZ += ordem * 0.1;
    printf("F3\n");
    RenderScene();
}

void F4Key(void) {
    ordem = -ordem;
    printf("F4\n");
    RenderScene();
}

void F5Key(void) {
    teste += ordem * 0.01;
    printf("%f", teste);
    printf("\n");
    RenderScene();
}

//Tratamento do pressionar das teclas no teclado
void KeyboardSpecialOptions(unsigned char key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        UpKey();
        break;
    case GLUT_KEY_DOWN:
        DownKey();
        break;
    case GLUT_KEY_LEFT:
        LeftKey();
        break;
    case GLUT_KEY_RIGHT:
        RightKey();
        break;
    case GLUT_KEY_F1:
        F1Key();
        break;
    case GLUT_KEY_F2:
        F2Key();
        break;
    case GLUT_KEY_F3:
        F3Key();
        break;
    case GLUT_KEY_F4:
        F4Key();
        break;
    case GLUT_KEY_F5:
        F5Key();
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lampida!");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyboardSpecialOptions);
    glutKeyboardFunc(KeyboardOptions);
    glutMouseFunc(MouseOptions);
    glutDisplayFunc(RenderScene);
    glutMainLoop();
}
