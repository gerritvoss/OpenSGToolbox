/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *					Authors: David Kabala, Eric Langkamp					 *
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

#ifndef _OSGMINIMAPTRANSFORMATION_H_
#define _OSGMINIMAPTRANSFORMATION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGMiniMapTransformationBase.h"
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/UserInterface/OSGChangeListener.h>
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief MiniMapTransformation class. See \ref 
           PageUserInterfaceMiniMapTransformation for a description.
*/

class OSG_GAMELIB_DLLMAPPING MiniMapTransformation : public MiniMapTransformationBase
{
  private:

    typedef MiniMapTransformationBase Inherited;

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
	virtual void addChangeListener(ChangeListenerPtr Listener);

	virtual void removeChangeListener(ChangeListenerPtr Listener);

	virtual void transform(Pnt3f& p) = 0;
	virtual void transform(Vec3f& v) = 0;
	virtual void transform(Quaternion& r) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MiniMapTransformationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MiniMapTransformation(void);
    MiniMapTransformation(const MiniMapTransformation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MiniMapTransformation(void); 

    /*! \}                                                                 */
	typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
	
    ChangeListenerSet       _ChangeListeners;
    void produceStateChanged(const ChangeEvent& e);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MiniMapTransformationBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MiniMapTransformation &source);
};

typedef MiniMapTransformation *MiniMapTransformationP;

OSG_END_NAMESPACE

#include "OSGMiniMapTransformationBase.inl"
#include "OSGMiniMapTransformation.inl"

#define OSGMINIMAPTRANSFORMATION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMINIMAPTRANSFORMATION_H_ */
