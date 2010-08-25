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
#include "OSGGLViewport.h"
#include "OSGGeometry.h"

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
        SPHERE_SHAPE   = 0,
        PLANE_SHAPE    = 1,
        BOX_SHAPE      = 2,
        TEAPOT_SHAPE   = 3,
        CONE_SHAPE     = 4,
        CYLINDER_SHAPE = 5,
        TORUS_SHAPE    = 6
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
    void createGeometry(void);

    static std::vector<const FieldContainerType*> _EditableTypes;

    GLViewportRefPtr _MaterialViewport;
    GeometryRefPtr  _MaterialGeometry;
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
