#include <bits/stdc++.h>
#include <limits.h>
#include <vector>
using namespace std;    
int **dist_arr;
int ROW,COL;

int isValid(int i,int j)//to include edges
{
	if((i<0)||(j<0)||(i>=ROW)||(j>=COL))
		return 0;
	else
		return 1;
}

struct Point
{
    int x;
    int y;
};
 
struct node
{
    Point pt;  
    int distance;  
};
 
int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};
 
int path(vector < vector < int > >& mat ,  Point start, Point Final)
{
    queue<node> q;

    // check source and finalination cell of the matrix have value 1
    if (!mat[start.x][start.y] || !mat[Final.x][Final.y])
        return INT_MAX;
 
    bool arr_visit[ROW][COL];
    memset(arr_visit, false, sizeof arr_visit);//setting all unvisited
     
    arr_visit[start.x][start.y] = true;
     
    node s = {start, 0};//co-ordinate & distance from start
    q.push(s);  

    while (!q.empty())
    {
        node current = q.front();
        Point pt = current.pt;
        q.pop();
 
        if (pt.x == Final.x && pt.y == Final.y)
            return current.distance;
 
        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];
             
            // if adjacent cell is valid, has path and not arr_visit yet, enqueue it.
            if (isValid(row, col) && mat[row][col] && !arr_visit[row][col])//if(5) equivalent to if(1)
            {
                // mar9k cell as arr_visit and enqueue it
                arr_visit[row][col] = true;
                node adjacent = { {row, col},
                                      current.distance + 1 };
                q.push(adjacent);
                dist_arr[row][col] = current.distance +1;

                //cout << 1;
                //system("clear");
                //cout<<row<<" "<<col<<"  ";
            }
        }
    }
 
    //return -1 if destination cannot be reached
    return INT_MAX;
}
 
int main()
{
    scanf("%d",&ROW);
    scanf("%d",&COL);

    vector <vector <int > > mat(ROW);    
    //int dist_arr[ROW][COL];
    dist_arr  = (int **)malloc(sizeof(int *) * ROW);//source
    dist_arr[0] = (int *)malloc(sizeof(int) * COL * ROW);//this dynamic decleration idea from http://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    for(int i = 0; i < ROW; i++)
        dist_arr[i] = (*dist_arr + COL * i);

    
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            dist_arr[i][j]=INT_MAX;
    //dist_arr[0][0] = 0;

    int num;
    for(int i=0;i<ROW;i++)
    for(int j=0;j<COL;j++)
    {
        scanf("%d", &num);
        if(num == 1)
        num = 0;
        else if( num == 0)
        num = 1;
        mat[i].push_back(num);
    }
    
    int x1,x0,y0,y1,c=0;

    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            if(mat[i][j] == 5)
                {x0=i;y0=j;}
            else if(mat[i][j] == 10)
                {x1=i;y1=j;}
            else
                continue;

    dist_arr[x0][y0]=0;
    Point source = {x0, y0};
    Point Final = {x1, y1};
 
    int distance = path(mat, source, Final);
 
    if (distance != INT_MAX)
       c=1;
    
    mat[x1][y1]=10;mat[x0][y0]=5;
    if(c)
    { 
        while(x1!=x0 || y1!=y0)
        for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
        if(i!=j && i!=(-j)  )
        if(isValid((x1+i), (y1+j)))
        if(dist_arr[x1+i][y1+j]-dist_arr[x1][y1] == -1)
            {x1=x1+i;y1=y1+j; mat[x1][y1]=4;}

            for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++) 
            {
                 if(mat[i][j] == 1)
                mat[i][j] =0;
                else if(mat[i][j] == 0)
                mat[i][j] =1;
                else if(mat[i][j]==5 || mat[i][j]==10)
                continue;
                else 
                continue;
            }
        }
        mat[x0][y0]=5;
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++) 

            {
               

                printf("%d  ",mat[i][j]);
            }

            printf("\n");
        }
    }
    return 0;
}
