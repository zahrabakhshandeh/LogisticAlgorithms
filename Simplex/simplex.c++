#include <iostream>
#include <vector>

using namespace std;

class Simplex {
private:
    vector<vector<double>> table;
    int m, n;

    void printTable(){
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n ; ++j){
                cout << setw(10) << table[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getPivotCol(){
        int col = -1;
        double minValue = 0;

        for(int i = 0; i < n-1 ; ++i){
            // table[m-1][i]
            if (table[m-1][i] < minValue){
                minValue = table[m-1][i];
                col = i;
            }

        }
        return col;
    }

    int getPivotRow(int col){
        int row = -1; 
        double minRate = INT_MAX;
        for (int i=0; i < m - 1 ; ++i){
            if(table[i][col] > 0){
                double ratio = table[i][n-1] / table[i][col];
                if(ratio < minRate){
                    minRate = ratio;
                    row = i;
                }
            }
        }
        return row;
    }

    void pivot(int row, int col){
        double item = table[row][col];
        for(int i = 0; i < n ; ++i){
            table[row][i] /= item;
        }

        for(int i = 0; i < m; ++i){
            if(i != row){
                double factor = table[i][col];
                for(int j =0; j < n; ++j){
                    table[i][j] -= factor * table[row][j];
                }
            }
        }
    }

}

int main(){
    // Define : (Z = 3X1 + 2X2)
    // X1 + 2X2 <= 8
    // 2X1 + X2 <= 8
    vector<vector<double>> table = {
        {1, 2, 1, 0, 8},
        {2, 1, 0, 1, 8},
        {-3, -2, 0, 0, 0}
    }

    // methods
    
}