#include "FileLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unordered_map< string, FileLoader::TextureData& > FileLoader::textures;
char* convertToChar;
FileLoader::ConfigData staticConfigData;

FileLoader::FileLoader() {
	configData = new ConfigData;
    convertToChar = nullptr;
}

FileLoader::~FileLoader() {
	delete configData;
    if (convertToChar == nullptr) {}
    else delete[] convertToChar;
}
 /***************************************************************************
  * ********************** Load Textures and Store them **********************
  * *************************************************************************/


void FileLoader::loadAllTextures() {
    string listFileNames[] = { "mine",       "tile_hidden", "tile_revealed", 
                               "number_1",   "number_2",    "number_3", 
                               "number_4",   "number_5",    "number_6", 
                               "number_7",   "number_8",    "flag", 
                               "face_happy", "face_win",    "face_lose", 
                               "digits",     "debug",       "test_1", 
                               "test_2",     "test_3" };
    int size = 20;

    for (int i = 0; i < size; i++) {
        FileLoader::textures.emplace(listFileNames[i], getTextureString(listFileNames[i]));
    }
}

FileLoader::TextureData& FileLoader::getTextureBMP(string name) {
    return FileLoader::textures.at(name);
}

const unordered_map< string, FileLoader::TextureData& > getTextureMap() {
    return FileLoader::textures;
}

FileLoader::TextureData& FileLoader::getTextureChar(char* name) {
    return loadTextureData32Bit(*readEntireFile(name));
}

FileLoader::TextureData& FileLoader::getTextureString(string name) {
    TextureData* result;
    string fileLocation = "../images/";
    string fileType = ".png";
    name = (fileLocation + name + fileType);
    result = &loadTextureData32Bit(*readEntireFile(stringToChar(name))); 

    return *result;
}

char* FileLoader::stringToChar(string str) {
    int sizeString = str.size();
    if (convertToChar == nullptr) {
        convertToChar = new char[sizeString + 1];
    }
    else {
        delete[] convertToChar;
        convertToChar = new char[sizeString + 1];
    }

    // Copy String to Char
    for (int i = 0; i < sizeString; i++) {
        convertToChar[i] = str.at(i);
    }
    convertToChar[sizeString] = '\0';
    return convertToChar;
}

FileLoader::FileReadInData* FileLoader::readEntireFile(char* path) {
    FileReadInData result = {0};

    DWORD fileSizeHigh = 0;
    DWORD bytesRead = 0;

    HANDLE fileHandle = CreateFileA( path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    result.size = GetFileSize(fileHandle, &fileSizeHigh);
    
    // Allocate memory for the file to be read
    result.data = VirtualAlloc( NULL, result.size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (ReadFile( fileHandle, result.data, result.size, &bytesRead, NULL) && result.size == bytesRead) {
        // Success, We read the file.
    }  
    else {
        // Fail!!!
    }
    return &result;
}

FileLoader::TextureData& FileLoader::loadTextureData32Bit(FileReadInData data) {
    TextureData* result = new TextureData;
    unsigned char temp0;
    unsigned char temp1;
    unsigned char temp2;
    unsigned char temp3;
    UINT32* destPixel;
    result->pixelData = stbi_load_from_memory((stbi_uc*)data.data, data.size, &result->width, &result->height, &result->n, 4);
    result->bitMapInfo.bmiHeader.biSize = sizeof(result->bitMapInfo.bmiHeader);
    result->bitMapInfo.bmiHeader.biWidth = result->width;
    result->bitMapInfo.bmiHeader.biHeight = -result->height;
    result->bitMapInfo.bmiHeader.biPlanes = 1;
    result->bitMapInfo.bmiHeader.biBitCount = 32;
    result->bitMapInfo.bmiHeader.biCompression = BI_RGB;
    result->bitMapInfo.bmiHeader.biSizeImage = 0;
    result->bitMapInfo.bmiHeader.biXPelsPerMeter = 0;
    int test = 0;


/*
    This is an attempt to fix the issue of data being loaded incorrectly.

    for (int i = 0; i < data.size; i = i + 4) {
        // NEED THESE LINES
        temp0 = result->pixelData[i];
        temp1 = result->pixelData[i + 1];
        temp2 = result->pixelData[i + 2];
        temp3 = result->pixelData[i + 3];
        
        // THIS HAS SHOWN TO BE CORRECT but eventually ~14 lines into the texture, 
        // the texture no longer shows correctly, looks liek r and b are flipped for some
        // reason. Not sure why
        result->pixelData[i] = temp2;
        result->pixelData[i + 1] = temp1;
        result->pixelData[i + 2] = temp0;
        result->pixelData[i + 3] = temp3;

        // NOT USED
        result->pixelData[i] = result->pixelData[i] & 0x00000000;
        result->pixelData[i] = ((result->pixelData[i]) | ((temp >> 24) & 0x000000ff));
        result->pixelData[i] = ((result->pixelData[i] << 8) | ((temp) & 0x000000ff));
        result->pixelData[i] = ((result->pixelData[i] << 8) | ((temp >> 8) & 0x000000ff));
        result->pixelData[i] = ((result->pixelData[i] << 8) | ((temp >> 16) & 0x000000ff));

        *destPixel = ((*destPixel << 8) | ((temp) & 0x000000ff));
        *destPixel = ((*destPixel << 8) | ((temp >> 8) & 0x000000ff));
        *destPixel = ((*destPixel << 8) | ((temp >> 16) & 0x000000ff));
        *destPixel++;
       if (test == 100) break;
    }
 */

    return *result;
}
 
 /***************************************************************************
  * ********************** Load Config and Test boards **********************
  * *************************************************************************/


void FileLoader::loadFileHelper(std::string fileName, fileTypeToLoad type) {
	std::string path = "boards/";
	switch (type)
	{
	case FileLoader::config:
		path += fileName + ".cfg";
		loadConfig(path);
		break;
	case FileLoader::board:
		path += fileName + ".brd";
		loadBoard(path);
		break;
	default:
		break;
	}
}

void FileLoader::loadConfig(std::string path) {

	FileReadInData* configData = readEntireFile(stringToChar(path));
	if (configData->size > 0) {
		//fileIn >> configData->column;
		//fileIn >> configData->rows;
		//fileIn >> configData->numOfMines;

		//TODO (Jon) remove the following:
		/*
		cout << "The column is " << configData->column << endl;
		cout << "The column is " << configData->rows << endl;
		cout << "The column is " << configData->numOfMines << endl;
		*/
	}
	else {
		cout << "ERROR: " << path << " did not open." << endl;
	}
}
/*
void FileLoader::loadBoard(std::string path) {
	fstream fileIn(path);
	std::string buffer;
	if (fileIn.is_open()) {
		while (getline(fileIn, buffer)) {
			testBoardString += buffer;
		}
	}
	else {
		cout << "ERROR: " << path << " did not open." << endl;
	}
	fileIn.close();
}

FileLoader::~FileLoader() {
	delete configData;
}

string FileLoader::getTestBoardString()
{
	return testBoardString;
}

void FileLoader::deleteTestBoardString() {
	testBoardString.clear();
}
*/