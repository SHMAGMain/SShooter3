#include "Standard/SCamera.hpp"



void shm::SCamera::updateController(shm::SWindow& window) {
    transform.updateOnlyMatrixView();
    shm::SVec3f& rotation = transform.getRotationParam();

    shm::SMatrix4x4 rx;
    shm::SMatrix4x4 ry;
    shm::SMatrix4x4 rz;

    rx.toRotX(rotation.x);
    ry.toRotY(rotation.y);
    rz.toRotZ(rotation.z);

    shm::SMatrix4x4 mr = shm::SMatrix4x4::mul(rz, shm::SMatrix4x4::mul(ry, rx));

    shm::SVec4f forward{0, 0, 1.0f, 0};
    shm::SVec4f right{1.0f, 0, 0, 0};

    forward = shm::SMatrix4x4::mul(mr, forward);
    right = shm::SMatrix4x4::mul(mr, right);


    shm::SVec3f inputDirect;

    if (glfwGetKey(window.get(), GLFW_KEY_W)) inputDirect.z += 1;
    if (glfwGetKey(window.get(), GLFW_KEY_S)) inputDirect.z -= 1;
    if (glfwGetKey(window.get(), GLFW_KEY_D)) inputDirect.x += 1;
    if (glfwGetKey(window.get(), GLFW_KEY_A)) inputDirect.x -= 1;

    shm::SVec3f forMove = shm::SVec3f::smul(forward.to3NoW(), inputDirect.z);
    shm::SVec3f rigMove = shm::SVec3f::smul(right.to3NoW(), inputDirect.x);

    shm::SVec3f vMove = shm::SVec3f::sadd(forMove, rigMove);
    vMove.normalize();
    vMove.mul(moveSpeed);


    transform.addPosition(vMove);


    double x = 0;
    double y = 0;
    glfwGetCursorPos(window.get(), &x, &y);

    int xd = int(x) - window.getSize().x / 2;
    int yd = int(y) - window.getSize().y / 2;

    forceRotationX -= xd * rotateSpeed;
    forceRotationY -= yd * rotateSpeed;

    transform.addRotation(0, forceRotationX, 0);
    transform.addRotation(forceRotationY, 0, 0);

    forceRotationX *= dampingRotation;
    forceRotationY *= dampingRotation;

    glfwSetCursorPos(window.get(), window.getSize().x / 2, window.getSize().y / 2);

    
    if (rotation.x > 90) rotation.x = 90;
    if (rotation.x < -90) rotation.x = -90;
}
