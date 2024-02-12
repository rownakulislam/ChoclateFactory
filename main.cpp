//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "sphere.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"

#include <iostream>
#include <vector>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void wall(Cube cube,unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether,int type);
void wall2(Cube cube, unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether, int type);
void secondwall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void secondmechine(Cube cube, Shader& lightingShaderWithTexture, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, unsigned int& bazierVAO);
void maker1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,int type);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void secondmechinechoclates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether,float currentFrame);
void carboardbox(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void container(Cube cube_metal, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void containerchoco(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
void door(Cube cube_door, Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether, Sphere knob, Shader& lightingShader);
void knob(Sphere knob, Shader& lightingShader, glm::mat4 alTogether, unsigned int& bezierVAO);

unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector <float>& coordinates,
    vector <float>& normals,
    vector <int>& indices,
    vector <float>& vertices);
void drawBazierCurveObj(Shader& lightingShader, glm::mat4 model, unsigned int& bezierVAO_, float r , float g , float b, float dr, float  dg , float db);
void draw_light_stands(Shader& lightingShader, glm::mat4 model, unsigned int& bezierVAO3, float r, float g, float b, float dr, float dg, float db);
glm::mat4 transformation(float transform_x, float transform_y, float transform_z, float rotate_x, float rotate_y,
    float rotate_z, float scale_x, float scale_y, float scale_z);
void secondmechinechoclates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether, float currentFrame, float lastFrame);
void secondmechinechoclates2(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether, float currentFrame, float lastFrame);
void slider(Cube cube, Shader& lightingShaderWithTexture, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, unsigned int& bezierVAO,Sphere sphere_choclate, float currentFrame, float lastFrame, unsigned int& bezierVAO_);
void draw_raw_containers(Cube cube,Shader& lightingShader, glm::mat4 model, unsigned int& bezierVAO5, unsigned int& bezierVAO6, unsigned int& bezierVAO3, float r, float g, float b, float dr, float dg, float db);
void draw_flatCircle(Cube cube, Shader& lightingShader, glm::mat4 model);

// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 1000;
float lastmechineoff;
float lastmechineoff2;
float lastmechineoff3;

//for curves
vector <float> cntrlPoints = {
-0.1750, 2.0600, 5.1000,
-0.3450, 1.5350, 5.1000,
-1.0650, 0.9850, 5.1000,
-0.0500, 0.7750, 5.1000,
};
vector<float> cntrlPoints2 = {
-0.0750, 1.6150, 5.1000,
-0.3550, 1.6100, 5.1000,
-0.5800, 1.4450, 5.1000,
-0.6700, 1.0550, 5.1000,
-0.7550, 0.7950, 5.1000,
-1.0250, 0.7150, 5.1000,
};
vector<float> cylinder = {
-0.6100, 2.1100, 5.1000,
-0.6100, 0.3300, 5.1000,
};
vector<float> raw_choclates = {
0.0100, 2.0350, 5.1000,
-0.0250, 1.7950, 5.1000,
-0.2550, 1.6200, 5.1000,
-0.7600, 1.4100, 5.1000,
-0.8000, 0.7400, 5.1000,
0.0400, 0.6800, 5.1000,
};

vector<float> raw_materials = {
-0.7000, 2.2150, 5.1000,
-0.7000, 1.5250, 5.1000,
-0.7250, 0.9100, 5.1000,
-0.0450, 0.6550, 5.1000,
};
vector<float> funnel = {
-0.6500, 1.8750, 5.1000,
-1.3850, 1.1300, 5.1000,
};
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;


vector <float> coordinates2;
vector <float> normals2;
vector <int> indices2;
vector <float> vertices2;

vector <float> cylinderCoordinates;
vector <float> cylinderNormals;
vector <int> cylinderIndices;
vector <float> cylinderVertices;

vector <float> rawCoordinates;
vector <float> rawNormals;
vector <int> rawIndices;
vector <float> rawVertices;

vector <float> rawMCoordinates;
vector <float> rawMNormals;
vector <int> rawMIndices;
vector <float> rawMVertices;

vector <float> funnelCoordinates;
vector <float> funnelNormals;
vector <int> funnelIndices;
vector <float> funnelVertices;

class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];

const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;

bool loadBezierCurvePoints = true;
bool showHollowBezier = true;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierVAO2;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float doorAngle = 0.0f;

// camera
Camera camera(glm::vec3(5.0f, 5.1f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 0.0, eyeZ = -1.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.2f,  4.8f,  2.5f),
    glm::vec3(9.8f,  4.8f,  2.5f),
    glm::vec3(0.2f,  9.8f,  2.5f),
    glm::vec3(9.8f,  9.8f,  2.5f),
    glm::vec3(6.0f,  18.8f,  6.0f),
    glm::vec3(-10.01f,4.0f,  2.5f),
    glm::vec3(-10.01f,10.0f,  2.5f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4      // light number
);
PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);
PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);
PointLight pointlight7(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7      // light number
);

DirectionalLight directionalLight(-15.0f, -12.0f, -10.0f,
    0.05f, 0.05f, 0.05f,
    0.5f, 0.5f, 0.5f,
    .70f, 0.70f, 0.70f);


SpotLight spotLight1(5.0f, 4.8f, 2.5f,
    0, -1.0f, 0, 0.05f,
    0.05f, 0.05f,
    0.8f, 0.8f, 0.8f,
    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(21.5f)));

SpotLight spotLight2(5.0f, 9.8f, 2.5f,
    0, -1.0f, 0, 0.05f,
    0.05f, 0.05f,
    0.8f, 0.8f, 0.8f,
    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(21.5f)));

SpotLight spotLight3(5.0f, 13.8f, 2.5f,
    0, -1.0f, 0, 0.05f,
    0.05f, 0.05f,
    0.8f, 0.8f, 0.8f,
    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(21.5f)));

SpotLight spotLight4(-5.0f, 13.8f, 2.5f,
    0, -1.0f, 0, 0.05f,
    0.05f, 0.05f,
    0.8f, 0.8f, 0.8f,
    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(21.5f)));



