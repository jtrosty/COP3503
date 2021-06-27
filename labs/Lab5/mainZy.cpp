#include <iostream>
#include <fstream>
using namespace std;

void readSpaceShipFileBinary(ifstream& binaryData) {
    int numOfSpaceships;
    binaryData.read((char*)&numOfSpaceships, sizeof(int));
    cout << "# of spaceships: " << numOfSpaceships << endl;
    char* nameOfShip;
    char* classOfShip;

    for (int i = 0; i < 1; i++) {
        int lengthOfName;
        binaryData.read((char*)&lengthOfName, sizeof(int));
        nameOfShip = new char[lengthOfName];
        binaryData.read(nameOfShip, lengthOfName);

        cout << "lenght of name " << lengthOfName << endl;
        cout << "Name of 1st Ship; " << nameOfShip << endl;

        binaryData.read((char*)&lengthOfName, sizeof(int));
        classOfShip = new char[lengthOfName];
        binaryData.read(classOfShip, lengthOfName);

        cout << "lenght of class " << lengthOfName << endl;
        cout << "Name of class " << classOfShip << endl;
    }
}

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;
    ifstream binaryInput;

    switch (option) {
        case 1:
            binaryInput.open("friendlyships.shp", ios_base::in);
            readSpaceShipFileBinary(binaryInput);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }

   /* Load files here */

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
	
   return 0;
}