
int intAdd(int* listOfNumbers, int size) {
    int result = 0;
    for (int i = 0; i < size; i++){
        result += listOfNumbers[i];
    }
    return result;
}