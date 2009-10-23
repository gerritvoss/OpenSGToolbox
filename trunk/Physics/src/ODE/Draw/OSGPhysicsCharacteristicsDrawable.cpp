/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#define OSG_COMPILEPHYSICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsCharacteristicsDrawable.h"
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGTypedFunctors.h>
#include "OSGPhysicsGeomDrawFuncs.h"
#include "OSGPhysicsBodyDrawFuncs.h"

#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPolygonChunk.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsCharacteristicsDrawable

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
MaterialPtr PhysicsCharacteristicsDrawable::_DefaultMaterial = NullFC;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsCharacteristicsDrawable::initMethod (void)
{
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, PhysicsCharacteristicsDrawablePtr,
              CNodePtr, Action *>(&PhysicsCharacteristicsDrawable::drawActionHandler));

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, PhysicsCharacteristicsDrawablePtr,
              CNodePtr, Action *>(&PhysicsCharacteristicsDrawable::renderActionHandler));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

MaterialPtr PhysicsCharacteristicsDrawable::getDefaultMaterial(void) const
{
    if(_DefaultMaterial == NullFC)
    {
        BlendChunkPtr TheBlend = BlendChunk::create();
        beginEditCP(TheBlend);
            TheBlend->setSrcFactor(GL_SRC_ALPHA);
            TheBlend->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        endEditCP(TheBlend);

        PolygonChunkPtr ThePolyChunk = PolygonChunk::create();
        beginEditCP(ThePolyChunk);
            ThePolyChunk->setOffsetFactor(-1.0f);
            ThePolyChunk->setOffsetBias(2.0f);
            ThePolyChunk->setOffsetFill(true);
        endEditCP(ThePolyChunk);

        _DefaultMaterial = ChunkMaterial::create();
        beginEditCP(_DefaultMaterial);
            ChunkMaterial::Ptr::dcast(_DefaultMaterial)->addChunk(TheBlend);
            ChunkMaterial::Ptr::dcast(_DefaultMaterial)->addChunk(ThePolyChunk);
        endEditCP(_DefaultMaterial);

        addRefCP(_DefaultMaterial);
    }

    return _DefaultMaterial;
}

Action::ResultE PhysicsCharacteristicsDrawable::drawActionHandler( Action* action )
{
    /*DrawAction *a = dynamic_cast<DrawAction*>(action);
    Material::DrawFunctor func;

    func=osgTypedMethodFunctor1ObjPtr(&(*this), 
                                      &PhysicsCharacteristicsDrawable::drawPrimitives);

    if(a->getMaterial() != NULL)
    {
        a->getMaterial()->draw(func, a);
    }
    else if ( getMaterial() != NullFC )
    {
        getMaterial()->draw( func, a );
    }
    else
    {
        getDefaultMaterial()->draw( func, a );
        FWARNING(("SkeletonDrawable::draw:: no material!\n"));;
    }*/
    return Action::Continue;
}

Action::ResultE PhysicsCharacteristicsDrawable::renderActionHandler( Action* action )
{
    /*RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;
    func = osgTypedMethodFunctor1ObjPtr(this, 
                                        &PhysicsCharacteristicsDrawable::drawPrimitives);

    Material* m = a->getMaterial();

    if(m == NULL)
    {
        if(getMaterial() != NullFC)
        {
            m = getMaterial().getCPtr();
        }
        else
        {
            m = getDefaultMaterial().getCPtr();
            FNOTICE(("SkeletonDrawable::render: no Material!?!\n"));
        }
    }

    a->dropFunctor(func, m);*/
    _DrawAction = static_cast<DrawActionBase*>(action);
    traverse(getRoot(),
            osgTypedMethodFunctor1ObjPtrCPtrRef<Action::ResultE, PhysicsCharacteristicsDrawable, NodePtr>(this, &PhysicsCharacteristicsDrawable::enter));
    

    return Action::Continue;
}

Action::ResultE PhysicsCharacteristicsDrawable::drawPrimitives (DrawActionBase *action)
{

    return Action::Continue;
}

void PhysicsCharacteristicsDrawable::adjustVolume(Volume & volume)
{
	Inherited::adjustVolume(volume);

	//Extend the volume to infinity
    volume.setInfinite();

}

Action::ResultE PhysicsCharacteristicsDrawable::enter(NodePtr& node)
{
    if(getDrawGeoms())
    {
        dropPhysicsGeom(_DrawAction, node, getGeomColor(),getDefaultMaterial());
    }
    if(getDrawJoints())
    {
        dropPhysicsBody(_DrawAction, node,getDefaultMaterial());
    }
    if(getDrawBodies())
    {
    }
    if(getDrawSpaces())
    {
    }
    if(getDrawWorlds())
    {
    }
    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsCharacteristicsDrawable::PhysicsCharacteristicsDrawable(void) :
    Inherited()
{
}

PhysicsCharacteristicsDrawable::PhysicsCharacteristicsDrawable(const PhysicsCharacteristicsDrawable &source) :
    Inherited(source)
{
}

PhysicsCharacteristicsDrawable::~PhysicsCharacteristicsDrawable(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsCharacteristicsDrawable::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsCharacteristicsDrawable::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsCharacteristicsDrawable NI" << std::endl;
}



OSG_END_NAMESPACE

