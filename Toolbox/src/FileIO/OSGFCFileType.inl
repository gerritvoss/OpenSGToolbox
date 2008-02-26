#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline 
void FCFileType::operator =(const FCFileType& source)
{
	SWARNING << "In FCFileType operator =" << std::endl;
}

inline
const FCFileType::ExtensionVector &FCFileType::getSuffixList(void) const
{
	return _SuffixList;
}

inline
UInt32 FCFileType::getFlags(void) const
{
	return _Flags;
}

OSG_END_NAMESPACE
