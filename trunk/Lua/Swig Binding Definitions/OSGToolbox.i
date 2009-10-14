%import  <OSGSystem.i>
%module OSGToolbox
%{
#include <OpenSG/Input/OSGWindowEventProducer.h>


#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldDescription.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGAttachmentContainerPtr.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGNodeCore.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSysFieldDataType.h>
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGMathFieldDataType.h>
#include <OpenSG/OSGSFVecTypes.h>
#include <OpenSG/OSGSFMathTypes.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGMFMathTypes.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>
#include <OpenSG/Toolbox/OSGActivity.h>
#include <OpenSG/Toolbox/OSGEventProducerType.h>
%}

namespace osg {

    class WindowEventProducer;
    
    /******************************************************/
    /*              WindowEventProducerPtr                             */
    /******************************************************/
    class WindowEventProducerPtr : public AttachmentContainerPtr
    {
      public:
         WindowEventProducerPtr(void);
         WindowEventProducerPtr(const WindowEventProducerPtr               &source);
         /*WindowEventProducerPtr(const NullFieldContainerPtr &source);*/


        ~WindowEventProducerPtr(void); 
        WindowEventProducer *operator->(void);
        
        static WindowEventProducerPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                       WindowEventProducer                       */
    /******************************************************/ 
    class WindowEventProducer : public AttachmentContainerPtr
    {
      public:

        /*class FileDialogFilter*/
        /*{*/
        /*public:*/
            /*FileDialogFilter(const std::string& Name, const std::string& Filter);*/

            /*const std::string& getName(void) const;*/
            /*const std::string& getFilter(void) const;*/
        /*private:*/
            /*std::string _Name;*/
            /*std::string _Filter;*/
        /*};*/

        enum CursorType {CURSOR_POINTER=0, 
            CURSOR_HAND=1,
            CURSOR_I_BEAM=2,
            CURSOR_WAIT=3,
            CURSOR_RESIZE_W_TO_E=4,
            CURSOR_RESIZE_N_TO_S=5,
            CURSOR_RESIZE_NW_TO_SE=6,
            CURSOR_RESIZE_SW_TO_NE=7,
            CURSOR_RESIZE_ALL=8,
            CURSOR_NONE=9};

        virtual WindowPtr initWindow(void);

        virtual void openWindow(const Pnt2f& ScreenPosition,
                           const Vec2f& Size,
                           const std::string& WindowName) = 0;
        virtual void closeWindow(void) = 0;
        
        /*virtual void mainLoop(void) = 0;*/

        //Set the Window Position
        virtual void setPosition(Pnt2f Pos) = 0;
        //Set the Window Position
        virtual Pnt2f getPosition(void) const = 0;

        //Set the Window size
        virtual void setSize(Vec2us Size) = 0;

        //Get the Window size
        virtual Vec2f getSize(void) const = 0;

        //Focused
        //Set the Window Focus
        virtual void setFocused(bool Focused) = 0;

        //Get the Window Focus
        virtual bool getFocused(void) const = 0;

        //Visible / Iconify / Normal
        //Set the Window Visible
        virtual void setVisible(bool Visible) = 0;

        //Get the Window Visible
        virtual bool getVisible(void) const = 0;

        //Set the Window Iconify
        virtual void setIconify(bool Iconify) = 0;

        //Get the Window Iconify
        virtual bool getIconify(void) const = 0;

        //Fullscreen
        virtual void setFullscreen(bool Fullscreen) = 0;

        //Get the Window Fullscreen
        virtual bool getFullscreen(void) const = 0;

        //Set the text on the Title bar of the window
        virtual void setTitle(const std::string& TitleText) = 0;

        //Get the text of the Title bar of the window
        virtual std::string getTitle(void) = 0;

        //Set the window to allow or not allow Resizing
        virtual void setRisizable(bool IsResizable) = 0;

        //Get whether or not the window allows resizing
        virtual bool getRisizable(void) = 0;

        //Set the window to draw or not draw it's border
        /*virtual void setDrawBorder(bool DrawBorder) = 0;*/

        //Get wether or not the window is drawing a border
        /*virtual bool getDrawBorder(void) = 0;*/

        virtual void setShowCursor(bool showCursor) = 0;

        virtual bool getShowCursor(void) const = 0;
        
        virtual void setAttachMouseToCursor(bool attach) = 0;
        
        virtual bool getAttachMouseToCursor(void) const = 0;

        //Set Display Callback Function
        /*virtual void setDisplayCallback(DisplayCallbackFunc Callback);*/

