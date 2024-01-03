#include"Model.h"
#include"skybox.h"
#include<iostream>
#include<glm/gtx/string_cast.hpp>
#include<glm/glm.hpp>
#include <cmath>
#include "cube.h"
#include "wall.cpp"
#include "floor.cpp"
#include "animation.h"
#include "animator.h"

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 1000;

const bool animate = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void renderSpire(Shader& spireShader, glm::vec3& lightPos, glm::mat4& projection, glm::mat4& view, Model& spire);

void renderCrowd(Shader& vanguardShader, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos, Animator& vanguardAnimator, Model& vanguard, Animator& survivorAnimator, Shader& survivorShader, Model& survivor);

void addSpotlight(Shader& shader);
void addPointLight(Shader& shader);

//void addDirLight(Shader& shader);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

template<typename T, size_t N, size_t M>
void printArray(T(&mat)[N][M])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << mat[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void renderSpire(Shader& spireShader, glm::vec3& lightPos, glm::mat4& projection, glm::mat4& view, Model& spire)
{
	spireShader.Activate();
	spireShader.setVec3("light.position", lightPos);
	spireShader.setVec3("viewPos", camera.Position);

	// light properties
	spireShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	spireShader.setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
	spireShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// material properties
	spireShader.setFloat("material.shininess", 100.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(7.0f, -2.0f, 7.0f));
	spireShader.setMat4("model", model);
	spireShader.setMat4("projection", projection);
	spireShader.setMat4("view", view);

	addSpotlight(spireShader);
	addPointLight(spireShader);

	spire.Draw(spireShader, camera);
}

void addSpotlight(Shader& shader) {
	shader.setVec3("spotLight.position", camera.Position);
	shader.setVec3("spotLight.direction", camera.Front);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09f);
	shader.setFloat("spotLight.quadratic", 0.032f);

	shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.intensityVal", 1.0f);
}

//void addDirLight(Shader& shader) {
//	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//	shader.setFloat("dirLight.intensityVal", 1.0f);
//}

void addPointLight(Shader& shader) {
	shader.setVec3("pointLight.position", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLight.constant", 1.0f);
	shader.setFloat("pointLight.linear", 0.09f);
	shader.setFloat("pointLight.quadratic", 0.032f);
	shader.setFloat("pointLight.intensityVal", 1.0f);
}

glm::mat4 modelCircle(glm::mat4 model, float angle, float radius = 5.0f) {
	float xPos = std::cos(glm::degrees(angle)) * radius;
	float yPos = std::sin(glm::degrees(angle)) * radius;
	glm::mat4 modelOut = model;

	modelOut = glm::rotate(modelOut, glm::degrees(angle), glm::vec3(0.0f, -1.0f, 0.0f)); // set rotated position tangent to circle path
	modelOut = glm::translate(model, glm::vec3(xPos, 0.0f, yPos)); // set translated position on circle path
	return modelOut;
}

void renderCrowd(Shader& vanguardShader, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos, Animator& vanguardAnimator, Model& vanguard, Animator& survivorAnimator, Shader& survivorShader, Model& survivor)
{
	vanguardShader.Activate();
	glm::mat4 model = glm::mat4(1.0f);
	auto transforms = vanguardAnimator.GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); i++)
		vanguardShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
	transforms = survivorAnimator.GetFinalBoneMatrices();
	survivorShader.Activate();
	for (int i = 0; i < transforms.size(); i++)
		survivorShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

	float angle = (float)glfwGetTime() / 200;
	float scaleFactor = 0.75f;
	float radius = 5.0f;
	for (int i = 0; i < 1; i++)
	{
		vanguardShader.Activate();
		model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		//model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::degrees(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
		//glm::rotate(model, glm::degrees((float)glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f);
		vanguardShader.setMat4("model", modelCircle(model, angle, radius));
		vanguardShader.setMat4("projection", projection);
		vanguardShader.setMat4("view", view);
		vanguardShader.setVec3("viewPos", camera.Position);
		vanguardShader.setVec3("lightPos", lightPos);
		addSpotlight(vanguardShader);
		addPointLight(vanguardShader);

		vanguard.Draw(vanguardShader, camera);

		survivorShader.Activate();
		//model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); // translate these boys to the side
		//model = modelCircle(model, angle, 1.0f); // and circle transformations
		survivorShader.setMat4("model", modelCircle(model, angle, radius + 1.0f));
		survivorShader.setMat4("projection", projection);
		survivorShader.setMat4("view", view);
		survivorShader.setVec3("viewPos", camera.Position);
		survivorShader.setVec3("lightPos", lightPos);
		addSpotlight(survivorShader);
		addPointLight(survivorShader);
		survivor.Draw(survivorShader, camera);
	}
}

