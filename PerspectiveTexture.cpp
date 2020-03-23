// MIT License
// Copyright (c) 2020 v0idv0id - Martin Willner - lvslinux@gmail.com

#include "PerspectiveTexture.h"

int main(int argc, char const *argv[])
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    if ((window = glfwCreateWindow(window_width, window_height, "PerspectiveTexture", NULL, NULL)) == NULL)
    {
        std::cout << "ERROR::GLFW::Failed to create window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::GLAD::Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH);
    glEnable(GL_MULTISAMPLE);
    unsigned int texture[2];
    load_texture("assets/uv1.png", &texture[0]);
    load_texture("assets/uv2.png", &texture[1]);

    Shader quadShader("shaders/quad_vs.glsl", "shaders/quad_fs.glsl");
    Shader pointShader("shaders/point_vs.glsl", "shaders/point_fs.glsl");

    memcpy(quadVertices, quadVertices_orig, sizeof(quadVertices));
    unsigned int quadVAO, quadVBO, quadEBO;

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), &quadIndices, GL_STATIC_DRAW);

    _id = 0;
    glEnableVertexAttribArray(_id);                                                  // vertex coordinates layout(location = 0)
    glVertexAttribPointer(_id, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0); // vertex coordinates

    _id = 1;
    glEnableVertexAttribArray(_id);                                                                    //texture coord,  layout(location = 1)
    glVertexAttribPointer(_id, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float))); //texture

    _id = 2;
    glEnableVertexAttribArray(_id);                                                                    //texture2 coord, layout(location = 2)
    glVertexAttribPointer(_id, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float))); //texture2

    glBindVertexArray(0); // unbind
    nonAffine(quadVertices);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        if (doanimation)
        {
            quadVertices[0] = sin(currentFrame) / 4. - 0.5;
            quadVertices[1] = cos(currentFrame) / 4. - 0.5;
            quadVertices[9] = sin(currentFrame * 0.2) / 4. + 0.5;
            quadVertices[10] = cos(currentFrame * 0.9) / 4. - 0.5;
            quadVertices[18] = sin(currentFrame * 0.3) / 4. + 0.5;
            quadVertices[19] = cos(currentFrame * 1.1) / 4. + 0.5;
            quadVertices[27] = sin(currentFrame * 0.6) / 4. - 0.5;
            quadVertices[28] = cos(currentFrame * 1.4) / 4. + 0.5;
        }
        processGLFWInput(window);
        nonAffine(quadVertices);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_MULTISAMPLE);

        glBindVertexArray(quadVAO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW); // update the vertices data

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

        quadShader.use();
        quadShader.setInt("texture0", 0);
        quadShader.setInt("texture1", 1);
        quadShader.setFloat("texmix", texmix);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        pointShader.use();
        glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void processGLFWInput(GLFWwindow *window)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {

        if (inCircleN(x / window_width * 2 - 1, 1 - y / window_height * 2, 0.1, quadVertices[0], quadVertices[1]) || activecorner == 0)
        {
            quadVertices[0] = x / window_width * 2 - 1;
            quadVertices[1] = 1 - y / window_height * 2;
            activecorner = 0;
        }
        if (inCircleN(x / window_width * 2 - 1, 1 - y / window_height * 2, 0.1, quadVertices[9], quadVertices[10]) || activecorner == 1)
        {
            quadVertices[9] = x / window_width * 2 - 1;
            quadVertices[10] = 1 - y / window_height * 2;
            activecorner = 1;
        }

        if (inCircleN(x / window_width * 2 - 1, 1 - y / window_height * 2, 0.1, quadVertices[18], quadVertices[19]) || activecorner == 2)
        {
            quadVertices[18] = x / window_width * 2 - 1;
            quadVertices[19] = 1 - y / window_height * 2;
            activecorner = 2;
        }

        if (inCircleN(x / window_width * 2 - 1, 1 - y / window_height * 2, 0.1, quadVertices[27], quadVertices[28]) || activecorner == 3)
        {
            quadVertices[27] = x / window_width * 2 - 1;
            quadVertices[28] = 1 - y / window_height * 2;
            activecorner = 3;
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
        activecorner = -1;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        memcpy(quadVertices, quadVertices_orig, sizeof(quadVertices_orig));
        nonAffine(quadVertices);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        texmix += 0.01;
        if (texmix > 1.0)
            texmix = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        texmix -= 0.01;
        if (texmix < 0)
            texmix = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        doanimation = !doanimation;
    }
}

void load_texture(const char *file, unsigned int *tex)
{
    int t_width, t_height, channels;
    unsigned char *texturedata = stbi_load(file, &t_width, &t_height, &channels, 0);
    std::cout << "channels: " << channels << std::endl;
    glGenTextures(1, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (texturedata)
    {
        if (channels < 4)

        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texturedata);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        {
            std::cout << "Failed to load image..." << std::endl;
        }
    }
    stbi_image_free(texturedata);
}

float inline inCircleN(float x, float y, float r, float x0, float y0)
{
    float dx = abs(x - x0);
    float dy = abs(y - y0);
    return (dx * dx + dy * dy <= r * r);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    window_height = height;
    window_width = width;
    glViewport(0, 0, width, height);
}

int nonAffine(float *vertex)
{

    float ax = vertex[18] - vertex[0];
    float ay = vertex[19] - vertex[1];
    float bx = vertex[27] - vertex[9];
    float by = vertex[28] - vertex[10];

    float cross = ax * by - ay * bx;

    if (cross != 0)
    {
        float cy = vertex[1] - vertex[10];
        float cx = vertex[0] - vertex[9];
        float s = (ax * cy - ay * cx) / cross;
        if (s > 0 && s < 1)
        {
            float t = (bx * cy - by * cx) / cross;
            if (t > 0 && t < 1)
            {
                float u0 = 0;
                float v0 = 0;
                float u2 = 1;
                float v2 = 1;

                float q0 = 1 / (1 - t);
                float q1 = 1 / (1 - s);
                float q2 = 1 / t;
                float q3 = 1 / s;

                vertex[3] = u0 * q0;
                vertex[4] = v2 * q0;
                vertex[5] = q0;

                vertex[12] = u2 * q1;
                vertex[13] = v2 * q1;
                vertex[14] = q1;

                vertex[21] = u2 * q2;
                vertex[22] = v0 * q2;
                vertex[23] = q2;

                vertex[30] = u0 * q3;
                vertex[31] = v0 * q3;
                vertex[32] = q3;
            }
            else
            {
                return 0;
                std::cout << "T not in range:" << t << std::endl;
            }
        }
        else
        {
            return 0;
            std::cout << "S not in range:" << s << std::endl;
        }
    }
    else
    {
        return 0;
        std::cout << "CROSS is ZERO:" << cross << std::endl;
    }
    return 1;
}
