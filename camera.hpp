/**
 * @file camera.hpp
 * @brief Definition of the Camera class for managing 3D camera properties and movements.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "include\glad\glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @class Camera
 * @brief Represents a 3D camera with various properties and movement capabilities.
 */
class Camera{
public:
    /**
     * @brief Camera position in 3D space.
     */
    glm::vec3 pos;

    /**
     * @brief Front direction of the camera.
     */
    glm::vec3 front;

    /**
     * @brief Up direction of the camera.
     */
    glm::vec3 up;

    /**
     * @brief Movement speed of the camera.
     */
    float movSpeed;

    /**
     * @brief Yaw angle (horizontal rotation) of the camera.
     */
    float yaw;

    /**
     * @brief Pitch angle (vertical rotation) of the camera.
     */
    float pitch;

    /**
     * @brief Last recorded mouse position x-coordinate.
     */
    double lastMposx;

    /**
     * @brief Last recorded mouse position y-coordinate.
     */
    double lastMposy;

    /**
     * @brief Flag indicating whether the mouse is active.
     */
    bool mouseActive;

    /**
     * @brief Zoom factor in the camera's projection.
     */
    float zoomC;

    /**
     * @brief Constructor for the Camera class.
     * @param iPos Initial position of the camera.
     * @param iFront Initial front direction of the camera.
     * @param iUp Initial up direction of the camera.
     * @param iMovSpeed Initial movement speed of the camera.
     * @param iYaw Initial yaw angle of the camera.
     * @param iPitch Initial pitch angle of the camera.
     */
    Camera(glm::vec3 iPos, glm::vec3 iFront, glm::vec3 iUp, float iMovSpeed, float iYaw, float iPitch);

    /**
     * @brief Default constructor for the Camera class.
     */
    Camera();

    /**
     * @brief Get the view matrix for the camera.
     * @return The view matrix.
     */
    glm::mat4 getViewMatrix();

    // Movements relative to the front ---------------------------------------

    /**
     * @brief Move the camera forward relative to its front direction.
     * @param deltaT Time delta for smooth movement.
     */
    void moveForwarRel(float deltaT);

    /**
     * @brief Move the camera backward relative to its front direction.
     * @param deltaT Time delta for smooth movement.
     */
    void moveBackwardRel(float deltaT);

    /**
     * @brief Move the camera left relative to its front direction.
     * @param deltaT Time delta for smooth movement.
     */
    void moveLeftRel(float deltaT);

    /**
     * @brief Move the camera right relative to its front direction.
     * @param deltaT Time delta for smooth movement.
     */
    void moveRightRel(float deltaT);

    /**
     * @brief Move the camera forward relative to its front direction on the XZ plane.
     * @param deltaT Time delta for smooth movement.
     */
    void moveForwarRelXZ(float deltaT);

    /**
     * @brief Move the camera backward relative to its front direction on the XZ plane.
     * @param deltaT Time delta for smooth movement.
     */
    void moveBackwardRelXZ(float deltaT);

    /**
     * @brief Move the camera left relative to its front direction on the XZ plane.
     * @param deltaT Time delta for smooth movement.
     */
    void moveLeftRelXZ(float deltaT);

    /**
     * @brief Move the camera right relative to its front direction on the XZ plane.
     * @param deltaT Time delta for smooth movement.
     */
    void moveRightRelXZ(float deltaT);

    // Absolute movements ----------------------------------------------------

    /**
     * @brief Move the camera up in absolute coordinates.
     * @param deltaT Time delta for smooth movement.
     */
    void moveUpAbs(float deltaT);

    /**
     * @brief Move the camera down in absolute coordinates.
     * @param deltaT Time delta for smooth movement.
     */
    void moveDownAbs(float deltaT);

    /**
     * @brief Interpret mouse movement to change the camera's front direction.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     */
    void interpretMouseMovement(double x, double y);

    /**
     * @brief Zoom in or out in the camera's projection.
     * @param iYoffset The offset for zooming.
     */
    void zoomSub(double iYoffset);
};

#endif
