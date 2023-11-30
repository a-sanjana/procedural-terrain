/**
\mainpage
* # IS F311 Computer Graphics Project
* ## Implementing Procedural Terrain Modeling using Perlin Noise
*
* Adapala Sanjana 2020B4A72243H

* ### Camera Controls
*
* + W,A,S,D,Left CTRL,Left Shift : Moving Front Back, Left, Right, Up, Down
* + P : Default Camera View
* + M : Show Mesh
* + K : Show Axes
* 
* ###Output : Different Terrains
*
* #### Plains
* <img src = "C:\Users\adapa\OpenGL\GLP\perlin3\plain.png" width = "40%">
*
* #### Mountains
* <img src = "C:\Users\adapa\OpenGL\GLP\perlin3\mountain.png" width = "40%">
*
* #### Valleys
* <img src = "C:\Users\adapa\OpenGL\GLP\perlin3\valley.png" width = "40%">
*
* #### Deserts
* <img src = "C:\Users\adapa\OpenGL\GLP\perlin3\desert.png" width = "40%">
*
*
* ### Algortihm Description
* The Noise generated is based on Perlin's Improvised Noise.
* It uses gradient vectors and the smooth interpolation between them to achieve cherent patterns.
* A terrain is drawn consisting of four different biomes - mountain, valley, desert and plain. 
* Each boundary between the biomes is interpolated.
* 
* ### Issues in Coding
* + Interpolation between different biomes
* + Adjusting the octaves to generate each biome
* + Mapping the colors according to noise and biome
* + Mapping the height according to noise and biome
*
* ### References
* 1. https://dl.acm.org/doi/10.1145/325165.325247
* 2. https://github.com/Reputeless/PerlinNoise
* 3. https://cs.nyu.edu/~perlin/noise/
*/
#include "ptg.hpp"


bool showMesh; ///< Flag to toggle between displaying mesh and filled terrain.
bool showAxes; ///< Flag to toggle the visibility of axes.
bool rebuildflag; ///< Flag to trigger the rebuild of the terrain chunk.

/**
 * @brief Main function for the Procedural Terrain Generation application.
 *
 * @return Program exit status.
 */
