
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

# define VALUE          6
# define M_PI           3.14159265358979323846
# define WIN_H          800
# define WIN_W          600
using namespace std;

GLfloat* vetricesSetter(GLfloat* vertices, int number);
GLuint*  vetrices2Setter(GLuint* vertices, int number);
void shadersCordinator(GLuint& ebo, int number, GLuint* vertices2, GLuint& buffer, GLfloat* vertices,
    GLuint& vertexShader, GLuint& fragmentShader, GLuint& shaderProgram);



// Kody shaderów
const GLchar* vertexSource = R"glsl(
#version 150 core
in vec2 position;
in vec3 color;
out vec3 Color;
void main(){
Color = color;
gl_Position = vec4(position, 0.0, 1.0);
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


    int punkty_ = 3;
    GLfloat* vertices = new GLfloat[punkty_ * VALUE];
    GLuint* vertices2 = new GLuint[punkty_ + 1];
    vertices  = vetricesSetter(vertices, punkty_);
    vertices2 = vetrices2Setter(vertices2, punkty_);

    GLuint ebo;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    shadersCordinator(ebo, punkty_, vertices2, buffer, vertices, vertexShader, fragmentShader, shaderProgram);




    // Specifikacja formatu danych wierzchołkowych
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, VALUE * sizeof(GLfloat), 0);
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, VALUE * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));


    

    GLenum primitiv = GL_TRIANGLES;

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

            if(sf::Event::MouseMoved){
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
            
                cout << mouse_y << " " << window.getSize().y << " " << punkty_;
                cout << endl;
            }

        }

        // Nadanie scenie koloru czarnego
        glClearColor(0.3f, 0.5f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(primitiv, punkty_, GL_UNSIGNED_INT, 0);
                
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







GLfloat* vetricesSetter(GLfloat* vertices, int number) {
    double angle  = 0.0;
    double change = 360 / number;
    delete[] vertices;
    GLfloat * result = new GLfloat[number * VALUE];

    for (int i = 0; i < number; ++i) {
        result[i * VALUE]     = cos(M_PI /180 * angle);
        result[i * VALUE + 1] = sin(M_PI /180 * angle);

        if (i % 3 == 1) {
            result[i * VALUE + 2] = 0.7;
            result[i * VALUE + 3] = 0.0;
            result[i * VALUE + 4] = 0.0;
        }
        else if (i % 3 == 2) {
            result[i * VALUE + 2] = 0.0;
            result[i * VALUE + 3] = 0.9;
            result[i * VALUE + 4] = 0.0;
        }
        else if (i % 3 == 0) {
            result[i * VALUE + 2] = 0.9;
            result[i * VALUE + 3] = 0.0;
            result[i * VALUE + 4] = 0.3;
        }
        result[i * VALUE + 5] = 0;

        angle += change;
        if (angle == 360) {
            angle = 0;
        }
    }

    return result;
}




GLuint* vetrices2Setter(GLuint* vertices, int number) {
    delete[] vertices;

    GLuint* result = new GLuint[number + 1];

    for (int i = 0; i < number + 1; ++i) {
        result[i] = i;
    }

    return result;
}




void shadersCordinator(GLuint& ebo, int number, GLuint* vertices2, GLuint& buffer, GLfloat* vertices,
    GLuint& vertexShader, GLuint& fragmentShader, GLuint& shaderProgram) {

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * number, vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * number * VALUE, vertices, GL_STATIC_DRAW);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
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

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

}