        //Set Reshape Callback Function
        /*virtual void setReshapeCallback(ReshapeCallbackFunc Callback);*/

        virtual Vec2f getDesktopSize(void) const = 0;

        /*virtual std::vector<Path> openFileDialog(const std::string& WindowTitle,*/
            /*const std::vector<FileDialogFilter>& Filters,*/
            /*const Path& InitialDir,*/
            /*bool AllowMultiSelect) = 0;*/

        /*virtual Path saveFileDialog(const std::string& DialogTitle,*/
                        /*const std::vector<FileDialogFilter>& Filters,*/
                        /*const std::string& InitialFile,*/
                        /*const Path& InitialDirectory,*/
                        /*bool PromptForOverwrite*/
                        /*) = 0;*/


        /*virtual void draw(void) = 0;*/
        /*virtual void update(void) = 0;*/

        /*virtual bool attachWindow(void) = 0;*/

        virtual UInt32 getKeyModifiers(void) const = 0;
        virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const = 0;
        
        virtual Pnt2f getMousePosition(void) const = 0;

        ViewportPtr windowToViewport(const Pnt2f& WindowPoint, Pnt2f& ViewportPoint);

        virtual std::string getClipboard(void) const = 0;

        virtual void putClipboard(const std::string Value) = 0;

        UInt32 getCursorType(void) const;
        void setCursorType(UInt32 Type); 

        /*RenderAction * getRenderAction(void);*/
        /*void setRenderAction(RenderAction *action);*/

        /*CursorRegionListItor addCursorRegion(const CursorRegion& r);*/
        /*bool removeCursorRegion(CursorRegionListItor RegionItor);*/

        void blockInputConnections(bool Block);
        bool isBlockInputConnections(void) const;
      protected:
        WindowEventProducer(void);
        WindowEventProducer(const WindowEventProducer &source);

        virtual ~WindowEventProducer(void);
    };

    /******************************************************/
    /*                StringToUInt32Map                   */
    /******************************************************/

    /******************************************************/
    /*                   LuaManager                       */
    /******************************************************/

    /******************************************************/
    /*                 SoundManager                       */
    /******************************************************/

    /******************************************************/
    /*                 VideoManager                       */
    /******************************************************/

    /******************************************************/
    /*                 ParticleSystemPtr                       */
    /******************************************************/
    class ParticleSystemPtr : public AttachmentContainerPtr
    {
      public:
         ParticleSystemPtr(void);
         ParticleSystemPtr(const ParticleSystemPtr               &source);
         /*ParticleSystemPtr(const NullFieldContainerPtr &source);*/


        ~ParticleSystemPtr(void); 
        ParticleSystem *operator->(void);
        
        static ParticleSystemPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                 ComponentPtr                       */
    /******************************************************/
    class ComponentPtr : public AttachmentContainerPtr
    {
      public:
         ComponentPtr(void);
         ComponentPtr(const ComponentPtr               &source);
         /*ComponentPtr(const NullFieldContainerPtr &source);*/


        ~ComponentPtr(void); 
        Component *operator->(void);
        
        static ComponentPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                 VideoWrapperPtr                       */
    /******************************************************/
    class VideoWrapperPtr : public AttachmentContainerPtr
    {
      public:
         VideoWrapperPtr(void);
         VideoWrapperPtr(const VideoWrapperPtr               &source);
         /*VideoWrapperPtr(const NullFieldContainerPtr &source);*/


        ~VideoWrapperPtr(void); 
        VideoWrapper *operator->(void);
        
        static VideoWrapperPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                 SoundPtr                       */
    /******************************************************/
    class SoundPtr : public AttachmentContainerPtr
    {
      public:
         SoundPtr(void);
         SoundPtr(const SoundPtr               &source);
         /*SoundPtr(const NullFieldContainerPtr &source);*/


        ~SoundPtr(void); 
        Sound *operator->(void);
        
        static SoundPtr dcast(const FieldContainerPtr oIn);
    };
    
    /******************************************************/
    /*                 AnimationPtr                       */
    /******************************************************/
    class AnimationPtr : public AttachmentContainerPtr
    {
      public:
         AnimationPtr(void);
         AnimationPtr(const AnimationPtr               &source);
         /*AnimationPtr(const NullFieldContainerPtr &source);*/


        ~AnimationPtr(void); 
        Animation *operator->(void);
        
        static AnimationPtr dcast(const FieldContainerPtr oIn);
    };
    
}

