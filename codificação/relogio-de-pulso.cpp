#include <GL/glut.h> // a glut inclui a gl.h
#include <unistd.h>

#include <cmath>
#include <cstdlib> // para usar a funcao exit
#include <iostream>
using namespace std;

struct PontoXY
{
    GLfloat x;
    GLfloat y;
    GLfloat angulo;
    GLfloat escala;
    // construtor padrao, vai construir o objeto na origem
    PontoXY()
    {
        x = 0;
        y = 0;
        angulo = 0;
        escala = 1;
    }
};

#define alturaTextura 64
#define larguraTextura 64
static GLubyte imagemTextura[alturaTextura][larguraTextura][4];
bool temIluminacao = false, animacaoAtiva = true, temTextura = false;

PontoXY pontoPrincipal = PontoXY();

float anguloSegundo = 360.0f, anguloMinuto = 360.0f, anguloHora = 360.0f;

void movimentarPonteiros()
{
    if (!animacaoAtiva)
        return;
    usleep(1000000);
    anguloSegundo -= 6.0f;
    anguloMinuto -= 6.0f / 60.0f;
    anguloHora -= 6.0f / 3600.0f;
    if (anguloSegundo == 0)
        anguloSegundo = 360.0f;
    if (anguloMinuto == 0)
        anguloMinuto = 360.0f;
    if (anguloHora == 0)
        anguloHora = 3600.f;
    glutPostRedisplay();
}

void criaImagemTextura(void)
{
    int tamanhoTextura;

    for (int i = 0; i < alturaTextura; i++)
    {
        for (int j = 0; j < larguraTextura; j++)
        {
            tamanhoTextura = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
            imagemTextura[i][j][0] = (GLubyte)tamanhoTextura;
            imagemTextura[i][j][1] = (GLubyte)tamanhoTextura;
            imagemTextura[i][j][2] = (GLubyte)tamanhoTextura;
            imagemTextura[i][j][3] = (GLubyte)255;
        }
    }
}

GLfloat BACKGROUND_COLOR_DEFAULT[3] = {0, 0, 0};

void quadrilatero(float x, float y, float tamanho, float larguraX, float larguraY, GLfloat backgroundColor[] = BACKGROUND_COLOR_DEFAULT)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
    glVertex2f(x - (tamanho * larguraX), y + (tamanho * larguraY));
    glVertex2f(x + (tamanho * larguraX), y + (tamanho * larguraY));
    glVertex2f(x + (tamanho * larguraX), y - (tamanho * larguraY));
    glVertex2f(x - (tamanho * larguraX), y - (tamanho * larguraY));
    glEnd();
    glPopMatrix();
}

void quadrilateroComTextura(float x, float y, float tamanho, float larguraX, float larguraY, GLfloat backgroundColor[] = BACKGROUND_COLOR_DEFAULT)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(backgroundColor[0], backgroundColor[1], backgroundColor[2]);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x - (tamanho * larguraX), y + (tamanho * larguraY));
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + (tamanho * larguraX), y + (tamanho * larguraY));
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + (tamanho * larguraX), y - (tamanho * larguraY));
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x - (tamanho * larguraX), y - (tamanho * larguraY));
    glEnd();
    glPopMatrix();
}

