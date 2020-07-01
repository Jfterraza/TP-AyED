#include <iostream>
#include <fstream>

using namespace std;

string min_production(int matrix[][3], int rows, string namesvec[], int dim_names)
{
    int sum0 = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;
    int sums[6] {sum0, sum1, sum2, sum3, sum4, sum5};
    for (int i = 0; i < rows; ++i)
    {
        int prd = matrix[i][0];
        switch (prd)
        {
        case 0:
            sums[0] += matrix[i][2];
            break;
        case 1:
            sums[1] += matrix[i][2];
            break;
        case 2:
            sums[2] += matrix[i][2];
            break;
        case 3:
            sums[3] += matrix[i][2];
            break;
        case 4:
            sums[4] += matrix[i][2];
            break;
        case 5:
            sums[5] += matrix[i][2];
            break;
        }
    }
    
    int minvalue = sums[0];
    int minindex = 0;
    for (int i = 0; i < 6; ++i){
        if (sums[i] < minvalue){
            minvalue = sums[i];
            minindex = i;
        }
    }
    
    return namesvec[minindex] + " with " + to_string(minvalue) + " units";
}

int main()
{
    ifstream names;
    ifstream prod;
    names.open("names.txt");
    prod.open("production.txt");
    int aux;
    int rows = 75;
    int col = 3;
    int products_matrix[rows][3];

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            prod >> aux;
            products_matrix[i][j] = aux;
        }
        cout << endl;
    }
    int dim_names = 6;
    int dim_colors = 3;
    string namesvec[dim_names];
    string colorsvec[dim_colors];
    string auxword;
    //rellena el nombre
    for (int i = 0; i < dim_names; ++i)
    {
        names >> auxword;
        namesvec[i] = auxword;
    }
    //rellena colores
    for (int i = 0; i < dim_colors; ++i)
    {
        names >> auxword;
        colorsvec[i] = auxword;
    }
    // // checkeo de vectores
    // for (int i = 0; i < dim_names; ++i)
    // {
    //     cout << namesvec[i] << endl;
    // }
    // cout << "-----------------------" << endl;
    // for (int i = 0; i < dim_colors; ++i)
    // {
    //     cout << colorsvec[i] << endl;
    // }
    // //checkeo de la matriz
    // cout << "-----------------------" << endl;
    // for (int i = 0; i < rows; ++i)
    // {
    //     for (int j = 0; j < col; ++j)
    //     {
    //         cout << products_matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << min_production(products_matrix, rows, namesvec, dim_names) << endl;
    return 0;
}
