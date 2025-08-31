#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum GameState {
    RUNNING,
    GAME_OVER
};

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

const int GRID_SIZE = 30;
const int CELL_SIZE = WINDOW_WIDTH / GRID_SIZE;

const int MAX_SNAKE_LENGTH = 100;
int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];
int snakeLength;
int direction;

int foodX, foodY;

int score;
GameState gameState;
bool isPaused;

void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void initializeGame() {
    snakeLength = 1;
    snakeX[0] = GRID_SIZE / 2;
    snakeY[0] = GRID_SIZE / 2;
    direction = 1;
    score = 0;
    gameState = RUNNING;
    isPaused = false;

    srand(time(0));
    foodX = rand() % GRID_SIZE;
    foodY = rand() % GRID_SIZE;
}

void generateFood() {
    bool onSnake;
    do {
        onSnake = false;
        foodX = rand() % GRID_SIZE;
        foodY = rand() % GRID_SIZE;
        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == foodX && snakeY[i] == foodY) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

void drawCell(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (gameState == RUNNING) {
        glColor3f(1.0, 0.0, 0.0);
        drawCell(foodX, foodY);

        for (int i = 0; i < snakeLength; i++) {
            if (i == 0) {
                glColor3f(0.0, 1.0, 0.0);
            } else {
                glColor3f(0.0, 0.8, 0.0);
            }
            drawCell(snakeX[i], snakeY[i]);
        }

        glColor3f(1.0, 1.0, 1.0);
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score);
        drawText(5, WINDOW_HEIGHT - 20, scoreText);

        if (isPaused) {
            drawText(WINDOW_WIDTH / 2.0 - 40, WINDOW_HEIGHT / 2.0, "PAUSED");
        }

    } else {
        glColor3f(1.0, 1.0, 1.0);
        char gameOverText[50];
        char finalScoreText[50];
        char restartText[50];

        sprintf(gameOverText, "GAME OVER");
        sprintf(finalScoreText, "Final Score: %d", score);
        sprintf(restartText, "Press 'R' to Restart");

        drawText(WINDOW_WIDTH / 2.0 - 50, WINDOW_HEIGHT / 2.0 + 20, gameOverText);
        drawText(WINDOW_WIDTH / 2.0 - 60, WINDOW_HEIGHT / 2.0 - 10, finalScoreText);
        drawText(WINDOW_WIDTH / 2.0 - 80, WINDOW_HEIGHT / 2.0 - 40, restartText);
    }

    glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y) {
    if (gameState == RUNNING) {
        switch (key) {
            case 't':
                if (direction != 2) direction = 0;
                break;
            case 'h':
                if (direction != 3) direction = 1;
                break;
            case 'g':
                if (direction != 0) direction = 2;
                break;
            case 'f':
                if (direction != 1) direction = 3;
                break;
            case 'p':
            case 'P':
                isPaused = !isPaused;
                break;
        }
    } else if (key == 'r' || key == 'R') {
        initializeGame();
    }
}

void mouseFunc(int button, int state, int x, int y) {
    if (gameState == RUNNING && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int mouseGridX = x / CELL_SIZE;
        int mouseGridY = (WINDOW_HEIGHT - y) / CELL_SIZE;

        int headX = snakeX[0];
        int headY = snakeY[0];

        int dx = mouseGridX - headX;
        int dy = mouseGridY - headY;

        if (abs(dx) > abs(dy)) {
            if (dx > 0) {
                if (direction != 3) direction = 1;
            } else {
                if (direction != 1) direction = 3;
            }
        } else {
            if (dy > 0) {
                if (direction != 2) direction = 0;
            } else {
                if (direction != 0) direction = 2;
            }
        }
    }
}

bool checkCollision() {
    if (snakeX[0] < 0 || snakeX[0] >= GRID_SIZE || snakeY[0] < 0 || snakeY[0] >= GRID_SIZE) {
        return true;
    }

    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            return true;
        }
    }
    return false;
}

void update(int value) {
    if (gameState == RUNNING && !isPaused) {
        for (int i = snakeLength - 1; i > 0; i--) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        switch (direction) {
            case 0:
                snakeY[0]++;
                break;
            case 1:
                snakeX[0]++;
                break;
            case 2:
                snakeY[0]--;
                break;
            case 3:
                snakeX[0]--;
                break;
        }

        if (checkCollision()) {
            gameState = GAME_OVER;
        }

        if (snakeX[0] == foodX && snakeY[0] == foodY) {
            score++;
            snakeLength++;
            generateFood();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(200, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 50);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Snake Game");

    glClearColor(0.2, 0.2, 0.2, 1.0);
    initializeGame();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutTimerFunc(200, update, 0);

    glutMainLoop();
    return 0;
}
