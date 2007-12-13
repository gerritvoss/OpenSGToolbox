#include "OSGTreeSelectionEvent.h"

#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>

#include <stdexcept>

OSG_BEGIN_NAMESPACE

EventType TreeSelectionEvent::_Type("TreeSelectionEvent", "EventType");

bool TreeSelectionEvent::isAddedPath(const UInt32& index) const
{
    if(index > 0 && index < _Path.size())
    {
         _IsPathNew[index];
    }
    else
    {
         return false;
    }
}

bool TreeSelectionEvent::isAddedPath(const TreePath& path) const
{
    for(UInt32 i(0) ; i<_Path.size() ; ++i)
    {
        if(path == _Path[i])
        {
            return _IsPathNew[i];
        }
    }
    
	return false;
}

TreeSelectionEvent::TreeSelectionEvent(FieldContainerPtr Source, Time TimeStamp, TreePath Path, bool IsNew, TreePath NewLeadSelectionPath, TreePath OldLeadSelectionPath)
		: Event(Source, TimeStamp),
		_NewLeadSelectionPath(NewLeadSelectionPath),
		_OldLeadSelectionPath(OldLeadSelectionPath)
{
    _Path.push_back(Path);
    _IsPathNew.push_back(IsNew);
}

TreeSelectionEvent::TreeSelectionEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<TreePath> Paths, std::vector<bool> AreNew, TreePath NewLeadSelectionPath, TreePath OldLeadSelectionPath)
		: Event(Source, TimeStamp),
		_NewLeadSelectionPath(NewLeadSelectionPath),
		_OldLeadSelectionPath(OldLeadSelectionPath),
		_Path(Paths),
		_IsPathNew(AreNew)
{
     if(_Path.size() != _IsPathNew.size())
     {
        throw std::invalid_argument("The size of number of elements in Paths does not equal the number of elements in AreNew.");
     }
}

OSG_END_NAMESPACE
