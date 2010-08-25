#ifndef _OSG_UI_LOOKANDFEELMANAGER_H_
#define _OSG_UI_LOOKANDFEELMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGLookAndFeel.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING LookAndFeelManager
{
public:
   static LookAndFeelManager* the(void);

   LookAndFeel* getLookAndFeel(void) const;
   void setLookAndFeel(LookAndFeel* const TheLookAndFeel);
   
   ~LookAndFeelManager(void);
private:
   static LookAndFeelManager* _the;

   LookAndFeelRefPtr _LookAndFeel;

   LookAndFeelManager(void);

   bool uninitialize(void);
	
};

OSG_END_NAMESPACE

#include "OSGLookAndFeelManager.inl"

#endif /* _OSG_UI_LOOKANDFEELMANAGER_H_ */
