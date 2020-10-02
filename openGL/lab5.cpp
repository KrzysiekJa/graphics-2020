
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

# define VALUE          6
# define WIN_H          800
# define WIN_W          800

void makeCube(int buffer);
void setCameraKeyboard(GLint _uniView, float _time);
void setCameraMouse(GLint _uniView, float _elapsedTime, const sf::Window& _window);



// Kody shaderów
const GLchar* vertexSource = R"glsl(
#version 150 core
in vec3 position;
in vec3 color;
     uniform mat4 model;
     uniform mat4 view;
     uniform mat4 proj;
out vec3 Color;
void main(){
Color = color;

gl_Position = proj * view * model * vec4(position, 1.0);
}
)glsl";

const GLchar* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
out vec4 outColor;
void main()
{
outColor = vec4(Color, 1.0);
}
)glsl";

bool firstMouse = true;
double yaw   = -90;
double pitch = 0.0;
int lastX, lastY;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);




int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;

    // Okno renderingu
    sf::Window window(sf::VideoMode(WIN_H, WIN_W, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
    
    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);

    // Inicjalizacja GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Utworzenie VAO (Vertex Array Object)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Utworzenie VBO (Vertex Buffer Object)
    // i skopiowanie do niego danych wierzchołkowych
    GLuint buffer;
    glGenBuffers(1, &buffer);

    makeCube(buffer);


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLint vertexSucces;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSucces);
    if (!vertexSucces) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    GLint fragmentSucces;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &fragmentSucces);
    if (!fragmentSucces) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
    }

    // Zlinkowanie obu shaderów w jeden wspólny program
    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specifikacja formatu danych wierzchołkowych
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, VALUE * sizeof(GLfloat), 0);
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, VALUE * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));


    GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));

    GLint uniView = glGetUniformLocation(shaderProgram, "view");

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));



    sf::Clock clock;
    window.setFramerateLimit(60);
    sf::Time time;

    GLenum primitiv = GL_TRIANGLES;
    glEnable(GL_DEPTH_TEST);
    // Rozpoczęcie pętli zdarzeń
    bool running = true;
    int licznik = 0;
    while (running) {
        time = clock.restart();
        ++licznik;
        float fFps = 1000000 / time.asMicroseconds();

        if (licznik > fFps) {
            window.setTitle(std::to_string(fFps));
            licznik = 0;
        }

        sf::Event windowEvent;
        while (window.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
            case (sf::Event::Closed):
                running = false;
                break;
            case sf::Event::KeyPressed:
                switch (windowEvent.key.code) {
                case sf::Keyboard::Escape:
                    running = false;
                    break;
             
                case sf::Keyboard::Num1:
                    primitiv = GL_TRIANGLES;
                    break;

                case sf::Keyboard::Num2:
                    primitiv = GL_TRIANGLE_STRIP;
                    break;

                case sf::Keyboard::Num3:
                    primitiv = GL_TRIANGLE_FAN;
                    break;

                case sf::Keyboard::Num4:
                    primitiv = GL_QUADS;
                    break;

                case sf::Keyboard::Num5:
                    primitiv = GL_QUAD_STRIP;
                    break;

                case sf::Keyboard::Num6:
                    primitiv = GL_LINES;
                    break;

                case sf::Keyboard::Num7:
                    primitiv = GL_LINE_STRIP;
                    break;

                case sf::Keyboard::Num8:
                    primitiv = GL_LINE_LOOP;
                    break;

                case sf::Keyboard::Num9:
                    primitiv = GL_POINTS;
                    break;

                case sf::Keyboard::Num0:
                    primitiv = GL_POLYGON;
                    break;
                }
                break;

            case sf::Event::MouseMoved:
                setCameraMouse(uniView, time.asMicroseconds(), window);
                break;
             }
        }

        setCameraKeyboard(uniView, time.asMicroseconds());

        // Nadanie scenie koloru czarnego
        glClearColor(0.3f, 0.5f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glDrawElements(primitiv, punkty_, GL_UNSIGNED_INT, 0);
        glDrawArrays(primitiv, 0, 36);
        window.display();
    }


    // Kasowanie programu i czyszczenie buforów
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &vao);
    // Zamknięcie okna renderingu
    window.close();

    return 0;
}







void makeCube(int buffer) {
    
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
    };


    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}



void setCameraKeyboard(GLint _uniView, float _time){
    float cameraSpeed = 0.000002f * _time;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(view));
}



void setCameraMouse(GLint _uniView, float _elapsedTime, const sf::Window& _window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(_window);
    sf::Vector2i position;
    bool relocation = false;

    if (localPosition.x <= 0) {
        position.x = _window.getSize().x;
        position.y = localPosition.y;
        relocation = true;
    }
    if (localPosition.x >= _window.getSize().x-1) {
        position.x = 0;
        position.y = localPosition.y;
        relocation = true;
    }
    if (localPosition.y <= 0) {
        position.y = _window.getSize().y;
        position.x = localPosition.x;
        relocation = true;
    }
    if (localPosition.y >= _window.getSize().y - 1) {
        position.y = 0;
        position.x = localPosition.x;
        relocation = true;
    }

    if (relocation) {
        sf::Mouse::setPosition(position, _window);
        firstMouse = true;
    }
    localPosition = sf::Mouse::getPosition(_window);

    if (firstMouse) {
        lastX = localPosition.x;
        lastY = localPosition.y;
        firstMouse = false;
    }

    double xoffset = localPosition.x - lastX;
    double yoffset = localPosition.y - lastY;
    lastX = localPosition.x;
    lastY = localPosition.y;

    double sensitivity = 0.8f;
    double cameraSpeed = 0.00001f * _elapsedTime;

    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw     += xoffset * cameraSpeed;
    pitch   -= yoffset * cameraSpeed;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);


    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(view));
}