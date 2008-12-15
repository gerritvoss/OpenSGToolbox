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

#ifndef _OSGDEFAULTMINIMAPINDICATORCOMPONENTGENERATOR_H_
#define _OSGDEFAULTMINIMAPINDICATORCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultMiniMapIndicatorComponentGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultMiniMapIndicatorComponentGenerator class. See \ref 
           PageGameDefaultMiniMapIndicatorComponentGenerator for a description.
*/

class OSG_GAMELIB_DLLMAPPING DefaultMiniMapIndicatorComponentGenerator : public DefaultMiniMapIndicatorComponentGeneratorBase
{
  private:

    typedef DefaultMiniMapIndicatorComponentGeneratorBase Inherited;

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
	virtual ComponentPtr getMiniMapComponent(MiniMapPtr Parent, bool IsSelected, bool HasFocus);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultMiniMapIndicatorComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultMiniMapIndicatorComponentGenerator(void);
    DefaultMiniMapIndicatorComponentGenerator(const DefaultMiniMapIndicatorComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultMiniMapIndicatorComponentGenerator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultMiniMapIndicatorComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultMiniMapIndicatorComponentGenerator &source);
};

typedef DefaultMiniMapIndicatorComponentGenerator *DefaultMiniMapIndicatorComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDefaultMiniMapIndicatorComponentGeneratorBase.inl"
#include "OSGDefaultMiniMapIndicatorComponentGenerator.inl"

#define OSGDEFAULTMINIMAPINDICATORCOMPONENTGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTMINIMAPINDICATORCOMPONENTGENERATOR_H_ */
