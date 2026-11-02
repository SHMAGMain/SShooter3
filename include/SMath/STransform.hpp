#ifndef SHM_STANDARD_STRANSFORM_HPP
#define SHM_STANDARD_STRANSFORM_HPP



#include "SVec3f.hpp"
#include "SMatrix4x4.hpp"



namespace shm {
    class STransform {
        private:

        shm::SVec3f position;
        shm::SVec3f rotation;
        shm::SVec3f scale;

        shm::SMatrix4x4 model;
        shm::SMatrix4x4 t;
        shm::SMatrix4x4 normal;

        public:

        STransform() {}

        STransform(const shm::SVec3f& position) : position(position) {}

        STransform(const shm::SVec3f& position, const shm::SVec3f& rotation) : position(position), rotation(rotation) {}

        STransform(const shm::SVec3f& position, const shm::SVec3f& rotation, const shm::SVec3f& scale) : position(position), rotation(rotation), scale(scale) {}


        void updateMatrix() {
            shm::SMatrix4x4 s;

            shm::SMatrix4x4 rx;
            shm::SMatrix4x4 ry;
            shm::SMatrix4x4 rz;

            shm::SMatrix4x4 rxyz;

            t.toTranslate(position.x, position.y, position.z);
            s.toScale(scale.x * 2.0f, scale.y * 2.0f, scale.z * 2.0f);

            rx.toRotX(rotation.x);
            ry.toRotY(rotation.y);
            rz.toRotZ(rotation.z);

            rxyz = shm::SMatrix4x4::mul(rz, shm::SMatrix4x4::mul(ry, rx));

            model = shm::SMatrix4x4::mul(t, shm::SMatrix4x4::mul(rxyz, s));
            normal = rxyz;
        }

        void updateOnlyMatrixPosition() {
            t.toTranslate(position.x, position.y, position.z);
        }
        

        shm::SMatrix4x4& getMatrixModel() {
            return model;
        }

        shm::SMatrix4x4& getMatrixNormal() {
            return normal;
        }

        shm::SMatrix4x4& getMatrixPosition() {
            return t;
        }


        void setPosition(float x, float y, float z) {
            position = shm::SVec3f(x, y, z);
        }

        void setPosition(const shm::SVec3f& newPosition) {
            position = newPosition;
        }

        void addPosition(float x, float y, float z) {
            position += shm::SVec3f(x, y, z);
        }

        void addPosition(const shm::SVec3f& v) {
            position += v;
        }

        const shm::SVec3f& getPosition() {
            return position;
        }


        void setRotation(float x, float y, float z) {
            rotation = shm::SVec3f(x, y, z);
        }

        void setRotation(const shm::SVec3f& newRotation) {
            rotation = newRotation;
        }

        void addRotation(float x, float y, float z) {
            rotation += shm::SVec3f(x, y, z);
        }

        void addRotation(const shm::SVec3f& v) {
            rotation += v;
        }

        const shm::SVec3f& getRotation() {
            return rotation;
        }


        void setScale(float x, float y, float z) {
            scale = shm::SVec3f(x, y, z);
        }

        void setScale(const shm::SVec3f& newScale) {
            scale = newScale;
        }

        void addScale(float x, float y, float z) {
            scale += shm::SVec3f(x, y, z);
        }

        void addScale(const shm::SVec3f& v) {
            scale += v;
        }

        const shm::SVec3f& getScale() {
            return scale;
        }
    };
}



#endif