// light settings
bool pointLight1On = true;
bool pointLight3On = true;
bool pointLight2On = true;
bool pointLight4On = true;
bool pointLight5On = true;
bool pointLight6On = true;
bool pointLight7On = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool directionalLightOn = true;
bool spotLightOn = true;
bool paOn = true;
bool pdOn = true;
bool psOn = true;
bool saOn = true;
bool sdOn = true;
bool ssOn = true;
bool pointLightOn = true;
bool runMechine = false;
bool runMechineTON = false;
bool runMechineTOFF = true;
bool runMechine2 = false;
bool runMechineTON2 = false;
bool runMechineTOFF2 = true;
bool runMechine3 = false;
bool runMechineTON3 = false;
bool runMechineTOFF3 = true;
bool doorOn = false;



// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    string diffuseMapPath = "floor.png";
    string specularMapPath = "container2_specular.png";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    


    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 0.48, 0.24, 0.0, 1.0f, 1.0f, 1.0f
    Sphere sphere = Sphere(1.0f, 36, 18, glm::vec3(0.48f, 0.24f, 1.0f), glm::vec3(0.48f, 0.24f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);
    Sphere sphere_choclate = Sphere(1.0f,36,18, glm::vec3(0.48f, 0.24f, 1.0f),  glm::vec3(0.48f, 0.24f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);
    Sphere sphere_knob = Sphere(1.0f, 36, 18, glm::vec3(0.66f, 0.66f, 0.66f), glm::vec3(0.66f, 0.66f, 0.66f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    printf("1 to turn of the first point light\n");
    printf("2 to turn of the second point light\n");
    printf("3 to turn of the directional light\n");
    printf("4 to turn of the spot light\n");
    printf("5 to turn of the ambient light\n");
    printf("6 to turn of the diffuse light\n");
    printf("7 to turn of the specular light\n");



    //cube for choclates
    diffuseMapPath = "choco.png";
    specularMapPath = "container2_specular.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_choco = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    //cube for choclate packet
    diffuseMapPath = "packet.png";
    specularMapPath = "container2_specular.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_packet = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    //cube for sign board
    diffuseMapPath = "sign.png";
    specularMapPath = "container2_specular.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_sign = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "metaltex.jpg";
    specularMapPath = "container2_specular.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_metal = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "box.png";
    specularMapPath = "container2_specular.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_box = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube cube_circle_pipe = Cube(glm::vec3(0.06f,0.06f,0.06f), glm::vec3(0.67f,0.67f,0.67f), glm::vec3(1.0f,1.0f,1.0f),32);
    Cube cube_basic1 = Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),32);

    diffuseMapPath = "door.png";
    specularMapPath = "container2_specular.png";
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_door = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    //curve vao,vbo,veo creation by hallowBazier
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1, coordinates, normals, indices, vertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;


    unsigned int bezierVAO2 = hollowBezier(cntrlPoints2.data(), ((unsigned int)cntrlPoints2.size() / 3) - 1, coordinates2, normals2, indices2, vertices2);
    unsigned int bezierVAO3 = hollowBezier(cylinder.data(), ((unsigned int)cylinder.size() / 3) - 1, cylinderCoordinates, cylinderNormals, cylinderIndices, cylinderVertices);
    unsigned int bezierVAO4 = hollowBezier(raw_choclates.data(), ((unsigned int)raw_choclates.size() / 3) - 1, rawCoordinates, rawNormals, rawIndices, rawVertices);
    unsigned int bezierVAO5 = hollowBezier(raw_materials.data(), ((unsigned int)raw_materials.size() / 3) - 1, rawMCoordinates, rawMNormals, rawMIndices, rawMVertices);
    unsigned int bezierVAO6 = hollowBezier(funnel.data(), ((unsigned int)funnel.size() / 3) - 1, funnelCoordinates, funnelNormals, funnelIndices, funnelVertices);
    loadBezierCurvePoints = false;
    showHollowBezier = true;




    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        

        // input
        // -----
        processInput(window);
        
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // set up point lights
        pointlight1.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);

        // set up directional and spot lights

        directionalLight.setUpDirectionalLight(lightingShader);
        spotLight1.setUpSpotLight(lightingShader);
        spotLight2.setUpSpotLight(lightingShader);
        spotLight3.setUpSpotLight(lightingShader);
        //spotLight4.setUpSpotLight(lightingShader);


        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);
        


        //bed(cubeVAO, lightingShader, model);
        model = transformation(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        wall(cube_box, cubeVAO, lightingShader, lightingShaderWithTexture, model, 1);
        //secondwall(cubeVAO, lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, 5.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        wall(cube_box, cubeVAO, lightingShader, lightingShaderWithTexture, model, 1);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, 10.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        wall(cube_metal, cubeVAO, lightingShader, lightingShaderWithTexture, model, 2);

        //second 
        model = transformation(-10.21f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        wall2(cube_box, cubeVAO, lightingShader, lightingShaderWithTexture, model, 2);
        //secondwall(cubeVAO, lightingShader, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.21f, 5.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        wall2(cube_box, cubeVAO, lightingShader, lightingShaderWithTexture, model, 2);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.21f, 10.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        wall2(cube_metal, cubeVAO, lightingShader, lightingShaderWithTexture, model, 2);

        //container for chocolates
        

        
        //mechine draw
        lightingShaderWithTexture.use();
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.7f, translate_Y, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        secondmechine(cube_metal,lightingShaderWithTexture,cubeVAO, lightingShader, model,bezierVAO3);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.7f, 5.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        secondmechine(cube_metal, lightingShaderWithTexture,cubeVAO, lightingShader, model,bezierVAO3);
        

        //maker
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, translate_Y, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        maker1(cubeVAO, lightingShader, model,2);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5f, 5.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        maker1(cubeVAO, lightingShader, model,2);



        //slider
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        float currentFrame3 = currentFrame;
        float lastFrame3 = lastmechineoff3;
        if (!runMechine3) {
            lastFrame3 = currentFrame;

        }

        lightingShaderWithTexture.use();
        slider(cube_metal, lightingShaderWithTexture, cubeVAO, lightingShader, model, bezierVAO3,sphere_choclate,currentFrame3,lastFrame3,bezierVAO4);

        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));


        //sun
        glm::mat4 modelForSphere = glm::mat4(1.0f);
        modelForSphere = glm::translate(model, glm::vec3(15.0f, 12.0f, 10.0f));
        sphere.drawSphere(lightingShader, modelForSphere);

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

       

        //buttons
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(7.5f, 1.7f, 2.6f));
        model = glm::scale(model, glm::vec3(0.2f,0.15f,0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec3("color", glm::vec3(1.0f, 0.3f, 0.3f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(8.2f, 1.7f, 2.6f));
        model = glm::scale(model, glm::vec3(0.2f, 0.15f, 0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec3("color", glm::vec3(.8f, 0.8f, 0.8f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(7.5f, 1.1f, 2.6f));
        model = glm::scale(model, glm::vec3(0.2f, 0.15f, 0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec3("color", glm::vec3(.8f, 0.8f, 0.8f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(8.2f, 1.1f, 2.6f));
        model = glm::scale(model, glm::vec3(0.2f, 0.15f, 0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", model);
        ourShader.setVec3("color", glm::vec3(1.0f, 0.8f, 0.8f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        



        //floor

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use(); // check for double usage

        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        
        //dir light
        directionalLight.setUpDirectionalLight(lightingShaderWithTexture);
        //spot light
        spotLight1.setUpSpotLight(lightingShaderWithTexture);
        spotLight2.setUpSpotLight(lightingShaderWithTexture);
        spotLight3.setUpSpotLight(lightingShaderWithTexture);
        //spotLight4.setUpSpotLight(lightingShaderWithTexture);

   

        //// point light 3
        //pointlight3.setUpPointLight(lightingShaderWithTexture);
        //// point light 4
        //pointlight4.setUpPointLight(lightingShaderWithTexture);

        lightingShaderWithTexture.use();
        model = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 translate2 = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);
        //cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);


        //floor
        scale = glm::scale(model, glm::vec3(10.0f, .20f, 4.99f));
        translate = glm::translate(model, glm::vec3(0, 0, 0));
        model =scale * translate;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(7.5f, .20f, 4.99f));
        translate = glm::translate(model, glm::vec3(0, 5.03f, 0));
        model =  translate*scale;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(7.5f, .20f, 4.99f));
        translate = glm::translate(model, glm::vec3(0, 10.03f, 0));
        model = translate * scale;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //floor 2
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);

        for (float i = -2.0f; i > -10; i-=1.8f) {
            //container
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.05f+i, 5.0f, translate_Z));
            model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            container(cube_metal, lightingShaderWithTexture, model);


            //packet chochlates on container
            glm::mat4 translateMatrix0 = glm::translate(identityMatrix, glm::vec3(0.1f, 1.505f - 1.0f, translate_Z));
            glm::mat4 model1 = translateMatrix0 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            model1 = model * model1;
            containerchoco(cube_packet, lightingShaderWithTexture, model1);



            glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.1f, 0.97f-1.0f, translate_Z));
            glm::mat4 model2 = translateMatrix2 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            model2 = model *model2 ;
            containerchoco(cube_packet, lightingShaderWithTexture, model2);

            glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.1f, 0.535f-1.0f, translate_Z));
            glm::mat4 model3 = translateMatrix3 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            model3 = model * model3 ;
            containerchoco(cube_packet, lightingShaderWithTexture, model3);

            glm::mat4 translateMatrix4 = glm::translate(identityMatrix, glm::vec3(0.1f, 0.10f-1.0f, translate_Z));
            glm::mat4 model4 = translateMatrix4 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            model4 = model * model4;
            containerchoco(cube_packet, lightingShaderWithTexture, model4);


        }




        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(10.21f, .20f, 4.99f));
        translate = glm::translate(model, glm::vec3(-10.0f, 0, 0));
        model = translate*scale;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(10.21f, .20f, 4.99f));
        translate = glm::translate(model, glm::vec3(-10.21f, 5.03f, 0));
        model = translate * scale;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(10.21f, .20f, 4.99f));
        translate = glm::translate(model, glm::vec3(-10.21f, 10.03f, 0));
        model = translate * scale;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);




        //door
        if (doorOn) {
            doorAngle +=  5.0f;
            if (doorAngle >= 90.0f) {
                doorAngle = 90.0f;
            }
        }
        else {
            if (doorAngle > 0.0f) {
                doorAngle -= 5.0f;
            }
            else {
                doorAngle = 0.0f;
            }
        }
        
        model = transformation(0.0f, 0.0f, 0.0f, 0.0f, doorAngle, 0.0f, 1.0f, 1.0f, 1.0f);
        door(cube_door, cube_basic1, lightingShaderWithTexture, model, sphere_knob,lightingShader);
        model = transformation(0.0f, 5.0f, 0.0f, 0.0f, doorAngle, 0.0f, 1.0f, 1.0f, 1.0f);
        door(cube_door, cube_basic1, lightingShaderWithTexture, model, sphere_knob,lightingShader);
        
        
        //door 2
        model = transformation(-10.21f, 0.0f, 0.0f, 0.0f, doorAngle, 0.0f, 1.0f, 1.0f, 1.0f);
        door(cube_door, cube_basic1, lightingShaderWithTexture, model, sphere_knob, lightingShader);
        model = transformation(-10.21f, 5.0f, 0.0f, 0.0f, doorAngle, 0.0f, 1.0f, 1.0f, 1.0f);
        door(cube_door, cube_basic1, lightingShaderWithTexture, model, sphere_knob, lightingShader);
        model = transformation(-10.21f, 10.0f, 0.0f, 0.0f, doorAngle, 0.0f, 1.0f, 1.0f, 1.0f);
        door(cube_door, cube_basic1, lightingShaderWithTexture, model, sphere_knob, lightingShader);
        //slider_texture

        model = transformation(1.7f, 7.01f, 0.79f, 0.0f, 0.0f, 20.0f, 9.1f, 0.1f, 1.5f);
        cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);

        //box
        model = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.5f));
        translate = glm::translate(model, glm::vec3(1.0f,0.22f, 1.0f));
        model = translate*scale;
        carboardbox(cube_box, lightingShaderWithTexture, model);
        
        //curcle for mechine
        model = transformation(6.5f, 14.22f, 4.05f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f);
        draw_flatCircle(cube_circle_pipe, lightingShader,model);
        model = transformation(1.1f, 10.95f, 4.05f, 0.0f, 0.0f, 90.0f, 0.4f, 0.4f, 0.4f);
        draw_flatCircle(cube_circle_pipe, lightingShader, model);

        


        //choclates on mechine 2
        lightingShaderWithTexture.use();
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.7f, translate_Y, translate_Z));

        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        float currentFrame1 = currentFrame;
        float lastFrame1=lastmechineoff;
        if (!runMechine) {
            lastFrame1 = currentFrame;
            
        }


        secondmechinechoclates(cube_packet, lightingShaderWithTexture, model, currentFrame1,lastFrame1);
        
        float currentFrame2 = currentFrame;
        float lastFrame2 = lastmechineoff2;
        if (!runMechine2) {
            lastFrame2 = currentFrame;

        }


        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.5f, 5.0f, translate_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        secondmechinechoclates2(cube_choco, lightingShaderWithTexture, model, currentFrame2, lastFrame2);

        //packet chochlates on container
        /*glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.1f, 4.97f, translate_Z));
        glm::mat4 model2 = translateMatrix2 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        
        containerchoco(cube_packet, lightingShaderWithTexture, model2);

        glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.1f, 4.535f, translate_Z));
        glm::mat4 model3 = translateMatrix3 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        containerchoco(cube_packet, lightingShaderWithTexture, model3);

        glm::mat4 translateMatrix4 = glm::translate(identityMatrix, glm::vec3(0.1f, 4.10f, translate_Z));
        glm::mat4 model4 = translateMatrix4 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        containerchoco(cube_packet, lightingShaderWithTexture, model4);*/

        
        //sign board
        glm::mat4 translateMatrix5 = glm::translate(identityMatrix, glm::vec3(2.5f,15.1f,3.0f));
        glm::mat4 scaleMatrix5 = glm::scale(identityMatrix, glm::vec3(5.0f, 2.0f, 1.0f));
        glm::mat4 model5 = translateMatrix5 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix5;
        cube_sign.drawCubeWithTexture(lightingShaderWithTexture, model5);



        lightingShader.use();

        

        //lights
        //point light 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.6f, 3.8f, 2.5f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.4f, 0.4f));
        glm::mat4 model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        //point light 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(9.6f, 3.8f, 2.5f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        //point light 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.6f, 8.8f, 2.5f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        //point light 4
        translateMatrix = glm::translate(identityMatrix, glm::vec3(9.6f, 8.8f, 2.5f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

       

        //point light 6
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.42f, 8.7f, 2.55f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        //point light 7
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.42f, 4.0f, 2.55f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        //spot light 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 4.0f, 2.5f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO2, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        //spot light 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 8.8f, 2.5f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO2, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        //spotlight 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 13.8f, 2.5f));
        model_for_pointlight = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        drawBazierCurveObj(lightingShader, model_for_pointlight, bezierVAO2, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

        //the stands
      
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_light_stands(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10.25f, translate_Y, 5.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_light_stands(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 5.0f, -0.1f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_light_stands(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10.25f, 5.0f, 5.1f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_light_stands(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 4.5f, 2.6f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.05f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        drawBazierCurveObj(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f,1.0f, 1.0f, 1.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 9.35f, 2.6f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        drawBazierCurveObj(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 14.3f, 2.6f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.05f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        drawBazierCurveObj(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);




        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.0f, 5.0f, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_light_stands(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.3f, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_light_stands(lightingShader, model, bezierVAO3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);





        //3rd floor container
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 9.4f, 0.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 1.3f, 1.3f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        draw_raw_containers(cube_circle_pipe,lightingShader, model, bezierVAO5,bezierVAO6,bezierVAO3, 0.67f, 0.67f, 0.67f, 1.0f, 1.0f, 1.0f);
       



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void drawBazierCurveObj(Shader& lightingShader, glm::mat4 model, unsigned int& bezierVAO_, float r = 1.0f, float g = 1.0f, float b = 1.0f, float dr = 0.8f, float  dg = 0.8f, float db = 0.8f) {
    lightingShader.use();
    lightingShader.setMat4("model", model);
    lightingShader.setVec3("material.emission", glm::vec3(0, 0, 0));
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(dr, dg, db));
    lightingShader.setFloat("material.shininess", 32.0f);

    glBindVertexArray(bezierVAO_);
    glDrawElements(GL_TRIANGLES,(unsigned int)indices.size(),GL_UNSIGNED_INT,(void*)0);                     

    // unbind VAO
    glBindVertexArray(0);
}


void drawWallCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, float dr = 1.0f, float  dg = 1.0f, float db = 1.0f)
{
    lightingShader.use();
    lightingShader.setVec3("material.emission", glm::vec3(0, 0, 0));
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(dr, dg, db));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void draw_flatCircle(Cube cube, Shader& lightingShader,glm::mat4 model) {
    //code for flat circle
        for (float i = 0.0f; i <= 360.0f; i += 2.0f) {
            //Center
            glm::mat4 identityMatrix = glm::mat4(1.0f);
            glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .15, .5));
            glm::mat4 model_ =  model* translateMatrix *rotateXMatrix*rotateYMatrix*rotateZMatrix * scaleMatrix;
            //drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
            //glBindVertexArray(VAO);

            cube.drawCubeWithMaterialisticProperty(lightingShader, model_);

        }
}

void draw_light_stands(Shader& lightingShader, glm::mat4 model, unsigned int& bezierVAO3, float r, float g, float b, float dr, float dg, float db) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 3.8f, 2.6f));
    glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.05f));
    glm::mat4 model_for_stand = model * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix ;

    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r,g,b,dr,dg,db);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.63f, 3.7f, 2.6f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.05f));
    model_for_stand = model * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
}

