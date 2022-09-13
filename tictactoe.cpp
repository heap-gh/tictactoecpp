#include <iostream>
#include <string>
#include <array>
#include <time.h>
#include <stdlib.h>
#include <vector>

// Every Object of this class represents one field on the tictactoe playboard

extern int currentPlayer = 0;
extern int startingPoint = 0;

class field;
std::array<field, 9> createField();
bool hasLineTwoSymbols(std::array<field, 9> matchField, int x);
void printField(std::array<field, 9> matchField);
std::array<field, 9> changeFieldValue(std::array<field, 9> matchField);
bool checkIfWon(std::array<field, 9> matchField);
void CheckWinner(bool b, std::array<field, 9> matchField);
std::string opponentSymbol();
std::array<std::array<field, 3>, 8> allLines_(std::array<field, 9> matchField);
int checkOpponent(std::array<field, 9> matchField);
std::array<field,9> computerMoves(std::array<field, 9> matchField);
bool isAgainstComputer();
bool isFieldFree(field field);
int isLineFreeMakeMove(std::array <field, 9> matchField);
bool isLineFree(std::array<field, 9> matchField, int lineNumber);
int makeWinningMove(std::array<field, 9> matchField);
bool isLineFreeFromOpponent(std::array<field, 9> matchField, std::array<field, 3> line);
std::vector<int> whereDoLinesCross(std::array<field, 9> matchField, std::vector<int> ownSymbols);


class field{

private:
    std::string value;
    int number;

public:
    field(){

    }
    
    field(int _number){

        this->number = _number;
        this->value = std::to_string(_number);
    }
    
    std::string getValue(){

        return this->value;
    }

    void setValue(std::string newValue){

        this->value = newValue;
    }

    int getNumber(){

        return this->number;
    }

};

std::array<field, 9> createField(){

    std::array<field , 9> matchField;

    for (int x = 0; x < matchField.size(); x++){

        matchField[x] = field(x + 1);
    }

    return matchField;
}

void printField(std::array<field, 9> matchField){

    std::cout << " " << matchField[0].getValue() << " | " << matchField[1].getValue() << " | " << matchField[2].getValue() << "\n";
    std::cout << "------------ \n";
    std::cout << " " << matchField[3].getValue() << " | " << matchField[4].getValue() << " | " << matchField[5].getValue() << "\n";
    std::cout << "------------ \n";
    std::cout << " " << matchField[6].getValue() << " | " << matchField[7].getValue() << " | " << matchField[8].getValue() << "\n";
}

std::array<field, 9> changeFieldValue(std::array<field, 9> matchField){

    std::string currentSymbol;

    if (currentPlayer == 0) { currentSymbol = "X";}
    if (currentPlayer == 1) { currentSymbol = "O";}
    if ((currentPlayer % 2) == 0){ currentSymbol = "X";} else { currentSymbol = "O";}
    
    int x; // Value on which field the symbol shall be set
    bool isPlaceFree = false;

    while (isPlaceFree == false){

        std::cout << "Enter number of the field to place symbol: \n";
        std::cin >> x;

        bool isValidInput = true;

        if (x == 0 || x > 9) { std::cout << "Cant accept 0 or >9 as input \n"; } else {        

            if (matchField[x - 1].getValue() == "X" || matchField[x - 1].getValue() == "O"){

                std::cout << "A symbol is already placed on this field \n";
            
            } else {

                matchField[x - 1].setValue(currentSymbol);
                isPlaceFree = true;
            
            }

        }
        
    }

    isPlaceFree = false;
    currentPlayer++;

    return matchField;
}

bool checkIfWon(std::array<field, 9> matchField){

    if (matchField[0].getValue() == matchField[1].getValue() && matchField[0].getValue() == matchField[2].getValue()){

        return true;
    }

    if (matchField[3].getValue() == matchField[4].getValue() && matchField[3].getValue() == matchField[5].getValue()){

        return true;
    }

    if (matchField[6].getValue() == matchField[7].getValue() && matchField[6].getValue() == matchField[8].getValue()){

        return true;
    }

    if (matchField[0].getValue() == matchField[4].getValue() && matchField[0].getValue() == matchField[8].getValue()){

        return true;
    }

    if (matchField[2].getValue() == matchField[4].getValue() && matchField[2].getValue() == matchField[6].getValue()){

        return true;
    }

    if (matchField[0].getValue() == matchField[3].getValue() && matchField[0].getValue() == matchField[6].getValue()){

        return true;
    }

    if (matchField[1].getValue() == matchField[4].getValue() && matchField[1].getValue() == matchField[7].getValue()){

        return true;
    }

    if (matchField[2].getValue() == matchField[5].getValue() && matchField[2].getValue() == matchField[8].getValue()){

        return true;
    }

    return false;
}

