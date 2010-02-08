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

#ifndef _OSGRGBCOLORCHOOSERPANEL_H_
#define _OSGRGBCOLORCHOOSERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGRGBColorChooserPanelBase.h"
#include "Component/Spinner/OSGSpinnerFields.h"
#include "Component/Slider/OSGSliderFields.h"
#include "Component/Spinner/OSGBoundedRangeSpinnerModel.h"
#include "Layer/OSGGradientLayer.h"

OSG_BEGIN_NAMESPACE

/*! \brief RGBColorChooserPanel class. See \ref 
           PageUserInterfaceRGBColorChooserPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING RGBColorChooserPanel : public RGBColorChooserPanelBase
{
  private:

    typedef RGBColorChooserPanelBase Inherited;

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

    void init(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in RGBColorChooserPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RGBColorChooserPanel(void);
    RGBColorChooserPanel(const RGBColorChooserPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RGBColorChooserPanel(void); 

    /*! \}                                                                 */
    
	//Builds a new chooser panel.
	virtual void buildChooser(void);
    
    BoundedRangeSpinnerModelPtr _RedModel;
    BoundedRangeSpinnerModelPtr _GreenModel;
    BoundedRangeSpinnerModelPtr _BlueModel;
    BoundedRangeSpinnerModelPtr _AlphaModel;

	SpinnerPtr _RedSpinner;
	SpinnerPtr _GreenSpinner;
	SpinnerPtr _BlueSpinner;
	SpinnerPtr _AlphaSpinner;

	GradientLayerPtr _RedSliderTrackBackground;
	GradientLayerPtr _GreenSliderTrackBackground;
	GradientLayerPtr _BlueSliderTrackBackground;
	GradientLayerPtr _AlphaSliderTrackBackground;

	SliderPtr _RedSlider;
	SliderPtr _GreenSlider;
	SliderPtr _BlueSlider;
	SliderPtr _AlphaSlider;
	
	class BoundedRangeSpinnerChangeListener : public ChangeListener
	{
	public :
		BoundedRangeSpinnerChangeListener(RGBColorChooserPanelPtr TheRGBColorChooserPanel);
		
		virtual void stateChanged(const ChangeEventPtr e);
	private:
		RGBColorChooserPanelPtr _RGBColorChooserPanel;
	};

	friend class BoundedRangeSpinnerChangeListener;

	BoundedRangeSpinnerChangeListener _BoundedRangeSpinnerChangeListener;

	void updateColorSelectedModel(void);
	void attachModelListener(void);
	void dettachModelListener(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class RGBColorChooserPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RGBColorChooserPanel &source);
};

typedef RGBColorChooserPanel *RGBColorChooserPanelP;

OSG_END_NAMESPACE

#include "OSGRGBColorChooserPanelBase.inl"
#include "OSGRGBColorChooserPanel.inl"

#define OSGRGBCOLORCHOOSERPANEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGRGBCOLORCHOOSERPANEL_H_ */
