#include "SPhysics/SPhysicsEngine.hpp"



bool shm::SPhysicsEngine::isAxesCollision(float p0, float p1, float q0, float q1) {
    return (q0 < p1 && q1 > p1) || (p0 < q1 && p1 > q1);
}



bool shm::SPhysicsEngine::checkCollisionBB(shm::SColliderBox& b1, shm::SColliderBox& b2) {
    shm::SVec3f axisX{1.0f, 0, 0};
    shm::SVec3f axisY(0, 1.0f, 0);
    shm::SVec3f axisZ(0, 0, 1.0f);

    std::vector<shm::SVec3f> b1as{3}; // box1 axes
    std::vector<shm::SVec3f> b2as{3}; // box2 axes

    b1as[0] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisX);
    b1as[1] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisY);
    b1as[2] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisZ);

    b2as[0] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisX);
    b2as[1] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisY);
    b2as[2] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisZ);

    std::vector<float> b1mm{12}; // box1 min max
    std::vector<float> b2mm{12}; // box2 min max

    for (size_t i = 0; i < 6; i++) {
        shm::SVec3f* axis;
        if (i >= 3) axis = &b2as[i - 3];
        else axis = &b1as[i];

        for (size_t k = 0; k < 12; k++) {
            float proj = shm::SVec3f::getProj(b1.vertices[k], *axis);

            if (proj > b1mm[i * 2 + 1]) b1mm[i * 2 + 1] = proj;
            else if (proj < b1mm[i * 2]) b1mm[i * 2] = proj;
        }
    }

    for (size_t i = 0; i < 6; i++) {
        shm::SVec3f* axis;
        if (i >= 3) axis = &b2as[i - 3];
        else axis = &b2as[i];

        for (size_t k = 0; k < 12; k++) {
            float proj = shm::SVec3f::getProj(b1.vertices[k], *axis);

            if (proj > b2mm[i * 2 + 1]) b2mm[i * 2 + 1] = proj;
            else if (proj < b2mm[i * 2]) b2mm[i * 2] = proj;
        }
    }

    bool isCollision = true;
    for (size_t i = 0; i < 6; i++) {
        float& p0 = b1mm[i * 2];
        float& p1 = b1mm[i * 2 + 1];

        float& q0 = b2mm[i * 2];
        float& q1 = b2mm[i * 2 + 1];

        if (!isAxesCollision(p0, p1, q0, q1)) {
            isCollision = false;
            break;
        }
    }

    return isCollision;
}
