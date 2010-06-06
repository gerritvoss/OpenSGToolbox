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

#ifndef _OSG_UI_BOUNDED_RANGE_SPINNER_MODEL_H_
#define _OSG_UI_BOUNDED_RANGE_SPINNER_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGBoundedRangeModel.h"
#include "OSGNumberSpinnerModel.h"
#include <set>

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

class BoundedRangeSpinnerModel;

typedef boost::shared_ptr<BoundedRangeSpinnerModel> BoundedRangeSpinnerModelPtr;

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING BoundedRangeSpinnerModel
{
  private:

  protected:
    BoundedRangeModelRefPtr _TheBoundedRangeModel;
    Int32SpinnerModelPtr _TheSpinnerModel;

    typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
    ChangeListenerSet _ChangeListeners;

    void produceStateChanged(void);

    //BoundedRangeModel Listener
    class BoundedRangeModelChangeListener : public ChangeListener
    {
      public :
        BoundedRangeModelChangeListener(BoundedRangeSpinnerModel* TheBoundedRangeSpinnerModel);

        virtual void stateChanged(const ChangeEventUnrecPtr e);
      private:
        BoundedRangeSpinnerModel* _BoundedRangeSpinnerModel;
    };

    friend class BoundedRangeModelChangeListener;

    BoundedRangeModelChangeListener _BoundedRangeModelChangeListener;

    //SpinnerModel Listener
    class SpinnerModelChangeListener : public ChangeListener
    {
      public :
        SpinnerModelChangeListener(BoundedRangeSpinnerModel* TheBoundedRangeSpinnerModel);

        virtual void stateChanged(const ChangeEventUnrecPtr e);
      private:
        BoundedRangeSpinnerModel* _BoundedRangeSpinnerModel;
    };

    friend class SpinnerModelChangeListener;

    SpinnerModelChangeListener _SpinnerModelChangeListener;

    void attachListenersToModels(void);

    void dettachListenersFromModels(void);
  public:
    //Returns the model's maximum.
    virtual Int32 getMaximum(void) const;

    //Returns the minimum acceptable value.
    virtual Int32 getMinimum(void) const;

    //Returns the model's current value.
    virtual Int32 getValue(void) const;

    //Sets the model's maximum to newMaximum.
    virtual void setMaximum(Int32 newMaximum);

    //Sets the model's minimum to newMinimum.
    virtual void setMinimum(Int32 newMinimum);

    //Sets the model's current value to newValue if newValue satisfies the model's constraints.
    virtual void setValue(Int32 newValue);

    virtual EventConnection addChangeListener(ChangeListenerPtr Listener);
    bool isChangeListenerAttached(ChangeListenerPtr Listener) const;
    virtual void removeChangeListener(ChangeListenerPtr Listener);

    BoundedRangeModelRefPtr getBoundedRangeModel(void);

    SpinnerModelPtr getSpinnerModel(void);

    BoundedRangeSpinnerModel(void);
    BoundedRangeSpinnerModel(const BoundedRangeSpinnerModel &source);
    ~BoundedRangeSpinnerModel(void);
};


OSG_END_NAMESPACE

#include "OSGBoundedRangeSpinnerModel.inl"

#endif /* _OSG_UI_BOUNDED_RANGE_SPINNER_MODEL_H_ */

