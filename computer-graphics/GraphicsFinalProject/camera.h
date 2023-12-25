#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default Camera Values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

//const float maxDown = 2.0f;
//const float maxUp = 5.0f;

class Camera {
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler angles
	float Yaw;
	float Pitch;
	// Camera movements
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	int width, height;
	bool firstClick = true;

	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	// constructor with scalars
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// get matrix with calculated euler angles and the lookat matrix
	glm::mat4 GetViewMatrix();

	// handling keyboard inputs
	void ProcessKeyboard(Camera_Movement, float deltaTime);
	// handling mouse movements
	void ProcessMouseMovements(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// handling moust scrolling
	void ProcessMouseScroll(float yoffset);

private:
	void updateCameraVectors();
};

#endif // !CAMERA_CLASS_H
