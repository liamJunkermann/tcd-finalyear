#pragma once
#ifndef LOADTEXTURE_h
#define LOADTEXTURE_h

#include<glad/glad.h>
#include<glm/glm.hpp>
#include <stb/stb_image.h>
#include <iostream>

using namespace std;

unsigned int LoadTexture(char const* path);

#endif