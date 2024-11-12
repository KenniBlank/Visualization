#include "common2.h"
#define Znear 0.1f
#define Zfar 1000.0f

typedef struct {
    float x, y, z;
} vec3D;

typedef struct {
    vec3D p[3];
} triangle;

typedef struct {
    float elements[4][4];
} matrix4x4;
matrix4x4 projectionMatrix;


void MultiplyMatrixVector(vec3D *i, vec3D *o, matrix4x4 *m) {
    o->x = i->x * m->elements[0][0] + i->y * m->elements[1][0] + i->z * m->elements[2][0] + m->elements[3][0];
    o->y = i->x * m->elements[0][1] + i->y * m->elements[1][1] + i->z * m->elements[2][1] + m->elements[3][1];
    o->z = i->x * m->elements[0][2] + i->y * m->elements[1][2] + i->z * m->elements[2][2] + m->elements[3][2];
    float w = i->x * m->elements[0][3] + i->y * m->elements[1][3] + i->z * m->elements[2][3] + m->elements[3][3];

    if (w != 0.0f) {
        o->x /= w;
        o->y /= w;
        o->z /= w;
    }
}


triangle verticesOfCube[] = {
    // SOUTH
    { { {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f} } },
    { { {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f} } },

    // East
    { { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f} } },
    { { {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f} } },

    // North
    { { {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f} } },
    { { {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f} } },

    // West
    { { {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f} } },
    { { {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f} } },

    // Top
    { { {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} } },
    { { {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f} } },

    // Bottom
    { { {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f} } },
    { { {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} } },
};

void initializeProjectionMatrix(matrix4x4 *projectionMatrix) {
    float theta = 90.0f; // degree of FOV
    float f = 1.0f / tan(theta * (Pie / 180.0f) / 2.0f); // field of view half in radian
    float AspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT; // Aspect Ratio
    float Q = Zfar / (Zfar - Znear);
    float projectionMatx[4][4] = {
        {AspectRatio * f, 0, 0, 0},
        {0, f, 0, 0},
        {0, 0, Q, 1},
        {0, 0, -Znear * Q, 0}
    };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            projectionMatrix->elements[i][j] = projectionMatx[i][j];
}

void ProcessInput(void);
void Update(void);
void Render(void);
int main(){
    if (LocalSetup() == false)
        return 1;
    setup();
    initializeProjectionMatrix(&projectionMatrix);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", projectionMatrix.elements[i][j]);
        }
        printf("\n");
    }

    while (gameIsRunning){
        // Limit the frames of the game to the frame cap
        limitFrames();
        ProcessInput();
        if (play){
            Update();
            Render();
        }
    }
    DestroyWindow();
    return 0; // 0 Signifizes success
}


void ProcessInput(void){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                gameIsRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        gameIsRunning = false;
                        break;
                    case SDLK_p:
                        play = play == true? false: true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
            default:
                break;
        }
    }
}

void Update(void){}


void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(Renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(Renderer, x3, y3, x1, y1);
}

void Render(void){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(Renderer);

    // Rotating the cube in x and z axis?
    matrix4x4 matRotZ, matRotX;

    float fTheta = SDL_GetTicks() * 0.001f; // Rotate 1 revolution per second
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matRotZ.elements[i][j] = (i == j) ? 1.0f : 0.0f; // Identity matrix
            matRotX.elements[i][j] = (i == j) ? 1.0f : 0.0f; // Identity matrix
        }
    }
    // Rotation Z
    matRotZ.elements[0][0] = cosf(fTheta);
    matRotZ.elements[0][1] = sinf(fTheta);
    matRotZ.elements[1][0] = -sinf(fTheta);
    matRotZ.elements[1][1] = cosf(fTheta);
    matRotZ.elements[2][2] = 1;
    matRotZ.elements[3][3] = 1;

    // Rotation X
    matRotX.elements[0][0] = 1;
    matRotX.elements[1][1] = cosf(fTheta * 0.5f);
    matRotX.elements[1][2] = sinf(fTheta * 0.5f);
    matRotX.elements[2][1] = -sinf(fTheta * 0.5f);
    matRotX.elements[2][2] = cosf(fTheta * 0.5f);
    matRotX.elements[3][3] = 1;

    // Draw Traingles
    int numTriangles = sizeof(verticesOfCube) / sizeof(triangle);
    for (int i = 0; i < numTriangles; i++){
        triangle inputTriangle;
        for (int j = 0; j < 3; j++){
            inputTriangle.p[j].x = verticesOfCube[i].p[j].x;
            inputTriangle.p[j].y = verticesOfCube[i].p[j].y;
            inputTriangle.p[j].z = verticesOfCube[i].p[j].z;
        }

        // Rotating about X and Z axis:
        triangle triangleRotatedinZ, triangleRotatedinZX;
        for (int k = 0; k < 3; k++){
            MultiplyMatrixVector(&inputTriangle.p[k], &triangleRotatedinZ.p[k], &matRotZ);
            MultiplyMatrixVector(&triangleRotatedinZ.p[k], &triangleRotatedinZX.p[k], &matRotX);
            inputTriangle.p[k].x = triangleRotatedinZX.p[k].x;
            inputTriangle.p[k].y = triangleRotatedinZX.p[k].y;
            inputTriangle.p[k].z = triangleRotatedinZX.p[k].z + 3.0f;
        }

        // Projection
        triangle projectedTriangle;
        MultiplyMatrixVector(&inputTriangle.p[0], &projectedTriangle.p[0], &projectionMatrix);
        MultiplyMatrixVector(&inputTriangle.p[1], &projectedTriangle.p[1], &projectionMatrix);
        MultiplyMatrixVector(&inputTriangle.p[2], &projectedTriangle.p[2], &projectionMatrix);

        // Scale to VIEW
        projectedTriangle.p[0].x += 1.0f; projectedTriangle.p[0].y += 1.0f;
        projectedTriangle.p[1].x += 1.0f; projectedTriangle.p[1].y += 1.0f;
        projectedTriangle.p[2].x += 1.0f; projectedTriangle.p[2].y += 1.0f;

        projectedTriangle.p[0].x *= 0.5f * WINDOW_WIDTH; projectedTriangle.p[0].y *= 0.5f * WINDOW_HEIGHT;
        projectedTriangle.p[1].x *= 0.5f * WINDOW_WIDTH; projectedTriangle.p[1].y *= 0.5f * WINDOW_HEIGHT;
        projectedTriangle.p[2].x *= 0.5f * WINDOW_WIDTH; projectedTriangle.p[2].y *= 0.5f * WINDOW_HEIGHT;


        DrawTriangle(
            projectedTriangle.p[0].x, projectedTriangle.p[0].y,
            projectedTriangle.p[1].x, projectedTriangle.p[1].y,
            projectedTriangle.p[2].x, projectedTriangle.p[2].y
        );

    }
    
    SDL_RenderPresent(Renderer);
}
