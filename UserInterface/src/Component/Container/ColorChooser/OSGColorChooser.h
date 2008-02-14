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

#ifndef _OSGCOLORCHOOSER_H_
#define _OSGCOLORCHOOSER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGColorChooserBase.h"
#include "OSGColorSelectionModel.h"
#include "OSGAbstractColorChooserPanelFields.h"
#include "Component/Container/OSGTabPanelFields.h"
#include "Component/Text/OSGLabelFields.h"
#include "Background/OSGColorUIBackgroundFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ColorChooser class. See \ref 
           PageUserInterfaceColorChooser for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ColorChooser : public ColorChooserBase
{
  private:

    typedef ColorChooserBase Inherited;

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
	typedef std::vector<AbstractColorChooserPanelPtr> ColorChooserPanelVector;

    virtual void updateLayout(void);

	//Adds a color chooser panel to the color chooser.
	void addChooserPanel(AbstractColorChooserPanelPtr panel);

	//Returns the specified color panels.
	ColorChooserPanelVector getChooserPanels(void) const;

	//Gets the current color value from the color chooser.
	Color4f getColor(void) const;

	//Returns the data model that handles color selections.
	ColorSelectionModelPtr getSelectionModel(void);

	//Removes the Color4f Panel specified.
	AbstractColorChooserPanelPtr removeChooserPanel(AbstractColorChooserPanelPtr panel);

	//Specifies the Color4f Panels used to choose a color value.
	void setChooserPanels(ColorChooserPanelVector panels);

	//Sets the current color of the color chooser to the specified color.
	void setColor(const Color4f& color);

	//Sets the model containing the selected color.
	void setSelectionModel(ColorSelectionModelPtr newModel);

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
    ColorSelectionModelPtr _SelectionModel;
	
	class ColorSelectedChangeListener : public ChangeListener
	{
	public :
		ColorSelectedChangeListener(ColorChooserPtr TheColorChooser);
		
		virtual void stateChanged(const ChangeEvent& e);
	private:
		ColorChooserPtr _ColorChooser;
	};

	friend class ColorSelectedChangeListener;

	ColorSelectedChangeListener _ColorSelectedChangeListener;

	TabPanelPtr _LayoutTabPanel;

	void updateChoosers(void);
    void updateChildren(void);

	void createDefaultPanel(void);

	LabelPtr _DefaultPreviewPanel;
	ColorUIBackgroundPtr _DefaultPreviewPanelBackground;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ColorChooserBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ColorChooser &source);
};

typedef ColorChooser *ColorChooserP;

OSG_END_NAMESPACE

#include "OSGColorChooserBase.inl"
#include "OSGColorChooser.inl"

#define OSGCOLORCHOOSER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOLORCHOOSER_H_ */
