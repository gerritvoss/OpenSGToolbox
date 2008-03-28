#include "OSGCameraUtils.h"
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGMatrixUtility.h>

OSG_BEGIN_NAMESPACE

void showAll(CameraPtr TheCamera, NodePtr Scene, Vec3f Up)
{
	if(TheCamera->getType() == PerspectiveCamera::getClassType())
	{
		showAll(PerspectiveCamera::Ptr::dcast(TheCamera), Scene, Up);
	}
}

void showAll(PerspectiveCameraPtr TheCamera, NodePtr Scene, Vec3f Up)
{
	Scene->updateVolume();

    Vec3f min,max;
    Scene->getVolume().getBounds( min, max );
    Vec3f d = max - min;

    if(d.length() < Eps) // Nothing loaded? Use a unity box
    {
        min.setValues(-1.f,-1.f,-1.f);
        max.setValues( 1.f, 1.f, 1.f);
        d = max - min;
    }

	Real32 dist = osgMax(d[0],d[1]) / (2 * osgtan(TheCamera->getFov() / 2.f));

    Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);
    Pnt3f from=at;
    from[2]+=(dist+fabs(max[2]-min[2])*0.5f); 

	if(TheCamera->getBeacon() != NullFC &&
		TheCamera->getBeacon()->getCore() != NullFC &&
		TheCamera->getBeacon()->getCore()->getType().isDerivedFrom(Transform::getClassType()))
	{
		Matrix m;

		if(!MatrixLookAt(m, from, at, Up))
		{
			beginEditCP(TheCamera->getBeacon()->getCore(), Transform::MatrixFieldMask);
				Transform::Ptr::dcast(TheCamera->getBeacon()->getCore())->setMatrix(m);
			endEditCP(TheCamera->getBeacon()->getCore(), Transform::MatrixFieldMask);
		}
	}

    // set the camera to go from 1% of the object to 10 times its size
    Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);
	beginEditCP(TheCamera, PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask);
		TheCamera->setNear (diag / 100.f);
		TheCamera->setFar  (10 * diag);
    endEditCP(TheCamera, PerspectiveCamera::NearFieldMask | PerspectiveCamera::FarFieldMask);
}

OSG_END_NAMESPACE

