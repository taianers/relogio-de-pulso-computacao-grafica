#include <GL/glut.h>  // a glut inclui a gl.h

#include <cmath>
#include <cstdlib>  // para usar a funcao exit
#include <iostream>

#define PI 3.14159265359;
#define alturaTextura 64
#define larguraTextura 64
static GLubyte imagemTextura[alturaTextura][larguraTextura][4];
bool temIluminacao, ativaAnimacao;

void criaImagemTextura(void) {
    int c;
    for (int i = 0; i < alturaTextura; i++) {
        for (int j = 0; j < larguraTextura; j++) {
            c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
            imagemTextura[i][j][0] = (GLubyte)c;
            imagemTextura[i][j][1] = (GLubyte)c;
            imagemTextura[i][j][2] = (GLubyte)c;
            imagemTextura[i][j][3] = (GLubyte)255;
        }
    }
}

struct PontoXY {
    GLfloat x;
    GLfloat y;
    GLfloat angulo;
    GLfloat escala;
    // construtor padrao, vai construir o objeto na origem
    PontoXY() {
        x = 0;
        y = 0;
        angulo = 0;
        escala = 1;
    }
    void setPonto(GLfloat x1, GLfloat y1) {
        x = x1;
        y = y1;
        angulo = 0;
        escala = 1;
    }
};

PontoXY vetorDePontos[20];

void posicaoOriginalRelogio() {
    // vetorDePontos[1].setPonto(0.551, 0.450);
}

// receber parâmetro da cor
void quadrilatero(float x, float y, float tamanho, float larguraX, float larguraY) {
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x - (tamanho * larguraX), y + (tamanho * larguraY));
    glVertex2f(x + (tamanho * larguraX), y + (tamanho * larguraY));
    glVertex2f(x + (tamanho * larguraX), y - (tamanho * larguraY));
    glVertex2f(x - (tamanho * larguraX), y - (tamanho * larguraY));
    glEnd();
}

void circulo(int raio, int x, int y, int min = 0, int max = 360) {
    float theta;
    for (int i = min; i < max; i++) {
        theta = i * PI / (max / 2);
        glVertex2f(x + raio * cos(theta), y + raio * sin(theta));
    }
}

void desenhaArmacao() {
    // quadrilatero(0, 0, 0.96, 1, 1);
}

void desenhaVidro() {
    // quadrilatero(0, 0, 0.96, 1, 1);
}

void desenhaDobradica() {
    // glPushMatrix();
    // glTranslatef(-0.800, -0.947, 0);
    // quadrilatero(0, 0, 0.2, 0.4, 0.05);
    // glPopMatrix();
}

void desenhaMarcadoresHora() {
    // glPushMatrix();
    // glTranslatef(-0.800, -0.947, 0);
    // chamar func scanline??
    // glPopMatrix();
}

void desenhaPonteiros() {
    // glPushMatrix();
    // glTranslatef(-0.800, -0.947, 0);
    // chamar func scanline ?? com a ponta do ponteiro ->
    // glPopMatrix();
}

void desenhaBraceletes() {
    // glPushMatrix();
    // glTranslatef(-0.800, -0.947, 0);
    // quadrilatero(0, 0, 0.2, 0.4, 0.05);
    // glPopMatrix();
}

void desenhaFivela() {
    // borda
    // glPushMatrix();
    // glTranslatef(-0.800, -0.947, 0);
    // quadrilatero(0, 0, 0.2, 0.4, 0.05);
    // glPopMatrix();

    // pino da fivela
    //  glPushMatrix();
    //  glTranslatef(-0.800, -0.947, 0);
    //  quadrilatero(0, 0, 0.2, 0.4, 0.05);
    //  glPopMatrix();
}

void desenhaRegulagens() {
    //  glPushMatrix();
    //  glTranslatef(-0.800, -0.947, 0);
    // circulo()
    //  glPopMatrix();
}

void desenhaRelogio(PontoXY ponto) {
    glPushMatrix();
    glTranslatef(ponto.x, ponto.y, 0.0f);
    glRotatef(ponto.angulo, 0.0f, 0.0f, 1.0);
    glScalef(ponto.escala, ponto.escala, 0.0f);
    quadrilatero(0, 0, 0.2, 1.85, 0.995);
    quadrilatero(0.250, 0, 0.2, 0.300, 0.8);
    glPopMatrix();
}

void opcoesMouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        printf("%f , %f\n", -1 + (float)x / (float)(glutGet(GLUT_WINDOW_WIDTH) / 2), +1 - (float)y / (float)(glutGet(GLUT_WINDOW_HEIGHT) / 2));
    }
    glutPostRedisplay();
}

void aplicaIluminacao() {
}

void aplicaTextura() {
}

void aplicaAnimacao() {
}

void mostraMenu() {
    using std::cout;
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
         << " [y] - Rotacionar ponteiro hora do relógio no sentido anti-horário\n"
         << " [u] - Rotacionar ponteiro minuto do relógio sentido anti-horário\n"
         << " [p] - Pausar ponteiro segundo do relógio\n"
         << " [i] - Ativar iluminação no vidro do relógio\n"
         << " [Botão esquerdo mouse] - Rotacionar o relógio para esquerda\n"
         << " [Botão direito mouse] - Rotacionar o relógio para direita\n\n";
}

void opcoesTeclado(unsigned char key, int x, int y) {
    // switch (key) {
    //     case 'a':
    //         vetorDePontos[pontoCentralRelogio].x -= 0.1f;
    //         break;
    //     case 's':
    //         vetorDePontos[pontoCentralRelogio].y -= 0.1f;
    //         break;
    //     case 'd':
    //         vetorDePontos[pontoCentralRelogio].x += 0.1f;
    //         break;
    //     case 'w':
    //         vetorDePontos[pontoCentralRelogio].y += 0.1f;
    //         break;
    //     case 'r':
    //         vetorDePontos[pontoCentralRelogio].angulo -= 1;
    //         break;
    //     case 'l':
    //         vetorDePontos[pontoCentralRelogio].angulo += 1;
    //         break;
    //     case '+':
    //         vetorDePontos[pontoCentralRelogio].escala += 0.1;
    //         break;
    //     case '-':
    //         vetorDePontos[pontoCentralRelogio].escala -= 0.1;
    //         break;
    //     case 27:
    //         exit(0);
    //         break;
    // }

    // if (vetorDePontos[pontoCentralRelogio].y < -1.0f)
    //     vetorDePontos[pontoCentralRelogio].y = -1.0f;

    // if (vetorDePontos[pontoCentralRelogio].y > 1.0f)
    //     vetorDePontos[pontoCentralRelogio].y = 1.0f;

    // if (vetorDePontos[pontoCentralRelogio].x < -1.0f)
    //     vetorDePontos[pontoCentralRelogio].x = -1.0f;

    // if (vetorDePontos[pontoCentralRelogio].x > 1.0f)
    //     vetorDePontos[pontoCentralRelogio].x = 1.0f;

    glutPostRedisplay();
}

void init(void) {
    glClearColor(0, 0, 0, 0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    mostraMenu();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("GAC 104 Computação Gráfica - Relógio de Pulso");
    init();
    glutKeyboardFunc(opcoesTeclado);
    glutMouseFunc(opcoesMouse);
    glutDisplayFunc(display);
    posicaoOriginalRelogio();
    glutMainLoop();
    return 0;
}
