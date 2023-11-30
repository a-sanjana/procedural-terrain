/**
 * @file ptg.hpp
 * @brief Defines the main header file for the Procedural Terrain Generation application.
 *
 * This file includes necessary libraries, global settings, and function declarations.
 */
#ifndef PTG_HPP
#define PTG_HPP


#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "include\glad\glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "PerlinNoise.hpp"
#include "TerrainGen.hpp"

#include <vector>
//Global settings
//initial screen size
const unsigned int ISCR_W = 100 * 16;//WIDTH
const unsigned int ISCR_H = 100 * 9;//HEIGHT

/**
 * @brief Error callback function for GLFW to handle errors.
 *
 * @param error The GLFW error code.
 * @param description A description of the error.
 */
static void errorCallback(int error, const char* description);//to show some glfw errors

/**
 * @brief GLFW key callback function to handle keyboard input.
 *
 * @param window The GLFW window.
 * @param key The pressed/released key.
 * @param scancode The system-specific scancode of the key.
 * @param action The action (press, release, repeat) of the key.
 * @param mods Modifier keys held down.
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);//input callBack

/**
 * @brief GLFW framebuffer size callback function to handle window resizing.
 *
 * @param window The GLFW window.
 * @param width The new width of the window.
 * @param height The new height of the window.
 */
void framebufferSizeCallback(GLFWwindow* window, int width, int height);//resize screen

/**
 * @brief Process input while holding down specific keys.
 *
 * @param window The GLFW window.
 * @param deltaTime Time between the current and last frame.
 */
void processInputHoldingKey(GLFWwindow *window, float deltaTime);//to manage keys holding down


/**
 * @brief GLFW cursor position callback function to handle mouse movement.
 *
 * @param window The GLFW window.
 * @param xpos The new x-coordinate of the cursor.
 * @param ypos The new y-coordinate of the cursor.
 */
static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);//send mouse position to the camera

/**
 * @brief GLFW scroll callback function to handle mouse scroll events.
 *
 * @param window The GLFW window.
 * @param xoffset The horizontal scroll offset.
 * @param yoffset The vertical scroll offset.
 */
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);//callback to get mouse scroll events and change zoom matrix in the view of camera

#endif