void draw_raw_containers(Cube cube,Shader& lightingShader, glm::mat4 model, unsigned int& bezierVAO5, unsigned int& bezierVAO6, unsigned int& bezierVAO3, float r, float g, float b, float dr, float dg, float db) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 0.0f, 1.5f));
    glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.00f, 1.0f, 1.0f));
    glm::mat4 model_for_stand = model * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO5, .48f, .24f, 0.0f, dr, dg, db);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, 1.5f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.00f, 1.0f, 1.00f));
    model_for_stand = model * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO5, .48f, .24f, 0.0f, dr, dg, db);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0f, 0.0f, 1.5f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.00f, 1.0f, 1.00f));
    model_for_stand = model * translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO5, .48f, .24f, 0.0f, dr, dg, db);

    model_for_stand = model * transformation(1.03f, 1.2f, 1.7f, 90.0f, 0.0f, 0.0f, 0.3f, 0.7f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(3.03f, 1.2f, 1.7f, 90.0f, 0.0f, 0.0f, 0.3f, 0.7f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(5.03f, 1.2f, 1.7f, 90.0f, 0.0f, 0.0f, 0.3f, 0.7f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(0.04f, 1.2f, 3.1f, 0.0f, 180.0f, 90.0f, 0.3f, 2.4f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(5.00f, 0.60f, 3.13f, 0.0f, 0.0f, 0.0f, 0.3f, 1.5f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(5.00f, 3.30f, 3.5f, -90.0f, 0.0f, 0.0f, 0.3f, 1.0f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(5.01f, 3.0f, 1.4f, 0.0f, 0.0f, 0.0f, 0.3f, 0.5f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);
    model_for_stand = model * transformation(7.0f, 3.9f, 1.4f, 0.0f, 0.0f, 90.0f, 0.3f, 1.0f, 0.3f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);

    model_for_stand = model * transformation(7.00f, 1.2f, 1.2f, 0.0f, 0.0f, 0.0f, 0.8f, 1.5f, 0.8f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO3, r, g, b, dr, dg, db);

    model_for_stand = model * transformation(7.0f, 0.1f, 1.2f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.5f);
    drawBazierCurveObj(lightingShader, model_for_stand, bezierVAO6, .48f, .24f, 0.0f, dr, dg, db);

   
}
void door(Cube cube_door,Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether,Sphere knob, Shader& lightingShader ) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 2.8f, 1.5f));
    translate = glm::translate(model, glm::vec3(0, 0.2f, 2.8f));
    model =  translate* alTogether * scale;
    cube_door.drawCubeWithTexture(lightingShaderWithTexture, model);

}


void wall(Cube cube,unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether,int type)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    ////floor
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 translate = glm::mat4(1.0f);
    //glm::mat4 translate2 = glm::mat4(1.0f);
    //glm::mat4 scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(10.0f, .1f, 5.0f));
    //translate = glm::translate(model, glm::vec3(0, 0, 0));
    //model = alTogether * scale * translate;
    //drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.2f, 0.2f, 0.2f);

    //left_wall
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 5.0f, 0.7f));
    translate = glm::translate(model, glm::vec3(0, 0, 4.3f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.2f, 2.8f, 1.5f));
    //translate = glm::translate(model, glm::vec3(0, 0.2f, 2.8f));
    //model = alTogether * translate * scale;
    //drawWallCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.00, 0.8f, 0.8f, 0.8f);
    //cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    //odel = transformation(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    //cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 2.0f, 1.5f));
    translate = glm::translate(model, glm::vec3(0, 3.0, 2.8f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);
    
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 5.0f, 2.8f));
    translate = glm::translate(model, glm::vec3(0, 0.0, 0.0f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    //right_wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 5.0f, 5.0f));
    translate = glm::translate(model, glm::vec3(50.0f, 0, 0));
    model = alTogether * scale * translate;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    //back_wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(10.0f, 5.0f, .2f));
    translate = glm::translate(model, glm::vec3(0, 0, 0));
    model = alTogether * scale * translate;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    if (type == 1) {
        //upper_wall
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(7.5f, 0.20f, 5.0f));
        translate = glm::translate(model, glm::vec3(0, 25.0f, 0));
        model = alTogether * scale * translate;
        drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);
    }
    else if (type == 2) {
        //upper_wall
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(10.2f, 0.20f, 5.0f));
        translate = glm::translate(model, glm::vec3(0.0f, 25.0f, 0));
        model = alTogether * scale * translate;
        drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);
    }
    



}


