// MIT License
// Copyright (c) 2020 v0idv0id - Martin Willner - lvslinux@gmail.com

#ifndef __PERSPECTIVETEXTURE_H
#define __PERSPECTIVETEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <shader.h>

int window_width = 800;
int window_height = 600;

GLFWwindow *window = NULL;
void processGLFWInput(GLFWwindow *window);
void load_texture(const char *file, unsigned int *texture);
float inline inCircleN(float x, float y, float r, float x0, float y0);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int nonAffine(float *vertex);
void usage();
unsigned int texture[2];
int textures=0;
float quadVertices[36];
float quadVertices_orig[36] = {
    // positions 3D        // texCoords 3D      // texCoords 3D original
    -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f,     0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 1.0f,
};

unsigned int quadIndices[] = {
    0, 1, 3, 1, 2, 3};

float texmix = 0.5;
int activecorner = -1;
int _id=0;
int doanimation = 0;
#endif