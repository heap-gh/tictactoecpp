#include <iostream>
#include <string>
#include <array>
#include <time.h>
#include <stdlib.h>
#include <vector>

extern int currentPlayer = 0;

class field;
std::array<field, 9> createField();
std::string returnCurrentPlayerSymbol();
std::string returnCurrentOpponentSymbol();
void printField(std::array<field, 9> matchField);
bool isFieldFree(field field);
int askForUserInput(std::array<field, 9> matchField);
std::string checkWhoWon(std::array<field, 9> matchField);
std::array<std::array<field, 3>, 8> allLines_(std::array<field, 9> matchField);
int checkOpponentWinningMove(std::array<field, 9> matchField);
int checkForWinningMove(std::array<field, 9> matchField);
int computerMoves(std::array<field, 9> matchField);
int makeMove(std::array<field, 9> matchField);
int placeInRandomCorner(std::array<field, 9> matchField);
int isOpponentInCriticalPosition(std::array<field, 9> matchField);
std::vector<std::array<field, 3>> calculateLinesFromSymbol(std::array<field, 9> matchField, int symbolFieldNumber);
std::vector<int> whereDoLinesCross(std::array<field, 9> matchField, std::vector<std::vector<std::array<field, 3>>> lines);
std::vector<int> allSymbolPositions(std::array<field, 9> matchField);
int bestWinningField(std::vector<int> whereLinesCross, std::array<field, 9> matchField);
void clearScreen();
bool isFieldFull(std::array<field, 9> matchField);

class field{ // declares the variables for one field

private:
    std::string value;  // The current symbol, which is on the field
    int number; // the number of the field

public:
    field(){};

    std::string getValue(){ // returns the value of the field
        return this->value;
    }

    void setValue(std::string newValue){ // sets the value of the field
        this->value = newValue;
    }

    int getNumber(){    // returns the number of the field
        return this->number;
    }

    void setNumber(int newNumber){
        this->number = newNumber;
    }

    void printValue(){
        if (this->value == "X"){
            std::cout << "\033[1;31mX\033[0m";
        } else if (this->value == "O"){
            std::cout << "\033[1;32mO\033[0m";
        } else {
            std::cout << getValue();
        }
    }

};

std::array<field, 9> createField(){ // creates the tic tac toe field

    std::array<field, 9> matchField;

    for (int x = 0; x < matchField.size(); x++){
        matchField[x].setValue(std::to_string(x + 1));
        matchField[x].setNumber(x);
    }
    
    return matchField;
}

std::string returnCurrentPlayerSymbol(){ // returns the symbol of the current player

    std::string symbol;

    if (currentPlayer == 0){ return "X";}
    if (currentPlayer == 1){ return "O";}
    if (currentPlayer % 2 == 0) { return "X";} else { return "O";}
    
    return symbol;
}

std::string returnCurrentOpponentSymbol(){ // return the symbol of the currents player opponent

    std::string symbol;

    if (currentPlayer == 0){ return "O";}
    if (currentPlayer == 1){ return "X";}
    if (currentPlayer % 2 == 0) { return "O";} else { return "X";}
    
    return symbol;

}

void printField(std::array<field, 9> matchField){ // prints out the Matchfield in console

    std::cout << "\n";
    std::cout << " "; matchField[0].printValue(); std::cout << " | "; matchField[1].printValue(); std::cout << " | "; matchField[2].printValue(); std::cout << "\n";
    std::cout << "------------ \n";
    std::cout << " "; matchField[3].printValue(); std::cout << " | "; matchField[4].printValue(); std::cout << " | "; matchField[5].printValue(); std::cout << "\n";
    std::cout << "------------ \n";
    std::cout << " "; matchField[6].printValue(); std::cout << " | "; matchField[7].printValue(); std::cout << " | "; matchField[8].printValue(); std::cout << "\n";
    std::cout << "\n";
}

bool isFieldFree(std::array<field, 9> matchField, int x){

    if (matchField[x].getValue() == "X" || matchField[x].getValue() == "O"){
        return false;
    } else {
        return true;
    }
    
}

bool isFieldFree(field field){ // true if the field is asked for free

    if (field.getValue() == "X" || field.getValue() == "O"){
        return false;
    } else {
        return true;
    }

}

