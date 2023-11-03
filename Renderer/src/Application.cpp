#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imGUI/imgui.h"
#include "imGUI/imgui_impl_glfw.h"
#include "imGUI/imgui_impl_opengl3.h"

#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"

#include "Renderer.h"

#include <map>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 640;

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Renderer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shue::Renderer renderer;
	renderer.SetBlending(true);

	//float vertices[] =
	//{
	//	-0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 0
	//	-0.1f, -0.1f,  0.1f, 0.0f, 1.0f, // 1
	//	 0.1f, -0.1f,  0.1f, 1.0f, 1.0f, // 2
	//	 0.1f, -0.1f,  0.1f, 1.0f, 1.0f, // 2
	//	 0.1f, -0.1f, -0.1f, 1.0f, 0.0f, // 3
	//	-0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 0
	//	-0.1f, -0.1f,  0.1f, 0.0f, 0.0f, // 1
	//	-0.1f,  0.1f,  0.1f, 0.0f, 1.0f, // 5
	//	 0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 6
	//	 0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 6
	//	 0.1f, -0.1f,  0.1f, 1.0f, 0.0f, // 2
	//	-0.1f, -0.1f,  0.1f, 0.0f, 0.0f, // 1
	//	-0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 0
	//	-0.1f,  0.1f, -0.1f, 0.0f, 1.0f, // 4
	//	-0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 5
	//	-0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 5
	//	-0.1f, -0.1f,  0.1f, 1.0f, 0.0f, // 1
	//	-0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 0
	//	 0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 3
	//	 0.1f,  0.1f, -0.1f, 0.0f, 1.0f, // 7
	//	 0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 6
	//	 0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 6
	//	 0.1f, -0.1f,  0.1f, 1.0f, 0.0f, // 2
	//	 0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 3
	//	-0.1f,  0.1f, -0.1f, 0.0f, 0.0f, // 4
	//	-0.1f,  0.1f,  0.1f, 0.0f, 1.0f, // 5
	//	 0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 6
	//	 0.1f,  0.1f,  0.1f, 1.0f, 1.0f, // 6
	//	 0.1f,  0.1f, -0.1f, 1.0f, 0.0f, // 7
	//	-0.1f,  0.1f, -0.1f, 0.0f, 0.0f, // 4
	//	-0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 0
	//	-0.1f,  0.1f, -0.1f, 0.0f, 1.0f, // 4
	//	 0.1f,  0.1f, -0.1f, 1.0f, 1.0f, // 7
	//	 0.1f,  0.1f, -0.1f, 1.0f, 1.0f, // 7
	//	 0.1f, -0.1f, -0.1f, 1.0f, 0.0f, // 3
	//	-0.1f, -0.1f, -0.1f, 0.0f, 0.0f, // 0
	//};

	float vertices[] =
	{
		-0.1f, -0.1f, -0.1f, // 0
		-0.1f, -0.1f,  0.1f, // 1
		 0.1f, -0.1f,  0.1f, // 2
		 0.1f, -0.1f, -0.1f, // 3
		-0.1f,  0.1f, -0.1f, // 4
		-0.1f,  0.1f,  0.1f, // 5
		 0.1f,  0.1f,  0.1f, // 6
		 0.1f,  0.1f, -0.1f  // 7
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		0, 4, 5,
		5, 1, 0,
		3, 7, 6,
		6, 2, 3,
		4, 5, 6,
		6, 7, 4,
		0, 4, 7,
		7, 3, 0
	};

	Shue::VertexArray va;
	Shue::VertexBuffer vb(sizeof(vertices), vertices);

	Shue::VertexBufferLayout layout;
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	Shue::IndexBuffer ib(sizeof(indices), indices);

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);

	glm::vec3 translationA(-0.45f, -0.2f, -1.0f);
	glm::vec3 translationB(0.0f, 0.0f, -1.0f);

	float viewRotationY = 0;
	float viewRotationX = 0;

	Shue::Texture marioTex("res/textures/Mario.png");	
	Shue::Texture tortoiseTex("res/textures/tortoise.jpg");

	marioTex.Bind(1);
	tortoiseTex.Bind(0);

	Shue::Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	shader.Unbind();
	va.Unbind();
	vb.Unbind();
	ib.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		renderer.Clear();

		view = glm::mat4(1.0f);
		view = glm::rotate(view, glm::radians(viewRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(viewRotationX), glm::vec3(1.0f, 0.0f, 0.0f));

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMatrix4fv("u_MVP", mvp);
			renderer.DrawIb(va, ib, shader);
			//renderer.DrawTriangles(va, shader, sizeof(vertices) / sizeof(float) / 5);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniform1i("u_Texture", 1);
			shader.SetUniformMatrix4fv("u_MVP", mvp);
			renderer.DrawIb(va, ib, shader);
			//renderer.DrawTriangles(va, shader, sizeof(vertices) / sizeof(float) / 5);
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::Begin("Positions");
			ImGui::SliderFloat("Camera Rotation Y", &viewRotationY, -180.0f, 180.0f);
			ImGui::SliderFloat("Camera Rotation X", &viewRotationX, -180.0f, 180.0f);
			ImGui::SliderFloat3("Translation A", &translationA.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("Translation B", &translationB.x, -1.0f, 1.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}