void CheckWinner(bool b, std::array<field, 9> matchField){

    if (currentPlayer == 9){

    std::cout << "Nobody won!";
    std::exit(0);
    
    }

    if (b == true){

    std::string currentSymbol;

    if (currentPlayer == 0) { currentSymbol = "O";}
    if (currentPlayer == 1) { currentSymbol = "X";}
    if ((currentPlayer % 2) == 0){ currentSymbol = "O";} else { currentSymbol = "X";}

    printField(matchField);

    std::cout << currentSymbol << " WINS!";
    
    std::exit(0);
    
    }
    
}

std::string opponentSymbol(){ // Call this method when its the one who is asking for OpponentSymbol has his turn

    std::string currentSymbol;

    if (currentPlayer == 0) { currentSymbol = "O";}
    if (currentPlayer == 1) { currentSymbol = "X";}
    if ((currentPlayer % 2) == 0){ currentSymbol = "O";} else { currentSymbol = "X";}

    if (currentSymbol == "X"){

        return "O";
    
    } else{

        return "X";
    }

}

std::array<std::array<field, 3>, 8> allLines_(std::array<field, 9> matchField){

    std::array<field, 3> row1 = {matchField[1], matchField[2], matchField[3]};
    std::array<field, 3> row2 = {matchField[4], matchField[5], matchField[6]};
    std::array<field, 3> row3 = {matchField[7], matchField[8], matchField[9]};
    std::array<field, 3> column1 = {matchField[1], matchField[4], matchField[7]};
    std::array<field, 3> column2 = {matchField[2], matchField[5], matchField[8]};
    std::array<field, 3> column3 = {matchField[3], matchField[6], matchField[9]};
    std::array<field, 3> diagonal1 = {matchField[1], matchField[4], matchField[9]};
    std::array<field, 3> diagonal2 = {matchField[3], matchField[4], matchField[7]};

     std::array<std::array<field, 3>, 8> allLines = {row1, row2, row3, column1, column2, column3, diagonal1, diagonal2};

    return allLines;
}

int checkOpponent(std::array<field, 9> matchField){
    
    int opponentCouldPlaceHere;
    int x;

    std::string currentSymbol;

    if (currentPlayer == 0) { currentSymbol = "O";}
    if (currentPlayer == 1) { currentSymbol = "X";}
    if ((currentPlayer % 2) == 0){ currentSymbol = "O";} else { currentSymbol = "X";}

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);

    for (x = 0; x < allLines.size(); x++){
        if (hasLineTwoSymbols(matchField, x) == true){
            for (int y = 0; y < allLines[x].size(); y++){
                    if (allLines[x][y].getValue() != "X" && allLines[x][y].getValue() != "O"){
                        return allLines[x][y].getNumber(); // means true (opponent can place on this position and win)
                    }
                }
            }
        }
    
    return 0; // means false (opponent can not place anywhere on board and win)
}

bool hasLineTwoSymbols(std::array<field, 9> matchField, int x){

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);

    int counter = 0;

    for (int z = 0; z < allLines[x].size(); z++){
        if (allLines[x][z].getValue() == opponentSymbol()){

            counter += 1;
        }
    }

    if (counter == 2) {

        return true;
    }

    return false;
}

bool isFieldFree(field field){

    if (field.getValue() != "X" && field.getValue() != "O"){

        return true;
    }

    return false;

}

