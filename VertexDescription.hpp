/**
 * @file
 * @brief Defines the Vertex structure for describing vertex attributes.
 *
 * This file contains the definition of the Vertex structure, which includes position and color attributes.
 */

#ifndef VERTEXDESCRIPTION_HPP
#define VERTEXDESCRIPTION_HPP

#include <glm/glm.hpp>
#include "stb_image.h"

 /**
  * @struct Vertex
  * @brief Describes the attributes of a vertex, including position and color.
  */
struct Vertex {
    glm::vec3 Position; /**< Position of the vertex in 3D space. */
    glm::vec3 Color;    /**< Color of the vertex. */
};

#endif


