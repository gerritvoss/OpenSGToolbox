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

#ifndef _OSGDEFAULTBOUNDEDRANGEMODEL_H_
#define _OSGDEFAULTBOUNDEDRANGEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultBoundedRangeModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultBoundedRangeModel class. See \ref
           PageContribUserInterfaceDefaultBoundedRangeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultBoundedRangeModel : public DefaultBoundedRangeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultBoundedRangeModelBase Inherited;
    typedef DefaultBoundedRangeModel     Self;

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
    //Returns the model's extent, the length of the inner range that begins at the model's value.
    virtual UInt32 getExtent(void) const;
    
    //Returns the model's maximum.
    virtual Int32 getMaximum(void) const;
    
    //Returns the minimum acceptable value.
    virtual Int32 getMinimum(void) const;
    
    //Returns the model's current value.
    virtual Int32 getValue(void) const;
    
    //Returns true if the current changes to the value property are part of a series of changes.
    virtual bool getValueIsAdjusting(void) const;
    
    //Sets the model's extent.
    virtual void setExtent(UInt32 newExtent);
    
    //Sets the model's maximum to newMaximum.
    virtual void setMaximum(Int32 newMaximum);
    
    //Sets the model's minimum to newMinimum.
    virtual void setMinimum(Int32 newMinimum);
    
    //This method sets all of the model's data with a single method call.
    virtual void setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting);
    
    //Sets the model's current value to newValue if newValue satisfies the model's constraints.
    virtual void setValue(Int32 newValue);
    
    //This attribute indicates that any upcoming changes to the value of the model should be considered a single event
    virtual void setValueIsAdjusting(bool b);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultBoundedRangeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultBoundedRangeModel(void);
    DefaultBoundedRangeModel(const DefaultBoundedRangeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultBoundedRangeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void produceStateChanged(ChangeEventDetails* const e);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultBoundedRangeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultBoundedRangeModel &source);
};

typedef DefaultBoundedRangeModel *DefaultBoundedRangeModelP;

OSG_END_NAMESPACE

#include "OSGDefaultBoundedRangeModelBase.inl"
#include "OSGDefaultBoundedRangeModel.inl"

#endif /* _OSGDEFAULTBOUNDEDRANGEMODEL_H_ */
