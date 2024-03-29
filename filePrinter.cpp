#include "filePrinter.hpp"


filePrinter::filePrinter()
{

}



bool filePrinter::doesFileExist(std::string fileName)
{
  
  // initialization constructor calls open(), if not open, then failbit is active
  std::ifstream stream(fileName.c_str());
  // failbit would be returned if the file did not exist
  return stream;
}

void filePrinter::newFile(std::string fileName)
{

  
  std::string badchars = ":\?\"<>*|";
  size_t pos;
  while ((pos =fileName.find_first_of(badchars))+1 != 0) {
    fileName.erase(fileName.begin()+pos);
    
  }

  if (!doesFileExist(fileName)) {
	fileName_ = fileName;	
	//TODO: throw exception
  }
}




void filePrinter::writeLine(std::string str)
{
  
#ifdef __gnu_linux__
  //std::ofstream writeStream(fileName_.c_str());
  if (!writeStream_.is_open())
    writeStream_.open(fileName_.c_str());
  if (!str.empty() && *(--str.end()) != '\n') 
	str.append("\n");

  writeStream_.write(str.c_str(), str.size());
  
  //DEPRICATED
//   for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
// //     std::cerr << *it;
// 	writeStream_.put(char(*it));
//   }
#endif
  
#ifdef __win32__
  std::ofstream writeStream(fileName_.c_str());
  if (!str.empty() && *(--str.end()) != '\n') 
	str.append("\n");
  writeStream.write(str.c_str(), str.size());
  writeStream.close();
#endif
}

void filePrinter::close()
{
writeStream_.close();
writeStream_.clear();
}


filePrinter::~filePrinter()
{
close();
}

