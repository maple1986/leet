#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <algorithm>

using namespace std;
class matrix
{
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        if(n <= 1) return;
        reverse(matrix.begin(), matrix.end());
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<i; ++j)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        return;
    }

    /*
    swap(matrix[a][a+i], matrix[a+i][b]);
                swap(matrix[a][a+i], matrix[b][b-i]);
                swap(matrix[a][a+i], matrix[b-i][a]);
    */
    //[[13,9,5,1],[14,10,6,2],[15,7,11,3],[16,12,8,4]]
    void rotate2(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        if(n <= 1) return;
        int left=0, right=n-1, top=0, bot=n-1;
        while(left<right)
        {
            for(int i=0; i<right-left; ++i)
            {
                swap(matrix[top][i+left], matrix[top+i][right]);
                swap(matrix[top][i+left], matrix[bot][right-i]);
                swap(matrix[top][i+left], matrix[bot-i][left]);
            }
            left++;
            right--;
            top++;
            bot--;
        }
        return;
    }

void rotate3(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int a = 0;
        int b = n-1;
        while(a<b){
            for(int i=0;i<(b-a);++i){
                swap(matrix[a][a+i], matrix[a+i][b]);
                swap(matrix[a][a+i], matrix[b][b-i]);
                swap(matrix[a][a+i], matrix[b-i][a]);
            }
            ++a;
            --b;
        }
    }


    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        if(matrix.empty()||matrix[0].empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;
        int top=0, left=0, right=n-1, bot=m-1;
        while(top<bot&&left<right)
        {
            for(int i= left; i<right; ++i)
            {
                res.push_back(matrix[top][i]);
            }
            for(int i= top; i<bot; ++i)
            {
                res.push_back(matrix[i][right]);
            }
            for(int i= right; i>left; --i)
            {
                res.push_back(matrix[bot][i]);
            }
            for(int i= bot; i>top; --i)
            {
                res.push_back(matrix[i][left]);
            }
            left++;
            right--;
            top++;
            bot--;
        }
        if(top == bot) while(left<=right) res.push_back(matrix[top][left++]);
        if(left == right) while(top<=bot) res.push_back(matrix[top++][left]);
        return res;
    }

    vector<vector<int>> generateMatrix(int n) {
        if(n <= 0) return {};
        if(n == 1) return {{1}};
        int top=0, left=0, right=n-1, bot=n-1;
        int x = 1;
        vector<vector<int>> matrix(n, vector<int>(n));
        while(top<bot)
        {
            for(int i= left; i<right; ++i)
            {
                matrix[top][i] = x++;
            }
            for(int i= top; i<bot; ++i)
            {
                matrix[i][right]= x++;
            }
            for(int i= right; i>left; --i)
            {
                matrix[bot][i]=x++;
            }
            for(int i= bot; i>top; --i)
            {
                matrix[i][left]=x++;
            }
            left++;
            right--;
            top++;
            bot--;
        }
        if(top == bot && left == right) matrix[top][left]=x++;
        return matrix;
    }
};

#endif // MATRIX_H