std::array<field,9> computerMoves(std::array<field, 9> matchField){

    std::string currentSymbol;
    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);
    std::array<int, 4> startingFields = {1, 3, 7, 9};

    if (currentPlayer == 0) { currentSymbol = "O";}
    if (currentPlayer == 1) { currentSymbol = "X";}
    if ((currentPlayer % 2) == 0) { currentSymbol = "O";} else { currentSymbol = "X";}

    srand(time(NULL));

    if (currentPlayer == 0){

        int chooseSlot = rand() % 4 + 1;
        startingPoint = startingFields[chooseSlot - 1];
        matchField[startingPoint].setValue(currentSymbol);
        
    } else {
        
        if (checkOpponent(matchField) != 0){ // If enemy Player can win in the next move (2 symbols in winning position)

            matchField[checkOpponent(matchField)].setValue(currentSymbol); // sets his marker in the spot where enemy could have won
            currentPlayer++;

        } else {

            if (currentPlayer == 1){
            
                srand(time(NULL));

                bool canPlace = false;
                bool one, two, three, four;

                while (canPlace == false){
                    
                    int random = rand() % 4 + 1;
                    int firstMove = startingFields[random - 1];

                    if (isFieldFree(matchField[firstMove]) == true){

                        matchField[firstMove].setValue(currentSymbol);
                        canPlace = true;
                        currentPlayer++;
                    
                    } else {

                        switch(firstMove){

                            case 1:
                                one = true;
                                break;
                            
                            case 2:
                                two = true;
                                break;

                            case 3:
                                three = true;
                                break;

                            case 4:
                                four = true;
                                break;

                        }
                    }
                
                    if (one == true && two == true && three == true && four == true){

                        break;
                    }

                }            
            
            } else {
                
                
                

            }
        }

    }

    return matchField;
}

int isLineFreeMakeMove(std::array <field, 9> matchField){

    std::string currentSymbol;
    std::vector<int> ownSymbols; // Field where own symbol is on
    std::vector<std::array<field, 3>> validLine; // All lines where the field from ownSymbols is a part of
    std::vector<std::vector<std::array<field, 3>>> allValidLines;

    if (currentPlayer == 0) { currentSymbol = "O";}
    if (currentPlayer == 1) { currentSymbol = "X";}
    if ((currentPlayer % 2) == 0) { currentSymbol = "O";} else { currentSymbol = "X";}

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);

    //save all fields where own marker is placed in vector "ownSymbols"
    for (int x = 0; x < allLines.size(); x++){
        for (int y = 0; y < allLines[x].size(); y++){
            if (allLines[x][y].getValue() == currentSymbol){

                ownSymbols.push_back(allLines[x][y].getNumber());
            }
        }
    }

    for (int fieldNumber : ownSymbols){ // for every fieldnumber where the symbol of the computer is stored
        std::vector<std::array<field, 3>> validLine; // create a new vector where all valid lines should be stored for the current field number
        for (int x = 0; x < allLines.size(); x++){   // iterate through the array where all lines are present
            for (int y = 0; y < allLines[x].size(); y++){   // iterate through the line

                if (allLines[x][y].getNumber() == fieldNumber && isLineFree(matchField, x)){ // when the field number is present in this line and the line is free of enemy symbol and own symbol. int x stands for the number of the line in the array allLines and should be passed so the function can check that exact line
                    validLine.push_back(allLines[x]);   // add it to the valid line vector (because the line is valid and could be potential win)
                }
            
            }
        }
        allValidLines.push_back(validLine); // all valid lines combined in a vector
    }

    if (ownSymbols.size() == 1){

        std::vector <int> goodFieldsCanPlace;
        std::array <int, 4> goodFields = {1, 3, 7, 9};
        for (std::vector<std::array<field, 3>> validLine : allValidLines){
            for (std::array<field, 3> line : validLine){
                for (field field : line){
                    switch(field.getNumber()){

                        case 1:
                            goodFieldsCanPlace.push_back(1);
                            break;
                        
                        case 3:
                            goodFieldsCanPlace.push_back(3);
                            break;

                        case 7:
                            goodFieldsCanPlace.push_back(7);
                            break;

                        case 9:
                            goodFieldsCanPlace.push_back(9);
                            break;
                        
                        default:
                            break;
                    }
                }
            }
        }

        srand(time(NULL));

        int decision = rand() % goodFieldsCanPlace.size() + 1;
        return decision;
        
    } else {

        return 0;
    }
    
}

