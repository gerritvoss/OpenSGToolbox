/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGGradientLayer.h"
#include "OSGQuaternion.h"
#include "OSGMatrix22.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGradientLayerBase.cpp file.
// To modify it, please change the .fcd file (OSGGradientLayer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GradientLayer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GradientLayer::draw(Graphics* const TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
	if(getMFColors()->size() == getMFStops()->size())
	{
		if(getMFColors()->size() == 1)
		{
			TheGraphics->drawQuad(TopLeft, Pnt2f(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2f(TopLeft.x(), BottomRight.y()), getColors(0), getColors(0), getColors(0), getColors(0), Opacity);
		}
		else
		{
			Pnt2f StartPosition= TopLeft;
			StartPosition[0] += getStartPosition()[0]*(BottomRight[0] - TopLeft[0]);
			StartPosition[1] += getStartPosition()[1]*(BottomRight[1] - TopLeft[1]);
			Pnt2f EndPosition= TopLeft;
			EndPosition[0] += getEndPosition()[0]*(BottomRight[0] - TopLeft[0]);
			EndPosition[1] += getEndPosition()[1]*(BottomRight[1] - TopLeft[1]);
			
			//Calculate the coordinate system
			Vec2f u(EndPosition-StartPosition);
			u.normalize();
			Vec3f v3D(Vec3f(u.x(), u.y(), 0.0f).cross(Vec3f(0.0,0.0,-1.0)));
			Vec2f v(v3D.x(), v3D.y());
			Matrix22<Real32> CoordinateSystem(u.x(), u.y(), v.x(), v.y());

			Pnt2f Min;
			Pnt2f Max;
			{
				//Calculate the bounding box in the new coordinate system
				Pnt2f UVTopLeft(CoordinateSystem*TopLeft), 
					UVBottomRight(CoordinateSystem*BottomRight), 
					UVTopRight(CoordinateSystem*Vec2f(BottomRight.x(), TopLeft.y())),
					UVBottomLeft(CoordinateSystem*Vec2f(TopLeft.x(), BottomRight.y()));


				Min.setValues( osgMin(UVTopLeft.x(), osgMin(UVBottomRight.x(), osgMin(UVTopRight.x(), UVBottomLeft.x()))),
							   osgMin(UVTopLeft.y(), osgMin(UVBottomRight.y(), osgMin(UVTopRight.y(), UVBottomLeft.y()))));
				Max.setValues( osgMax(UVTopLeft.x(), osgMax(UVBottomRight.x(), osgMax(UVTopRight.x(), UVBottomLeft.x()))),
							   osgMax(UVTopLeft.y(), osgMax(UVBottomRight.y(), osgMax(UVTopRight.y(), UVBottomLeft.y()))));
			}

			Pnt2f Origin(CoordinateSystem.inverse() * Min);
			Real32 PreStartLength(((CoordinateSystem*StartPosition).x()-Min.x())/(Max.x() - Min.x())),
				   PostEndLength((Max.x()- (CoordinateSystem*EndPosition).x())/(Max.x() - Min.x())),
				   GradientLength(1.0f-PostEndLength-PreStartLength);
			
			if(getSpreadMethod() == SPREAD_REFLECT||
			   getSpreadMethod() == SPREAD_REPEAT)
			{
				//Code for drawing the Gradient with Repeating/Reflection
					//Determine the Number of Repeats
					UInt32 RepeatCount = static_cast<UInt32>(osgCeil(1.0f/GradientLength));

					//Determine the relative location in the gradient that the Start left is at
					Real32 StartGradientLocation = PreStartLength - GradientLength * osgCeil(PreStartLength/GradientLength);

					//Determine whether the start is a reflection or normal
					bool isReflection = getSpreadMethod() == SPREAD_REFLECT && static_cast<UInt32>(osgCeil(PreStartLength/GradientLength))%2==1;

					for(UInt32 i(0) ; i<RepeatCount ; ++i)
					{
						if(isReflection)
						{
							drawGradient(TheGraphics, Origin, Max-Min,u,StartGradientLocation+GradientLength*(i+1),StartGradientLocation+GradientLength*i,Opacity);					
						}
						else
						{
							drawGradient(TheGraphics, Origin, Max-Min,u,StartGradientLocation+GradientLength*i,StartGradientLocation+GradientLength*(i+1),Opacity);					
						}

						if(getSpreadMethod() == SPREAD_REFLECT)
						{
							isReflection = !isReflection;
						}
					}
				
			}
			else
			{
				//Code for drawing the Gradient with Padding
				
				//Front Pad
				if(PreStartLength != 0.0f)
				{
					drawPad(TheGraphics, Origin,
                            Max-Min,u,0.0,PreStartLength,getMFColors()->front(),Opacity);
				}
				
				drawGradient(TheGraphics, Origin, Max-Min,u,PreStartLength,PreStartLength+GradientLength,Opacity);
				
				//End Pad
				if(PostEndLength != 0.0f)
				{
					drawPad(TheGraphics, Origin, Max-Min,u,PreStartLength+GradientLength,1.0,getMFColors()->back(),Opacity);
				}
			}
		}
	}
}