int askForUserInput(std::array<field, 9> matchField){ // validates the number of the field the user wants to place on and returns it if its valid

    int userInput;

    std::cout << "\nEnter fieldnumber to place: \n";
    while(true){
        std::cin >> userInput;
        if (isFieldFree(matchField, userInput - 1)){
            return userInput - 1;
        }
        std::cout << "Can not place on field. Enter fieldnumber: \n";
    }
}

std::string checkWhoWon(std::array<field, 9> matchField){ // checks if somebody has won

    bool over = true;

    if (matchField[0].getValue() == matchField[1].getValue() && matchField[0].getValue() == matchField[2].getValue())
    {return matchField[0].getValue();}

    if (matchField[3].getValue() == matchField[4].getValue() && matchField[3].getValue() == matchField[5].getValue())
    {return matchField[3].getValue();}

    if (matchField[6].getValue() == matchField[7].getValue() && matchField[6].getValue() == matchField[8].getValue())
    {return matchField[6].getValue();}
    
    if (matchField[0].getValue() == matchField[4].getValue() && matchField[0].getValue() == matchField[8].getValue())
    {return matchField[0].getValue();}

    if (matchField[2].getValue() == matchField[4].getValue() && matchField[2].getValue() == matchField[6].getValue())
    {return matchField[2].getValue();}

    if (matchField[0].getValue() == matchField[3].getValue() && matchField[0].getValue() == matchField[6].getValue())
    {return matchField[0].getValue();}

    if (matchField[1].getValue() == matchField[4].getValue() && matchField[1].getValue() == matchField[7].getValue())
    {return matchField[1].getValue();}

    if (matchField[2].getValue() == matchField[5].getValue() && matchField[2].getValue() == matchField[8].getValue())
    {return matchField[2].getValue();}

    return "0";
}

std::array<std::array<field, 3>, 8> allLines_(std::array<field, 9> matchField){ // return all lines on the field in an array
//
    std::array<field, 3> row1 = {matchField[0], matchField[1], matchField[2]};
    std::array<field, 3> row2 = {matchField[3], matchField[4], matchField[5]}; // 1 -
    std::array<field, 3> row3 = {matchField[6], matchField[7], matchField[8]};
    std::array<field, 3> column1 = {matchField[0], matchField[3], matchField[6]}; // 3
    std::array<field, 3> column2 = {matchField[1], matchField[4], matchField[7]};
    std::array<field, 3> column3 = {matchField[2], matchField[5], matchField[8]};   
    std::array<field, 3> diagonal1 = {matchField[0], matchField[4], matchField[8]}; // 6
    std::array<field, 3> diagonal2 = {matchField[2], matchField[4], matchField[6]}; // 7

     std::array<std::array<field, 3>, 8> allLines = {row1, row2, row3, column1, column2, column3, diagonal1, diagonal2};

    return allLines;
}

// FROM HERE BEGIN THE COMPUTER METHODS

int checkOpponentWinningMove(std::array<field, 9> matchField){ // the computer checks if his opponent can make a winning move

    int symbolCounter = 0;
    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);
    bool lineHasOwnSymbol;

    for (std::array<field, 3> line : allLines){
        for (field field : line){
            if (field.getValue() == returnCurrentOpponentSymbol()){
                symbolCounter++;
            }
            if (field.getValue() == returnCurrentPlayerSymbol()){
                symbolCounter--;
            }
        }
        if (symbolCounter == 2){
            for (field field : line){
                if (field.getValue() != returnCurrentOpponentSymbol()){
                    return field.getNumber();
                }
            }
        }
        lineHasOwnSymbol;
        symbolCounter = 0;
    }
    return -1;
}

int checkForWinningMove(std::array<field, 9> matchField){ // the computer checks if he can make a winning move

    int symbolCounter = 0;
    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);
    
    for (std::array<field, 3> line : allLines){
        for (field field : line){
            if (field.getValue() == returnCurrentPlayerSymbol()){
                symbolCounter++;
            }
        }
        if (symbolCounter == 2){
            for (field field : line){
                if (field.getValue() != returnCurrentOpponentSymbol() && field.getValue() != returnCurrentPlayerSymbol()){
                    return field.getNumber();
                }
            }
        }
        symbolCounter = 0;
    }
    return -1;
}

