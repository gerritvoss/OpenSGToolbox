/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGFIELDCHANGEEVENT_H_
#define _OSGFIELDCHANGEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGFieldChangeEventBase.h"
#include <OpenSG/OSGField.h>
#include <OpenSG/OSGFieldDescription.h>

OSG_BEGIN_NAMESPACE

/*! \brief FieldChangeEvent class. See \ref 
           PageToolboxFieldChangeEvent for a description.
*/

class OSG_TOOLBOXLIB_DLLMAPPING FieldChangeEvent : public FieldChangeEventBase
{
  private:

    typedef FieldChangeEventBase Inherited;

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

    static  FieldChangeEventPtr      create(  FieldContainerPtr Source,
                                              Time TimeStamp,
                                              Field* TheField,
                                              const FieldDescription* TheDescription); 
    Field* getField(void);

    const FieldDescription* getFieldDescription(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FieldChangeEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FieldChangeEvent(void);
    FieldChangeEvent(const FieldChangeEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FieldChangeEvent(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FieldChangeEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FieldChangeEvent &source);

    Field* _Field;
    const FieldDescription* _FieldDescription;
};

typedef FieldChangeEvent *FieldChangeEventP;

OSG_END_NAMESPACE

#include "OSGFieldChangeEventBase.inl"
#include "OSGFieldChangeEvent.inl"

#endif /* _OSGFIELDCHANGEEVENT_H_ */
