// C++ program to find Maximum path sum
// start any column in row '0' and ends
// up to any column in row 'n-1'
#include<bits/stdc++.h>
using namespace std;
#define N 4

int MaximumPath(int m[N][N]) {
    int dp[N][N] = {0};
    
//dp[i][j] = maximum path len starting from any 1st rowcell and ending at (i,j)
//dp[i][j] = max(dp[i-1][j], dp[i-1][j-1], dp[i-1][j+1]) + m[i][j]
    for(int i = 0; i < N; i++)
        dp[0][i] = m[0][i];
    
    for(int i = 1; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int x = 0, y = 0, z = 0;
            if(j < N-1)
                x = dp[i-1][j+1];
            if(j > 0)
                y = dp[i-1][j-1];
            z = dp[i-1][j];
            dp[i][j] = m[i][j] + max(x, max(y, z));
        }
    }
    int result = -1;
    for(int i = 0; i < N; i++) {
        if(result < dp[N-1][i])
            result = dp[N-1][i];
    }
    return result;
    // final answer = maximum in all dp[N-1][i] for i in [0, N-1]
}


// driver program to test above function
int main()
{
	int Mat[4][4] = { { 4, 2 , 3 , 4 },
		{ 2 , 9 , 1 , 10},
		{ 15, 1 , 3 , 0 },
		{ 16 ,92, 41, 44 }
	};

	cout << MaximumPath ( Mat ) <<endl ;
	return 0;
}
