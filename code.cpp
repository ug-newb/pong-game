#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <string>


#define PADDLE_WIDTH 15
#define PADDLE_HEIGHT 90
#define BALL_SIZE 10

int windowWidth = 1280;
int windowHeight = 720;
int paddle1_y = windowHeight / 2 - PADDLE_HEIGHT / 2;
int paddle2_y = windowHeight/ 2 - PADDLE_HEIGHT / 2;
int ball_x = windowWidth/ 2;
int ball_y = windowWidth / 2;
int ball_dx = 5;
int ball_dy = 5;
int player1_score = 0;
int player2_score = 0;
bool gameStarted = false;
bool gamePaused = false;
bool showMainMenu = false;
bool upPressed1 = false;
bool downPressed1 = false;
bool upPressed2 = false;
bool downPressed2 = false;
float ballSpeed = 0.8f;
bool showIntroduction = false;
bool showIntroScreen = true;
bool showInstructions = false;


//Method to display the starting instructions
void welcomeScreen() {
    
    const char* message = "*******************************************************";
    glColor3f(0.0, 1.0, 0.1);  // color
    glRasterPos2f(350, 50);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    
    message = "JAWAHARLAL NEHRU NEW COLLEGE OF ENGINEERING";
    glColor3f(0.9, 0.4, 0.1);  // Orange color
    glRasterPos2f(350, 100);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    
    message = "SHIMOGA";
    glColor3f(0.9, 0.4, 0.1);  // Orange color
    glRasterPos2f(620, 140);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    
    message = "*******************************************************";
    glColor3f(0.0, 1.0, 0.1);  // Orange color
    glRasterPos2f(350, 180);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    
    message = "A Mini-project on:";
    glColor3f(0.9, 0.1, 0.1);  // Orange color
    glRasterPos2f(600, 210);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    
    message = "PONG GAME";
    glColor3f(0.9, 0.1, 0.1);  // Orange color
    glRasterPos2f(600, 260);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    
    
    message = "Press ENTER to start";
    glColor3f(0.3, 0.7, 0.9);  // Light blue color
    glRasterPos2f(500, 350);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
    
    message = "Team Members:";
    glColor3f(0.8, 0.2, 0.2);  // Purple color
    glRasterPos2f(150, 500);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "4JN20CS001 - Abdul Rahman Pasha";
    glColor3f(0.8, 0.2, 0.6);  // Purple color
    glRasterPos2f(150, 550);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "4JN20CS029 - Dhruv G R";
    glRasterPos2f(150, 600);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "4JN20CS030 - Faisal Ahmed Khan";
    glRasterPos2f(150, 650);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "4JN20CS061 - Mohammed Nihal";
    glRasterPos2f(150, 700);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "Under the guidance of:";
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(800, 500);  // Purple color
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "Mrs. Sushma R B";
    glColor3f(0.8, 0.2, 0.6);  // Purple color
    glRasterPos2f(800, 550);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "Asst.Prof., Dept. of CS&E";
    glRasterPos2f(800, 570);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *message++);
    
    message = "JNNCE, Shimoga";
    glRasterPos2f(800, 590);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *message++);
    
    message = "Mrs. Shreedevi S";
    glColor3f(0.8, 0.2, 0.6);  // Purple color
    glRasterPos2f(800, 630);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
    
    message = "Asst.Prof., Dept. of CS&E";
    glRasterPos2f(800, 650);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *message++);
    
    message = "JNNCE, Shimoga";
    glRasterPos2f(800, 670);
    while (*message)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *message++);
    
}



void drawText(const std::string& text, int x, int y, float r, float g, float b);
void drawRect(int x, int y, int width, int height, float r, float g, float b);
void draw();

