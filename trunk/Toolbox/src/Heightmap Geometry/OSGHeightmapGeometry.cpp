/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILETOOLBOXLIB

#include <OpenSG/OSGConfig.h>

#include "OSGHeightmapGeometry.h"
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGIntersectActor.h>
#include <OpenSG/OSGGeoFunctions.h>

#include "Util/OSGImageUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::HeightmapGeometry

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HeightmapGeometry::initMethod (void)
{
#if OSG_VERSION == 0x010801

    // DrawAction
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionEnterHandler));
    
    DrawAction::registerLeaveDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionLeaveHandler));

    // IntersectAction
    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, GeometryPtr,
              CNodePtr, Action *>(&Geometry::intersect));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            GeometryPtr,
            NodeCorePtr,
            ActorBase::FunctorArgumentType &>(&Geometry::intersectActor),
        getClassType());

    // RenderAction
    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionEnterHandler));
    
    RenderAction::registerLeaveDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionLeaveHandler));
#else
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionHandler));

    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, GeometryPtr,
              CNodePtr, Action *>(&Geometry::intersect));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            GeometryPtr,
            NodeCorePtr,
            ActorBase::FunctorArgumentType &>(&Geometry::intersectActor),
        getClassType());

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionHandler));
#endif
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void HeightmapGeometry::createHeightMapGeometry(void)
{
	if(getHeightImage() == NullFC)
	{
		SWARNING << "HeightmapGeometry::createHeightMapGeometry: The HeightImage is NullFC" << std::endl;
		return;
	}

	beginEditCP(HeightmapGeometryPtr(this), PositionsFieldMask | TypesFieldMask | LengthsFieldMask | NormalsFieldMask | TexCoordsFieldMask);
		//This is a sub-optimal tesselation approach
	    //Simply iterate over the number of width, and length segments.  Then create
	    //a quad, out of 2 tris, at each segment.
	    //TODO: implement a tesselation approach that decreases the number of segments in
	    //low curve areas, and increases the number of segments in high curve areas

		if(getTypes() == NullFC)
		{
			setTypes( GeoPTypesUI8::create() );
			//TODO: optimize to use GL_TRIANGLE_STRIP
			getTypes()->addValue(GL_TRIANGLES);
		}
		if(getLengths() == NullFC)
		{
			setLengths( GeoPLengthsUI32::create() );
		}
		getLengths()->clear();
		getLengths()->addValue(2.0 * 3.0 * osgfloor(getSegments().x()) * osgfloor(getSegments().y()));

		if(getPositions() == NullFC)
		{
			setPositions( GeoPositions3f::create() );
		}
		getPositions()->clear();
		//if(getNormals() == NullFC)
		//{
		//	setNormals( GeoNormals3f::create() );
		//}
		//getNormals()->clear();
		if(getTexCoords() == NullFC)
		{
			setTexCoords( GeoTexCoords2f::create() );
		}
		getTexCoords()->clear();

		Pnt3f p1,p2,p3,p4;
		Vec3f n1,n2,n3,n4;
		Vec2f t1,t2,t3,t4;

		Vec3f Offset(0.0f,getOffset(), 0.0f);
		Real32 height;

		

		for(UInt32 i(0) ; i<getSegments().x(); ++i)
		{
			for(UInt32 j(0) ; j<getSegments().y(); ++j)
			{
				//Calculate the positions
				height = getPixelIntensity(Vec2f(static_cast<Real32>(i)/getSegments().x(),static_cast<Real32>(j)/getSegments().y()), getHeightImage());
				p1 = Pnt3f(getDimensions().x()*static_cast<Real32>(i)/getSegments().x(),height*getScale(),getDimensions().y()*static_cast<Real32>(j)/getSegments().y()) + Offset;
				n1.setValues(0.0,1.0,0.0);
				t1.setValues(static_cast<Real32>(i)/getSegments().x(),static_cast<Real32>(j)/getSegments().y());

				height = getPixelIntensity(Vec2f(static_cast<Real32>(i+1)/getSegments().x(),static_cast<Real32>(j)/getSegments().y()), getHeightImage());
				p2 = Pnt3f(getDimensions().x()*static_cast<Real32>(i+1)/getSegments().x(),height*getScale(),getDimensions().y()*static_cast<Real32>(j)/getSegments().y()) + Offset;
				n2.setValues(0.0,1.0,0.0);
				t2.setValues(static_cast<Real32>(i+1)/getSegments().x(),static_cast<Real32>(j)/getSegments().y());

				height = getPixelIntensity(Vec2f(static_cast<Real32>(i+1)/getSegments().x(),static_cast<Real32>(j+1)/getSegments().y()), getHeightImage());
				p3 = Pnt3f(getDimensions().x()*static_cast<Real32>(i+1)/getSegments().x(),height*getScale(),getDimensions().y()*static_cast<Real32>(j+1)/getSegments().y()) + Offset;
				n3.setValues(0.0,1.0,0.0);
				t3.setValues(static_cast<Real32>(i+1)/getSegments().x(),static_cast<Real32>(j+1)/getSegments().y());

				height = getPixelIntensity(Vec2f(static_cast<Real32>(i)/getSegments().x(),static_cast<Real32>(j+1)/getSegments().y()), getHeightImage());
				p4 = Pnt3f(getDimensions().x()*static_cast<Real32>(i)/getSegments().x(),height*getScale(),getDimensions().y()*static_cast<Real32>(j+1)/getSegments().y()) + Offset;
				n4.setValues(0.0,1.0,0.0);
				t4.setValues(static_cast<Real32>(i)/getSegments().x(),static_cast<Real32>(j+1)/getSegments().y());

				Vec3f tri1Normal(p1-p3);
				tri1Normal.cross(p1-p2);
				tri1Normal.normalize();

				Vec3f tri2Normal(p1-p3);
				tri2Normal.cross(p1-p4);
				tri2Normal.normalize();

				//Triangle 1
				getPositions()->addValue(p1);
				//getNormals()->addValue(tri1Normal);
				getTexCoords()->addValue(t1);

				getPositions()->addValue(p3);
				//getNormals()->addValue(tri1Normal);
				getTexCoords()->addValue(t3);

				getPositions()->addValue(p2);
				//getNormals()->addValue(tri1Normal);
				getTexCoords()->addValue(t2);

				//Triangle 2
				getPositions()->addValue(p1);
				//getNormals()->addValue(tri2Normal);
				getTexCoords()->addValue(t1);

				getPositions()->addValue(p4);
				//getNormals()->addValue(tri2Normal);
				getTexCoords()->addValue(t4);

				getPositions()->addValue(p3);
				//getNormals()->addValue(tri2Normal);
				getTexCoords()->addValue(t3);
			}
		}
	endEditCP(HeightmapGeometryPtr(this), PositionsFieldMask | TypesFieldMask | LengthsFieldMask | NormalsFieldMask | TexCoordsFieldMask);

	_InternallyCalculatingNormals = true;
	calcVertexNormals(GeometryPtr(this));
	_InternallyCalculatingNormals = false;

}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

HeightmapGeometry::HeightmapGeometry(void) :
    Inherited(),
		_InternallyCalculatingNormals(false)
{
}

HeightmapGeometry::HeightmapGeometry(const HeightmapGeometry &source) :
    Inherited(source),
		_InternallyCalculatingNormals(false)
{
}

HeightmapGeometry::~HeightmapGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HeightmapGeometry::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(((whichField & HeightImageFieldMask) ||
		(whichField & DimensionsFieldMask) ||
		(whichField & ScaleFieldMask) ||
		(whichField & OffsetFieldMask) ||
		(whichField & SegmentsFieldMask)) &&
		!_InternallyCalculatingNormals)
	{
		createHeightMapGeometry();
	}
}

void HeightmapGeometry::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump HeightmapGeometry NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGHEIGHTMAPGEOMETRYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGHEIGHTMAPGEOMETRYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGHEIGHTMAPGEOMETRYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

