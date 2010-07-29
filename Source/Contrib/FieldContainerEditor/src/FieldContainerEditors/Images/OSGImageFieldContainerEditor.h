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

#ifndef _OSGIMAGEFIELDCONTAINEREDITOR_H_
#define _OSGIMAGEFIELDCONTAINEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGImageFieldContainerEditorBase.h"
#include "OSGGenericFieldContainerEditor.h"
#include "OSGImageComponent.h"

OSG_BEGIN_NAMESPACE

/*! \brief ImageFieldContainerEditor class. See \ref
           PageContribFieldContainerEditorImageFieldContainerEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING ImageFieldContainerEditor : public ImageFieldContainerEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ImageFieldContainerEditorBase Inherited;
    typedef ImageFieldContainerEditor     Self;

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
    virtual const std::vector<const FieldContainerType*>& getEditableTypes(void) const;

    virtual bool attachFieldContainer(FieldContainer* fc);
    virtual bool dettachFieldContainer(void);

	virtual Vec2f getContentRequestedSize(void) const;

    //Returns the preferred size of the viewport for a view component.
    virtual Vec2f getPreferredScrollableViewportSize(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one block of rows or columns, depending on the value of orientation.
    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    virtual void setCommandManager(CommandManagerPtr manager);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ImageFieldContainerEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ImageFieldContainerEditor(void);
    ImageFieldContainerEditor(const ImageFieldContainerEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ImageFieldContainerEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ImageFieldContainerEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    void updateImageComponent(void);

    static std::vector<const FieldContainerType*> _EditableTypes;

    GenericFieldContainerEditorRefPtr _GenericEditor;
    ImageComponentRefPtr _ImageDisplayComponent;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ImageFieldContainerEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ImageFieldContainerEditor &source);
};

typedef ImageFieldContainerEditor *ImageFieldContainerEditorP;

OSG_END_NAMESPACE

#include "OSGImageFieldContainerEditorBase.inl"
#include "OSGImageFieldContainerEditor.inl"

#endif /* _OSGIMAGEFIELDCONTAINEREDITOR_H_ */
