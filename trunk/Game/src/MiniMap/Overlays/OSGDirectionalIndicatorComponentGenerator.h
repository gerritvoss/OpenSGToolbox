/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#ifndef _OSGDIRECTIONALINDICATORCOMPONENTGENERATOR_H_
#define _OSGDIRECTIONALINDICATORCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGDirectionalIndicatorComponentGeneratorBase.h"
#include "MiniMap/Indicators/OSGMiniMapIndicatorFields.h"
#include "MiniMap/OSGMiniMapFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief DirectionalIndicatorComponentGenerator class. See \ref 
           PageGameDirectionalIndicatorComponentGenerator for a description.
*/

class OSG_GAMELIB_DLLMAPPING DirectionalIndicatorComponentGenerator : public DirectionalIndicatorComponentGeneratorBase
{
  private:

    typedef DirectionalIndicatorComponentGeneratorBase Inherited;

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
	virtual ComponentPtr getComponent(ComponentPtr Parent, const boost::any & Value, Int32 PrimaryAxisIndex, Int32 SecondaryAxisIndex, bool IsSelected, bool HasFocus);

    virtual ComponentPtr getDirectionalComponent(MiniMapPtr Parent, MiniMapIndicatorPtr TheIndicator,const Vec3f& Direction, bool IsSelected) = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DirectionalIndicatorComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DirectionalIndicatorComponentGenerator(void);
    DirectionalIndicatorComponentGenerator(const DirectionalIndicatorComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DirectionalIndicatorComponentGenerator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DirectionalIndicatorComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DirectionalIndicatorComponentGenerator &source);
};

typedef DirectionalIndicatorComponentGenerator *DirectionalIndicatorComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDirectionalIndicatorComponentGeneratorBase.inl"
#include "OSGDirectionalIndicatorComponentGenerator.inl"

#define OSGDIRECTIONALINDICATORCOMPONENTGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIRECTIONALINDICATORCOMPONENTGENERATOR_H_ */
