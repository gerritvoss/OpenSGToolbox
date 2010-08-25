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

#ifndef _OSGTEXTUREFIELDCONTAINEREDITOR_H_
#define _OSGTEXTUREFIELDCONTAINEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextureFieldContainerEditorBase.h"
#include "OSGImageComponent.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextureFieldContainerEditor class. See \ref
           PageContribFieldContainerEditorTextureFieldContainerEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING TextureFieldContainerEditor : public TextureFieldContainerEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextureFieldContainerEditorBase Inherited;
    typedef TextureFieldContainerEditor     Self;

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

    // Variables should all be in TextureFieldContainerEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextureFieldContainerEditor(void);
    TextureFieldContainerEditor(const TextureFieldContainerEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureFieldContainerEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const TextureFieldContainerEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    void updateImageComponent(void);

    static std::vector<const FieldContainerType*> _EditableTypes;

    ImageComponentRefPtr _ImageDisplayComponent;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextureFieldContainerEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextureFieldContainerEditor &source);
};

typedef TextureFieldContainerEditor *TextureFieldContainerEditorP;

OSG_END_NAMESPACE

#include "OSGTextureFieldContainerEditorBase.inl"
#include "OSGTextureFieldContainerEditor.inl"

#endif /* _OSGTEXTUREFIELDCONTAINEREDITOR_H_ */
