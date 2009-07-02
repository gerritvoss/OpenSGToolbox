// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with WIN32 to create a little
// interactive scene viewer.
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/Input/OSGWindowAdapter.h>


#include <OpenSG/Dynamics/OSGBooleanFunction.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerPtr TheWindowEventProducer;

bool ExitMainLoop = false;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);


class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEvent& e)
    {
        switch(e.getKey()){
            case KeyEvent::KEY_ESCAPE:
                TheWindowEventProducer->closeWindow();
                break;
            default:
                break;
        }
    }
    virtual void keyReleased(const KeyEvent& e)
    {
    }
    virtual void keyTyped(const KeyEvent& e)
    {
    }
};

class TutorialWindowListener : public WindowAdapter
{
    /*=========================  PUBLIC  ===============================*/
  public:

    virtual void windowClosed(const WindowEvent& e)
    {
       ExitMainLoop = true;
    }

};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    TheWindowEventProducer = createDefaultWindowEventProducer();
    TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Attach Key Listener
    TutorialKeyListener TheTutorialKeyListener;
    TheWindowEventProducer->addKeyListener(&TheTutorialKeyListener);
    //Attach Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    
    // create the scene
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer->getWindow() );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                        Vec2s(250,250),
                        "02BooleanFunctions Tutorial");

	BooleanFunctionPtr BooleanAndFunction = BooleanFunction::create();
	beginEditCP(BooleanAndFunction);
		BooleanAndFunction->setOperation(BooleanFunction::BOOLEAN_AND);
	endEditCP(BooleanAndFunction);
	
	BooleanFunctionPtr BooleanOrFunction = BooleanFunction::create();
	beginEditCP(BooleanOrFunction);
		BooleanOrFunction->setOperation(BooleanFunction::BOOLEAN_OR);
	endEditCP(BooleanOrFunction);
	
	BooleanFunctionPtr BooleanNandFunction = BooleanFunction::create();
	beginEditCP(BooleanNandFunction);
		BooleanNandFunction->setOperation(BooleanFunction::BOOLEAN_NAND);
	endEditCP(BooleanNandFunction);
	
	BooleanFunctionPtr BooleanNorFunction = BooleanFunction::create();
	beginEditCP(BooleanNorFunction);
		BooleanNorFunction->setOperation(BooleanFunction::BOOLEAN_NOR);
	endEditCP(BooleanNorFunction);

	BooleanFunctionPtr BooleanXorFunction = BooleanFunction::create();
	beginEditCP(BooleanXorFunction);
		BooleanXorFunction->setOperation(BooleanFunction::BOOLEAN_XOR);
	endEditCP(BooleanXorFunction);

	BooleanFunctionPtr BooleanNotFunction = BooleanFunction::create();
	beginEditCP(BooleanNotFunction);
		BooleanNotFunction->setOperation(BooleanFunction::BOOLEAN_NOT);
	endEditCP(BooleanNotFunction);
	
	FunctionIOParameterVector TTParameters;
	TTParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	TTParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	
    FunctionIOParameterVector TFParameters;
	TFParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	TFParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(false)));
	
    FunctionIOParameterVector FTParameters;
	FTParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(false)));
	FTParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	
    FunctionIOParameterVector FFParameters;
	FFParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(false)));
	FFParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(false)));

	FunctionIOParameterVector ManyParameters;
	ManyParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	ManyParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	ManyParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(false)));
	ManyParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(true)));
	ManyParameters.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<bool>(false)));

	FunctionIOParameterVector Result;
	std::string Operation("And");
	Result = BooleanAndFunction->evaluate(TTParameters);
	std::cout << "T " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanAndFunction->evaluate(TFParameters);
	std::cout << "T " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanAndFunction->evaluate(FTParameters);
	std::cout << "F " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanAndFunction->evaluate(FFParameters);
	std::cout << "F " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Operation = std::string("Or");
	Result = BooleanOrFunction->evaluate(TTParameters);
	std::cout << "T " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanOrFunction->evaluate(TFParameters);
	std::cout << "T " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanOrFunction->evaluate(FTParameters);
	std::cout << "F " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanOrFunction->evaluate(FFParameters);
	std::cout << "F " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Operation = std::string("Nand");
	Result = BooleanNandFunction->evaluate(TTParameters);
	std::cout << "T " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanNandFunction->evaluate(TFParameters);
	std::cout << "T " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanNandFunction->evaluate(FTParameters);
	std::cout << "F " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanNandFunction->evaluate(FFParameters);
	std::cout << "F " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Operation = std::string("Nor");
	Result = BooleanNorFunction->evaluate(TTParameters);
	std::cout << "T " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanNorFunction->evaluate(TFParameters);
	std::cout << "T " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanNorFunction->evaluate(FTParameters);
	std::cout << "F " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanNorFunction->evaluate(FFParameters);
	std::cout << "F " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;

	Operation = std::string("Xor");
	Result = BooleanXorFunction->evaluate(TTParameters);
	std::cout << "T " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanXorFunction->evaluate(TFParameters);
	std::cout << "T " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanXorFunction->evaluate(FTParameters);
	std::cout << "F " << Operation << " T: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;
	
	Result = BooleanXorFunction->evaluate(FFParameters);
	std::cout << "F " << Operation << " F: " << dynamic_cast<const FunctionIOData<bool>* >(Result[0].getDataPtr())->getData() << std::endl;

	Operation = std::string("Not");
	Result = BooleanNotFunction->evaluate(ManyParameters);
	for(UInt32 i(0) ; i<Result.size() ; ++i)
	{
		std::cout << dynamic_cast<const FunctionIOData<bool>* >(ManyParameters[i].getDataPtr())->getData()
			<< " " << Operation << " " << dynamic_cast<const FunctionIOData<bool>* >(Result[i].getDataPtr())->getData() << std::endl;
	}
    while(!ExitMainLoop)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }

    osgExit();
    return 0;
}

//
// callback functions
//

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}


