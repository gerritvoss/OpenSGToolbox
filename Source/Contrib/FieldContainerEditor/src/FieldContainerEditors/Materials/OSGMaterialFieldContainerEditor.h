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

#ifndef _OSGMATERIALFIELDCONTAINEREDITOR_H_
#define _OSGMATERIALFIELDCONTAINEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaterialFieldContainerEditorBase.h"
#include "OSGGLViewportFields.h"
#include "OSGSplitPanelFields.h"
#include "OSGSwitchFields.h"
#include "OSGMaterialGroupFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaterialFieldContainerEditor class. See \ref
           PageContribFieldContainerEditorMaterialFieldContainerEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MaterialFieldContainerEditor : public MaterialFieldContainerEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum MaterialShapes
    {
        FIRST_SHAPE    = 0,
        SPHERE_SHAPE   = FIRST_SHAPE,
        PLANE_SHAPE    = SPHERE_SHAPE   + 1,
        BOX_SHAPE      = PLANE_SHAPE    + 1,
        TEAPOT_SHAPE   = BOX_SHAPE      + 1,
        CONE_SHAPE     = TEAPOT_SHAPE   + 1,
        CYLINDER_SHAPE = CONE_SHAPE     + 1,
        TORUS_SHAPE    = CYLINDER_SHAPE + 1,
        LAST_SHAPE     = TORUS_SHAPE
    };

    typedef MaterialFieldContainerEditorBase Inherited;
    typedef MaterialFieldContainerEditor     Self;

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

    void setShape(Int32 TheShape);
    Int32 getShape(void) const;
    void toggleShape(void);

    //Return true if a viewport should always force the height of this
    //Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this
    //Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this
    //Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this
    //Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MaterialFieldContainerEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialFieldContainerEditor(void);
    MaterialFieldContainerEditor(const MaterialFieldContainerEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialFieldContainerEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const MaterialFieldContainerEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    void updateMaterialViewport(void);
    void createGLViewport(void);
    NodeTransitPtr createMatNode(void);

    static std::vector<const FieldContainerType*> _EditableTypes;

    SplitPanelRecPtr    _MainSplitPanel;
    GLViewportRecPtr    _MaterialViewport;
    SwitchRecPtr        _GeoChoiceCore;
    MaterialGroupRecPtr _MatGroupCore;
    Int32               _Shape;


    void handleViewportKeyTyped(KeyEventDetails* const details);

    boost::signals2::connection _ViewportKeyTypedConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaterialFieldContainerEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialFieldContainerEditor &source);
};

typedef MaterialFieldContainerEditor *MaterialFieldContainerEditorP;

OSG_END_NAMESPACE

#include "OSGMaterialFieldContainerEditorBase.inl"
#include "OSGMaterialFieldContainerEditor.inl"

#endif /* _OSGMATERIALFIELDCONTAINEREDITOR_H_ */