std::vector<int> whereDoLinesCross(std::array<field, 9> matchField, std::vector<int> ownSymbols){

    std::vector<std::vector<std::array<field, 3>>> allsymbolLines; // a vector for every symbols lines
    std::vector<int> whereDoLinesCross;
    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);

    for (int symbol : ownSymbols){ // for every symbol on the matchField (only computers symbols)
        std::vector<std::array<field, 3>> symbolLines; // make a new vector to save every line the symbol is in
        for (std::array<field, 3> line : allLines){ // for every line in the array allLines
            for (field matchfield : line){  // for every field number in the line
                if (matchfield.getNumber() == symbol){  // check if the number of the symbol is in the line
                    symbolLines.push_back(line);    // save the line in symbollines
                }
            }
        }
        allsymbolLines.push_back(symbolLines);
    }

    for (int i = 0; i < allsymbolLines.size() - 1; i++){
        for (int j = 0; j < allsymbolLines[i].size(); j++){
            for (int k = 0; k < allsymbolLines[i][j].size(); k++){
        for (int a = i + 1; a < allsymbolLines.size(); a++){
            for (int b = 0; b < allsymbolLines[a].size(); b++){
                for (int c = 0; c < allsymbolLines[a][b].size(); c++){
                    if (allsymbolLines[i][j][k].getNumber() == allsymbolLines[a][b][c].getNumber() && isLineFreeFromOpponent(matchField, allsymbolLines[a][b])){

                                whereDoLinesCross.push_back(allsymbolLines[i][j][k].getNumber());
                            }
                        }
                    }
                }  
            }
        }
    }

    return whereDoLinesCross;
}

bool isLineFreeFromOpponent(std::array<field, 9> matchField, std::array<field, 3> line){

    std::string currentSymbol;
    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);

    if (currentPlayer == 0) { currentSymbol = "X";}
    if (currentPlayer == 1) { currentSymbol = "O";}
    if ((currentPlayer % 2) == 0){ currentSymbol = "X";} else { currentSymbol = "O";} 

    for (field field : line){

        if (field.getValue() == opponentSymbol()){

            return false;
        }
    }

    return true;
}

bool isLineFree(std::array<field, 9> matchField, int lineNumber){

    std::string currentSymbol;

    if (currentPlayer == 0) { currentSymbol = "X";}
    if (currentPlayer == 1) { currentSymbol = "O";}
    if ((currentPlayer % 2) == 0){ currentSymbol = "X";} else { currentSymbol = "O";}

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField); 

    for (int y = 0; y < allLines[lineNumber].size(); y++){

        if (allLines[lineNumber][y].getValue() == opponentSymbol() || allLines[lineNumber][y].getValue() == currentSymbol){

            return false;
        }
    }

    return true;
}

int makeWinningMove(std::array<field, 9> matchField){ // function must be called before isLineFree()

    int counter = 0;
    std::string currentSymbol;

    if (currentPlayer == 0) { currentSymbol = "O";}
    if (currentPlayer == 1) { currentSymbol = "X";}
    if ((currentPlayer % 2) == 0) { currentSymbol = "O";} else { currentSymbol = "X";}

    std::array<std::array<field, 3>, 8> allLines = allLines_(matchField);

    for (std::array<field, 3> line : allLines){
        counter = 0;
        for (field field : line){
            
            if (field.getValue() == currentSymbol){
                
                counter++;
            }
            if (field.getValue() == opponentSymbol()){
                
                counter--;
            }
        
        if (counter == 2){
            
            for (int x = 0; x < line.size(); x++){
                
                if (line[x].getValue() != "X" && line[x].getValue() != "O"){ // if field has not own symbol and opponent symbol as its value

                    return line[x].getNumber();
                }
            }
        }
        }
    }

    return 0;
}

//int makemove() --- calculate best move (see picture on desktop)

bool isAgainstComputer(){

    int decision;
    bool isValidInput = false;
    
    std::cout << "1 - Play against computer \n";
    std::cout << "2 - Play against human \n";

    while (isValidInput == false){

        std::cin >> decision;

        if (decision != 1 && decision != 2){

            std::cout << "Please enter 1 or 2 \n";
    
        } else {

            isValidInput = true;
        }
    }

    if (decision == 1) {

        return true;
        
    } 

    return false;
           
}

int main(){

    if (isAgainstComputer() == false){
    
        auto theField = createField();
        
        while (true){
        
        printField(theField);
        theField = changeFieldValue(theField);
        CheckWinner(checkIfWon(theField), theField);

        }
    
    } else {

        
    }

}