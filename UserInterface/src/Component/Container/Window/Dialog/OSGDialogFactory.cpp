#include "OSGDialogFactory.h"

#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

InternalWindowPtr DialogFactory::createMessageDialog(const std::string& Title, const std::string& Message, const std::string& ConfirmButtonText)
{
    //TODO: Implement
    return NullFC;
}

ContainerPtr DialogFactory::createMessagePanel(const std::string& Message, const std::string& ConfirmButtonText)
{
    //TODO: Implement
    return NullFC;
}


OSG_END_NAMESPACE
