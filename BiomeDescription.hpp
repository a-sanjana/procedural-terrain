/**
 * @file BiomeDescription.hpp
 * @brief Defines the BiomeDescription struct and related functions for biome generation.
 */

#ifndef BIOMEDESCRIPTION_HPP
#define BIOMEDESCRIPTION_HPP

#define BIOMESN 5

#include <glm/glm.hpp>

/**
 * @enum BiomeType
 * @brief Enumeration representing different types of biomes.
 */
enum BiomeType : int {
    PLAINS = 0,     /**< Plains biome. */
    MOUNTAINS = 1,  /**< Mountains biome. */
    VALLEY = 2,     /**< Valley biome. */
    DESERT = 3,     /**< Desert biome. */
    CANYONS = 4     /**< Canyons biome. */
};

/**
 * @struct BiomeValues
 * @brief Represents the description of a biome.
 */
struct BiomeValues{
    double bFrequence;  /**< Frequency of the biome. */
    int bOctaves;       /**< Octaves for generating the biome. */
    glm::vec3 minColor; /**< Minimum color of the biome. */
    glm::vec3 midColor; /**< Midpoint color of the biome. */
    glm::vec3 maxColor; /**< Maximum color of the biome. */
};

/**
 * @brief Transform RGB values from 0-255 range to 0-1 range.
 * @param inrgb RGB values in the range of 0-255.
 * @return Transformed RGB values in the range of 0-1.
 */
glm::vec3 rgbTransform(glm::vec3 inrgb){
    return glm::vec3(inrgb.r/255.0, inrgb.g/255.0, inrgb.b/255.0);
}

/**
 * @brief Get the description of a specific biome.
 * @param pbt The type of biome.
 * @return The biome description.
 */
BiomeValues getTheBiomeDescription(BiomeType pbt){
    
    
    BiomeValues descrip;
    //--------------------------------------------------------------------------PLAINS
    if(pbt == PLAINS){
        descrip.bFrequence = 10.0;
        descrip.bOctaves   = 4;
        descrip.minColor   = rgbTransform(glm::vec3(34.0,139.0,34.0));
        descrip.midColor   = rgbTransform(glm::vec3(154.0,205.0,50.0));
        descrip.maxColor   = rgbTransform(glm::vec3(143.0,188.0,143.0));//(143,188,143)

    }else if(pbt == MOUNTAINS){//------------------------------------------------MOUNTAINS
        descrip.bFrequence = 18.0;
        descrip.bOctaves   = 8;
        descrip.minColor   = rgbTransform(glm::vec3(26.0, 19.0, 59.0));
        descrip.midColor   = rgbTransform(glm::vec3(48.0, 65.0, 82.0));
        descrip.maxColor   = rgbTransform(glm::vec3(255.0, 255.0, 255.0));
        
    }else if(pbt == VALLEY){//--------------------------------------------------VALLEY
        descrip.bFrequence = 8.0;
        descrip.bOctaves   = 8;
        descrip.minColor   = rgbTransform(glm::vec3(7.0, 0.0, 119.0));
        descrip.midColor   = rgbTransform(glm::vec3(46.0, 139.0, 87.0));
        descrip.maxColor   = rgbTransform(glm::vec3(8.0, 73.0, 15.0));
        
    }else if(pbt == DESERT){//--------------------------------------------------DESERT
        descrip.bFrequence = 6.0;
        descrip.bOctaves   = 2;
        descrip.minColor   = rgbTransform(glm::vec3(0, 0, 0));
        descrip.midColor   = rgbTransform(glm::vec3(125, 75, 33));
        descrip.maxColor   = rgbTransform(glm::vec3(173, 156, 78));
        
    }else if(pbt == CANYONS){//-------------------------------------------------CANYONS
        descrip.bFrequence = 6.0;
        descrip.bOctaves   = 4;
        descrip.minColor   = rgbTransform(glm::vec3(0, 0, 0));
        descrip.midColor   = rgbTransform(glm::vec3(244.0, 164.0, 96.0));
        descrip.maxColor   = rgbTransform(glm::vec3(255, 255, 255));
        
    }
    
    return descrip;
}



#endif