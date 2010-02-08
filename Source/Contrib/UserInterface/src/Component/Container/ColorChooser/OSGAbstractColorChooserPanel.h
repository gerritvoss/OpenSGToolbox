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

#ifndef _OSGABSTRACTCOLORCHOOSERPANEL_H_
#define _OSGABSTRACTCOLORCHOOSERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractColorChooserPanelBase.h"
#include "OSGColorChooserFields.h"
#include "OSGColorSelectionModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractColorChooserPanel class. See \ref 
           PageUserInterfaceAbstractColorChooserPanel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractColorChooserPanel : public AbstractColorChooserPanelBase
{
  private:

    typedef AbstractColorChooserPanelBase Inherited;

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

	//Returns the model that the chooser panel is editing.
	ColorSelectionModelPtr getColorSelectionModel(void);

	//Returns the large display icon for the panel.
	//virtual Icon getLargeDisplayIcon(void) const = 0;

	//Returns the small display icon for the panel.
	//virtual Icon getSmallDisplayIcon(void) const = 0;

	virtual std::string getDisplayText(void) const = 0;

	//Invoked when the panel is added to the chooser.
	virtual void installChooserPanel(ColorChooserPtr enclosingChooser);

	//Draws the panel.
	//virtual void paint(Graphics g);

	//Invoked when the panel is removed from the chooser.
	virtual void uninstallChooserPanel(ColorChooserPtr enclosingChooser);

	//Invoked automatically when the model's state changes.
	virtual void updateChooser(void) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AbstractColorChooserPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractColorChooserPanel(void);
    AbstractColorChooserPanel(const AbstractColorChooserPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractColorChooserPanel(void); 

    /*! \}                                                                 */
    
	//Builds a new chooser panel.
	virtual void buildChooser(void) = 0;

	//Returns the color that is currently selected.
	Color4f getColorFromModel(void) const;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractColorChooserPanelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractColorChooserPanel &source);
};

typedef AbstractColorChooserPanel *AbstractColorChooserPanelP;

OSG_END_NAMESPACE

#include "OSGAbstractColorChooserPanelBase.inl"
#include "OSGAbstractColorChooserPanel.inl"

#define OSGABSTRACTCOLORCHOOSERPANEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTCOLORCHOOSERPANEL_H_ */
