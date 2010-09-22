
#include <OSGConfig.h>

#include <OSGPlainDocument.h>

#include <OSGTextFileHandler.h>


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
	PlainDocumentRefPtr TheDocument;
	TheDocument = dynamic_pointer_cast<PlainDocument>(TextFileHandler::the()->read(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TextDom\\Data\\SampleText2.txt")));


	UInt32 documentLength = TheDocument->getLength();
	std::cout<<"documentLength:"<<documentLength<<std::endl;

	
	UInt32 choice,offset,length;
	std::string stringToInsert;
	std::map<std::string,UInt32> temp;
	std::string result;
	std::string path;

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
			result = TheDocument->getText(offset,length);

			std::cout<<"----------------------------------------------"<<std::endl;
			std::cout<<"TheDocument->getText("<<offset<<","<<length<<")\n"<<result<<std::endl;
			std::cout<<"----------------------------------------------"<<std::endl;

			break;

		case 2:// test for insertString
			std::cout<<"Enter offset:";
			std::cin>>offset;
			std::cout<<"Enter string to insert:";
			std::cin>>stringToInsert;
			
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

			TheDocument->replace(offset,length,stringToInsert,temp);

			result= TheDocument->getText(0,TheDocument->getLength());
			
			std::cout<<"----------------------------------------------"<<std::endl;
			std::cout<<"TheDocument->replace("<<offset<<","<<length<<","<<stringToInsert<<")\n"<<result<<std::endl;
			std::cout<<"----------------------------------------------"<<std::endl;

			break;

		case 5://test for writing
			std::cout<<"Enter the name of file to write to(without extension):";
			std::cin>>path;
			TextFileHandler::the()->write(TheDocument,BoostPath(path+".txt"));
			break;
		default:
			more = false;
			
		}
		
	}

    osgExit();
    return 0;
}
