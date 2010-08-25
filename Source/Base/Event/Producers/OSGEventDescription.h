/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGEVENTDESCRIPTIONIMPL_H_
#define _OSGEVENTDESCRIPTIONIMPL_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGBaseTypes.h"
#include "OSGTypeBase.h"
#include <boost/function.hpp>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_BASE_DLLMAPPING EventDescription
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

     EventDescription(const std::string         &szName,
                       const std::string         &szDescription,
                       const  UInt32             uiEventId,
                       const  TypeBase           &EventArgumentType,
                              bool               bConsumable,
                              EventGetMethod fAccessFunctor);

    EventDescription(const EventDescription &source                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~EventDescription(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    const Char8       *getCName           (void) const;
    const std::string &getName            (void) const;
    const std::string &getDescription     (void) const;
          UInt32      getEventId         (void) const;
          bool        getConsumable       (void) const;
    const TypeBase&   getEventArgumentType(void) const;
    GetEventHandlePtr getEvent(const ReflexiveContainer &oContainer) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void                setAccessFunctor     (EventGetMethod fAccessFunctor);
    EventGetMethod  getAccessFunctor     (void                              );
    void                setEventId          (UInt32 uiEventId                 );
    bool                isValid(void)  const;


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    std::string        _szName;
    std::string        _Description;
    UInt32             _EventId;
    const TypeBase&    _EventArgumentType;
    bool               _Consumable;
    EventGetMethod _fAccessFunctor;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class Listener;
    friend class ListenerPtr;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const EventDescription &source);
};

OSG_END_NAMESPACE

#include "OSGEventHandle.h"
#include "OSGEventDescription.inl"

#endif /* _OSGEVENTDESCRIPTIONIMPL_H_ */
