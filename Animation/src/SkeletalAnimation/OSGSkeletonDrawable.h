/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
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

#ifndef _OSGSKELETONDRAWABLE_H_
#define _OSGSKELETONDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGSkeletonDrawableBase.h"
#include "OSGBoneFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonDrawable class. See \ref 
           PageAnimationSkeletonDrawable for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING SkeletonDrawable : public SkeletonDrawableBase
{
  private:

    typedef SkeletonDrawableBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );



    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    Action::ResultE drawPrimitives (DrawActionBase *action);
    Action::ResultE drawActionHandler( Action* action );
    Action::ResultE renderActionHandler( Action* action );
    Action::ResultE intersect( Action* action );
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SkeletonDrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonDrawable(void);
    SkeletonDrawable(const SkeletonDrawable &source);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonDrawable(void); 

    /*! \}                                                                 */
    void    adjustVolume(Volume & volume);
    void drawBone (BonePtr TheBone, DrawActionBase *action);
    void expandVolumeByBone (BonePtr TheBone, Volume &volume);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SkeletonDrawableBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SkeletonDrawable &source);
};

typedef SkeletonDrawable *SkeletonDrawableP;

OSG_END_NAMESPACE

#include "OSGSkeletonDrawableBase.inl"
#include "OSGSkeletonDrawable.inl"

#define OSGSKELETONDRAWABLE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSKELETONDRAWABLE_H_ */
