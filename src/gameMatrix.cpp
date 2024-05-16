#include <iostream>
#include <vector>

using namespace std;

class gameMatrix{
    public:
        vector<vector<int>> parking;

        gameMatrix(int rows, int cols){
            parking.resize(rows);
            for(int i = 0; i < rows; i++){
                parking[i].resize(cols);
            }
        }

        void print(){
            for(int i = 0; i < parking.size(); i++){
                for(int j = 0; j < parking[i].size(); j++){
                    cout << parking[i][j] << " ";
                }
                cout << endl;
            }
        }
        
        ~gameMatrix(){};
};