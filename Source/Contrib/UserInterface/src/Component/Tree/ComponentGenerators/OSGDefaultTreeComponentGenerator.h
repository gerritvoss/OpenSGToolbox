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

#ifndef _OSGDEFAULTTREECOMPONENTGENERATOR_H_
#define _OSGDEFAULTTREECOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultTreeComponentGeneratorBase.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGLabel.h"
#include "OSGPanel.h"
#include "OSGLayer.h"
#include "OSGBorder.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeComponentGenerator class. See \ref
           PageContribUserInterfaceDefaultTreeComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultTreeComponentGenerator : public DefaultTreeComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultTreeComponentGeneratorBase Inherited;
    typedef DefaultTreeComponentGenerator     Self;

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

	virtual ComponentTransitPtr getTreeComponent(Tree* const Parent,
                                             const boost::any& Value,
                                             bool IsSelected,
                                             bool Expanded,
                                             bool Leaf,
                                             UInt32 Row,
                                             bool HasFocus);

	virtual ComponentTransitPtr getTreeComponentText(Tree* const Parent,
                                                 const std::string& Value,
                                                 bool IsSelected, bool Expanded,
                                                 bool Leaf,
                                                 UInt32 Row,
                                                 bool HasFocus);
    
    virtual ComponentTransitPtr getTreeExpandedComponent(Tree* const Parent,
                                                     const boost::any& Value,
                                                     bool IsSelected,
                                                     bool Expanded,
                                                     bool Leaf,
                                                     UInt32 Row,
                                                     bool HasFocus);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultTreeComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTreeComponentGenerator(void);
    DefaultTreeComponentGenerator(const DefaultTreeComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTreeComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultTreeComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultTreeComponentGenerator &source);
};

typedef DefaultTreeComponentGenerator *DefaultTreeComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDefaultTreeComponentGeneratorBase.inl"
#include "OSGDefaultTreeComponentGenerator.inl"

#endif /* _OSGDEFAULTTREECOMPONENTGENERATOR_H_ */