int computerMoves(std::array<field, 9> matchField){ // the computer decides which move to make

    if (checkForWinningMove(matchField) != -1){
        return checkForWinningMove(matchField);
    }

    if (checkOpponentWinningMove(matchField) != -1){
        return checkOpponentWinningMove(matchField);
    }

    if (isFieldFull(matchField)){
        clearScreen();
        printField(matchField);
        std::cout << "\nNobody wins!\n"; 
        std::exit(1);
    }

    return makeMove(matchField);
}

bool isFieldFull(std::array<field, 9> matchField){
    
    for (field field : matchField){
        if (field.getValue() != "X" && field.getValue() != "O"){
           
           return false;
        }
    }

    return true;
}

int makeMove(std::array<field, 9> matchField){ // the computer calculates the best move
    
    if (currentPlayer == 0){
        return placeInRandomCorner(matchField);
    }

    if (currentPlayer == 1){
        if (isOpponentInCriticalPosition(matchField) != -1){
            return isOpponentInCriticalPosition(matchField);
        } else {
            return placeInRandomCorner(matchField);
        }

    }

    if (allSymbolPositions(matchField).size() == 1){
        return placeInRandomCorner(matchField);
    }

    std::vector<std::vector<std::array<field, 3>>> allSymbolsLines;

    for (int position : allSymbolPositions(matchField)){
        allSymbolsLines.push_back(calculateLinesFromSymbol(matchField, position));
    }

    return bestWinningField(whereDoLinesCross(matchField, allSymbolsLines), matchField);
}

std::vector<std::array<field, 3>> calculateLinesFromSymbol(std::array<field, 9> matchField, int symbolFieldNumber){ // assign at the top

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);
    std::vector<std::array<field, 3>> symbolsLines; // all lines going away from the symbol

    for (std::array<field, 3> line : allLines){
        for (field field : line){
            if (field.getNumber() == symbolFieldNumber){
                symbolsLines.push_back(line);
            }
        }
    }

    return symbolsLines;
}

bool isLineFreeFromEnemy(std::array<field, 3> line){ // assign at the top

    for (field field : line){
        if (field.getValue() == returnCurrentOpponentSymbol()){
            return false;
        }
    }

    return true;
}

bool isLineFree(std::array<field, 3> line){

    int counter = 0;

    for (field field : line){
        if (field.getValue() == returnCurrentPlayerSymbol() || field.getValue() == returnCurrentOpponentSymbol()){
            counter++;
        }
    }

    if (counter > 1){
        
        return false;
    }

    return true;
}

std::vector<int> whereDoLinesCross(std::array<field, 9> matchField, std::vector<std::vector<std::array<field, 3>>> lines){

    std::vector<int> whereLinesCross;
    bool isAlreadyInside;
    std::vector<std::vector<int>> lineNumbers;

    if (lines.size() > 1){
        for (std::vector<std::array<field, 3>> symbol : lines){ 
                std::vector<int> numbers;
                for (std::array<field, 3> line : symbol){
                    if(isLineFree(line)) {
                        for (field field : line){
                            if (numbers.size() == 0){
                                numbers.push_back(field.getNumber());
                            } else {
                                for (int number : numbers){
                                    if (number == field.getNumber()){
                                        isAlreadyInside = true;
                                    }
                                }
                                if (isAlreadyInside == false){
                                    numbers.push_back(field.getNumber());
                                }
                                isAlreadyInside = false;
                            }
                        }
                    }
                }
                if (!numbers.empty()){
                    lineNumbers.push_back(numbers);
                }
        }
    } else {
        
        return {};
    }

    for (int x = 0; x < lineNumbers.size() - 1; x++){
        for (int y = 0; y < lineNumbers[x].size(); y++){
    for (int a = x + 1; a < lineNumbers.size(); a++){
        for (int b = 0; b < lineNumbers[a].size(); b++){
            if (lineNumbers[x][y] == lineNumbers[a][b] && isFieldFree(matchField, lineNumbers[x][y])){
                whereLinesCross.push_back(lineNumbers[x][y]);
            }
        }
    }
        }
    }

    return whereLinesCross;
}