void GradientLayer::drawGradient(Graphics* const TheGraphics, const Pnt2f& Origin, const Vec2f& Size, const Vec2f& UAxis, const Real32& Start, const Real32& End, const Real32& Opacity) const
{
	glPushMatrix();
	Matrix Transformation;
	Transformation.setTransform(Vec3f(Origin.x()+Start*UAxis.x()*Size.x(), Origin.y()+Start*UAxis.y()*Size.x(),0.0f), Quaternion(Vec3f(1.0f,0.0f,0.0f),Vec3f(UAxis.x(), UAxis.y(), 0.0f)), Vec3f(Size.x()*(End-Start), Size.y(),0.0f));
	glMultMatrixf(Transformation.getValues());

	if (osgMin(getMFColors()->size(),getMFStops()->size()) > 1)
	{
		if(getMFColors()->size() != getMFStops()->size())
		{    
			SWARNING << "GradientLayer::drawGradient: The number of colors and the number of stops are not equal." << std::endl;
		}

		UInt32 NumStops = osgMin(getMFColors()->size(),getMFStops()->size());
		Real32 CurentRelaviteStop= 0.0f;
			
		for(UInt32 i(0) ; i<NumStops-1 ; ++i)
		{
			TheGraphics->drawQuad(Pnt2f(getStops(i),0.0f),
				                  Pnt2f(getStops(i+1),0.0f),
				                  Pnt2f(getStops(i+1),1.0f),
				                  Pnt2f(getStops(i),1.0f),
								  getColors(i),
								  getColors(i+1),
								  getColors(i+1),
								  getColors(i),
								  Opacity);
		}
	}
	glPopMatrix();
}

void GradientLayer::drawPad(Graphics* const TheGraphics, const Pnt2f& Origin, const Vec2f& Size, const Vec2f& UAxis, const Real32& Start, const Real32& End, const Color4f Color, const Real32& Opacity) const
{
	glPushMatrix();
	Matrix Transformation;
	Transformation.setTransform(Vec3f(Origin.x()+Start*UAxis.x()*Size.x(), Origin.y()+Start*UAxis.y()*Size.x(),0.0f), Quaternion(Vec3f(1.0f,0.0f,0.0f),Vec3f(UAxis.x(), UAxis.y(), 0.0f)), Vec3f(Size.x()*(End-Start), Size.y(),0.0f));
	glMultMatrixf(Transformation.getValues());

	
	TheGraphics->drawRect(Pnt2f(0.0,0.0f),
		                  Pnt2f(1.0,1.0f),
						  Color,
						  Opacity);

	glPopMatrix();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GradientLayer::GradientLayer(void) :
    Inherited()
{
}

GradientLayer::GradientLayer(const GradientLayer &source) :
    Inherited(source)
{
}

GradientLayer::~GradientLayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GradientLayer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GradientLayer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GradientLayer NI" << std::endl;
}

OSG_END_NAMESPACE
