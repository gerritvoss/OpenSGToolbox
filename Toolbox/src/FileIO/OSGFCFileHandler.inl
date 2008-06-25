#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline 
void FCFileHandler::operator =(const FCFileHandler& source)
{
	SWARNING << "In FCFileHandler operator =" << std::endl;
}

inline
const Path& FCFileHandler::getRootFilePath(void) const
{
    return _RootFilePath;
}

OSG_END_NAMESPACE
