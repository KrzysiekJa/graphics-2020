
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

# define VALUE          6
# define WIN_H          800
# define WIN_W          600
using namespace std;


void makeCube(int buffer);
void setCamera(GLint _uniView);



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

double rotation = 0.0;
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

    //glm::mat4 trans;
    //trans = glm::rotate(trans, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));


    

    GLenum primitiv = GL_TRIANGLES;
    glEnable(GL_DEPTH_TEST);
    // Rozpoczęcie pętli zdarzeń
    bool running = true;
    while (running) {
        sf::Event windowEvent;
        float  mouse_y = sf::Mouse::getPosition(window).y;

        while (window.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
            case (sf::Event::Closed):
                running = false;
                break;
            }

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

            /*if(sf::Event::MouseMoved){
                if (mouse_y > 0.9 * window.getSize().y) {
                    punkty_ = 3;

                }
                else if (mouse_y > 0.7 * window.getSize().y) {
                    punkty_ = 6;

                }
                else if (mouse_y > 0.6 * window.getSize().y) {
                    punkty_ = 9;

                }
                else if (mouse_y > 0.5 * window.getSize().y) {
                    punkty_ = 12;

                }
                else if (mouse_y > 0.4 * window.getSize().y) {
                    punkty_ = 15;

                }
                else if (mouse_y > 0.3 * window.getSize().y) {
                    punkty_ = 18;

                }
                else if (mouse_y > 0.1 * window.getSize().y) {
                    punkty_ = 24;

                }
                else if (mouse_y >= 0) {
                    punkty_ = 36;
                }

                vertices = vetricesSetter(vertices, punkty_);
                vertices2 = vetrices2Setter(vertices2, punkty_);
                shadersCordinator(ebo, punkty_, vertices2, buffer, vertices, vertexShader, fragmentShader, shaderProgram);
                
             }*/
        }

        setCamera(uniView);

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



void setCamera(GLint _uniView) {
    float cameraSpeed = 0.001;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotation -= cameraSpeed;
        cameraFront.x = sin(rotation);
        cameraFront.z = -cos(rotation);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotation += cameraSpeed;
        cameraFront.x = sin(rotation);
        cameraFront.z = -cos(rotation);
    }

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(view));
}