void wall2(Cube cube, unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether, int type)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    ////floor
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 translate = glm::mat4(1.0f);
    //glm::mat4 translate2 = glm::mat4(1.0f);
    //glm::mat4 scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(10.0f, .1f, 5.0f));
    //translate = glm::translate(model, glm::vec3(0, 0, 0));
    //model = alTogether * scale * translate;
    //drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.2f, 0.2f, 0.2f);

    //left_wall
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 5.0f, 0.7f));
    translate = glm::translate(model, glm::vec3(0, 0, 4.3f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);



    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 2.0f, 1.5f));
    translate = glm::translate(model, glm::vec3(0, 3.0, 2.8f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.2f, 5.0f, 2.8f));
    translate = glm::translate(model, glm::vec3(0, 0.0, 0.0f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    //right_wall
    // 
    // 
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.2f, 5.0f, 5.0f));
    //translate = glm::translate(model, glm::vec3(50.0f, 0, 0));
    //model = alTogether * scale * translate;
    //drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);
    
    
    //back_wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(10.21f, 5.0f, .2f));
    translate = glm::translate(model, glm::vec3(0, 0, 0));
    model = alTogether * scale * translate;
    drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);

    if (type == 1) {
        //upper_wall
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(7.5f, 0.20f, 5.0f));
        translate = glm::translate(model, glm::vec3(0, 25.0f, 0));
        model = alTogether * scale * translate;
        drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);
    }
    else if (type == 2) {
        //upper_wall
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(10.2f, 0.20f, 5.0f));
        translate = glm::translate(model, glm::vec3(0.0f, 25.0f, 0));
        model = alTogether * scale * translate;
        drawWallCube(cubeVAO, lightingShader, model, 0.67, 0.84, 0.90, 0.8f, 0.8f, 0.8f);
    }




}