int placeInRandomCorner(std::array<field, 9> matchField){

    srand(time(NULL));
    int goodStartingPositions[] = {0, 2, 6, 8};

        while (true){
            srand(time(NULL));
            int startingField = rand() % 4;
            if (isFieldFree(matchField[goodStartingPositions[startingField]])){
                return goodStartingPositions[startingField];
            }
        }
    
}

int isOpponentInCriticalPosition(std::array<field, 9> matchField){

    std::array<int, 4> criticalPositions = {0, 2, 6, 8};
    int arr1[] = {1, 3}, arr2[] = {1, 5}, arr3[] = {3, 7}, arr4[] = {5, 7};

    for (int position : criticalPositions){
        if (matchField[position].getValue() == returnCurrentOpponentSymbol()){
            switch(position){
                case 0:
                    srand(time(NULL));
                    return arr1[rand() % 2];
                    break;
                case 2:
                    srand(time(NULL));
                    return arr2[rand() % 2];
                    break;
                case 6:
                    srand(time(NULL));
                    return arr3[rand() % 2];
                    break;
                case 8:
                    srand(time(NULL));
                    return arr4[rand() % 2];
                    break;
                default:
                    break;
            }
        }
    }

    return -1;
}

std::vector<int> allSymbolPositions(std::array<field, 9> matchField){

    std::vector<int> computersSymbols;

    for (field field : matchField){
        if (field.getValue() == returnCurrentPlayerSymbol()){
            computersSymbols.push_back(field.getNumber());
        }
    }

    return computersSymbols;
}

int bestWinningField(std::vector<int> whereLinesCross, std::array<field, 9> matchField){

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);
    std::vector<int> computersSymbols;
    bool isCrossingPointInside;
    bool isComputerSymbolInside;
    std::vector<std::vector<std::array<field, 3>>> potentialWinningSpots; // every crossing point -> every crossing points lines -> every crossing points line field
    computersSymbols = allSymbolPositions(matchField);

    if (whereLinesCross.empty()){
        for (std::array<field, 3> line : allLines){
            for (field field : line){
                if (field.getValue() == returnCurrentPlayerSymbol() && isLineFreeFromEnemy(line)){
                    srand(time(NULL));
                    while (true){
                        for (int x = 0; x < line.size(); x++){
                            if (line[x].getValue() != "X" && line[x].getValue() != "O"){
                                return line[x].getNumber();
                            }
                        }
                    }
                }
            }
        }
    }

    for (int crossingPoint : whereLinesCross){
        std::vector<std::array<field, 3>> crossingPointVectors;
        for (int computerSpots : computersSymbols){
            for (std::array<field, 3> line : allLines){
                for (field field : line){
                    if (field.getNumber() == crossingPoint){
                        isCrossingPointInside = true;
                    }
                    if (field.getNumber() == computerSpots){
                        isComputerSymbolInside = true;
                    }
                }
                if (isCrossingPointInside && isComputerSymbolInside && isLineFreeFromEnemy(line)){
                    crossingPointVectors.push_back(line);
                }
            }
        }
        if (crossingPointVectors.size() > 1){
            return crossingPoint;
        }
    }
}

void clearScreen(){

    for (int x = 0; x < 100 ; x++){
        std::cout << "\n";
    }
}

int main(){

    auto field = createField();
    int start;

    srand(time(NULL));
    start = rand() % 2 + 1;

    while (true){
        if (start == 1){
            printField(field);
        }
        
        if (start % 2 == 0){
            field[computerMoves(field)].setValue(returnCurrentPlayerSymbol());
            clearScreen();
            printField(field);
            if (checkWhoWon(field) != "0"){
                std::cout << checkWhoWon(field) << " WINS!\n";
                printField(field);
                break;
            }
            if (isFieldFull(field)){
                clearScreen();
                printField(field);
                std::cout << "\nNobody wins!\n"; 
                std::exit(1);
            }
            start++;
            currentPlayer++;
        } else {
            field[askForUserInput(field)].setValue(returnCurrentPlayerSymbol());
            if (checkWhoWon(field) != "0"){
                std::cout << checkWhoWon(field) << " WINS!";
                printField(field);
                break;
            }
            if (isFieldFull(field)){
                clearScreen();
                printField(field);
                std::cout << "\nNobody wins!\n"; 
                std::exit(1);
            }
            start++;
            currentPlayer++;
        }
    }
}
