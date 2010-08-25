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

#ifndef _OSGTOGGLEBUTTON_H_
#define _OSGTOGGLEBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGToggleButtonBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ToggleButton class. See \ref
           PageContribUserInterfaceToggleButton for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ToggleButton : public ToggleButtonBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        SelectedBorderFieldId                = Inherited::ActiveBorderFieldId,
        SelectedBackgroundFieldId            = Inherited::ActiveBackgroundFieldId,
        SelectedTextColorFieldId             = Inherited::ActiveTextColorFieldId,
        SelectedDrawObjectFieldId            = Inherited::ActiveDrawObjectFieldId
    };

    static const OSG::BitVector SelectedBorderFieldMask;
    static const OSG::BitVector SelectedBackgroundFieldMask;
    static const OSG::BitVector SelectedTextColorFieldMask;
    static const OSG::BitVector SelectedDrawObjectFieldMask;

    typedef ToggleButtonBase Inherited;
    typedef ToggleButton     Self;

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

    void setSelectedBorder   ( Border* const value );
    void setSelectedBackground( Layer* const value );
    void setSelectedTextColor( const Color4f &value );
    void setSelectedDrawObject( UIDrawObjectCanvas* const value );
    void setSelectedImage(Image* const TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setSelectedTexture(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setSelectedImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));

    Border * getSelectedBorder   (void) const;
    Layer * getSelectedBackground(void) const;
    Layer * getSelectedForeground(void) const;
    UIDrawObjectCanvas * getSelectedDrawObject     (void) const;

    Color4f             &editSelectedTextColor(void);
    const Color4f             &getSelectedTextColor(void) const;

	void setSelected       (const bool value);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ToggleButtonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ToggleButton(void);
    ToggleButton(const ToggleButton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ToggleButton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    virtual void actionPreformed(ActionEventDetails* const e);

    void produceButtonSelected(ButtonSelectedEventDetails* const e);
    void produceButtonDeselected(ButtonSelectedEventDetails* const e);
    
    virtual Border* getDrawnBorder(void) const;
    virtual Layer* getDrawnBackground(void) const;
    virtual Layer* getDrawnForeground(void) const;
    virtual Color4f getDrawnTextColor(void) const;
    virtual Vec2f getDrawnOffset(void) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ToggleButtonBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ToggleButton &source);
};

typedef ToggleButton *ToggleButtonP;

OSG_END_NAMESPACE

#include "OSGToggleButtonBase.inl"
#include "OSGToggleButton.inl"

#endif /* _OSGTOGGLEBUTTON_H_ */
