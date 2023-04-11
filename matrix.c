#include <stdio.h>
#include <stdlib.h>

int A_row, A_column;
int B_row, B_column; 
int M_row, M_column;//행렬 크기를 수월히 처리하기 위해 전역변수로 선언.

int ** make_matrix(int, int);
void print_matrix(int *[], int , int);
int ** addition_matrix(int *[], int *[]);
int ** subtraction_matrix(int *[], int *[]);
int ** transpose_matrix(int *[], int, int);
int ** multiply_matrix(int *[], int *[]);
void free_matrix(int *[], int);

int main()
{
    printf("[------ [최 현 철]  [2022078014] ------]\n\n");
    printf("행렬 A의 크기를 입력하시오(mxn) : ");
    scanf("%d %d", &A_row, &A_column); //A의 행,열의 값을 입력받는다.
    int ** A = make_matrix(A_row, A_column);    //make_matrix 함수를 호출하여 2차원 배열 A를 만든다.
    for(int i = 0; i < A_row; i++) //이중 for문을 이용하여 각 요소의 값을 입력받는다.
    {
        for(int j = 0; j < A_column; j++)
        {
            printf("행렬의 [%d][%d]값 입력 : ", i+1, j+1);
            scanf("%d", &A[i][j]);
        }
    }
    
    
    printf("행렬 B의 크기를 입력하시오(mxn) : ");
    scanf("%d %d", &B_row, &B_column);
    int ** B = make_matrix(B_row, B_column);    //make_matrix 함수를 호출하여 2차원 배열 B를 만든다.
    for(int i = 0; i < B_row; i++) //이중 for문을 이용하여 각 요소의 값을 입력받는다.
    {
        for(int j = 0; j < B_column; j++)
        {
            printf("행렬의 [%d][%d]값 입력 : ", i+1, j+1);
            scanf("%d", &B[i][j]);
        }
    }
    printf("print A\n");
    print_matrix(A, A_row, A_column);  
    printf("print B\n");
    print_matrix(B, B_row, B_column);   //행렬 A,B를 출력한다.

    int ** matrix;  //결과값을 저장할 이중포인터 matrix선언.

    printf("A+B\n");
    matrix = addition_matrix(A, B);
    print_matrix(matrix, M_row, M_column);
    free_matrix(matrix, M_row); //addition_matrix함수를 호출하여 A+B의 결과값을 matrix에 입력받은 후 matrix출력 후 free_matrix함수 호출
    
    printf("A-B\n");
    matrix = subtraction_matrix(A,B);
    print_matrix(matrix, M_row, M_column);
    free_matrix(matrix, M_row); //subtraction_matrix함수를 호출하여 A+B의 결과값을 matrix에 입력받은 후 matrix출력 후 free_matrix함수 호출

    printf("Transpose A\n");
    matrix = transpose_matrix(A, A_row, A_column);
    print_matrix(matrix, M_row, M_column);
    free_matrix(matrix, M_row); //transpose A를 matrix에 입력 받은 후 출력 및 free.

    printf("Transpose B\n");
    matrix = transpose_matrix(B, B_row, B_column);
    print_matrix(matrix, M_row, M_column);
    free_matrix(matrix, M_row); //transpose A를 matrix에 입력 받은 후 출력 및 free.

    printf("Multiply A B\n");
    matrix = multiply_matrix(A,B);
    print_matrix(matrix, M_row, M_column);
    free_matrix(matrix, M_row); //multiply A,B를 matrix에 입력받은 후 출력 및 free.

    free_matrix(A, A_row);
    free_matrix(B, B_row);  //A,B 모두 free_matrix를 이용하여 메모리 해제를 한다.
    
    return 0;
}


int ** make_matrix(int row, int column) //만들 2차원 배열의 행,열의 크기를 인수로 넘겨받아 동적할당을 한 주소를 matrix에 받는다. 그리고 해당 주소를 반환한다.
{
    int ** matrix = (int **)malloc(sizeof(int *) * row);
    for(int i = 0; i < row; i++)
        matrix[i] = (int *)malloc(sizeof(int) * column);

    return matrix;
}

