#include <iostream>
#include <cassert>
#include <fstream>

#define CATALOGUE_FILE "catalogue.data"
#define PRODUCTION_FILE "production.data"

#define PRODUCTS    6
#define COLOURS     3
#define COLS        COLOURS

#define ERROR -1
//#define NDEBUG 1

using namespace std;

int
catalogue_read(string file_name, string buff[], unsigned const int size)
{
    assert(buff);

    ifstream file;

    file.open(file_name);

    if(!file.is_open()) {
        return ERROR;
    }

    for(unsigned int i = 0; i < size; i++) {
        file >> buff[i];
    }

    file.close();
    return 0;
}

int
catalogue_create(string products_and_colours[], unsigned const int size,
        unsigned const int products, unsigned const int colours,
        string catalogue[][COLOURS])
{
    assert(catalogue);
    assert(products_and_colours);

    if (size > (colours + products)) {
        return ERROR;
    }

    for(unsigned int i = 0; i < (products + colours); i++) {
        if(i < products) {
            for(unsigned int j = 0; j < colours; j++)
                catalogue[i][j] = products_and_colours[i];
        } else {
            for(unsigned int j = 0; j < products; j++)
                (catalogue[j][i-products] += " ") += products_and_colours[i];
        }
    }

    return 0;
}

void
matrix_clear(int matrix[][COLS], unsigned const int rows)
{
    for(unsigned int i = 0; i < rows; i++)
        for(unsigned int j = 0; j < COLS; j++)
            matrix[i][j] = 0;
}

int
production_read(string file_name, int production[][COLOURS], unsigned const int products)
{
    assert(production);

    ifstream file;

    file.open(file_name);

    if(!file.is_open()) {
        return ERROR;
    }

    matrix_clear(production, products);

    int a, b, n;

    file >> a;
    while(!file.eof()) {
        file >> b;

        file >> n;
        production[a][b] += n;

        file >> a;
    }

    file.close();
    return 0;
}

string
min_production(int production[][COLOURS], string catalogue[][COLOURS],
        unsigned const int products, unsigned const int colours)
{
    int min_x = 0;
    int min_y = 0;

    int min_value = production[min_x][min_y];

    for(unsigned int i = 0; i < products; i++) {
        for(unsigned int j = 0; j < colours; j++) {
            if (production[i][j] < min_value) {
                min_value = production[i][j];
                min_x = i;
                min_y = j;
            }
        }
    }

    return catalogue[min_x][min_y] + " with " + to_string(min_value) + " units.";
}

int main()
{
    /* CATALOGUE */
    string products_and_colours[PRODUCTS + COLOURS];

    if (catalogue_read(CATALOGUE_FILE, products_and_colours, PRODUCTS + COLOURS)) {
        cout << "failed to read " << CATALOGUE_FILE << "." << endl;
        return ERROR;
    }

    string catalogue[PRODUCTS][COLOURS];

    if (catalogue_create(products_and_colours, PRODUCTS + COLOURS, PRODUCTS, COLOURS, catalogue)) {
        cout << "failed to create catalogue." << endl;
        return ERROR;
    }

    /* PRODUCTION DATA */
    int production[PRODUCTS][COLOURS];

    if (production_read(PRODUCTION_FILE, production, PRODUCTS)) {
        cout << "failed to read " << CATALOGUE_FILE << "." << endl;
        return ERROR;
    }

    /* DATA ANALYSIS */
    cout << "Product with the least units per lot: "
         << min_production(production, catalogue, PRODUCTS, COLOURS) << endl;

    return 0;
}