void drawText(const std::string &text, int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2i(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}


void drawRect(int x, int y, int width, int height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}



void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (showIntroScreen) {
        welcomeScreen();
    } else if (showMainMenu) {
        drawText("Main Menu:", 620, 200, 1.0f, 1.0f, 1.0f);
        drawRect(620, 280, 100, 20, 1.0f, 0.0f, 0.0f); // PLAY option
        drawRect(620, 320, 210, 20, 0.7f, 0.4f, 0.3f); // INSTRUCTIONS option
        drawRect(620, 360, 100, 20, 0.0f, 0.0f, 1.0f); // EXIT option
        
        drawText("PLAY", 640, 300, 1.0f, 1.0f, 1.0f);
        drawText("INSTRUCTIONS", 640, 340, 1.0f, 1.0f, 1.0f);
        drawText("EXIT", 640, 380, 1.0f, 1.0f, 1.0f);
    } else if (showInstructions) {
        drawText("Instructions:", 40, 40, 1.0f, 0.3f, 0.3f);
        drawText("Player 1: Move with W and S keys", 70, 80, 0.0f, 0.3f, 1.0f);
        drawText("Player 2: Move with I and K keys", 70, 120, 0.0f, 0.3f, 1.0f);
        drawText("Press P to pause the game", 70, 160, 0.0f, 0.3f, 1.0f);
        drawText("Press ESC to go back to main menu", 70, 200, 1.0f, 1.0f, 1.0f);
        
        drawRect(20, 540, 100, 40, 1.0f, 0.0f, 0.0f); // BACK button
        drawText("BACK", 40, 565, 1.0f, 1.0f, 1.0f);
    } else {
        // Draw the paddles
        drawRect(0, paddle1_y, PADDLE_WIDTH, PADDLE_HEIGHT, 0.0f, 0.7f, 0.0f);
        drawRect(windowWidth - PADDLE_WIDTH, paddle2_y, PADDLE_WIDTH, PADDLE_HEIGHT, 0.7f, 0.0f, 0.0f);
        
        // Draw the ball
        drawRect(ball_x, ball_y, BALL_SIZE, BALL_SIZE, 1.0f, 1.0f, 1.0f);
        
        // Draw the scores
        drawText("Player 1: " + std::to_string(player1_score), 20, 20, 1.0f, 1.0f, 1.0f);
        drawText("Player 2: " + std::to_string(player2_score), windowWidth - 120, 20, 1.0f, 1.0f, 1.0f);
        
        // Game over condition
        if (player1_score >= 5) {
            gameStarted = false;
            drawText("Player 1 Wins!", windowWidth / 2 - 30, windowHeight / 2, 1.0f, 1.0f, 1.0f);
            drawText("Press ESC to restart or go back to main menu", windowWidth / 2 - 150, windowHeight / 2 + 20, 1.0f, 1.0f, 1.0f);
        }
        if (player2_score >= 5) {
            gameStarted = false;
            drawText("Player 2 Wins!", windowWidth / 2 - 30, windowHeight / 2, 1.0f, 1.0f, 1.0f);
            drawText("Press ESC to go back to main menu", windowWidth / 2 - 150, windowHeight / 2 + 20, 1.0f, 1.0f, 1.0f);
        }
    }
    
    if (gamePaused) {
        drawText("Paused", windowWidth / 2 - 20, windowHeight / 2, 1.0f, 1.0f, 1.0f);
    }
    
    glutSwapBuffers();
}

