/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGRGBColorChooserPanelBase.h"
#include "OSGSpinnerFields.h"
#include "OSGSliderFields.h"
#include "OSGBoundedRangeSpinnerModel.h"
#include "OSGGradientLayerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief RGBColorChooserPanel class. See \ref
           PageContribUserInterfaceRGBColorChooserPanel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING RGBColorChooserPanel : public RGBColorChooserPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef RGBColorChooserPanelBase Inherited;
    typedef RGBColorChooserPanel     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

	//Builds a new chooser panel.
	virtual void buildChooser(void);
    
    BoundedRangeSpinnerModelPtr _RedModel;
    BoundedRangeSpinnerModelPtr _GreenModel;
    BoundedRangeSpinnerModelPtr _BlueModel;
    BoundedRangeSpinnerModelPtr _AlphaModel;

	SpinnerRefPtr _RedSpinner;
	SpinnerRefPtr _GreenSpinner;
	SpinnerRefPtr _BlueSpinner;
	SpinnerRefPtr _AlphaSpinner;

	GradientLayerRefPtr _RedSliderTrackBackground;
	GradientLayerRefPtr _GreenSliderTrackBackground;
	GradientLayerRefPtr _BlueSliderTrackBackground;
	GradientLayerRefPtr _AlphaSliderTrackBackground;

	SliderRefPtr _RedSlider;
	SliderRefPtr _GreenSlider;
	SliderRefPtr _BlueSlider;
	SliderRefPtr _AlphaSlider;
	
    void handleControlStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _RedModelStateChangedConnection,
                                _GreenModelStateChangedConnection,
                                _BlueModelStateChangedConnection,
                                _AlphaModelStateChangedConnection;

	void updateColorSelectedModel(void);
	virtual void attachModelListener(void);
	virtual void dettachModelListener(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RGBColorChooserPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RGBColorChooserPanel &source);
};

typedef RGBColorChooserPanel *RGBColorChooserPanelP;

OSG_END_NAMESPACE

#include "OSGRGBColorChooserPanelBase.inl"
#include "OSGRGBColorChooserPanel.inl"

#endif /* _OSGRGBCOLORCHOOSERPANEL_H_ */
