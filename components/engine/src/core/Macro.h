//
// Created by BlackFlage on 09.10.2021.
//

#ifndef MAIN_MACRO_H
#define MAIN_MACRO_H
#include <iostream>
#include "GL/glew.h"

#define ASSERT(x, message) { if(!(x)) { std::cout << "Assertion failed! Message: " << message << '\n'; } }
#define ASSERT_B(x, message) { if(!(x)) { std::cout << "Assertion failed! Message: " << message << '\n'; return false; }}

void mCheckGLError(const char* file, int line);

#ifdef _DEBUG
    #define CheckGLError() mCheckGLError(__FILE__, __LINE__)
#elif
    #define CheckGLError() {}
#endif

#endif //MAIN_MACRO_H
