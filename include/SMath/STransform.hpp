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
        shm::SMatrix4x4 rxyz;
        shm::SMatrix4x4 normal;
        shm::SMatrix4x4 view;
        shm::SMatrix4x4 s;

        public:

        shm::STransform* parent = nullptr;



        STransform() {}

        STransform(const shm::SVec3f& position) : position(position) {}

        STransform(const shm::SVec3f& position, const shm::SVec3f& rotation) : position(position), rotation(rotation) {}

        STransform(const shm::SVec3f& position, const shm::SVec3f& rotation, const shm::SVec3f& scale) : position(position), rotation(rotation), scale(scale) {}


        void updateMatrixes() {
            t.toTranslate(position.x, position.y, position.z);
            s.toScale(scale.x * 2.0f, scale.y * 2.0f, scale.z * 2.0f);

            updateOnlyMatrixRotation();

            if (parent != nullptr && parent->parent == nullptr) {
                shm::SMatrix4x4 rp = parent->getMatrixRotation();
                shm::SMatrix4x4& tp = parent->getMatrixPosition();


                model = shm::SMatrix4x4::mul(tp, shm::SMatrix4x4::mul(rp, shm::SMatrix4x4::mul(t, shm::SMatrix4x4::mul(rxyz, s))));
                normal = shm::SMatrix4x4::mul(rp, rxyz);

                t = tp;
                rxyz = rp;
            }
            else if (parent != nullptr && parent->parent != nullptr) {
                shm::STransform* p = parent->parent;

                shm::SMatrix4x4 tp;
                parent->updateOnlyMatrixRotation();
                tp.toTranslate(parent->getPosition());
                shm::SMatrix4x4& rp = parent->getMatrixRotation();

                model = shm::SMatrix4x4::mul(t, shm::SMatrix4x4::mul(rxyz, s));
                model = shm::SMatrix4x4::mul(tp, shm::SMatrix4x4::mul(rp, model));
                normal = shm::SMatrix4x4::mul(rp, rxyz);

                while (p != nullptr) {
                    shm::SMatrix4x4 tp;
                    p->updateOnlyMatrixRotation();
                    tp.toTranslate(p->getPosition());
                    shm::SMatrix4x4& rp = p->getMatrixRotation();

                    model = shm::SMatrix4x4::mul(tp, shm::SMatrix4x4::mul(rp, model));
                    normal = shm::SMatrix4x4::mul(rp, normal);

                    p = p->parent;
                }
            }
            else {
                model = shm::SMatrix4x4::mul(t, shm::SMatrix4x4::mul(rxyz, s));
                normal = rxyz;
            }
        }

        void updateOnlyMatrixPosition() {
            t.toTranslate(position.x, position.y, position.z);
        }

        void updateOnlyMatrixView() {
            view.toTranslate(-position.x, -position.y, -position.z);
            
            updateOnlyMatrixRotationZYX();

            view = shm::SMatrix4x4::mul(rxyz, view);
        }

        void updateOnlyMatrixRotation() {
            shm::SMatrix4x4 rx;
            shm::SMatrix4x4 ry;
            shm::SMatrix4x4 rz;

            rx.toRotX(rotation.x);
            ry.toRotY(rotation.y);
            rz.toRotZ(rotation.z);

            rxyz = shm::SMatrix4x4::mul(rz, shm::SMatrix4x4::mul(ry, rx));
        }

        void updateOnlyMatrixRotationZYX() {
            shm::SMatrix4x4 rx;
            shm::SMatrix4x4 ry;
            shm::SMatrix4x4 rz;

            rx.toRotX(rotation.x);
            ry.toRotY(rotation.y);
            rz.toRotZ(rotation.z);

            rxyz = shm::SMatrix4x4::mul(rx, shm::SMatrix4x4::mul(ry, rz));
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

        shm::SMatrix4x4& getMatrixView() {
            return view;
        }

        shm::SMatrix4x4& getMatrixRotation() {
            return rxyz;
        }

        shm::SMatrix4x4& getMatrixScale() {
            return s;
        }


        const shm::SMatrix4x4& getMatrixNegativePosition() {
            shm::SMatrix4x4 npos;
            npos.toTranslate(-position.x, -position.y, -position.z);

            return npos;
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



        shm::SVec3f& getRotationParam() {
            return rotation;
        }
    };
}



#endif
