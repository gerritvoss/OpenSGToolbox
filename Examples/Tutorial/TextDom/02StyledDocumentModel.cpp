
#include <OSGConfig.h>

#include <OSGStyledDocument.h>
//Sound
#include <OSGTextFileHandler.h>

#include <StyledDocumentAttributes.h>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE	

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
   
    //Load Document
	StyledDocumentRefPtr TheDocument;
	BoostPath temps = BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TextDom\\Data\\SampleText2.rtf");

	DocumentRefPtr tempr = TextFileHandler::the()->read(temps);

	if(tempr==NULL) {
		std::cout<<"File Read failed.Exiting...\n";
		getchar();
		return -1;
	}

	TheDocument =  dynamic_pointer_cast<StyledDocument>(tempr);


	UInt32 documentLength = TheDocument->getLength();
	std::cout<<"documentLength:"<<documentLength<<std::endl;

	
	UInt32 choice,offset,length;
	std::string stringToInsert;
	TextWithProps temp;
	
	Color tempColor;
	tempColor.r = tempColor.g = tempColor.b = 255;

	temp.bold = true;
	temp.underlined = true;
	temp.italics = true;
	temp.fontfaceindex = 0;
	temp.backgroundindex = 0;
	temp.foregroundindex = 0;
	temp.foreground = tempColor;
	temp.background = tempColor;
	temp.fontface = "";
	temp.text = "";
	temp.processed = false;
	temp.fontsize = 28;


	

	std::string result="";
	std::string path="";
	std::string result2;

	bool more = true;
	while(more)
	{
		std::cout<<"\n\nOptions:\n\n1. getText \n2. insertString \n3. remove \n4. replace \n5. write \n<else>. End\n\n";
		std::cout<<"Enter your choice:";
		std::cin>>choice;
		
		switch(choice)
		{

		case 1: //  test for getText
			std::cout<<"Enter offset:";
			std::cin>>offset;
			std::cout<<"Enter length:";
			std::cin>>length;
			TheDocument->displayDebugInfo();
			
			result=TheDocument->getText(offset,length);

			std::cout<<"----------------------------------------------"<<std::endl;
			std::cout<<"TheDocument->getText("<<offset<<","<<length<<")\n"<<result<<std::endl;
			std::cout<<"----------------------------------------------"<<std::endl;

			break;

		case 2:// test for insertString
			std::cout<<"Enter offset:";
			std::cin>>offset;
			std::cout<<"Enter string to insert:";
			std::cin>>stringToInsert;
			
			temp.text = stringToInsert;
			
			TheDocument->insertString(offset,stringToInsert,temp);
			
			result= TheDocument->getText(0,TheDocument->getLength());
			
			std::cout<<"----------------------------------------------"<<std::endl;
			std::cout<<"TheDocument->insertString("<<offset<<","<<stringToInsert<<")\n"<<result<<std::endl;
			std::cout<<"----------------------------------------------"<<std::endl;

			break;

		case 3:// test for remove
			std::cout<<"Enter offset:";
			std::cin>>offset;
			std::cout<<"Enter length:";
			std::cin>>length;

			TheDocument->remove(offset,length);

			result= TheDocument->getText(0,TheDocument->getLength());
			
			std::cout<<"----------------------------------------------"<<std::endl;
			std::cout<<"TheDocument->remove("<<offset<<","<<length<<")\n"<<result<<std::endl;
			std::cout<<"----------------------------------------------"<<std::endl;

			break;

		case 4:// test for replace
			std::cout<<"Enter offset:";
			std::cin>>offset;
			std::cout<<"Enter length:";
			std::cin>>length;
			std::cout<<"Enter string to insert:";
			std::cin>>stringToInsert;

			temp.text = stringToInsert;

			TheDocument->replace(offset,length,stringToInsert,temp);

			result= TheDocument->getText(0,TheDocument->getLength());
			
			std::cout<<"----------------------------------------------"<<std::endl;
			std::cout<<"TheDocument->replace("<<offset<<","<<length<<","<<stringToInsert<<")\n"<<result<<std::endl;
			std::cout<<"----------------------------------------------"<<std::endl;

			break;

		case 5://test for writing
			std::cout<<"Enter the name of file to write to(without extension):";
			std::cin>>path;
			TextFileHandler::the()->write(TheDocument,BoostPath(path+".rtf"));
			break;
		default:
			more = false;
			
		}
		
	}

    osgExit();
    return 0;
}
