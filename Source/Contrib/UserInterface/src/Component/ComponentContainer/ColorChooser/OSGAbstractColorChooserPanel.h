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

#ifndef _OSGABSTRACTCOLORCHOOSERPANEL_H_
#define _OSGABSTRACTCOLORCHOOSERPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractColorChooserPanelBase.h"
#include "OSGColorChooser.h"
#include "OSGColorSelectionModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractColorChooserPanel class. See \ref
           PageContribUserInterfaceAbstractColorChooserPanel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractColorChooserPanel : public AbstractColorChooserPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractColorChooserPanelBase Inherited;
    typedef AbstractColorChooserPanel     Self;

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

	//Returns the model that the chooser panel is editing.
	ColorSelectionModel* getColorSelectionModel(void);

	//Returns the large display icon for the panel.
	//virtual Icon getLargeDisplayIcon(void) const = 0;

	//Returns the small display icon for the panel.
	//virtual Icon getSmallDisplayIcon(void) const = 0;

	virtual std::string getDisplayText(void) const = 0;

	//Invoked when the panel is added to the chooser.
	virtual void installChooserPanel(ColorChooser* const enclosingChooser);

	//Draws the panel.
	//virtual void paint(Graphics g);

	//Invoked when the panel is removed from the chooser.
	virtual void uninstallChooserPanel(ColorChooser* const enclosingChooser);

	//Invoked automatically when the model's state changes.
	virtual void updateChooser(void) = 0;

    ColorChooser* getParentChooser(void) const;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	//Builds a new chooser panel.
	virtual void buildChooser(void) = 0;

	//Returns the color that is currently selected.
	Color4f getColorFromModel(void) const;

    
	virtual void attachModelListener(void) = 0;
	virtual void dettachModelListener(void) = 0;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractColorChooserPanelBase;
    friend class ColorChooser;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractColorChooserPanel &source);
};

typedef AbstractColorChooserPanel *AbstractColorChooserPanelP;

OSG_END_NAMESPACE

#include "OSGAbstractColorChooserPanelBase.inl"
#include "OSGAbstractColorChooserPanel.inl"

#endif /* _OSGABSTRACTCOLORCHOOSERPANEL_H_ */
