#include <string>
#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

void display(vector<string> grid){
    for (size_t i = 0; i < grid.size(); i++){
        cout << grid[i] << endl;
    }
}

vector<string> initialize(ifstream& file){
    string line;
    vector<string> grid;

    if (!file){
        cerr << "File not found" << endl;
        exit(1);
    }

    while (getline(file,line)){
        grid.push_back(line);
    }
    return grid;
}

char compute(vector<string> grid, int i, int k){ //size_t -> int cause size_t is only positive nums
    int num = 0;
    char curr_char = grid[i][k];
    int x = -1; //moore's algorithmn    
    while (x <= 1){
        int y = -1;
        while (y <= 1){
            if (i + x >= 0 && k + y >= 0 && i + x < grid.size() && k + y < grid[0].size()){ //checking to make sure if it's not out of bounds
                if (grid[i+x][k+y] == '*'){
                    if (x != 0 || y != 0){ //makes sure that it's not a copy of itself 
                        num += 1;
                    }
                }
            }
            y++;
        }
        x++;
    }

    if (curr_char == '-'){ //dead -> alive
        if (num == 3){
            curr_char = '*';
        }
    }
    else{
        if (num < 2 || num > 3){ //alive -> dead
            curr_char = '-';
        }
    }
    return curr_char;
}

void traverse(vector<string>& grid,vector<string> gridcopy){
    for (size_t i = 0; i < grid.size(); i++){
        for (size_t k = 0; k < grid[i].size(); k++){
            grid[i][k] = compute(gridcopy,i,k);
        }
    }
}


int main(){
    ifstream file("life.txt");
    vector<string> grid = initialize(file);
    vector<string> gridcopy = grid;

    int generation = 1;

    cout << "Initailize World" << endl;
    display(grid);
    cout << "===========================" << endl;

    while (generation <= 10){
        cout << "Generation: " << generation << endl;
        traverse(grid,gridcopy);
        display(grid);
        gridcopy = grid;
        cout << "====================" << endl;
        generation++;
    }
}