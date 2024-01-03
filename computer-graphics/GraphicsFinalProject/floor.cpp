#ifndef FLOOR_CLASS
#define FLOOR_CLASS
#include "loadTexture.h"
#include "model.h"
#include "shaderClass.h"
#include "camera.h"

class Floor {
public:
    //Shader* shader;
    glm::vec3 lightPos;
    unsigned int planeVAO, planeVBO, floorTexture;
	Floor(Shader shader, glm::vec3 lightPos) {
        //Floor::shader = shader;
        Floor::lightPos = lightPos;
		setupFloor(shader);
	};

	void setupFloor(Shader shader) {
        //shader.Activate();
        float planeVertices[] = {
            // positions            // normals         // texcoords
             10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
             10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
             10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
        };

        glGenVertexArrays(1, &planeVAO);
        glGenBuffers(1, &planeVBO);
        glBindVertexArray(planeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);

        floorTexture = LoadTexture("textures/dirtFloor.png");
        shader.Activate();
        shader.setInt("material.texture_diffuse1", 0);
        shader.setFloat("material.shininess", 8.0f);
	}

    void Draw(Camera& camera) {
        glBindVertexArray(planeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};

#endif