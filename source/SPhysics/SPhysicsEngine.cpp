#include "SPhysics/SPhysicsEngine.hpp"



bool shm::SPhysicsEngine::isAxesCollision(float p0, float p1, float q0, float q1) {
    if (p0 == q0 && p1 == q1) return true;
    return (q0 < p1 && q1 > p1) || (p0 < q1 && p1 > q1);
}

float shm::SPhysicsEngine::getAxesCollision(float p0, float p1, float q0, float q1) {
    if (p0 == q0 && p1 == q1) {
        return p1 - p0;
    }
    else if (p1 > q1) {
        return q1 - p0;
    }
    else {
        return p1 - q0;
    }
}



bool shm::SPhysicsEngine::checkCollisionBB(shm::SColliderBox& b1, shm::SColliderBox& b2) {
    shm::SVec3f axisX(1.0f, 0, 0);
    shm::SVec3f axisY(0, 1.0f, 0);
    shm::SVec3f axisZ(0, 0, 1.0f);

    std::vector<shm::SVec3f> bases;
    bases.resize(15);

    bases[0] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisX);
    bases[1] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisY);
    bases[2] = shm::SMatrix4x4::mul(b1.transform->getMatrixRotation(), axisZ);

    bases[3] = shm::SMatrix4x4::mul(b2.transform->getMatrixRotation(), axisX);
    bases[4] = shm::SMatrix4x4::mul(b2.transform->getMatrixRotation(), axisY);
    bases[5] = shm::SMatrix4x4::mul(b2.transform->getMatrixRotation(), axisZ);

    for (size_t i = 0; i < 3; i++) {
        bases[6 + i * 3] = shm::SVec3f::scross(bases[i], bases[3]);
        bases[7 + i * 3] = shm::SVec3f::scross(bases[i], bases[4]);
        bases[8 + i * 3] = shm::SVec3f::scross(bases[i], bases[5]);
    }

    std::vector<float> b1mm;
    std::vector<float> b2mm;
    b1mm.resize(30);
    b2mm.resize(30);

    for (size_t i = 0; i < 15; i++) {
        shm::SVec3f& axis = bases[i];

        float pr1 = shm::SVec3f::getProj(b1.vertices[0].to3NoW(), axis);
        float pr2 = shm::SVec3f::getProj(b2.vertices[0].to3NoW(), axis);

        b1mm[i * 2] = pr1;
        b1mm[i * 2 + 1] = pr1;
        b2mm[i * 2] = pr2;
        b2mm[i * 2 + 1] = pr2;
    }

    for (size_t i = 0; i < 15; i++) {
        shm::SVec3f& axis = bases[i];

        for (size_t k = 0; k < 8; k++) {
            shm::SVec4f* v4 = &b1.vertices[k];
            shm::SVec3f v3 = v4->to3NoW();

            float proj = shm::SVec3f::getProj(v3, axis);

            if (proj < b1mm[i * 2]) b1mm[i * 2] = proj;
            else if (proj > b1mm[i * 2 + 1]) b1mm[i * 2 + 1] = proj;


            v4 = &b2.vertices[k];
            v3 = v4->to3NoW();

            proj = shm::SVec3f::getProj(v3, axis);

            if (proj < b2mm[i * 2]) b2mm[i * 2] = proj;
            else if (proj > b2mm[i * 2 + 1]) b2mm[i * 2 + 1] = proj;
        }
    }


    bool isCollision = true;
    for (size_t i = 0; i < 15; i++) {
        float& p0 = b1mm[i * 2];
        float& p1 = b1mm[i * 2 + 1];

        float& q0 = b2mm[i * 2];
        float& q1 = b2mm[i * 2 + 1];

        if (!shm::SPhysicsEngine::isAxesCollision(p0, p1, q0, q1)) {
            isCollision = false;
            break;
        }
    }

    if (isCollision) {
        float minCollision = shm::SPhysicsEngine::getAxesCollision(b1mm[0], b1mm[1], b2mm[0], b2mm[1]);
        shm::SVec3f* axis = &bases[0];
        int indexAxis = 0;

        for (size_t i = 1; i < 6; i++) {
            float col = shm::SPhysicsEngine::getAxesCollision(b1mm[i * 2], b1mm[i * 2 + 1], b2mm[i * 2], b2mm[i * 2 + 1]);

            if (col < minCollision) {
                minCollision = col;
                indexAxis = i;
                
                axis = &bases[i];
            }
        }

        if (!b1.isStatic && !b2.isStatic) minCollision *= 0.5f;

        if (!b1.isStatic && b1mm[indexAxis * 2] < b2mm[indexAxis * 2]) {
            b1.transform->addPosition(shm::SVec3f::smul(*axis, -minCollision));
        }
        else if (!b1.isStatic) {
            b1.transform->addPosition(shm::SVec3f::smul(*axis, minCollision));
        }

        if (!b2.isStatic && b2mm[indexAxis * 2] < b1mm[indexAxis * 2]) {
            b2.transform->addPosition(shm::SVec3f::smul(*axis, -minCollision));
        }
        else if (!b2.isStatic) {
            b2.transform->addPosition(shm::SVec3f::smul(*axis, minCollision));
        }
    }

    return isCollision;
}
