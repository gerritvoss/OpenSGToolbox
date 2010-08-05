/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala, Dan Guilliams (djkabala/dan.guilliams@gmail.com)*
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

#include "OSGQuadSequenceParticleSystemDrawer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGQuadSequenceParticleSystemDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGQuadSequenceParticleSystemDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void QuadSequenceParticleSystemDrawer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


Action::ResultE QuadSequenceParticleSystemDrawer::draw(DrawEnv *pEnv, ParticleSystemUnrecPtr System, const MFUInt32& Sort)
{
	bool isSorted(Sort.size() > 0);
    UInt32 NumParticles;
    if(isSorted)
    {
        NumParticles = Sort.size();
    }
    else
    {
        NumParticles = System->getNumParticles();
    }
    Pnt3f P1,P2,P3,P4;
    UInt32 Index, SequenceLength(getSequenceDimensions().x() * getSequenceDimensions().y());
	
    glBegin(GL_QUADS);
        for(UInt32 i(0); i<NumParticles;++i)
        {
            if(isSorted)
            {
                Index = Sort[i];
            }
            else
            {
                Index = i;
            }

			UInt32 seqIndex = getSequenceFunction()->evaluate(System,Index,SequenceLength);
			calcTexCoords(seqIndex);
            //Loop through all particles
            //Get The Normal of the Particle
            Vec3f Normal = getQuadNormal(pEnv,System, Index);


            //Calculate the Binormal as the cross between Normal and Up
            Vec3f Binormal = getQuadUpDir(pEnv,  System, Index).cross(Normal);

            //Get the Up Direction of the Particle
            Vec3f Up = Normal.cross(Binormal);

            //Determine Local Space of the Particle
            Pnt3f Position = System->getPosition(Index);

            //Determine the Width and Height of the quad
            Real32 Width = System->getSize(Index).x()*getQuadSizeScaling().x(),Height =System->getSize(Index).y()*getQuadSizeScaling().y();

            //Calculate Quads positions
            P1 = Position + (Width/2.0f)*Binormal + (Height/2.0f)*Up;
            P2 = Position + (Width/2.0f)*Binormal - (Height/2.0f)*Up;
            P3 = Position - (Width/2.0f)*Binormal - (Height/2.0f)*Up;
            P4 = Position - (Width/2.0f)*Binormal + (Height/2.0f)*Up;

            //Draw the Quad
            glNormal3fv(Normal.getValues());

            glColor4fv(System->getColor(Index).getValuesRGBA());
            glTexCoord2f(_texCoords[0].x(), _texCoords[0].y());
            glVertex3fv(P1.getValues());


            glTexCoord2f(_texCoords[3].x(), _texCoords[3].y());
            glVertex3fv(P4.getValues());


            glTexCoord2f(_texCoords[2].x(), _texCoords[2].y());
            glVertex3fv(P3.getValues());

            glTexCoord2f(_texCoords[1].x(), _texCoords[1].y());
            glVertex3fv(P2.getValues());
        }
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    glEnd();

	return Action::Continue;
}

void QuadSequenceParticleSystemDrawer::calcTexCoords(UInt32 SequenceIndex)
{	// this is where the texture coordinates are calculated
	UInt32 dimX(getSequenceDimensions().x()),dimY(getSequenceDimensions().y());
	if(dimX > 0 && dimY > 0)
	{

		Vec2i spriteLoc;
		Vec2f spriteCenter;
		
		spriteLoc[0] = SequenceIndex % dimX;
		spriteLoc[1] = SequenceIndex / dimX;

		// get the center of the sprite in texcoords.
		Real32 divX(1/((Real32)dimX)),divY(1/((Real32)dimY));
		Real32 halfDimX(divX/2), halfDimY(divY/2);
		spriteCenter.setValues(spriteLoc.x() * divX + halfDimX, spriteLoc.y() * divY + halfDimY);
		
		Real32 borderX(0),borderY(0);
		if( getBorderOffsets().x() > 0 && getBorderOffsets().y() > 0)
		{
		// calculate width of border in tex coords
			borderX = getBorderOffsets().x()/getImageDimensions().x();
			borderY = getBorderOffsets().y()/getImageDimensions().y();
		}
	

		_texCoords[0][0] = _texCoords[1][0] = spriteCenter.x() + halfDimX - borderX;
		_texCoords[2][0] = _texCoords[3][0] = spriteCenter.x() - halfDimX + borderX;

		_texCoords[0][1] = _texCoords[3][1] = 1.0f - spriteCenter.y() + halfDimY - borderY;
		_texCoords[1][1] = _texCoords[2][1] = 1.0f - spriteCenter.y() - halfDimY + borderY;

	}
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

QuadSequenceParticleSystemDrawer::QuadSequenceParticleSystemDrawer(void) :
    Inherited()
{
}

QuadSequenceParticleSystemDrawer::QuadSequenceParticleSystemDrawer(const QuadSequenceParticleSystemDrawer &source) :
    Inherited(source)
{
}

QuadSequenceParticleSystemDrawer::~QuadSequenceParticleSystemDrawer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void QuadSequenceParticleSystemDrawer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void QuadSequenceParticleSystemDrawer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump QuadSequenceParticleSystemDrawer NI" << std::endl;
}

OSG_END_NAMESPACE
