#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream names;
    ifstream prod;
    names.open("names.txt");
    prod.open("production.txt");
    string aux;
    int rows = 75;
    int col = 3;
    string products_matrix [rows][col];
    
     for (int i = 0; i < rows; ++i){
        for (int j = 0; j < col; ++j){
            prod >> aux;
            products_matrix[i][j] = aux;
        }
        cout << endl;
    }


    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < col; ++j){
            cout << products_matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
