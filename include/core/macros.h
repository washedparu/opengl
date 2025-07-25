#pragma once

// includes
#include <iostream>
#include <csignal>

// GLCall macro 

#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__ ))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


