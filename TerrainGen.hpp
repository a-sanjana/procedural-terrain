/**
 * @file
 * @brief Defines the TerrainGen class for terrain generation and rendering.
 */

#ifndef TERRAINGEN_HPP
#define TERRAINGEN_HPP

#include <glm/glm.hpp>
#include "TerrainChunk.hpp"
#include "shader.hpp"

 /**
  * @class TerrainGen
  * @brief Class for terrain generation and rendering.
  */

class TerrainGen{
private:
    unsigned int seed, chunkSize;
    float vertexInterval;
    unsigned int biomeSize, borderLen;
    Shader sProgram;
public:
    TerrainChunk *tca1; /**< Pointer to the first terrain chunk. */
    //TerrainChunk *tca2;
    
    /**
     * @brief Constructor for TerrainGen class.
     * @param pSeed The seed for terrain generation.
     * @param psp Shader program ID.
     */
    TerrainGen(unsigned int pSeed, unsigned int psp):sProgram(psp){
        this->seed = pSeed;
        this->vertexInterval = 0.5;
        this->chunkSize = 1024*2;
        this->biomeSize = 512;
        this->borderLen = 64;
        tca1 = new TerrainChunk(this->seed, this->vertexInterval, this->chunkSize, this->chunkSize/2.0f*-1.0f,  this->chunkSize/2.0f*-1.0f, this->biomeSize, this->borderLen);
        //tca2 = new TerrainChunk(this->seed, this->vertexInterval, this->chunkSize, 0, 0, this->biomeSize, this->borderLen);
        //tca2 = new TerrainChunk(this->seed, this->vertexInterval, this->chunkSize, 1024-1 , this->chunkSize/2.0f*-1.0f, this->biomeSize, this->borderLen);
        
    }
    
    /**
     * @brief Draws the terrain using the specified shader program.
     */
    void drawTerrain(){
        this->sProgram.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tca1->getInitialXZ());
        this->sProgram.setMat4("model", model);
        tca1->DrawChunk();
        
        
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, tca2->getInitialXZ());
        //this->sProgram.setMat4("model", model);
        //tca2->DrawChunk();
        
    }
    
    /**
     * @brief Rebuilds the terrain based on the current camera position.
     * @param cpos The current camera position.
     */
    void rebuild(glm::vec3 cpos){
        //tca2->shutDown();
        double offsetxz = this->chunkSize/2.0;
        
    }
    
    /**
     * @brief Shuts down the terrain generator and releases resources.
     */
    void shutDown(){
        tca1->shutDown();
        //tca2->shutDown();
    }
    
    
};

#endif