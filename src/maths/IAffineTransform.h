#ifndef IAFFINETRANSFORM_H
#define IAFFINETRANSFORM_H


#include "IMatrix4x4.h"

namespace IMath
{

    // Class Object3D
    // This class represent a generic 3D object on the scene.
    template<class T>
    class IAffineTransform
    {

        public:

        // -------------------- Attributes -------------------- //

            // Transformation matrix that convert local-space
            // coordinates to world-space coordinates
            IMatrix4x4<T> mTransformMatrix;


            T wera;

        public:

            // -------------------- Methods -------------------- //

            // Constructor
            IAffineTransform()
            {
                SetToIdentity();
            }

            // Destructor
            virtual ~IAffineTransform()
            {

            }

            // Return the transform matrix
            const IMatrix4x4<T> &GetTransformMatrix() const;

            // Set to the transform matrix
            void  SetTransformMatrix( const IMatrix4x4<T>& matrix );



            // Set to the identity transform
            void SetToIdentity();

            // Return the origin of object in world-space
            IVector3D<T> GetOrigin() const;

            // Translate the object in world-space
            void TranslateWorld(const IVector3D<T>& v);

            // Translate the object in local-space
            void TranslateLocal(const IVector3D<T>& v);

            // Rotate the object in world-space
            void RotateWorld(const IVector3D<T>& axis, float angle);

            // Rotate the object in local-space
            void RotateLocal(const IVector3D<T>& axis, float angle);

            /**/
            // Rotate around a world-space point
            void RotateAroundWorldPoint(const IVector3D<T>& axis, float angle, const IVector3D<T>& point);

            // Rotate around a local-space point
            void RotateAroundLocalPoint(const IVector3D<T>& axis, float angle, const IVector3D<T>& worldPoint);
            /**/


            /**/
            // Scale around a world-space point
            void ScaleAroundWorldPoint(const IVector3D<T>& axis, float scale, const IVector3D<T>& point);

            // Scale around a local-space point
            void ScaleAroundLocalPoint(const IVector3D<T>& axis, float scale, const IVector3D<T>& worldPoint);
            /**/

    };





    template<class T>
    inline const IMatrix4x4<T> &IAffineTransform<T>::GetTransformMatrix() const
    {
        return mTransformMatrix;
    }


    template<class T>
    inline void  IAffineTransform<T>::SetTransformMatrix( const IMatrix4x4<T>& matrix )
    {
        mTransformMatrix = matrix;
    }


    // Set to the identity transform
    template<class T>
    inline void IAffineTransform<T>::SetToIdentity()
    {
        mTransformMatrix.SetToIdentity();
    }

     // Return the origin of object in world-space
    template<class T>
    inline IVector3D<T> IAffineTransform<T>::GetOrigin() const
    {
        return mTransformMatrix * IVector3D<T>(0.0, 0.0, 0.0);
    }


    //// Translate the object in world-space
    template<class T>
    inline void IAffineTransform<T>::TranslateWorld(const IVector3D<T>& v)
    {
        mTransformMatrix = IMatrix4x4<T>::CreateTranslation(v) * mTransformMatrix;
    }

    // Translate the object in local-space
    template<class T>
    inline void IAffineTransform<T>::TranslateLocal(const IVector3D<T>& v)
    {
        mTransformMatrix = mTransformMatrix * IMatrix4x4<T>::CreateTranslation(v);
    }

    // Rotate the object in world-space
    template<class T>
    inline void IAffineTransform<T>::RotateWorld(const IVector3D<T>& axis, float angle)
    {
        mTransformMatrix = IMatrix4x4<T>::CreateRotationAxis(axis, angle) * mTransformMatrix;
    }

    // Rotate the object in local-space
    template<class T>
    inline void IAffineTransform<T>::RotateLocal(const IVector3D<T>& axis, float angle)
    {
        mTransformMatrix = mTransformMatrix * IMatrix4x4<T>::CreateRotationAxis(axis, angle);
    }


    /**/
    // Rotate the object around a world-space point
    template<class T>
    inline void IAffineTransform<T>::RotateAroundWorldPoint(const IVector3D<T>& axis, float angle, const IVector3D<T>& worldPoint)
    {
        mTransformMatrix =   IMatrix4x4<T>::CreateTranslation( worldPoint)  *
                             IMatrix4x4<T>::CreateRotationAxis(axis, angle) *
                             IMatrix4x4<T>::CreateTranslation(-worldPoint)  * mTransformMatrix;
    }



    // Rotate the object around a local-space point
    template<class T>
    inline void IAffineTransform<T>::RotateAroundLocalPoint(const IVector3D<T>& axis, float angle, const IVector3D<T>& worldPoint)
    {
        // Convert the world point into the local coordinate system
        IVector3D<T> localPoint = mTransformMatrix.GetInverse() * worldPoint;

        mTransformMatrix = mTransformMatrix * IMatrix4x4<T>::CreateTranslation(localPoint)
                                            * IMatrix4x4<T>::CreateRotationAxis(axis, angle)
                                            * IMatrix4x4<T>::CreateTranslation(-localPoint);
    }

    // Scale around a world-space point
    template<class T>
    inline void IAffineTransform<T>::ScaleAroundWorldPoint(const IVector3D<T> &axis, float scale, const IVector3D<T> &worldPoint)
    {
        mTransformMatrix =   IMatrix4x4<T>::CreateTranslation( worldPoint) * IMatrix4x4<T>::CreateScaleAroundAxis(axis, scale)
                           * IMatrix4x4<T>::CreateTranslation(-worldPoint) * mTransformMatrix;
    }

    // Scale around a local-space poin
    template<class T>
    inline void IAffineTransform<T>::ScaleAroundLocalPoint(const IVector3D<T> &axis, float scale, const IVector3D<T> &worldPoint)
    {
        // Convert the world point into the local coordinate system
        IVector3D<T> localPoint = mTransformMatrix.GetInverse() * worldPoint;

        mTransformMatrix = mTransformMatrix * IMatrix4x4<T>::CreateTranslation(localPoint)
                                            * IMatrix4x4<T>::CreateScaleAroundAxis(axis, scale)
                                            * IMatrix4x4<T>::CreateTranslation(-localPoint);
    }



    //--------------------------------------
    // Typedef shortcuts for IAffineTransform
    //-------------------------------------
    using IAffineTransformr    = IAffineTransform<Real>;
    using IAffineTransformf    = IAffineTransform<float>;
    using IAffineTransformd    = IAffineTransform<double>;
    using IAffineTransformi    = IAffineTransform<std::int32_t>;
    using IAffineTransformui   = IAffineTransform<std::uint32_t>;
    using IAffineTransformb    = IAffineTransform<std::int8_t>;
    using IAffineTransformub   = IAffineTransform<std::uint8_t>;


}



#endif // IAFFINETRANSFORM_H
