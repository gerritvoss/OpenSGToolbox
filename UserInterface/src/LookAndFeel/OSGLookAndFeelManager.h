#ifndef _OSG_UI_LOOKANDFEELMANAGER_H_
#define _OSG_UI_LOOKANDFEELMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/OSGConfig.h>

#include "OSGLookAndFeel.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING LookAndFeelManager
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