void circunferencia(GLfloat x, GLfloat y, GLfloat raio)
{
    int i;
    int triangleAmount = 20;

    GLfloat twicePi = 2.0f * 3.14159265359;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (raio * cos(i * twicePi / triangleAmount)),
            y + (raio * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

void desenhaArmacao()
{
    GLfloat lineRgbColor[] = {0.94, 0.64, 0.04};
    quadrilatero(0, 0, 0.25, 1, 1, lineRgbColor);
}

void desenhaMarcadoresHora()
{
    glPushMatrix();
    GLfloat lineRgbColor[] = {0.0, 0.31, 0.93};
    quadrilatero(0, 0.205, 0.015, 0.1, 1, lineRgbColor);
    quadrilatero(0, -0.205, 0.015, 0.1, 1, lineRgbColor);
    quadrilatero(0.205, 0, 0.015, 1, 0.1, lineRgbColor);
    quadrilatero(-0.205, 0, 0.015, 1, 0.1, lineRgbColor);
    glPopMatrix();
}

void desenhaPonteiros()
{
    glPushMatrix();
    glRotatef(anguloHora, 0, 0, 1);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0.09, 0);
    glEnd();

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2f(0.09, 0.01);
    glVertex2f(0.11, 0);
    glVertex2f(0.09, -0.01);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(anguloMinuto, 0, 0, 1);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0, 0.13);
    glEnd();

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.01, 0.13);
    glVertex2f(0, 0.15);
    glVertex2f(0.01, 0.13);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(anguloSegundo, 0, 0, 1);
    glColor3f(0, 0, 0);
    glColor3f(0.72, 0.33, 0.31);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0, -0.15);
    glEnd();
    glPopMatrix();
}

void desenhaVidro()
{
    GLfloat lineRgbColor[] = {0.70, 0.86, 0.94};
    glPushMatrix();
    if (temIluminacao)
    {
        GLfloat light_position[] = {0.0, 0.0, 0.0, 0.0};
        GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
        quadrilatero(0, 0, 0.22, 1, 1, lineRgbColor);
        desenhaMarcadoresHora();
        desenhaPonteiros();
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_DEPTH_TEST);
    }
    else
    {
        quadrilatero(0, 0, 0.22, 1, 1, lineRgbColor);
        desenhaMarcadoresHora();
        desenhaPonteiros();
    }

    glPopMatrix();
}

void desenhaDobradica()
{
    GLfloat lineRgbColor[] = {0.60, 0.60, 0.60};
    quadrilatero(0, 0.290, 0.1, 1.8, 0.4, lineRgbColor);
    quadrilatero(0, -0.290, 0.1, 1.8, 0.4, lineRgbColor);
}

void desenhaBraceletes()
{
    if (temTextura)
    {
        GLfloat lineRgbColor[] = {1, 1, 1};
        quadrilateroComTextura(0, 0.553, 0.8, 0.20, 0.28, lineRgbColor);
        quadrilateroComTextura(0, -0.553, 0.8, 0.20, 0.28, lineRgbColor);
    }
    else
    {
        GLfloat lineRgbColor[] = {0, 0, 0};
        quadrilateroComTextura(0, 0.553, 0.8, 0.20, 0.28, lineRgbColor);
        quadrilateroComTextura(0, -0.553, 0.8, 0.20, 0.28, lineRgbColor);
    }

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.157333, -0.777);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(-0.109333, -0.897500);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.109333, -0.897500);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.157333, -0.777);
    glEnd();
}

void desenhaFivela()
{
    GLfloat lineRgbColor[] = {1, 0.8, 0.6};
    quadrilatero(0, 0.837, 0.1, 1.6, 0.6, lineRgbColor);
    GLfloat lineRgbColor1[] = {1, 1, 1};
    quadrilatero(0, 0.837, 0.1, 1.4, 0.4, lineRgbColor1);
    quadrilatero(0, 0.827, 0.1, 0.1, 0.3, lineRgbColor);
}

void desenhaRegulagens()
{
    glColor3f(1, 1, 1);
    circunferencia(0, -0.45, 0.01);
    circunferencia(0, -0.55, 0.01);
    circunferencia(0, -0.65, 0.01);
}

void desenhaRelogio()
{
    glPushMatrix();
    desenhaArmacao();
    glPopMatrix();

    glPushMatrix();
    desenhaVidro();
    glPopMatrix();

    glPushMatrix();
    desenhaDobradica();
    glPopMatrix();

    glPushMatrix();
    desenhaBraceletes();
    glPopMatrix();

    glPushMatrix();
    desenhaFivela();
    glPopMatrix();

    glPushMatrix();
    desenhaRegulagens();
    glPopMatrix();
}

