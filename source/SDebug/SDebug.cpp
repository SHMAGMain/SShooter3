#include "SDebug/SDebug.hpp"



shm::SVAO dshm::SDebug::vaoLines;
shm::SVBO dshm::SDebug::vboLines;

shm::SShaderProgram dshm::SDebug::shaderProgram;

shm::SMatrix4x4* dshm::SDebug::per = nullptr;
shm::SCamera* dshm::SDebug::camera = nullptr;

std::string dshm::SDebug::pathVertexShaderSource = "res/shaders/VertexShader.versh";
std::string dshm::SDebug::pathFragmentShaderSource = "res/shaders/FragmentShader.frash";

std::vector<float> dshm::SDebug::dataBox = std::vector<float>{
    -1, -1, -1, 1, -1, -1,
    1, -1, -1, 1, 1, -1,
    1, 1, -1, -1, 1, -1,
    -1, 1, -1, -1, -1, -1,
    -1, -1, 1, 1, -1, 1, 
    1, -1, 1, 1, 1, 1,
    1, 1, 1, -1, 1, 1,
    -1, 1, 1, -1, -1, 1,
    -1, -1, 1, -1, -1, -1,
    -1, 1, 1, -1, 1, -1,
    1, -1, 1, 1, -1, -1,
    1, 1, 1, 1, 1, -1
};

std::vector<float> dshm::SDebug::dataRay = std::vector<float>{
    0, 0, 0, 0, 0, 0
};
