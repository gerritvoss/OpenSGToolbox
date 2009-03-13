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
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGRotatedComponent.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>


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

	/*****************************************
    Removes an image from the set of layered Images
    by taking in the index of that Image.
    *****************************************/
	void removeLayer(UInt32 index);

    /*****************************************
    Takes an Image pointer and a Real number as
    the distance from the layer before it. The 
    image is then placed at the top of the 
    set of layered images.
    *****************************************/
	void insertLayer(ImagePtr Image, Real32 DistanceFromPrevious);
	void insertLayer(const char *fileName, Real32 DistanceFromPrevious, const char *mimeType = 0);

    /*****************************************
    Takes an index of where the layer should
    be placed in the the layer set, takes the 
    Distance from the entry before it, and an
    Image pointer for the image to be placed 
    in the set.
    *****************************************/
	void insertLayer(UInt32 index, Real32 DistanceFromPrevious, ImagePtr Image);
	void insertLayer(UInt32 index, Real32 DistanceFromPrevious, const char *fileName, const char *mimeType = 0);

	void setLayer(UInt32 index, Real32 DistanceFromPrevious, ImagePtr Image);
	void setLayer(UInt32 index, Real32 DistanceFromPrevious, const char *fileName, const char *mimeType = 0);


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
	void setupLockedMapDrawInternals(void);
	void setupUnLockedMapDrawInternals(void);

	Pnt2f ViewPointLocation;
	Quaternion ViewPointOrientation;
    Pnt2f LockedIndicatorLocation;

	std::vector<Pnt2f> InidicatorLocations;
	std::vector<Quaternion> InidicatorOrientations;

	RotatedComponentPtr _RotatedIndicator;
	ComponentPtr        _ViewpointIndicatorComponent;
	RotatedComponentPtr _RotatedMap;
	ContainerPtr        _MapComponent;
	ImageComponentPtr	_MapImageComponent;

	struct IndicatorComponent
	{
		RotatedComponentPtr _RotatedComponent;
		ComponentPtr        _IndicatorComponent;
		AbsoluteLayoutConstraintsPtr _RotatedComponentConstraints;
	};

	std::vector<IndicatorComponent> _IndicatorComponents;

	Int32 _DrawnLayerIndex;
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
