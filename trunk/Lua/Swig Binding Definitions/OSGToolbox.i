
%module OSGToolbox
%import  <OSGBase.i>
%import  <OSGSystem.i>
%include <lua/std_map.i>
%include <lua/std_vector.i>
%{
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGKeyEvent.h>
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundGroup.h>
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Animation/OSGAnimation.h>
#include <OpenSG/UserInterface/OSGComponent.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/Physics/OSGPhysicsHandler.h>
#include <OpenSG/Physics/OSGPhysicsBody.h>
#include <OpenSG/Physics/OSGPhysicsWorld.h>


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

namespace std {
    %template(UInt32Vec) vector<osg::UInt32>;
    %template(StringToUInt32Map) map<string, osg::UInt32>;
}
    

namespace osg {

    class WindowEventProducer;
    class Sound;
    class Animation;
    class Component;
    class ParticleSystem;
    class PhysicsBody;
    class PhysicsHandler;
    class PhysicsWorld;
    
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

        //virtual WindowPtr initWindow(void);

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
        //virtual void setSize(Vec2us Size) = 0;

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
        //virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const = 0;
        
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
    /*                   LuaManager                       */
    /******************************************************/
    
    /******************************************************/
    /*                 PhysicsHandlerPtr                  */
    /******************************************************/
    class PhysicsHandlerPtr : public FieldContainerPtr
    {
      public:
         PhysicsHandlerPtr(void);
         PhysicsHandlerPtr(const PhysicsHandlerPtr               &source);
         /*PhysicsHandlerPtr(const NullFieldContainerPtr &source);*/


        ~PhysicsHandlerPtr(void); 
        PhysicsHandler *operator->(void);
        
        static PhysicsHandlerPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                 PhysicsHandler                     */
    /******************************************************/
    class PhysicsHandler : public FieldContainer
    {
      public:
        //void attachUpdateProducer(EventProducerPtr TheProducer);
        //void detachUpdateProducer(EventProducerPtr TheProducer);

      protected:
        PhysicsHandler(void);
        PhysicsHandler(const PhysicsHandler &source);

        virtual ~PhysicsHandler(void);
    };

    /******************************************************/
    /*                 PhysicsWorldPtr                  */
    /******************************************************/
    class PhysicsWorldPtr : public FieldContainerPtr
    {
      public:
         PhysicsWorldPtr(void);
         PhysicsWorldPtr(const PhysicsWorldPtr               &source);
         /*PhysicsWorldPtr(const NullFieldContainerPtr &source);*/


        ~PhysicsWorldPtr(void); 
        PhysicsWorld *operator->(void);
        
        static PhysicsWorldPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                 PhysicsWorld                     */
    /******************************************************/
    class PhysicsWorld : public FieldContainer
    {
      public:
        Vec3f impulseToForce(Real32 stepsize, const Vec3f& Impulse);
        //void worldStep(Real32 stepsize);
        //void worldQuickStep(Real32 stepsize);
        void initWorld();

        PhysicsHandlerPtr getParentHandler(void) const;

      protected:
        PhysicsWorld(void);
        PhysicsWorld(const PhysicsWorld &source);

        virtual ~PhysicsWorld(void);
    };

    /******************************************************/
    /*                 PhysicsBodyPtr                  */
    /******************************************************/
    class PhysicsBodyPtr : public FieldContainerPtr
    {
      public:
         PhysicsBodyPtr(void);
         PhysicsBodyPtr(const PhysicsBodyPtr               &source);
         /*PhysicsBodyPtr(const NullFieldContainerPtr &source);*/


        ~PhysicsBodyPtr(void); 
        PhysicsBody *operator->(void);
        
        static PhysicsBodyPtr dcast(const FieldContainerPtr oIn);
    };

    /******************************************************/
    /*                 PhysicsBody                     */
    /******************************************************/
    class PhysicsBody : public FieldContainer
    {
      public:
      //dBodyID getBodyID(void);

      static  PhysicsBodyPtr      create          (PhysicsWorldPtr World);

      void setEnable(bool enable);
      bool getEnable(void) const;

	  //void setMassStruct(const dMass &mass );
	  //void getMassStruct(dMass &mass );
	  void addForce(const Vec3f &v);
	  void addTorque(const Vec3f &v);
	  void addRelForce(const Vec3f &v);
	  void addRelTorque(const Vec3f &v);
	  void addForceAtPos(const Vec3f &v,const  Vec3f &p);
	  void addForceAtRelPos(const Vec3f &v,const  Vec3f &p);
	  void addRelForceAtPos(const Vec3f &v,const Vec3f &p);
	  void addRelForceAtRelPos(const Vec3f &v,const Vec3f &p);
	  void getRelPointPos(const Vec3f &p, Vec3f &result);
	  void getRelPointVel(const Vec3f &p, Vec3f &result);
	  void getPointVel(const Vec3f &p, Vec3f &result);
	  void getPosRelPoint(const Vec3f &p, Vec3f &result);
	  void vectorToWorld(const Vec3f &p, Vec3f &result);
	  void vectorFromWorld(const Vec3f &p, Vec3f &result);
	  void setAutoDisableDefaults(void);
	  //void setData(void* someData);
	  //void* getData(void);
	  Int32 getNumJoints(void);
	  //dJointID getJoint(Int32 index);
      void initDefaults(void);

      //Mass
      void resetMass();
      void setMassParams( Real32 theMass, const Vec3f& cg,
          Real32 I11, Real32 I22, Real32 I33,
          Real32 I12, Real32 I13, Real32 I23 );
      void setSphereMass( Real32 density, Real32 radius );
      void setSphereMassTotal( Real32 totalMass, Real32 radius );
      void setCapsuleMass( Real32 density, Int32 direction,
          Real32 radius, Real32 length );
      void setCapsuleMassTotal( Real32 totalMass, Int32 direction,
          Real32 radius, Real32 length );
      void setBoxMass( Real32 density, Real32 lx, Real32 ly, Real32 lz );
      void setBoxMassTotal( Real32 totalMass, Real32 lx, Real32 ly, Real32 lz );
      void adjustMass( Real32 newMass );
      void translateMass( const Vec3f& );
      void rotateMass( const Matrix& );
      //void addMassOf( dBodyID otherBody );

      //Damping
      void setDamping (Real32 linear_scale, Real32 angular_scale);


      void setDampingDefaults (void);

      protected:
        PhysicsBody(void);
        PhysicsBody(const PhysicsBody &source);

        virtual ~PhysicsBody(void);
    };

    /******************************************************/
    /*                 Key Bindings                       */
    /******************************************************/
    class KeyEvent
    {
      public:

         enum KeyModifiers { KEY_MODIFIER_UNKNOWN     = 0,
                             KEY_MODIFIER_SHIFT       = 1,
                             KEY_MODIFIER_CONTROL     = 2,
                             KEY_MODIFIER_ALT         = 4,
                             KEY_MODIFIER_META        = 8,
                             KEY_MODIFIER_CAPS_LOCK   = 16,
                             KEY_MODIFIER_NUM_LOCK    = 32,
                             KEY_MODIFIER_SCROLL_LOCK = 64 };
         enum Key
          {
             KEY_UNKNOWN = 0,

             KEY_BACK_SPACE = 8,
             KEY_TAB        = 9 ,


             KEY_ESCAPE     = 27 ,

             KEY_SPACE             = 32,
             KEY_EXCLAMATION_MARK  = 33 ,
             KEY_QUOTE             = 34 ,
             KEY_NUMBER_SIGN       = 35 ,
             KEY_DOLLAR            = 36 ,
             KEY_PERCENT           = 37 ,
             KEY_AMPERSAND         = 38 ,
             KEY_APOSTROPHE        = 39 ,
             KEY_LEFT_PARENTHESIS  = 40 ,
             KEY_RIGHT_PARENTHESIS = 41 ,
             KEY_ASTERISK          = 42 ,
             KEY_PLUS              = 43 ,
             KEY_COMMA             = 44,
             KEY_MINUS  = 45,
             KEY_PERIOD = 46 ,
             KEY_SLASH  = 47 ,
             KEY_0 = 48,
             KEY_1 = 49 ,
             KEY_2 = 50 ,
             KEY_3 = 51 ,
             KEY_4 = 52 ,
             KEY_5 = 53 ,
             KEY_6 = 54 ,
             KEY_7 = 55 ,
             KEY_8 = 56 ,
             KEY_9 = 57 ,
             KEY_COLON         = 58,
             KEY_SEMICOLON     = 59 ,
             KEY_LESS          = 60 ,
             KEY_EQUALS        = 61 ,
             KEY_GREATER       = 62 ,
             KEY_QUESTION_MARK = 63 ,
             KEY_AT            = 64 ,
             KEY_A = 65,
             KEY_B = 66,
             KEY_C = 67,
             KEY_D = 68,
             KEY_E = 69,
             KEY_F = 70,
             KEY_G = 71,
             KEY_H = 72,
             KEY_I = 73,
             KEY_J = 74,
             KEY_K = 75,
             KEY_L = 76,
             KEY_M = 77,
             KEY_N = 78,
             KEY_O = 79,
             KEY_P = 80,
             KEY_Q = 81,
             KEY_R = 82,
             KEY_S = 83,
             KEY_T = 84,
             KEY_U = 85,
             KEY_V = 86,
             KEY_W = 87,
             KEY_X = 88,
             KEY_Y = 89,
             KEY_Z = 90,
             KEY_OPEN_BRACKET  = 91,
             KEY_BACK_SLASH    = 92 ,
             KEY_CLOSE_BRACKET = 93 ,
             KEY_CIRCUMFLEX    = 94 ,
             KEY_UNDERSCORE    = 95 ,
             KEY_BACK_QUOTE    = 96 ,

             
             KEY_BRACE_LEFT  = 123,
             KEY_PIPE        = 124 ,
             KEY_BRACE_RIGHT = 125 ,
             KEY_TILDE       = 126 ,
             KEY_DELETE      = 127 ,

             KEY_INVERTED_EXCLAMATION_MARK,

             KEY_ALT           = 131,
             KEY_CONTROL       = 132 ,
             KEY_CAPS_LOCK     = 133 ,
             KEY_SCROLL_LOCK   = 134 ,
             KEY_NUM_LOCK      = 135 ,
             KEY_SHIFT         = 136 ,
             KEY_MENU          = 137 ,
             KEY_META          = 138 ,
             KEY_ENTER         = 139 ,

             KEY_CANCEL        = 140 ,
             KEY_CLEAR         = 141 ,
             KEY_COPY          = 142 ,
             KEY_CUT           = 143 ,
             KEY_END           = 144 ,
             KEY_INSERT        = 145 ,
             KEY_HOME          = 146 ,
             KEY_PAGE_DOWN     = 147 ,
             KEY_PAGE_UP       = 148 ,
             KEY_FIND          = 149 ,
             KEY_HELP          = 150 ,
             KEY_PASTE         = 151 ,
             KEY_PAUSE         = 152 ,
             KEY_PRINTSCREEN   = 153 ,
             KEY_STOP          = 154 ,
             KEY_UNDO          = 155 ,

             KEY_F1            = 156 ,
             KEY_F2            = 157 ,
             KEY_F3            = 158 ,
             KEY_F4            = 159 ,
             KEY_F5            = 160 ,
             KEY_F6            = 161 ,
             KEY_F7            = 162 ,
             KEY_F8            = 163 ,
             KEY_F9            = 164 ,
             KEY_F10           = 165 ,
             KEY_F11           = 166 ,
             KEY_F12           = 167 ,
             KEY_F13           = 168 ,
             KEY_F14           = 169 ,
             KEY_F15           = 170 ,
             KEY_F16           = 171 ,
             KEY_F17           = 172 ,
             KEY_F18           = 173 ,
             KEY_F19           = 174 ,
             KEY_F20           = 175 ,
             KEY_F21           = 176 ,
             KEY_F22           = 177 ,
             KEY_F23           = 178 ,
             KEY_F24           = 179 ,


             KEY_RIGHT         = 180 ,
             KEY_LEFT          = 181 ,
             KEY_UP            = 182 ,
             KEY_DOWN          = 183 ,

             KEY_MULTIPLY      = 184 ,
             KEY_DECIMAL       = 185 ,
             KEY_ADD           = 186 ,
             KEY_DIVIDE        = 187 ,
             KEY_SUBTRACT      = 188 ,
             KEY_KEYPAD_UP     = 189 ,
             KEY_KEYPAD_DOWN   = 190 ,
             KEY_KEYPAD_LEFT   = 191 ,
             KEY_KEYPAD_RIGHT  = 192 ,
             KEY_NONE          = 193 ,
             KEY_NUMPAD_0      = 194 ,
             KEY_NUMPAD_1      = 195 ,
             KEY_NUMPAD_2      = 196 ,
             KEY_NUMPAD_3      = 197 ,
             KEY_NUMPAD_4      = 198 ,
             KEY_NUMPAD_5      = 199 ,
             KEY_NUMPAD_6      = 200 ,
             KEY_NUMPAD_7      = 201 ,
             KEY_NUMPAD_8      = 202 ,
             KEY_NUMPAD_9      = 203 ,
             KEY_NUMPAD_EQUALS = 204 ,

             KEY_UNDEFINED     = 205 ,
          };
          enum KeyState
          {
              KEY_STATE_UP      = 1,
              KEY_STATE_DOWN    = 2 ,
              KEY_STATE_TOGGLED = 3 
          };
      protected:
        KeyEvent(void);
        KeyEvent(const PhysicsHandler &source);

        virtual ~KeyEvent(void);
    };

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
    /*                 ParticleSystem                       */
    /******************************************************/
    class ParticleSystem : public AttachmentContainer
    {
      public:
    
        UInt32 getNumParticles(void) const;
        const Pnt3f& getPosition(const UInt32& Index) const;
        const Pnt3f& getSecPosition(const UInt32& Index) const;
        const Vec3f getPositionChange(const UInt32& Index) const;
        const Vec3f& getNormal(const UInt32& Index) const;
        const Color4f& getColor(const UInt32& Index) const;
        const Vec3f& getSize(const UInt32& Index) const;
        Real32 getLifespan(const UInt32& Index) const;
        Real32 getAge(const UInt32& Index) const;
        const Vec3f& getVelocity(const UInt32& Index) const;
        const Vec3f& getSecVelocity(const UInt32& Index) const;
        const Vec3f getVelocityChange(const UInt32& Index) const;
        const Vec3f& getAcceleration(const UInt32& Index) const;
        UInt32 getAttribute(const UInt32& Index, const std::string& AttributeKey) const;
        const std::map<std::string, osg::UInt32>& getAttributes(const UInt32& Index) const;
    
        void setPosition(const Pnt3f& Pos, const UInt32& Index);
        void setSecPosition(const Pnt3f& SecPosition, const UInt32& Index);
        void setNormal(const Vec3f& Normal, const UInt32& Index);
        void setColor(const Color4f& Color, const UInt32& Index);
        void setSize(const Vec3f& Size, const UInt32& Index);
        void setLifespan(const Time& Lifespan, const UInt32& Index);
        void setAge(const Time& Age, const UInt32& Index);
        void setVelocity(const Vec3f& Velocity, const UInt32& Index);
        void setSecVelocity(const Vec3f& SecVelocity, const UInt32& Index);
        void setAcceleration(const Vec3f& Acceleration, const UInt32& Index);
        //void setAttribute(const std::string& AttributeKey, UInt32 AttributeValue, const UInt32& Index);
        void setAttributes(const std::map<std::string, osg::UInt32>& Attributes, const UInt32& Index);
    
        bool addParticle(const Pnt3f& Position,
                         const Pnt3f& SecPosition,
                         const Vec3f& Normal,
                         const Color4f& Color,
                         const Vec3f& Size,
                         Real32 Lifespan,
                         Real32 Age,
                         const Vec3f& Velocity,
                         const Vec3f& SecVelocity,
                         const Vec3f& Acceleration,
                         const std::map<std::string, osg::UInt32>& Attributes);
    
        bool addWorldSpaceParticle(const Pnt3f& Position,
                         const Pnt3f& SecPosition,
                         const Vec3f& Normal,
                         const Color4f& Color,
                         const Vec3f& Size,
                         Real32 Lifespan,
                         Real32 Age,
                         const Vec3f& Velocity,
                         const Vec3f& SecVelocity,
                         const Vec3f& Acceleration,
                         const std::map<std::string, osg::UInt32>& Attributes);
    
    
        bool killParticle(UInt32 Index);
    
        bool attachUpdateListener(WindowEventProducerPtr UpdateProducer);
        void dettachUpdateListener(WindowEventProducerPtr UpdateProducer);
        
        std::vector<UInt32> intersect(const Line& Ray, Real32 IntersectionDistance, NodePtr Beacon = NullFC) const;
        std::vector<UInt32> intersect(const Pnt3f& p1, const Pnt3f& p2, Real32 IntersectionDistance, NodePtr Beacon = NullFC) const;
        std::vector<UInt32> intersect(const Volume& Vol, Real32 IntersectionDistance, NodePtr Beacon = NullFC) const;
        std::vector<UInt32> intersect(const NodePtr CollisionNode, NodePtr Beacon = NullFC) const;
        
      protected:
            ParticleSystem(void);
            ParticleSystem(const ParticleSystem &source);
    
            virtual ~ParticleSystem(void);
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
    /*                 Component                       */
    /******************************************************/
    class Component : public AttachmentContainer
    {
      public:
        //virtual void draw(const GraphicsPtr Graphics) const;
    
        virtual void getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const;
        virtual void updateContainerLayout(void);
        virtual void updateClipBounds(void);
        virtual Vec2f getRequestedSize(void) const;
        virtual Vec2f getContentRequestedSize(void) const;
        virtual Vec2f getBorderingLength(void) const;
        
        //Mouse Events
        //virtual void mouseClicked(const MouseEventPtr e);
        //virtual void mouseEntered(const MouseEventPtr e);
        ///virtual void mouseExited(const MouseEventPtr e);
        //virtual void mousePressed(const MouseEventPtr e);
        //virtual void mouseReleased(const MouseEventPtr e);
    
        //Mouse Motion Events
        //virtual void mouseMoved(const MouseEventPtr e);
        //virtual void mouseDragged(const MouseEventPtr e);
    
        //Mouse Wheel Events
        //virtual void mouseWheelMoved(const MouseWheelEventPtr e);
    
        //Key Events
        //virtual void keyPressed(const KeyEventPtr e);
        //virtual void keyReleased(const KeyEventPtr e);
        //virtual void keyTyped(const KeyEventPtr e);
    
        //Focus Events
        //virtual void focusGained(const FocusEventPtr e);
        //virtual void focusLost(const FocusEventPtr e);
    
        void setMouseContained(bool Value);
        bool getMouseContained(void);
    
        virtual bool takeFocus(bool Temporary = false);
        
        virtual bool isContained(const Pnt2f& p, bool TestAgainstClipBounds = true) const;
    
        virtual Real32 getBaseline(const Real32& x, const Real32& y) const;
    
        virtual Pnt2f getToolTipLocation(Pnt2f MousePosition);
        //virtual ToolTipPtr createToolTip(void);
        
        virtual Vec2f getPreferredScrollableViewportSize(void);
    
        virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
        virtual bool getScrollableTracksViewportHeight(void);
    
        virtual bool getScrollableTracksViewportWidth(void);
    
        virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);
    
        virtual void scrollToPoint(const Pnt2f& PointInComponent);
    
        //static const OSG::BitVector BordersFieldMask;
        //virtual void setBorders(BorderPtr TheBorder);
    
        //static const OSG::BitVector BackgroundsFieldMask;
        //virtual void setBackgrounds(LayerPtr TheBackground);
        
        //static const OSG::BitVector ForegroundsFieldMask;
        //virtual void setForegrounds(LayerPtr TheForeground);
    
        virtual Pnt2f getParentToLocal(const Pnt2f& Location);
    
        virtual Pnt2f getLocalToParent(const Pnt2f& Location);
    
      protected:
            Component(void);
            Component(const Component &source);
    
            virtual ~Component(void);
    };

    /******************************************************/
    /*                 VideoWrapperPtr                       */
    /******************************************************/
    /*class VideoWrapperPtr : public AttachmentContainerPtr
    {
      public:
         VideoWrapperPtr(void);
         VideoWrapperPtr(const VideoWrapperPtr               &source);
         //VideoWrapperPtr(const NullFieldContainerPtr &source);


        ~VideoWrapperPtr(void); 
        VideoWrapper *operator->(void);
        
        static VideoWrapperPtr dcast(const FieldContainerPtr oIn);
    };*/
    
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
    /*                 Sound                              */
    /******************************************************/
    class Sound : public AttachmentContainer
    {
      public:
    
        virtual UInt32 play(void) = 0;
        virtual Real32 getLength(void) const = 0;
        
        //Channel Methods
        virtual UInt32 getNumChannels(void) const = 0;
        virtual UInt32 getNumPlayingChannels(void) const = 0;
        virtual bool isPlaying(UInt32 ChannelID) const = 0;
        virtual bool isValid(UInt32 ChannelID) const = 0;
        virtual void stop(UInt32 ChannelID) = 0;
    
        virtual void pause(UInt32 ChannelID) = 0;
        virtual void unpause(UInt32 ChannelID) = 0;
        virtual void pauseToggle(UInt32 ChannelID) = 0;
        virtual bool isPaused(UInt32 ChannelID) const = 0;
    
        virtual void seek(Real32 pos, UInt32 ChannelID) = 0;
        virtual Real32 getTime(UInt32 ChannelID) const = 0;
    
        virtual void setChannelPosition(const Pnt3f &pos, UInt32 ChannelID) = 0;
        virtual Pnt3f getChannelPosition(UInt32 ChannelID) const = 0;
    
        virtual void setChannelVelocity(const Vec3f &vec, UInt32 ChannelID) = 0;
        virtual Vec3f getChannelVelocity(UInt32 ChannelID) const = 0;
    
        virtual void setChannelVolume(Real32 volume, UInt32 ChannelID) = 0;
        virtual Real32 getChannelVolume(UInt32 ChannelID) const = 0;
        virtual bool getMute(UInt32 ChannelID) const = 0;
        virtual void mute(bool shouldMute, UInt32 ChannelID) = 0;
    
        
        virtual void setAllChannelsVolume(Real32 volume) = 0;
        virtual void stopAllChannels(void) = 0;
        virtual void setAllChannelPaused(bool paused) = 0;
        virtual void setAllChannelMute(bool shouldMute) = 0;
        
        static  SoundPtr      create(void); 
      private:
        Sound(void);
        Sound(const Sound &source);

        virtual ~Sound(void);
    
    };
    
    /******************************************************/
    /*                 SoundManager                       */
    /******************************************************/
    class SoundManager
    {
      public:
        static SoundManager* the(void);
    
        //create a new sound object by its integer id
        virtual SoundPtr createSound(void) const = 0;
    
        virtual void setCamera(CameraPtr TheCamera);
        virtual CameraPtr getCamera(void) const;
    
        void attachUpdateProducer(WindowEventProducerPtr TheProducer);
        void detachUpdateProducer(WindowEventProducerPtr TheProducer);
    
      protected:
        SoundManager(void);
        SoundManager(const SoundManager &source);
        virtual ~SoundManager(void); 
    };
    
    /******************************************************/
    /*                 SoundGroup                       */
    /******************************************************/
    class SoundGroup : public AttachmentContainer
    {
        public:

            void stop(void);
            void pause(void);
            void unpause(void);
            void setVolume(Real32 volume);
            Real32 getVolume(void) const;
            void mute(bool muted);

            UInt32 getNumSounds(void) const;
            UInt32 getNumPlayingSounds(void) const;
            UInt32 getNumPlayingChannels(void) const;
        protected:
            SoundGroup(void);
            SoundGroup(const SoundGroup &source);
            virtual ~SoundGroup(void); 
    };
    
    /******************************************************/
    /*                 SoundGroupPtr                       */
    /******************************************************/
    class SoundGroupPtr : public AttachmentContainerPtr
    {
      public:
         SoundGroupPtr(void);
         SoundGroupPtr(const SoundGroupPtr               &source);
         /*SoundGroupPtr(const NullFieldContainerPtr &source);*/


        ~SoundGroupPtr(void); 
        SoundGroup *operator->(void);
        
        static SoundGroupPtr dcast(const FieldContainerPtr oIn);
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
    
    /******************************************************/
    /*                 AnimationPtr                       */
    /******************************************************/
    class Animation : public AttachmentContainer
    {
      public:
        
        //virtual bool update(const AnimationAdvancerPtr& advancer);
    
        virtual Real32 getLength(void) const = 0;
      protected:
        Animation(void);
        Animation(const Animation &source);
        virtual ~Animation(void); 
    };
}