void container(Cube cube_metal, Shader& lightingShaderWithTexture, glm::mat4 alTogether) {
    //left
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, 2.0f, 1.5f));
    translate = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.2f));
    model = alTogether * scale * translate;
    cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, 2.0f, 1.5f));
    translate = glm::translate(model, glm::vec3(18.0f, 0.0f, 0.2f));
    model = alTogether * scale * translate;
    cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);
    //up
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.4f, 0.1f, 1.5f));
    translate = glm::translate(model, glm::vec3(0.3f, 18.0f, 0.2f));
    model = alTogether * scale * translate;
    cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);
    //mid
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.4f, 0.03f, 1.5f));
    translate = glm::translate(model, glm::vec3(0.3f, 45.0f, 0.2f));
    model = alTogether * scale * translate;
    cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);
    //low mid

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.4f, 0.03f, 1.5f));
    translate = glm::translate(model, glm::vec3(0.3f, 30.0f, 0.2f));
    model = alTogether * scale * translate;
    cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);
    //low low


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.4f, 0.03f, 1.5f));
    translate = glm::translate(model, glm::vec3(0.3f, 15.0f, 0.2f));
    model = alTogether * scale * translate;
    cube_metal.drawCubeWithTexture(lightingShaderWithTexture, model);
}


void slider(Cube cube, Shader& lightingShaderWithTexture, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, unsigned int& bezierVAO,Sphere sphere_choclate, float currentFrame, float lastFrame,unsigned int& bezierVAO_) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));

    scale = glm::scale(model, glm::vec3(9.1f, 0.1f, 1.5f));
    translate = glm::translate(model, glm::vec3(1.7f, 7.0f,0.8f));
    model =  translate*alTogether * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.66f, 0.66f, 0.66f, 1.0f, 1.0f, 1.0f);
    //cube.drawCubeWithTexture(lightingShaderWithTexture, model);


    if (runMechineTOFF3) {
        currentFrame = 0;
    }
    else if (runMechineTON3) {
        currentFrame = (currentFrame - lastFrame);
    }

    float i = 14.5f;
    for (int k = 0; k < 7; k++) {
        float z = 1.1f;
        while (z < 2.2f) {
            if ((translate_X - currentFrame + i)*0.632f > 6.18f) {

                model = glm::mat4(1.0f);
                translate = glm::mat4(1.0f);
                translate2 = glm::mat4(1.0f);
                scale = glm::mat4(1.0f);
                scale = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
                translate = glm::translate(model, glm::vec3(9.0f, translate_X - currentFrame + i, 0 + z));
                rotateZMatrix = glm::rotate(identityMatrix, glm::radians(currentFrame * 30), glm::vec3(0.0f, 0.0f, 1.0f));
                rotateXMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = translate * rotateZMatrix * rotateXMatrix * scale;
                drawBazierCurveObj(lightingShader, model, bezierVAO_, 0.48, 0.24, 0.0, 1.0f, 1.0f, 1.0f);
            }
            else {
                //for (float i = 11.6f; i > 3.2f; i -= 0.5f) {
                    //for (float z = 1.1f; z < 2.2f; z += 0.4f) {
                if (translate_X - currentFrame + i > 2.17f) {
                    model = glm::mat4(1.0f);
                    translate = glm::mat4(1.0f);
                    translate2 = glm::mat4(1.0f);
                    scale = glm::mat4(1.0f);
                    scale = glm::scale(model, glm::vec3(0.13f, 0.13f, 0.13f));
                    translate = glm::translate(model, glm::vec3(translate_X - currentFrame + i+1.83f, 6.18f, 0 + z));
                    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(currentFrame * 1000), glm::vec3(0.0f, 0.0f, 1.0f));
                    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(70.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                    model = alTogether * translate * rotateZMatrix * rotateXMatrix * scale;
                    //drawWallCube(cubeVAO, lightingShader, model, 0.48, 0.24, 0.0, 0.5f, 0.5f, 0.5f);

                        //sphere_choclate.drawSphere(lightingShader, model);
                    drawBazierCurveObj(lightingShader, model, bezierVAO_, 0.48, 0.24, 0.0, 1.0f, 1.0f, 1.0f);
                }
                else {
                    if (4.0f - currentFrame + i > 5.0f) {
                        float temp_X = 1.5f;
                        model = glm::mat4(1.0f);
                        model = glm::mat4(1.0f);
                        translate = glm::mat4(1.0f);
                        translate2 = glm::mat4(1.0f);
                        scale = glm::mat4(1.0f);
                        scale = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
                        translate = glm::translate(model, glm::vec3(temp_X, 5.11f - currentFrame + i, translate_Z + z));
                        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(currentFrame*80 ), glm::vec3(0.0f, 0.0f, 1.0f));
                        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                        model = translate * rotateZMatrix * rotateXMatrix * scale;
                        //sphere_choclate.drawSphere(lightingShader, model);
                        drawBazierCurveObj(lightingShader, model, bezierVAO_, 0.48, 0.24, 0.0, 1.0f, 1.0f, 1.0f);
                    }
                }
            }

            z += 0.4f;
        }
        i -= 0.5f;


    }

    


}



