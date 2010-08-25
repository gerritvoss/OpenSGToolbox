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

#ifndef _OSGCOLORCHOOSER_H_
#define _OSGCOLORCHOOSER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGColorChooserBase.h"
#include "OSGColorSelectionModel.h"
#include "OSGAbstractColorChooserPanelFields.h"
#include "OSGTabPanel.h"
#include "OSGLabel.h"
#include "OSGColorLayer.h"
#include "OSGBorder.h"
#include "OSGChangeEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ColorChooser class. See \ref
           PageContribUserInterfaceColorChooser for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ColorChooser : public ColorChooserBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ColorChooserBase Inherited;
    typedef ColorChooser     Self;

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

	typedef std::vector<AbstractColorChooserPanelRefPtr> ColorChooserPanelVector;

    virtual void updateLayout(void);

	//Adds a color chooser panel to the color chooser.
	void addChooserPanel(AbstractColorChooserPanel* const panel);

	//Returns the specified color panels.
	const ColorChooserPanelVector& getChooserPanels(void) const;

	//Gets the current color value from the color chooser.
	Color4f getColor(void) const;

	//Removes the Color4f Panel specified.
	AbstractColorChooserPanel* removeChooserPanel(AbstractColorChooserPanel* const panel);

	//Specifies the Color4f Panels used to choose a color value.
	void setChooserPanels(ColorChooserPanelVector panels);

	//Sets the current color of the color chooser to the specified color.
	void setColor(const Color4f& color);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ColorChooserBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorChooser(void);
    ColorChooser(const ColorChooser &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorChooser(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ColorChooser *Id = NULL);
	void onDestroy();
    virtual void resolveLinks(void);
	
	/*! \}                                                                 */
    void handleColorSelectedStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _ColorSelectedStateChangedConnection;

    TabPanelRefPtr _LayoutTabPanel;

    void updateChoosers(void);
    void updateChildren(void);

    void createDefaultPanel(void);

    LabelRefPtr _DefaultPreviewPanel;
    ColorLayerRefPtr _DefaultPreviewPanelBackground;
    ColorChooserPanelVector _ColorChooserPanels;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ColorChooserBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ColorChooser &source);
};

typedef ColorChooser *ColorChooserP;

OSG_END_NAMESPACE

#include "OSGAbstractColorChooserPanel.h"
#include "OSGColorChooserBase.inl"
#include "OSGColorChooser.inl"

#endif /* _OSGCOLORCHOOSER_H_ */