void update(int value) {
    if (gameStarted && !gamePaused) {
        // Move the ball
        ball_x += ball_dx * ballSpeed;
        ball_y += ball_dy * ballSpeed;
        
        // Check for collisions with top and bottom walls
        if (ball_y < 0 || ball_y + BALL_SIZE > windowHeight) {
            ball_dy = -ball_dy;
        }
        
        // Check for collisions with paddles
        if (ball_x < PADDLE_WIDTH && ball_y + BALL_SIZE >= paddle1_y && ball_y <= paddle1_y + PADDLE_HEIGHT) {
            ball_dx = -ball_dx;
            ballSpeed += 0.1f;
        }
        if (ball_x + BALL_SIZE > windowWidth - PADDLE_WIDTH && ball_y + BALL_SIZE >= paddle2_y && ball_y <= paddle2_y + PADDLE_HEIGHT) {
            ball_dx = -ball_dx;
            ballSpeed += 0.1f;
        }
        
        if (ball_x < 0) {
            player2_score++;
            ball_x = (windowWidth / 2);
            ball_y = windowHeight / 2;
            ball_dx = -ball_dx;
        }
        if (ball_x + BALL_SIZE > windowWidth ) {
            player1_score++;
            ball_x = windowWidth / 2;
            ball_y = windowHeight / 2;
            ball_dx = -ball_dx;
        }
        
        // Check for game over
        if (player1_score >= 5 || player2_score >= 5) {
            gameStarted = false;
        }
        
        // Move the paddles
        if (upPressed1 && paddle1_y > 0) {
            paddle1_y -= 10;
        }
        if (downPressed1 && paddle1_y + PADDLE_HEIGHT < windowHeight) {
            paddle1_y += 10;
        }
        if (upPressed2 && paddle2_y > 0) {
            paddle2_y -= 10;
        }
        if (downPressed2 && paddle2_y + PADDLE_HEIGHT < windowHeight) {
            paddle2_y += 10;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (showMainMenu) {
            if (x >= 620 && x <= 700 && y >= 270 && y <= 310) {
                // PLAY option clicked
                showMainMenu = false;
                gameStarted = true;
            } else if (x >= 620 && x <= 800 && y >= 320 && y <= 350) {
                // INSTRUCTIONS option clicked
                showMainMenu = false;
                showInstructions = true;
            } else if (x >= 620 && x <= 700 && y >= 360 && y <= 400) {
                // EXIT option clicked
                exit(0);
            }
        } else if (showInstructions) {
            if (x >= 20 && x <= 120 && y >= 540 && y <= 600) {
                // BACK button clicked
                showInstructions = false;
                showMainMenu = true;
            }
        }
    }
}

void keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            upPressed1 = true;
            break;
        case 's':
            downPressed1 = true;
            break;
        case 'W':
            upPressed1 = true;
            break;
        case 'S':
            downPressed1 = true;
            break;
        case 'i':
            upPressed2 = true;
            break;
        case 'k':
            downPressed2 = true;
            break;
        case 'I':
            upPressed2 = true;
            break;
        case 'K':
            downPressed2 = true;
            break;
        case ' ':
            if (showMainMenu) {
                //gameStarted = true;
                showMainMenu = false;
                break;
            }
            if (!gameStarted && !gamePaused) {
                gameStarted = true;
                ball_x = windowWidth / 2;
                ball_y = windowHeight / 2;
                ball_dx = 5;
                ball_dy = 5;
            }
            break;
        case 'p':
            if (gameStarted) {
                gamePaused = !gamePaused;
            }
            break;
            
        case 13: // Enter key
            if (showIntroScreen) {
                showIntroScreen = false;
                showMainMenu = true;
            } else if (showMainMenu) {
                // Handle menu options based on user input
                // ...
            }
            break;
        case 27: // ESC key
            if (gameStarted || !gamePaused) {
                gameStarted = false;
                gamePaused = false;
                showMainMenu = true;
                showInstructions = false;
                paddle1_y = windowHeight / 2 - PADDLE_HEIGHT / 2;
                paddle2_y = windowHeight / 2 - PADDLE_HEIGHT / 2;
                player1_score = 0;
                player2_score = 0;
            }else if (gamePaused) {
                gamePaused = false;
            }
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            upPressed1 = false;
            break;
        case 's':
            downPressed1 = false;
            break;
        case 'W':
            upPressed1 = false;
            break;
        case 'S':
            downPressed1 = false;
            break;
        case 'i':
            upPressed2 = false;
            break;
        case 'k':
            downPressed2 = false;
            break;
        case 'I':
            upPressed2 = false;
            break;
        case 'K':
            downPressed2 = false;
            break;
    }
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Pong Game");
    glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
    glutDisplayFunc(draw);
    glutTimerFunc(30, update, 0);
    glutKeyboardFunc(keyboardDown);
    glutMouseFunc(mouse);
    glutKeyboardUpFunc(keyboardUp);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}