//mechine
void secondmechine(Cube cube, Shader& lightingShaderWithTexture,unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,unsigned int& bezierVAO)
{
    


    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);


    //base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(5.0f, 0.3f, 1.5f));
    translate = glm::translate(model, glm::vec3(0.5f, 1.0f, 1.0f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 0.47, 0.43, 0.43, 0.5f, 0.5f, 0.5f);
    //cube.drawCubeWithTexture(lightingShaderWithTexture, model);


    //white-cover
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(5.2f, 0.4f, 1.3f));
    translate = glm::translate(model, glm::vec3(0.4f, 1.0f, 1.1f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f, 0.8f, 0.8f, 0.8f);

    //legs-back-left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, -0.5f, 0.1f));
    translate = glm::translate(model, glm::vec3(0.6f, 1.3f, 1.1f));
    model = alTogether * translate * scale;
    //drawWallCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0, 0.5f, 0.5f, 0.5f);
    drawBazierCurveObj(lightingShader, model, bezierVAO, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    //back-right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, -0.5f, 0.1f));
    translate = glm::translate(model, glm::vec3(5.3f, 1.3f, 1.1f));
    model = alTogether * translate * scale;
    drawBazierCurveObj(lightingShader, model, bezierVAO, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


    //legs-front-left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, -0.5f, 0.1f));
    translate = glm::translate(model, glm::vec3(0.6f, 1.3f, 2.3f));
    model = alTogether * translate * scale;
    drawBazierCurveObj(lightingShader, model, bezierVAO, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);


    //front-right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, -0.5f, 0.1f));
    translate = glm::translate(model, glm::vec3(5.3f, 1.3f, 2.3f));
    model = alTogether * translate * scale;
    drawBazierCurveObj(lightingShader, model, bezierVAO, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    ////chochlates
    //for (float i = 0.6f; i < 5.2f; i += 0.5f) {
    //    for (float z = 1.3f; z < 2.2f; z += 0.4f) {
    //        model = glm::mat4(1.0f);
    //        translate = glm::mat4(1.0f);
    //        translate2 = glm::mat4(1.0f);
    //        scale = glm::mat4(1.0f);
    //        scale = glm::scale(model, glm::vec3(0.3f, 0.03f, 0.15f));
    //        translate = glm::translate(model, glm::vec3(0+i, 1.4f, 0+z));
    //        model = alTogether * translate * scale;
    //        drawWallCube(cubeVAO, lightingShader, model, 0.48, 0.24, 0.0, 0.5f, 0.5f, 0.5f);
    //    }
    //}


}


//choclates on mechine2
void secondmechinechoclates(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether,float currentFrame,float lastFrame)
{
    if (runMechineTOFF) {
        currentFrame = 0;
    }
    else if (runMechineTON) {
        currentFrame = (currentFrame - lastFrame);
    }


    float rotation_angle = 20.0f;


        //chochlates
        for (float i = 5.2f; i >= 0.6f; i -= 0.5f) {
            for (float z = 1.3f; z < 2.2f; z += 0.4f) {
                glm::mat4 model = alTogether;


                if (translate_X + i - currentFrame > 0.0f) {
                    model = model * transformation(translate_X + i - currentFrame, 1.4f
                        , translate_Z + z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.3f, 0.03f, 0.15f);

                    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
                }
                else {

                    if (1.4f - currentFrame + i > 0) {
                        float temp_X = 0.1f;
                        if (rotation_angle < 90.0f) {
                            rotation_angle = rotation_angle + (i * 10);
                        }
                        else {
                            rotation_angle = 90.0f;
                        }
                        model = model * transformation(temp_X, 1.4f - currentFrame + i
                            , translate_Z + z, rotateAngle_X, rotateAngle_Y, rotation_angle, 0.3f, 0.03f, 0.15f);
                        cube.drawCubeWithTexture(lightingShaderWithTexture, model);
                    }

                }
            }


        }
    
    

}
//2nd floor choclates
void secondmechinechoclates2(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether, float currentFrame, float lastFrame)
{
    if (runMechineTOFF2) {
        currentFrame = 0;
    }
    else if (runMechineTON2) {
        currentFrame = (currentFrame - lastFrame);
    }


    float rotation_angle = -15.0f;


    //chochlates
    for (float i = 5.2f; i >= 0.6f; i -= 0.5f) {
        for (float z = 1.3f; z < 2.2f; z += 0.4f) {
            glm::mat4 model = alTogether;


            if (translate_X + (5.2f-i) + currentFrame <5.2f) {
                model = model * transformation(translate_X + (5.2f-i) + currentFrame, 1.4f
                    , translate_Z + z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.3f, 0.03f, 0.15f);

                cube.drawCubeWithTexture(lightingShaderWithTexture, model);
            }
            else {

                if (1.4f - currentFrame + i > -3.8f) {
                    float temp_X = 5.4f;
                    if (rotation_angle > -90.0f) {
                        rotation_angle = rotation_angle - (i);
                    }
                    else {
                        rotation_angle = -90.0f;
                    }
                    model = model * transformation(temp_X, 1.4f - currentFrame + i
                        , translate_Z + z, rotateAngle_X, rotateAngle_Y, rotation_angle, 0.3f, 0.03f, 0.15f);
                    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
                }

            }
        }


    }



}

void containerchoco(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether) {
    for (float i = 0.4f; i < 1.8f; i += 0.5f) {
        for (float z = 0.6f; z < 1.8f; z += 0.4f) {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 translate = glm::mat4(1.0f);
            glm::mat4 translate2 = glm::mat4(1.0f);
            glm::mat4 scale = glm::mat4(1.0f);
            scale = glm::scale(model, glm::vec3(0.3f, 0.03f, 0.15f));
            translate = glm::translate(model, glm::vec3(0 + i, 1.4f, 0 + z));
            model = alTogether * translate * scale;
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
    }
}

void carboardbox(Cube cube, Shader& lightingShaderWithTexture, glm::mat4 alTogether) {
    //bottom
    glm::mat4 model = glm::mat4(1.0f);
    model = alTogether * transformation(translate_X, translate_Y, translate_Z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.0f, 0.01f, 1.0f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    //left
    model = alTogether * transformation(translate_X, translate_Y, translate_Z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.01f, 1.00f, 1.0f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    //right
    model = alTogether * transformation(0.99f, translate_Y, translate_Z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.01f, 1.00f, 1.0f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //back
    model = alTogether * transformation(translate_X, translate_Y, translate_Z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.00f, 1.00f, 0.01f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //front
    model = alTogether * transformation(translate_X, translate_Y, 0.99f, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.00f, 1.00f, 0.01f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //front fly
    model = alTogether * transformation(translate_X,0.99f, 0.99f, 45.0f, rotateAngle_Y, rotateAngle_Z, 1.00f, 0.01f, 0.5f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //left fly
    model = alTogether * transformation(translate_X, 0.99f,0.0f, 0.0f, rotateAngle_Y,215.0f, 0.5f, 0.01f, 1.00f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);

    //back fly
    model = alTogether * transformation(translate_X, 0.99f, 0.0f, -45.0f, rotateAngle_Y, 0.0f, 1.00f, 0.01f, -0.5f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    //right fly 
    model = alTogether * transformation(0.99f, 0.99f, 0.0f, 0.0f, rotateAngle_Y, -45.0f, 0.5f, 0.01f, 1.00f);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
}


//maker
void maker1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,int type)
{



    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);


    //back
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.1f));
    translate = glm::translate(model, glm::vec3(7.0f, 0.2f, 0.8f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, .96f, .96f, .96f, 0.5f, 0.5f, 0.5f);

    //front
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.1f));
    translate = glm::translate(model, glm::vec3(7.0f, 0.2f, 2.5f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, .96f, .96f, .96f, 0.5f, 0.5f, 0.5f);

    

    if (type == 1) {
        //top
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(2.0f, 0.1f, 1.7f));
        translate = glm::translate(model, glm::vec3(7.0f, 2.0f, 0.8f));
        model = alTogether * translate * scale;
        drawWallCube(cubeVAO, lightingShader, model, .96f, .96f, .96f, 0.5f, 0.5f, 0.5f);
    }
    else {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(0.8f, 0.1f, 1.7f));
        translate = glm::translate(model, glm::vec3(7.0f, 2.0f, 0.8f));
        model = alTogether * translate * scale;
        drawWallCube(cubeVAO, lightingShader, model, .96f, .96f, .96f, 0.5f, 0.5f, 0.5f);

        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(0.7f, 0.1f, 1.7f));
        translate = glm::translate(model, glm::vec3(8.3f, 2.0f, 0.8f));
        model = alTogether * translate * scale;
        drawWallCube(cubeVAO, lightingShader, model, .96f, .96f, .96f, 0.5f, 0.5f, 0.5f);
    }

    //cover
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.5f, 1.5f, 0.1f));
    translate = glm::translate(model, glm::vec3(7.2f, 0.5f, 2.55f));
    model = alTogether * translate * scale;
    drawWallCube(cubeVAO, lightingShader, model, 1.0f, 0.75, 0.75, 0.5f, 0.5f, 0.5f);



    



}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    

    
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
   
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    
    

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLight1On)
        {
            pointlight1.turnOff();
            pointlight3.turnOff();
            pointlight5.turnOff();
            pointlight6.turnOff();
            pointlight7.turnOff();
            
            pointLight1On = !pointLight1On;
            pointLight3On = !pointLight3On;
            pointLight5On = !pointLight5On;
            pointLight6On = !pointLight6On;
            pointLight7On = !pointLight7On;
        }
        else
        {
            pointlight1.turnOn();
            pointlight3.turnOn();
            pointlight5.turnOn();
            pointlight6.turnOn();
            pointlight7.turnOn();

            
            pointLight1On = !pointLight1On;
            pointLight3On = !pointLight3On;
            pointLight5On = !pointLight5On;
            pointLight6On = !pointLight6On;
            pointLight7On = !pointLight7On;
        }
    }
   if (key == GLFW_KEY_2 && action == GLFW_PRESS)
   {
       if (pointLight2On)
       {
           pointlight2.turnOff();
           pointlight4.turnOff();

           pointLight2On = !pointLight2On;
           pointLight4On = !pointLight4On;
       }
       else
       {

           pointlight2.turnOn();
           pointlight4.turnOn();

           pointLight2On = !pointLight2On;
           pointLight4On = !pointLight4On;
       }
   }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (directionalLightOn)
        {
            directionalLight.turnOff();

            directionalLightOn = !directionalLightOn;
        }
        else
        {
            directionalLight.turnOn();

            directionalLightOn = !directionalLightOn;
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            spotLight1.turnOff();
            spotLight2.turnOff();
            spotLight3.turnOff();
            spotLight4.turnOff();

            spotLightOn = !spotLightOn;
        }
        else
        {
            spotLight1.turnOn();
            spotLight2.turnOn();
            spotLight3.turnOn();
            spotLight4.turnOn();
            spotLightOn = !spotLightOn;
        }
    }


    else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            pointlight5.turnSpecularOff();
            pointlight6.turnSpecularOff();
            pointlight7.turnSpecularOff();
            
         
            directionalLight.turnSpecularOff();
            spotLight1.turnSpecularOff();
            spotLight2.turnSpecularOff();
            spotLight3.turnSpecularOff();
            spotLight4.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            pointlight5.turnSpecularOn();
            pointlight6.turnSpecularOn();
            pointlight7.turnSpecularOn();
            
          
            directionalLight.turnSpecularOn();
            spotLight1.turnSpecularOn();
            spotLight2.turnSpecularOn();
            spotLight3.turnSpecularOn();
            spotLight4.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            pointlight5.turnDiffuseOff();
            pointlight6.turnDiffuseOff();
            pointlight7.turnDiffuseOff();
          
            directionalLight.turnDiffuseOff();
            spotLight1.turnDiffuseOff();
            spotLight2.turnDiffuseOff();
            spotLight3.turnDiffuseOff();
            spotLight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            pointlight5.turnDiffuseOn();
            pointlight6.turnDiffuseOn();
            pointlight7.turnDiffuseOn();
            
            directionalLight.turnDiffuseOn();
            spotLight1.turnDiffuseOn();
            spotLight2.turnDiffuseOn();
            spotLight3.turnDiffuseOn();
            spotLight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            pointlight5.turnAmbientOff();
            pointlight6.turnAmbientOff();
            pointlight7.turnAmbientOff();
            
            directionalLight.turnAmbientOff();
            spotLight1.turnAmbientOff();
            spotLight2.turnAmbientOff();
            spotLight3.turnAmbientOff();
            spotLight4.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            pointlight5.turnAmbientOn();
            pointlight6.turnAmbientOn();
            pointlight7.turnAmbientOn();
          
            directionalLight.turnAmbientOn();
            spotLight1.turnAmbientOn();
            spotLight2.turnAmbientOn();
            spotLight3.turnAmbientOn();
            spotLight4.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (runMechine) {
            runMechine = false;
            runMechineTOFF = true;
            runMechineTON = false;
            
        }
        else {
            runMechine = true;
            runMechineTON = true;
            runMechineTOFF = false;
            lastmechineoff= static_cast<float>(glfwGetTime());
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (runMechine2) {
            runMechine2 = false;
            runMechineTOFF2 = true;
            runMechineTON2 = false;

        }
        else {
            runMechine2 = true;
            runMechineTON2 = true;
            runMechineTOFF2 = false;
            lastmechineoff2 = static_cast<float>(glfwGetTime());
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (runMechine3) {
            runMechine3 = false;
            runMechineTOFF3 = true;
            runMechineTON3 = false;

        }
        else {
            runMechine3 = true;
            runMechineTON3 = true;
            runMechineTOFF3 = false;
            lastmechineoff3 = static_cast<float>(glfwGetTime());
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        if (doorOn) {
            doorOn = false;
        }
        else {
            doorOn = true;
        }
    }
}



long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector <float>& coordinates,
    vector <float>& normals,
    vector <int>& indices,
    vector <float>& vertices)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
glm::mat4 transformation(float transform_x, float transform_y, float transform_z, float rotate_x, float rotate_y,
    float rotate_z, float scale_x, float scale_y, float scale_z) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(transform_x, transform_y, transform_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotate_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotate_z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_x, scale_y, scale_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return model;
}