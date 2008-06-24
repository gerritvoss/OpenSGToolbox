/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGHSVCOLORCHOOSERPANEL_H_
#define _OSGHSVCOLORCHOOSERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGHSVColorChooserPanelBase.h"
#include "Component/Spinner/OSGSpinnerFields.h"
#include "Component/Slider/OSGSliderFields.h"
#include "Component/Spinner/OSGBoundedRangeSpinnerModel.h"
#include "Layer/OSGGradientLayer.h"

OSG_BEGIN_NAMESPACE

/*! \brief HSVColorChooserPanel class. See \ref 
           PageUserInterfaceHSVColorChooserPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING HSVColorChooserPanel : public HSVColorChooserPanelBase
{
  private:

    typedef HSVColorChooserPanelBase Inherited;

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
	virtual std::string getDisplayText(void) const;

	//Invoked automatically when the model's state changes.
	virtual void updateChooser(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in HSVColorChooserPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    HSVColorChooserPanel(void);
    HSVColorChooserPanel(const HSVColorChooserPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~HSVColorChooserPanel(void); 

    /*! \}                                                                 */
    
    
	//Builds a new chooser panel.
	virtual void buildChooser(void);
    
    BoundedRangeSpinnerModelPtr _HueModel;
    BoundedRangeSpinnerModelPtr _SaturationModel;
    BoundedRangeSpinnerModelPtr _ValueModel;
    BoundedRangeSpinnerModelPtr _AlphaModel;

	SpinnerPtr _HueSpinner;
	SpinnerPtr _SaturationSpinner;
	SpinnerPtr _ValueSpinner;
	SpinnerPtr _AlphaSpinner;

	GradientLayerPtr _HueSliderTrackBackground;
	GradientLayerPtr _SaturationSliderTrackBackground;
	GradientLayerPtr _ValueSliderTrackBackground;
	GradientLayerPtr _AlphaSliderTrackBackground;

	SliderPtr _HueSlider;
	SliderPtr _SaturationSlider;
	SliderPtr _ValueSlider;
	SliderPtr _AlphaSlider;
	
	class BoundedRangeSpinnerChangeListener : public ChangeListener
	{
	public :
		BoundedRangeSpinnerChangeListener(HSVColorChooserPanelPtr TheHSVColorChooserPanel);
		
		virtual void stateChanged(const ChangeEvent& e);
	private:
		HSVColorChooserPanelPtr _HSVColorChooserPanel;
	};

	friend class BoundedRangeSpinnerChangeListener;

	BoundedRangeSpinnerChangeListener _BoundedRangeSpinnerChangeListener;

	void updateColorSelectedModel(void);
	void attachModelListener(void);
	void dettachModelListener(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class HSVColorChooserPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const HSVColorChooserPanel &source);
};

typedef HSVColorChooserPanel *HSVColorChooserPanelP;

OSG_END_NAMESPACE

#include "OSGHSVColorChooserPanelBase.inl"
#include "OSGHSVColorChooserPanel.inl"

#define OSGHSVCOLORCHOOSERPANEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGHSVCOLORCHOOSERPANEL_H_ */