void opcoesMouse(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON)
    {
        pontoPrincipal.angulo += 1;
    }
    else if (botao == GLUT_RIGHT_BUTTON)
    {
        pontoPrincipal.angulo -= 1;
    }
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        printf("%f , %f\n", -1 + (float)x / (float)(glutGet(GLUT_WINDOW_WIDTH) / 2), +1 - (float)y / (float)(glutGet(GLUT_WINDOW_HEIGHT) / 2));
    }
    glutPostRedisplay();
}

void aplicaTextura()
{
    if (!temTextura)
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
    }
}

void mostraMenu()
{
    cout << "\nDurante a execucao, voce pode usar as seguintes teclas:\n"
         << " [ESC] - Para fechar a janela\n"
         << " [v] - Voltar o relógio para posição original\n"
         << " [a] - Transladar o relógio para esquerda\n"
         << " [d] - Transladar o relógio para direita\n"
         << " [w] - Transladar o relógio para cima\n"
         << " [s] - Transladar o relógio para baixo\n"
         << " [+] - Aumentar a escala do relógio\n"
         << " [-] - Diminuir a escala do relógio\n"
         << " [k] - Rotacionar ponteiro hora do relógio no sentido horário\n"
         << " [l] - Rotacionar ponteiro minuto do relógio sentido horário\n"
         << " [z] - Rotacionar ponteiro hora do relógio no sentido anti-horário\n"
         << " [x] - Rotacionar ponteiro minuto do relógio sentido anti-horário\n"
         << " [p] - Pausar ponteiro segundo do relógio\n"
         << " [i] - Ativar iluminação no vidro do relógio\n"
         << " [t] - Ativar textura no bracelete do relógio\n"
         << " [Botão esquerdo mouse] - Rotacionar o relógio para esquerda\n"
         << " [Botão direito mouse] - Rotacionar o relógio para direita\n\n";
}

void opcoesTeclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        pontoPrincipal.x -= 0.1f;
        break;
    case 's':
        pontoPrincipal.y -= 0.1f;
        break;
    case 'd':
        pontoPrincipal.x += 0.1f;
        break;
    case 'w':
        pontoPrincipal.y += 0.1f;
        break;
    case 'i':
        temIluminacao = !temIluminacao;
        break;
    case '+':
        pontoPrincipal.escala += 0.1;
        break;
    case '-':
        pontoPrincipal.escala -= 0.1;
        break;
    case 'v':
        pontoPrincipal = PontoXY();
        break;
    case 't':
        temTextura = !temTextura;
        break;
    case 'p':
        animacaoAtiva = !animacaoAtiva;
        break;
    case 'k':
        anguloHora -= 30;
        break;
    case 'l':
        anguloMinuto -= 24;
        break;
    case 'z':
        anguloHora += 30;
        break;
    case 'x':
        anguloMinuto += 24;
        break;
    case 27:
        exit(0);
        break;
    }
    if (anguloHora == 0)
        anguloHora = 360;
    if (anguloMinuto == 0)
        anguloMinuto = 360;
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(1, 1, 1, 1); // Cor de fundo da janela
    criaImagemTextura();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, larguraTextura, alturaTextura,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, imagemTextura);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    aplicaTextura();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    aplicaTextura();
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glTranslatef(pontoPrincipal.x, pontoPrincipal.y, 0.0f);
    glRotatef(pontoPrincipal.angulo, 0.0f, 0.0f, 1.0);
    glScalef(pontoPrincipal.escala, pontoPrincipal.escala, 0.0f);
    desenhaRelogio();
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(-1.0, 1.0,
                   -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h,
                   1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    mostraMenu();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(750, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("GAC 104 Computacao Grafica - Relogio de Pulso");
    init();
    glutKeyboardFunc(opcoesTeclado);
    glutMouseFunc(opcoesMouse);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(movimentarPonteiros);
    glutMainLoop();
    return 0;
}
