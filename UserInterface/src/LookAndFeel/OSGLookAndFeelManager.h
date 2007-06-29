#ifndef _OSG_UI_LOOKANDFEELMANAGER_H_
#define _OSG_UI_LOOKANDFEELMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUserInterfaceConfig.h"
#include <OpenSG/OSGConfig.h>

#include "OSGLookAndFeel.h"

OSG_BEGIN_NAMESPACE

class OSG_USER_INTERFACE_CLASS_API LookAndFeelManager
{
public:
   static LookAndFeelManager* the(void);

   LookAndFeelPtr getLookAndFeel(void);
   void setLookAndFeel(LookAndFeelPtr TheLookAndFeel);
   
   ~LookAndFeelManager(void);
private:
   static LookAndFeelManager* _the;

   LookAndFeelPtr _LookAndFeel;

   LookAndFeelManager(void);
	
};

OSG_END_NAMESPACE

#include "OSGLookAndFeelManager.inl"

#endif /* _OSG_UI_LOOKANDFEELMANAGER_H_ */
