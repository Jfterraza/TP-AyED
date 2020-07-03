#include <iostream>
#include <cassert>
#include <fstream>

#define CATALOGUE_FILE "catalogue.txt"
#define PRODUCTION_FILE "production.txt"

#define PRODUCTS 6
#define COLOURS 3
#define COLS COLOURS

#define ERROR -1
//#define NDEBUG 1

using namespace std;

int catalogue_read(string file_name, string buff[], unsigned const int size)
{
    assert(buff);

    ifstream file;

    file.open(file_name);

    if (!file.is_open())
    {
        return ERROR;
    }

    for (unsigned int i = 0; i < size; i++)
    {
        file >> buff[i];
    }

    file.close();
    return 0;
}

int catalogue_create(string products_and_colours[], unsigned const int size,
                     unsigned const int products, unsigned const int colours,
                     string catalogue[][COLOURS])
{
    assert(catalogue);
    assert(products_and_colours);

    if (size > (colours + products))
    {
        return ERROR;
    }

    for (unsigned int i = 0; i < (products + colours); i++)
    {
        if (i < products)
        {
            for (unsigned int j = 0; j < colours; j++)
                catalogue[i][j] = products_and_colours[i];
        }
        else
        {
            for (unsigned int j = 0; j < products; j++)
                (catalogue[j][i - products] += " ") += products_and_colours[i];
        }
    }

    return 0;
}

void matrix2D_clear(int matrix[][COLS], unsigned const int rows)
{
    assert(matrix);

    for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < COLS; j++)
            matrix[i][j] = 0;
}

int production_read(string file_name, int production[][COLOURS],
                    int production_batch[][COLOURS], unsigned const int products)
{
    assert(production);
    assert(production_batch);

    ifstream file;

    file.open(file_name);

    if (!file.is_open())
    {
        return ERROR;
    }

    matrix2D_clear(production, products);
    matrix2D_clear(production_batch, products);

    int a, b, n;

    file >> a;
    while (!file.eof())
    {
        if (!(file >> b))
            break;

        if (!(file >> n))
            break;

        production[a][b] += n;
        production_batch[a][b]++;

        file >> a;
    }

    file.close();
    return 0;
}

string min_production(int production[][COLOURS], string catalogue[][COLOURS],
                      unsigned const int products, unsigned const int colours)
{
    assert(production);
    assert(catalogue);

    int sum[products]{0};

    for (unsigned int i = 0; i < products; i++)
        for (unsigned int j = 0; j < colours; j++)
            sum[i] += production[i][j];

    int min_value = sum[0];
    int min_index = 0;

    for (unsigned int i = 0; i < products; i++)
    {
        if (sum[i] < min_value)
        {
            min_value = sum[i];
            min_index = i;
        }
    }

    string product_name = catalogue[min_index][0];
    int fromwhitespaceto = product_name.find(" ");
    product_name.erase(fromwhitespaceto, product_name.length());

    return product_name + " with " + to_string(min_value) + " units.";
}

string max_productionmean(int production[][COLOURS],
                          int production_batch[][COLOURS], string catalogue[][COLOURS],
                          unsigned const int products, unsigned const int colours)
{
    assert(catalogue);
    assert(production);
    assert(production_batch);

    int maxmean = production[0][0] / production_batch[0][0];
    int maxmean_x = 0;
    int maxmean_y = 0;

    for (unsigned int i = 0; i < products; i++)
    {
        for (unsigned int j = 0; j < colours; j++)
        {
            int mean = production[i][j] / production_batch[i][j];
            if (maxmean < mean)
            {
                maxmean = mean;
                maxmean_x = i;
                maxmean_y = j;
            }
        }
    }

    return catalogue[maxmean_x][maxmean_y] + " with a mean of " + to_string(maxmean) + " units per batch.";
}

int main(void)
{
    /* CATALOGUE */
    string products_and_colours[PRODUCTS + COLOURS];

    if (catalogue_read(CATALOGUE_FILE, products_and_colours, PRODUCTS + COLOURS))
    {
        cout << "failed to read " << CATALOGUE_FILE << "." << endl;
        return ERROR;
    }

    string catalogue[PRODUCTS][COLOURS];

    if (catalogue_create(products_and_colours, PRODUCTS + COLOURS, PRODUCTS, COLOURS, catalogue))
    {
        cout << "failed to create catalogue." << endl;
        return ERROR;
    }

    /* PRODUCTION DATA */
    int production[PRODUCTS][COLOURS];
    int production_batch[PRODUCTS][COLOURS];

    if (production_read(PRODUCTION_FILE, production, production_batch, PRODUCTS))
    {
        cout << "failed to read " << CATALOGUE_FILE << "." << endl;
        return ERROR;
    }

    /* DATA ANALYSIS */
    cout << "Product with the least units per lot: "
         << min_production(production, catalogue, PRODUCTS, COLOURS)
         << endl;

    cout << "Product with the most units per batch: "
         << max_productionmean(production, production_batch, catalogue,
                               PRODUCTS, COLOURS)
         << endl;

    return 0;
}
