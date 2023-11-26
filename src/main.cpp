#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  " FragColor = vec4(255.0f/255.0f, 230.0f/255.0f, 167.0f/255.0f, 1.0f);\n"
  "}\n\0";

const char *fragmentShader2Source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(153.0f/255.0f, 88.0f/255.0f, 42.0f/255.0f, 1.0f);\n"
  "}\n\0";

const char *fragmentShaderWindowSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
  "}\n\0";

void process_input(GLFWwindow *window);

int main() {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << '\n';
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  GLFWwindow *window = glfwCreateWindow(800, 600, "my home 🥺", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to initialize window" << '\n';
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, []([[maybe_unused]]GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << '\n';
    glfwTerminate();
    return -1;
  }

  int success;
  char infoLog[512];

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << '\n';
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << '\n';
  }

  unsigned int fragmentRoofShader;
  fragmentRoofShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentRoofShader, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragmentRoofShader);
  glGetShaderiv(fragmentRoofShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentRoofShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << '\n';
  }

  unsigned int fragmentWindowShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentWindowShader, 1, &fragmentShaderWindowSource, NULL);
  glCompileShader(fragmentWindowShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  unsigned int shaderProgramRoof;
  shaderProgramRoof = glCreateProgram();
  glAttachShader(shaderProgramRoof, vertexShader);
  glAttachShader(shaderProgramRoof, fragmentRoofShader);
  glLinkProgram(shaderProgramRoof);

  unsigned int shaderProgramWindow = glCreateProgram();
  glAttachShader(shaderProgramWindow, vertexShader);
  glAttachShader(shaderProgramWindow, fragmentWindowShader);
  glLinkProgram(shaderProgramWindow);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << '\n';
  }

  float vertices[] = {
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
  };

  float second_triangle[] = {
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };

  float roof[] = {
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.0f, 1.0f, 0.0f
  };

  float door[] = {
    0.10f, -0.5f, 0.0f,
    -0.10f, -0.5f, 0.0f,
    0.10f, -0.05f, 0.0f,

    0.10f, -0.05f, 0.0f,
    -0.10f, -0.05f, 0.0f,
    -0.10f, -0.5f, 0.0f
  };

  float windows[] = {
    0.43f, 0.25f, 0.0f,
    0.43, 0.0f, 0.0f,
    0.25, 0.0f, 0.0f,

    0.25f, 0.0f, 0.0f,
    0.25f, 0.25f, 0.0f,
    0.43f, 0.25f, 0.0f,

    -0.43f, 0.25f, 0.0f,
    -0.43, 0.0f, 0.0f,
    -0.25, 0.0f, 0.0f,

    -0.25f, 0.0f, 0.0f,
    -0.25f, 0.25f, 0.0f,
    -0.43f, 0.25f, 0.0f
  };

  unsigned int VBO[5], VAO[5];
  glGenBuffers(5, VBO);
  glGenVertexArrays(5, VAO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glBindVertexArray(VAO[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(roof), roof, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[3]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(windows), windows, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[4]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(door), door, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);
  

  while (!glfwWindowShouldClose(window)) {

    process_input(window);

    glClearColor(231.0f/255.0f, 111.0f/255.0f, 81.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramRoof);
    glBindVertexArray(VAO[2]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramWindow);
    glBindVertexArray(VAO[3]);
    glDrawArrays(GL_TRIANGLES, 0, 12);

    glUseProgram(shaderProgramRoof);
    glBindVertexArray(VAO[4]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return -1;
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
