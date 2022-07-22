/*
    created by pokpoongryu

    FloodFill 

    stack 자료구조를 이용한 비재귀호출버전
*/
#include <iostream>
#include <stack>
#include <string>

using namespace std;



#define MAX_ROW 6
#define MAX_COL 6

//STL 이 제공하는 컨테이너 중에서 스택을 이용하였다
typedef stack<int> CIntStack;


CIntStack mIntStack;


int mGrid[MAX_ROW][MAX_COL];






void ClearGrid();
void DisplayGrid();




void DoFloodFill(int tCol, int tRow);


int main(int argc, const char * argv[]) {
    
    //flood_fill
    ClearGrid();
    
    
    DisplayGrid();
    
    //OnClickBtnTest
    int tInput = 0;
    cin>>tInput;
    
    DoFloodFill(1, 1);
    
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



//여기서 스택 자료구조를 이용하는 이유는 무엇인가?
//
/*
    재귀호출 구조에서

    함수를 재귀적으로 호출하여 형성되는 반복구조는
    제어구조의 반복구조로

    함수의 매개변수들은
    스택에 담기는 데이터들로

    교체한 것이다.

    재귀호출 형태로 만들어진 것은
    '제어의 흐름'을 파악하는데 어려움이 크고
    또한 같은 맥락으로
    제어구조의 '형태를 변형'하는데 어려움이 크다.
 */

void DoFloodFill(int tCol, int tRow)
{
    //clear stack
    while( false == mIntStack.empty() )
    {
        mIntStack.pop();
    }
    
    
    mIntStack.push(tCol);
    mIntStack.push(tRow);
    
    
    while( false == mIntStack.empty() )
    {
        //1개를 꺼낸다.
        tRow = mIntStack.top();
        mIntStack.pop();
        
        tCol = mIntStack.top();
        mIntStack.pop();
        
        //이미 다녀간 곳이거나 경계라면 아무것도 하지 않고 다음 것으로 넘어간다.
        if( 1 == mGrid[tRow][tCol] || 2 == mGrid[tRow][tCol] )
        {
            continue;
        }
        
        mGrid[tRow][tCol] = 1;
        
        
        
        
        //4개를 넣는다.
        mIntStack.push(tCol - 1 );
        mIntStack.push(tRow );
        
        mIntStack.push(tCol + 1 );
        mIntStack.push(tRow );
        
        mIntStack.push(tCol );
        mIntStack.push(tRow - 1 );
        
        mIntStack.push(tCol );
        mIntStack.push(tRow + 1 );
        
    }
}






//이 함수의 정의는 붙여넣자.
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

