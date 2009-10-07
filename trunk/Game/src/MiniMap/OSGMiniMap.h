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

#ifndef _OSGMINIMAP_H_
#define _OSGMINIMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGMiniMapBase.h"
#include "MiniMap/Events/OSGMiniMapListener.h"
#include <OpenSG/UserInterface/OSGChangeListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief MiniMap class. See \ref 
           PageUserInterfaceMiniMap for a description.
*/

class OSG_GAMELIB_DLLMAPPING MiniMap : public MiniMapBase
{
  private:

    typedef MiniMapBase Inherited;

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
    void addMiniMapListener(MiniMapListenerPtr Listener);
    void removeMiniMapListener(MiniMapListenerPtr Listener);
	
	virtual void mousePressed(const MouseEventPtr e);

    Vec3f getMapSpace(const Vec3f& Position) const;
    virtual Pnt2f getComponentSpace(MiniMapIndicatorPtr Indicator) const = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MiniMapBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MiniMap(void);
    MiniMap(const MiniMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MiniMap(void); 

    /*! \}                                                                 */
    virtual void locationSelected(const MiniMapEventPtr e);
	virtual void updateAllTransformations(void);
    
	typedef std::set<MiniMapListenerPtr> MiniMapListenerSet;
    typedef MiniMapListenerSet::iterator MiniMapListenerSetItor;
    typedef MiniMapListenerSet::const_iterator MiniMapListenerSetConstItor;
	
    MiniMapListenerSet       _MiniMapListeners;
    virtual void produceLocationSelected(void);
	
	class TransformationChangedListener : public ChangeListener
	{
	public :
		TransformationChangedListener(MiniMapPtr TheMiniMap);
		
		virtual void stateChanged(const ChangeEventPtr e);
	protected :
		MiniMapPtr _MiniMap;
	};

	friend class TransformationChangedListener;

	TransformationChangedListener _TransformationChangedListener;

	void updateOverlays(void);
	void updateOverlayPanels(void);
	void attachAllOverlays(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MiniMapBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MiniMap &source);
};

typedef MiniMap *MiniMapP;

OSG_END_NAMESPACE

#include "OSGMiniMapBase.inl"
#include "OSGMiniMap.inl"

#endif /* _OSGMINIMAP_H_ */
