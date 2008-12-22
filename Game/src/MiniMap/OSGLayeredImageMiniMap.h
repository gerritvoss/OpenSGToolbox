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

#ifndef _OSGLAYEREDIMAGEMINIMAP_H_
#define _OSGLAYEREDIMAGEMINIMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGLayeredImageMiniMapBase.h"
#include <OpenSG/UserInterface/OSGComponent.h>
#include <OpenSG/UserInterface/OSGRotatedComponent.h>


OSG_BEGIN_NAMESPACE

/*! \brief LayeredImageMiniMap class. See \ref 
           PageUserInterfaceLayeredImageMiniMap for a description.
*/

class OSG_GAMELIB_DLLMAPPING LayeredImageMiniMap : public LayeredImageMiniMapBase
{
  private:

    typedef LayeredImageMiniMapBase Inherited;

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

	
	void removeTexture(UInt32 index);

	void insertImage(ImagePtr Image);
	void insertImage(const char *fileName, const char *mimeType = 0);

	void insertImage(UInt32 index, ImagePtr Image);
	void insertImage(UInt32 index, const char *fileName, const char *mimeType = 0);

	void setImage(UInt32 index, ImagePtr Image);
	void setImage(UInt32 index, const char *fileName, const char *mimeType = 0);

	void setCharacterTexture(ImagePtr Image);


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in LayeredImageMiniMapBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LayeredImageMiniMap(void);
    LayeredImageMiniMap(const LayeredImageMiniMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LayeredImageMiniMap(void); 

    /*! \}                                                                 */
	virtual void drawInternal(const GraphicsPtr Graphics) const;
    
	virtual void updateAllTransformations(void);

	void setupDrawInternals(void);

	Pnt2f ViewPointLocation;
	Quaternion ViewPointOrientation;

	std::vector<Pnt2f> InidicatorLocations;
	std::vector<Quaternion> InidicatorOrientations;

	RotatedComponentPtr _RotatedIndicator;
	ComponentPtr        _ViewpointIndicatorComponent;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LayeredImageMiniMapBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LayeredImageMiniMap &source);
};

typedef LayeredImageMiniMap *LayeredImageMiniMapP;

OSG_END_NAMESPACE

#include "OSGLayeredImageMiniMapBase.inl"
#include "OSGLayeredImageMiniMap.inl"

#define OSGLAYEREDIMAGEMINIMAP_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLAYEREDIMAGEMINIMAP_H_ */