int main() {
	// Init GLFW
	glfwInit();

	// Tell GLFW which version we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LJ Graphics", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	gladLoadGL();
	glViewport(0, 0, WIDTH, HEIGHT);

	//Shader shaderProgram("default.vert", "default.frag");

	// Lighting
	//Shader lightShader("light.vert", "light.frag");
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	//lightModel = glm::translate(lightModel, lightPos);

	//lightShader.Activate();
	//lightShader.setMat4("model", lightModel);
	//lightShader.setVec4("lightColor", lightColor);

	//lightShader.setInt("material.diffuse", 0);
	//lightShader.setInt("material.specular", 1);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Model Setup
	Shader backpackShader("backpack.vs", "backpack.fs");
	Model backpackModel((char*)"models/backpack/backpack.obj");

	// Floor Setup
	Shader floorShader("floor.vs", "floor.fs");
	Floor floor(floorShader, lightPos);

	// Vanguard Anim
	Shader vanguardShader("anim_model.vs", "anim_model.fs");
	const char* vanguardPath = "models/vanguard/zombie_walk.dae";
	Model vanguard((char*)vanguardPath);
	Animation vanguardWalk((char*)vanguardPath, &vanguard);
	Animator vanguardAnimator(&vanguardWalk);

	// Survivor Anim
	Shader survivorShader("anim_model.vs", "anim_model.fs");
	const char* survivorPath = "models/survivor/zombie_walk.dae";
	Model survivor((char*)survivorPath);
	Animation survivorWalk((char*)survivorPath, &survivor);
	Animator survivorAnimator(&survivorWalk);


	// Zombie Static
	//Model staticZombie((char*)"models/zombie/zombie.obj");

	// Cube Setup
	vector<std::string> faces
	{
		"textures/postapocalyptic_skybox/right.jpg", // right
		"textures/postapocalyptic_skybox/left.jpg", // left
		"textures/postapocalyptic_skybox/top.jpg", // top
		"textures/postapocalyptic_skybox/bottom.jpg", // bottom
		"textures/postapocalyptic_skybox/front.jpg", // front
		"textures/postapocalyptic_skybox/back.jpg" // back
	};
	unsigned int cubemapTexture = Skybox::LoadCubemap(faces);
	Shader cubeShader("cube.vs", "cube.fs");
	Cube theCube(cubemapTexture);

	// Spire Setup
	Shader spireShader("spire.vs", "spire.fs");
	Model spire((char*)"models/spire/Spire.obj");


	// Skybox setup
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	Shader skyboxShader("skybox.vs", "skybox.fs");
	Skybox skybox(skyboxShader, faces, skyboxVertices);
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	bool firstFrame = true;
	bool debug = false;

	// main while loop
	while (!glfwWindowShouldClose(window))
	{
		// updating time
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// handling input
		processInput(window);
		if (firstFrame) {
			vanguardAnimator.UpdateAnimation(deltaTime);
			survivorAnimator.UpdateAnimation(deltaTime);
			if (debug) {
				firstFrame = false;
			}
		}

		// frame resets
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		// Draw Floor
		floorShader.Activate();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.0f));

		//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 10), glm::vec3(0.0f, 1.0f, 0.0f));
		floorShader.setMat4("model", model);
		floorShader.setMat4("projection", projection);
		floorShader.setMat4("view", view);
		addSpotlight(floorShader);
		addPointLight(floorShader);
		floor.Draw(camera);

		// Robot
		if (animate) {
			renderCrowd(vanguardShader, projection, view, lightPos, vanguardAnimator, vanguard, survivorAnimator, survivorShader, survivor);
		}

		// Draw Spire
		renderSpire(spireShader, lightPos, projection, view, spire);

		// Draw skybox last
		//skybox.Draw(skyboxShader, camera, projection);
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.Activate();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
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
	//cout << "mouse callback (" << xposIn << "," << yposIn << ")" << endl;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		//cout << "got first mouse" << endl;
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovements(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
