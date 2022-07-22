/*
    created by pokpoongryu

    FloodFill 

    함수의 재귀호출을 이용한 버전
*/
#include <iostream>
#include <string>

using namespace std;



#define MAX_ROW 6
#define MAX_COL 6

int mGrid[MAX_ROW][MAX_COL];

void ClearGrid();
void DisplayGrid();



void DoFloodFillRecursive(int tCol, int tRow);



int main(int argc, const char * argv[]) {
    
    //flood_fill
    ClearGrid();
    
    
    DisplayGrid();
    
    //OnClickBtnTest
    int tInput = 0;
    cin>>tInput;
    
    DoFloodFillRecursive(1, 1);
    
    DisplayGrid();
    
    
    return 0;
}

//이 함수의 정의는 붙여넣자.
void ClearGrid()
{
    int tRow = 0;
    int tCol = 0;
    for( tRow = 0; tRow <MAX_ROW; tRow++ )
    {
        for( tCol = 0; tCol <MAX_COL; tCol++ )
        {
            mGrid[tRow][tCol] = 0;
        }
    }
    
    
    
    for(int ti = 0; ti<MAX_COL; ti++)
    {
        mGrid[0][ti] = 2;
        
        mGrid[MAX_ROW - 1][ti] = 2;
    }
    
    for(int ti = 0; ti<MAX_ROW; ti++)
    {
        mGrid[ti][0] = 2;
        
        mGrid[ti][MAX_COL - 1] = 2;
    }
    
    
    
    
     for(int ti = 0; ti<MAX_COL; ti++)
     {
         mGrid[2][ti] = 2;
         
         mGrid[MAX_ROW - 1][ti] = 2;
     }
    
}


//flood_fill
//FLOOD FILL 알고리즘을 사용하여 모든 격자를 채움.
void DoFloodFillRecursive(int tCol, int tRow)
{
    //이미 칠한 곳이거나 벽이라면 아무것도 하지 않는다
    if( 1 == mGrid[tRow][tCol] || 2 == mGrid[tRow][tCol] )
    {
        return;
    }
    else
    {
        //칠한다
        mGrid[tRow][tCol] = 1;
        
        //셀에 칠하기 동작을 상하좌우 셀에 대해 수행한다 
        DoFloodFillRecursive( tCol - 1, tRow);
        DoFloodFillRecursive( tCol + 1, tRow);
        DoFloodFillRecursive( tCol, tRow - 1);
        DoFloodFillRecursive( tCol, tRow + 1);
    }
}

//이 함수의 정의는 붙여넣자. sprintf_s
void DisplayGrid()
{
    int tRow = 0;
    int tCol = 0;
    
    
    //display grid
    string tString = "";
    char tszTemp[1024];
    memset( tszTemp, 0, 1024 );
    
    for( tRow = 0; tRow<MAX_ROW; tRow++ )
    {
        for( tCol = 0; tCol<MAX_COL; tCol++ )
        {
            sprintf_s(tszTemp, "%d", mGrid[tRow][tCol]);
            
            tString = tString + tszTemp;
        }
        
        tString = tString + "\n";
    }
    
    cout<<tString;
}


