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
#ifndef _OPENSG_TOOLBOX_FIELD_CONATINER_GATHER_UTILS_H_
#define _OPENSG_TOOLBOX_FIELD_CONATINER_GATHER_UTILS_H_

#include "OSGConfig.h"
#include "OSGTBFileIODef.h"

#include "OSGFieldContainer.h"
#include "OSGFCFileType.h"
#include "OSGFieldContainerMapFields.h"
#include <set>
#include <vector>

OSG_BEGIN_NAMESPACE

FCFileType::FCPtrStore
OSG_TBFILEIO_DLLMAPPING getAllDependantFCs(const FCFileType::FCPtrStore& Containers,
                                           const FCFileType::FCPtrStore& IgnoreContainers,
                                           const std::vector<const FieldContainerType*>& IgnoreTypes,
                                           bool RecurseFilePathAttachedContainers=false);

FCFileType::FCPtrStore
OSG_TBFILEIO_DLLMAPPING getAllDependantFCs(const FCFileType::FCPtrStore& Containers,
                                           const FCFileType::FCPtrStore& IgnoreContainers,
                                           const std::vector<UInt32>& IgnoreTypes,
                                           bool RecurseFilePathAttachedContainers=false);

void OSG_TBFILEIO_DLLMAPPING getAllDependantFCs(FieldContainer* const TheContainer,
                                                const FCFileType::FCPtrStore& Containers,
                                                FCFileType::FCPtrStore& AllContainers,
                                                FCFileType::FCPtrStore& IgnoreContainers,
                                                const std::vector<UInt32>& IgnoreTypes,
                                                bool RecurseFilePathAttachedContainers);

void OSG_TBFILEIO_DLLMAPPING getAllDependantFCs(const FieldContainerMap& TheContainerMap,
                                                const FCFileType::FCPtrStore& Containers,
                                                FCFileType::FCPtrStore& AllContainers,
                                                FCFileType::FCPtrStore& IgnoreContainers,
                                                const std::vector<UInt32>& IgnoreTypes,
                                                bool RecurseFilePathAttachedContainers);

OSG_END_NAMESPACE

#endif


