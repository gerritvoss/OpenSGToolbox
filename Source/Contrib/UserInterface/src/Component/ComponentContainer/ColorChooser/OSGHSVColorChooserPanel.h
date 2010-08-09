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

#ifndef _OSGHSVCOLORCHOOSERPANEL_H_
#define _OSGHSVCOLORCHOOSERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGHSVColorChooserPanelBase.h"
#include "OSGSpinnerFields.h"
#include "OSGSliderFields.h"
#include "OSGBoundedRangeSpinnerModel.h"
#include "OSGGradientLayerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief HSVColorChooserPanel class. See \ref
           PageContribUserInterfaceHSVColorChooserPanel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING HSVColorChooserPanel : public HSVColorChooserPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef HSVColorChooserPanelBase Inherited;
    typedef HSVColorChooserPanel     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	//Builds a new chooser panel.
	virtual void buildChooser(void);
    
    BoundedRangeSpinnerModelPtr _HueModel;
    BoundedRangeSpinnerModelPtr _SaturationModel;
    BoundedRangeSpinnerModelPtr _ValueModel;
    BoundedRangeSpinnerModelPtr _AlphaModel;

	SpinnerRefPtr _HueSpinner;
	SpinnerRefPtr _SaturationSpinner;
	SpinnerRefPtr _ValueSpinner;
	SpinnerRefPtr _AlphaSpinner;

	GradientLayerRefPtr _HueSliderTrackBackground;
	GradientLayerRefPtr _SaturationSliderTrackBackground;
	GradientLayerRefPtr _ValueSliderTrackBackground;
	GradientLayerRefPtr _AlphaSliderTrackBackground;

	SliderRefPtr _HueSlider;
	SliderRefPtr _SaturationSlider;
	SliderRefPtr _ValueSlider;
	SliderRefPtr _AlphaSlider;
	
    void handleControlStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _HueModelStateChangedConnection,
                                _SaturationModelStateChangedConnection,
                                _ValueModelStateChangedConnection,
                                _AlphaModelStateChangedConnection;

	void updateColorSelectedModel(void);
	virtual void attachModelListener(void);
	virtual void dettachModelListener(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class HSVColorChooserPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const HSVColorChooserPanel &source);
};

typedef HSVColorChooserPanel *HSVColorChooserPanelP;

OSG_END_NAMESPACE

#include "OSGHSVColorChooserPanelBase.inl"
#include "OSGHSVColorChooserPanel.inl"

#endif /* _OSGHSVCOLORCHOOSERPANEL_H_ */