int ** addition_matrix(int *A[], int *B[])  //2차원 배열 A,B를 인수로 넘겨받은 후 A+B의 값을 2차원 배열 matrix에 저장 후 해당 배열의 주소를 반환한다.
{

    if(A_row != B_row && A_column != B_column)  //A,B의 크기가 같지 않으면 연산이 불가하므로 예외처리를 위해 NULL값을 반환한다.
    {
        printf("크기가 달라 행렬 연산이 불가합니다.\n");
        return NULL;
    }
    else
    {
        int ** matrix;  //A+B연산의 결과값을 입력받을 이중포인터 matrix를 선언한다. 해당 포인터는 동적할당을 통해 2차원 배열을 만든다.
        matrix = make_matrix(A_row, A_column);  //make_matrix함수를 호출하여 2차원 배열을 할당받는다.
        for(int i = 0; i < A_row; i++)  //이중 for문을 이용하여 A+B연산을 한다.
        {
            for(int j = 0; j < A_column; j++)
            {
                matrix[i][j] = A[i][j] + B[i][j];
            }
        }
        M_row = A_row;  
        M_column = A_column;    //전역변수 M_row,M_column에 A의 행,열의 크기를 대입한다. 이를 통해 print_matrix 호출시, 일일이 배열의 크기를 인수로 넘길 필요가 없어진다.
        return matrix;
    }
}

int ** subtraction_matrix(int *A[], int *B[])   //2차원 배열 A,B를 인수로 넘겨받은 후 A-B의 값을 2차원 배열 matrix에 저장 후 해당 배열의 주소를 반환한다.
{

    if(A_row != B_row && A_column != B_column)  //addition_matrix와 마찬가지로 예외처리.
    {
        printf("크기가 달라 행렬 연산이 불가합니다.\n");
        return NULL;
    }
    else
    {
        int ** matrix;
        matrix = make_matrix(A_row, A_column);
        for(int i = 0; i < A_row; i++)
        {
            for(int j = 0; j < A_column; j++)
            {
                matrix[i][j] = A[i][j] - B[i][j];
            }
        }
        M_row = A_row;
        M_column = A_column;
        return matrix;
    }   //해당 로직은 연산만 +에서 -로 바뀌었을 뿐, addition_matrix와 동일함.
}

int ** multiply_matrix(int *A[], int *B[])  //2차원 배열 A,B를 인수로 넘겨받은 후 AxB의 값을 2차원 배열 matrix에 저장 후 해당 배열의 주소를 반환한다.
{

    if(A_column != B_row)   //배열 A의 열과, 배열 B의 행의 크기가 다를시 연산이 불가하므로 예외처리.
    {
        printf("크기가 달라 행렬 연산이 불가합니다.\n");
        return NULL;
    }
    else
    {
        int tmp;
        int **matrix = make_matrix(A_row, B_column);

        for(int i = 0; i < A_row; i++)  //삼중 for문을 이용하여 행렬 A의 행과 행렬 B의 열을 계산한 값을 tmp에 중첩 저장했다가, 행렬 matrix의 각 위치에 대입한다.
        {
            for(int j = 0; j < B_column; j++)
            {
                tmp = 0;
                for(int k = 0; k < A_column; k++)
                {
                    tmp += A[i][k] * B[k][j];
                }
                matrix[i][j] = tmp;
                
            }
        }
        M_row = A_row;
        M_column = B_column;    //전역 변수 M_row, M_column에 행렬 연산이 끝난 후의 행렬 matrix 크기를 저장한다.
        return matrix;
    }
}

int ** transpose_matrix(int * tmp[], int row, int column)   //임의의 2차원 배열의 주소와 행,열의 크기를 인수로 넘겨받아 전치행렬의 주소를 반환한다.
{
    int ** matrix = make_matrix(column, row);   //결과값을 저장할 2차원 배열 matrix를 선언 및 동적할당 받는다.
    for(int i = 0; i < row; i++)    //tmp의 행은 matrix의 열로, tmp의 열은 matrix의 행으로 대입하여 전치행렬을 만든다.
        for(int j = 0; j < column; j++)
            matrix[j][i] = tmp[i][j];

    M_row = column;
    M_column = row; //tmp의 전치행렬 MATRIX의 크기를 저장한다. (print_matrix를 위해)
    return matrix;
}

void print_matrix(int * matrix[], int row, int column)  //임의의 2차원 배열과, 행,열의 크기를 인수로 넘겨받아 행렬을 출력한다.
{
    for(int i = 0; i < row; i++) 
    {
        for(int j = 0; j < column; j++)
            printf("%4d", matrix[i][j]);    //이중 for문을 이용하여 각 요소를 출력한다.
        printf("\n");   //행의 출력이 끝나면 다음 행을 출력하기 위해 줄바꿈 문자를 출력한다.
    }
    printf("\n");
}

void free_matrix(int *matrix[], int row)    //인수로 넘겨받은 2차원 배열을 free함수를 이용하여 메모리 해제한다.
{
    for(int i = 0; i < row; i++)    //make_matrix에서 matrix의 각 요소에 동적할당을 받았으므로 row의 크기만큼 일일이 메모리 해제를 해준다.
    {
        free(matrix[i]);
    }
    free(matrix);   //마지막 이중 포인터 matrix의 동적할당된 메모리 주소를 해제한다.
}