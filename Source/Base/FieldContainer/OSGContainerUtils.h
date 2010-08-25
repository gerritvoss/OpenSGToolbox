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
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#ifndef _OPENSG_TOOLBOX_FIELD_CONATINER_UTILS_H_
#define _OPENSG_TOOLBOX_FIELD_CONATINER_UTILS_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGFieldContainer.h"
#include "OSGFieldContainerMFields.h"
#include "OSGEventProducerType.h"
#include <set>
#include <vector>

OSG_BEGIN_NAMESPACE

FieldContainerUnrecPtr OSG_BASE_DLLMAPPING getFieldContainer(const std::string &szTypeName, const std::string &namestring);
FieldContainerUnrecPtr OSG_BASE_DLLMAPPING getFieldContainer(const FieldContainerType *szType, const std::string &namestring);
FieldContainerUnrecPtr OSG_BASE_DLLMAPPING getFieldContainer(const std::string &namestring);

//std::vector<FieldContainerRefPtr> OSG_BASE_DLLMAPPING getAllFieldContainers(const std::string &namestring);

bool OSG_BASE_DLLMAPPING isFieldContentDerivedFrom(const FieldType &TheFieldType, const FieldContainerType* TheFCType);

const FieldContainerType OSG_BASE_DLLMAPPING *getFieldContainerTypeFromPtrType(const DataType& type);

//std::vector<FieldContainerPtr> OSG_BASE_DLLMAPPING getAllContainersByType(const FieldContainerType *szType);
std::vector<FieldContainerUnrecPtr> OSG_BASE_DLLMAPPING getAllContainersByDerivedType(const FieldContainerType *szType);

const FieldContainerType OSG_BASE_DLLMAPPING *getClosestAncestor(const FieldContainerType *type,
                                                                 MFUnrecFieldContainerPtr::const_iterator begin,
                                                                 MFUnrecFieldContainerPtr::const_iterator end);

OSG_END_NAMESPACE

#endif


