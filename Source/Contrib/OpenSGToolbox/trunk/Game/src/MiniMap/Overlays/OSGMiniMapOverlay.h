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

#ifndef _OSGMINIMAPOVERLAY_H_
#define _OSGMINIMAPOVERLAY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGMiniMapOverlayBase.h"
#include "MiniMap/OSGMiniMapFields.h"
#include <OpenSG/UserInterface/OSGPanel.h>

OSG_BEGIN_NAMESPACE

/*! \brief MiniMapOverlay class. See \ref 
           PageUserInterfaceMiniMapOverlay for a description.
*/

class OSG_GAMELIB_DLLMAPPING MiniMapOverlay : public MiniMapOverlayBase
{
  private:

    typedef MiniMapOverlayBase Inherited;

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
    virtual void update(MiniMapPtr TheMiniMap, PanelPtr OverlayPanel, const Vec2f& TopLeft, const Vec3f& BottomRight) = 0;
    virtual PanelPtr getPanel(void) const = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MiniMapOverlayBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MiniMapOverlay(void);
    MiniMapOverlay(const MiniMapOverlay &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MiniMapOverlay(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MiniMapOverlayBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MiniMapOverlay &source);
};

typedef MiniMapOverlay *MiniMapOverlayP;

OSG_END_NAMESPACE

#include "OSGMiniMapOverlayBase.inl"
#include "OSGMiniMapOverlay.inl"

#define OSGMINIMAPOVERLAY_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMINIMAPOVERLAY_H_ */