int main(){
    printf("Compiled against GLFW %i.%i.%i\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    
    //set the callback to show glfw errors
    glfwSetErrorCallback(errorCallback);
    
    printf("Calling glfwInit...\n");
    if (!glfwInit()){
        printf("Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Note: now cant work with Immediate mode, only with Core-profile
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    
    printf("Creating window...\n");
    GLFWwindow* window = glfwCreateWindow(ISCR_W, ISCR_H, "Perlin Terrain", NULL, NULL);
    if (! window ){
        printf("Failed to create window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //set GLFW callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//No cursor, camera mode only
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    //Configure global opengl state to use z-buffer
    glEnable(GL_DEPTH_TEST);
    
    //read shader files
    Shader terrainProgram("terrain.vs", "terrain.fs");
    
    
    float myAxes[] = {
        1000.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        -1000.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.0f,  1000.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  -1000.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f,  0.0f, 1000.0f,  0.0f, 0.0f, 1.0f,
        0.0f,  0.0f, -1000.0f,  0.0f, 0.0f, 1.0f
    };
    unsigned int aVBO, aVAO;
    glGenVertexArrays(1, &aVAO);
    glGenBuffers(1, &aVBO);
    glBindVertexArray(aVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, aVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myAxes), myAxes, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    
    rebuildflag = false;
    TerrainGen tManager(0, terrainProgram.ID);
    
    
    glViewport(0, 0, ISCR_W, ISCR_H);
    
    //creating variables
    int cscr_w=ISCR_W, cscr_h=ISCR_H;
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    double lastTime = glfwGetTime();
    unsigned frameCounter = 0, fps = 0.0;
    showMesh = false;
    showAxes = false;
    
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    
    Camera cam;
    glfwSetWindowUserPointer(window, &cam);
    
    unsigned myi=0;
    //mainLoop
    printf("Entering in the main loop...\n");
    while (!glfwWindowShouldClose(window)){
        float cFrameTime = glfwGetTime();
        deltaTime = cFrameTime - lastFrame;
        lastFrame = cFrameTime;
        frameCounter++;
        if(cFrameTime - lastTime >= 1.0){
            fps = frameCounter;
            frameCounter = 0;
            lastTime = cFrameTime;
        }
        
        printf("\r%u (%lf, %lf, %lf),(%lf, %lf, %lf)(%lf)  %u   ",myi++, cam.pos.x, cam.pos.y, cam.pos.z, cam.front.x, cam.front.y, cam.front.z, cam.zoomC, fps);
        fflush(stdout);
        
        //process holding keys
        processInputHoldingKey(window, deltaTime);
        
        //render
        //clear the collor buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the buffers
        
        
        //active the shader and bind uniforms
        terrainProgram.use();
        
        // create transformations
        view  = cam.getViewMatrix();
        glfwGetWindowSize(window, &cscr_w, &cscr_h);//essa função é threadsafe
        projection = glm::perspective(glm::radians(cam.zoomC), (float)cscr_w / (float)cscr_h, 0.1f, 2200.0f);
        terrainProgram.setMat4("projection", projection);
        terrainProgram.setMat4("view", view);
        
        
        //render container
        if(showAxes){
            glBindVertexArray(aVAO);
            model = glm::mat4(1.0f);
            terrainProgram.setMat4("model", model);
            glDrawArrays(GL_LINES, 0, 6);
            
            
        }
        
        if(rebuildflag){
            
            tManager.rebuild(cam.pos);
            rebuildflag = false;
        }
        
        
        if(showMesh){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            
        }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            
        }
        
        tManager.drawTerrain();
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("\n");
    
    printf("Free memory space...\n");
    //de-allocate all resources once they've outlived their purpose
    
    glDeleteVertexArrays(1, &aVAO);
    glDeleteBuffers(1, &aVBO);
    tManager.shutDown();
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/**
 * @brief GLFW error callback function.
 *
 * @param error Error code.
 * @param description Error description.
 */
static void errorCallback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}


/**
 * @brief GLFW key callback function for handling key input.
 *
 * @param window GLFW window.
 * @param key Pressed key.
 * @param scancode System-specific scancode of the key.
 * @param action Action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
 * @param mods Modifiers (e.g., GLFW_MOD_SHIFT).
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){//input callBack
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//close window
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_M && action == GLFW_PRESS)//intercalate, mesh and fill terrain
        showMesh = !showMesh;
    if (key == GLFW_KEY_K && action == GLFW_PRESS)//show/hide axes
        showAxes = !showAxes;
    if (key == GLFW_KEY_P && action == GLFW_PRESS){//move camera to specific location with specific angle view
        Camera* cam = (Camera*)glfwGetWindowUserPointer(window);
        cam->pos = glm::vec3(42.237156, 142.904083, -199.660156);
        cam->front = glm::vec3(0.921904, -0.365689, -0.127925);
        
    }
    
    if (key == GLFW_KEY_R && action == GLFW_PRESS){//build a new terrain chunk in the camera position
        rebuildflag = true;
    }
}

/**
 * @brief GLFW framebuffer size callback function for handling window resizing.
 *
 * @param window GLFW window.
 * @param width New width of the window.
 * @param height New height of the window.
 */
void framebufferSizeCallback(GLFWwindow* window, int width, int height){//resize screen
    glViewport(0, 0, width, height);
}

/**
 * @brief Process input for holding down keys.
 *
 * @param window GLFW window.
 * @param deltaTime Time between the current frame and the last frame.
 */
void processInputHoldingKey(GLFWwindow *window, float deltaTime){
    Camera* cam = (Camera*)glfwGetWindowUserPointer(window);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->moveForwarRelXZ(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->moveBackwardRelXZ(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->moveLeftRelXZ(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->moveRightRelXZ(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam->moveUpAbs(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cam->moveDownAbs(deltaTime);
}

/**
 * @brief GLFW cursor position callback function for handling mouse movement.
 *
 * @param window GLFW window.
 * @param xpos X-coordinate of the cursor position.
 * @param ypos Y-coordinate of the cursor position.
 */
static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    Camera* cam = (Camera*)glfwGetWindowUserPointer(window);
    cam->interpretMouseMovement(xpos, ypos);
    
}


/**
 * @brief GLFW scroll callback function for handling mouse scroll events.
 *
 * @param window GLFW window.
 * @param xoffset Horizontal scroll offset.
 * @param yoffset Vertical scroll offset.
 */
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    Camera* cam = (Camera*)glfwGetWindowUserPointer(window);
    cam->zoomSub(yoffset);
}