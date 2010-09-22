
#include <OSGConfig.h>

#include <OSGSyntaxHighlighter.h>


OSG_USING_NAMESPACE


int main(int argc, char **argv)
{

	
	// OSG init
    osgInit(argc,argv);

	SyntaxHighlighter::the()->processInputFile("hi");

    
	//TheDocument = dynamic_pointer_cast<PlainDocument>(TextFileHandler::the()->read(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TextDom\\Data\\SampleText2.txt")));

	getchar();

    osgExit();
    return 0;
}
