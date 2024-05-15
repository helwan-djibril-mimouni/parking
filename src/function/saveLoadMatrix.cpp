#include <fstream>
#include <iostream>
#include <string>

void SaveMatrixToFile(int matrix[32][22])
{
    std::ofstream outFile("data/matrix.txt");

    if (outFile.is_open())
    {
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                outFile << matrix[i][j] << " ";
            }
            outFile << std::endl;
        }
        outFile.close();
    }
}

void LoadMatrixFromFile(int matrix[32][22], std::string fileName = "matrix.txt")
{
    std::ifstream inFile("data/"+fileName);

    if (inFile.is_open())
    {
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 22; j++)
            {
                inFile >> matrix[i][j];
            }
        }
        inFile.close();
        std::cout << "Matrix loaded from file 'matrix.txt'" << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for reading. Initializing matrix..." << std::endl;
    }
}