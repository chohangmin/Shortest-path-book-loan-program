#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define INF 999
#define TRUE  1
#define FALSE 0

int n;
int W[INF][INF];

int minlength;
int P[INF][INF];
int D[INF][INF];


int adjMat[INF][INF];

int selectedBook[INF];

int bookData[10][10] = {
        {0, 1, 7, 8, 3, 4, 2, 1, 3, 2},
        {1, 2, 2, 3, 1, 6, 4, 3, 5, 3},
        {6, 7, 4, 3, 7, 8 ,5, 9, 2, 8},
        {2 ,1, 4, 2, 4, 5, 7, 4, 2, 3},
        {7, 4, 4, 4, 8, 5, 5, 8, 2, 3},
        {9, 7, 5, 8, 4, 5, 1, 3, 7, 8},
        {5, 8, 0, 0, 1, 1, 7, 9, 4, 7},
        {7, 5, 9, 5, 3, 1, 2, 5, 4, 2},
        {4, 2, 1, 7, 5, 4, 8, 5, 8, 2},
        {2, 3, 0, 1, 3, 1, 6, 4, 8, 4}
};

typedef struct {
    int book_num;
    char book_name[30];
    char book_writer[30];
} BookInfo;

BookInfo book[10] = {
        {1, "사피엔스", "Harari Yuval N"},
        {2, "코스모스", "Segan, Carl"},
        {3, "이기적 유전자", "Dawkins, Richard"},
        {4, "총, 균, 쇠", "Diamond, Jared M"},
        {5, "유토피아", "More, Thomas"},
        {6, "종의 기원", "Darwin, Charles"},
        {7, "자유론", "Mill, John Stuart"},
        {8, "국화와 칼", "Benedict, Ruth"},
        {9, "삼국유사", "일연"},
        {10, "논어", "이강수"}
};


void main_menu()
{
    
    printf("************\n");
    
    printf("소장번호\t책 이름\t\t저자\n");
    printf("%d.\t\t%s\t%s\n", book[0].book_num, book[0].book_name, book[0].book_writer);
    printf("%d.\t\t%s\t%s\n", book[1].book_num, book[1].book_name, book[1].book_writer);
    printf("%d.\t\t%s\t%s\n", book[2].book_num, book[2].book_name, book[2].book_writer);
    printf("%d.\t\t%s\t%s\n", book[3].book_num, book[3].book_name, book[3].book_writer);
    printf("%d.\t\t%s\t%s\n", book[4].book_num, book[4].book_name, book[4].book_writer);
    printf("%d.\t\t%s\t%s\n", book[5].book_num, book[5].book_name, book[5].book_writer);
    printf("%d.\t\t%s\t\t%s\n", book[6].book_num, book[6].book_name, book[6].book_writer);
    printf("%d.\t\t%s\t%s\n", book[7].book_num, book[7].book_name, book[7].book_writer);
    printf("%d.\t\t%s\t%s\n", book[8].book_num, book[8].book_name, book[8].book_writer);
    printf("%d.\t\t%s\t\t%s\n", book[9].book_num, book[9].book_name, book[9].book_writer);
    printf("************\n");
    printf("\n");

    printf("대출하실 책의 권수를 입력해주세요 (최대 10권) : ");
    scanf("%d", &n);
    if (n > 10) {
        printf("Error: 10권이 초과하여 프로그램을 종료합니다. \n");
        exit(1);
    }
    

    int *input = (int *)malloc(sizeof(int) * n);
    int *input_cmp = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        input[i] = -1;
        input_cmp[i] = INF;
    }

    int cnt = 0;

    printf("%d. 처음 고르실 책 번호를 입력해주세요: ", cnt + 1);
    scanf("%d", &input[cnt]);
    input_cmp[cnt] = selectedBook[cnt] = input[cnt];
    ++cnt;

    while (cnt < n) { 
        printf("%d. 원하는 책 번호를 입력하시오: ", cnt + 1);
        scanf("%d", &input[cnt]);

        input_cmp[cnt] = selectedBook[cnt] = input[cnt];


        for (int i = 0; i <= n; ++i) {
            if (i != cnt) {
                if (input[cnt] == input_cmp[i]) {
                    printf("Error: 책이 중복되었습니다. 다시 입력해주세요. \n");
                    --cnt;
                    break;
                }
            }     
        }

        ++cnt;
    }
    

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == input[j]) {         
                for (int k = 0; k < 10; ++k) {
                    for (int l = 0; l < n; ++l) {
                        if (k == input[l]) 
                            adjMat[j][l] = bookData[i][k];
                    }
                }
            }      
        }
    }

    free(input);
    free(input_cmp);
    
    printf("\n");

}

void print_matrix(int n, int m[][INF])
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%4d ", m[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_powered(int n, int m[][INF])
{
    int size = (int)pow(2, n - 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= size; j++) {
            printf("%4d ", m[i][j]);
        }
        printf("\n");
    }
}

int contains(int A, int k)
{
    int i, count = 0;

    for (i = 0; i < n; i++) {
        if ((A & (1 << i)) != 0) ++count;
    }

    return (count == k) ? TRUE : FALSE;
}

int isIn(int j, int A)
{
    return ((A & (1 << (j - 2))) != 0) ? TRUE : FALSE;
}

int diff(int A, int j) 
{
    int t = 1 << (j - 2);
    return (A & (~t));
}

int minimum(int A, int i, int *minj)
{
    int j, m, min;

    min = INF;
    for (j = 1; j < (int)pow(2, n - 1); j++) {
        if (!isIn(j, A)) continue;
        m = W[i][j] + D[j][diff(A, j)];
        if (min > m) {
            min = m;
            *minj = j;
        }
    }

    return min;
}

void travel() {
    int i, j, k, A, size;

    size = (int)pow(2, n - 1);

    for (i = 2; i <= n; i++) {
        D[i][0] = W[i][1];
    }

    for (k = 1; k <= n - 2; k++) {
        for (A = 0; A < size; A++) {
            if (!contains(A, k)) continue;
            for (i = 2; i <= n; i++) {
                if (isIn(i, A)) continue;
                D[i][A] = minimum(A, i, &j);
                P[i][A] = j;
            }
        }
        
    }
    A = size - 1;
    D[1][A] = minimum(A, 1, &j);
    P[1][A] = j;
    minlength = D[1][A];

}

void printBookName(int v)
{
    int tmp_num = selectedBook[v - 1];
    printf("struct num : %d ", tmp_num);
    printf("%s -> \n", book[tmp_num].book_name);
}

void tour(int v, int A)
{
    int next = P[v][A];
    printf("%s - > ", book[selectedBook[v - 1] - 1].book_name);
    if (A == 0) return;
    tour(next, diff(A, next));
}


int main()
{
    int v, size;


    main_menu();
    
    size = (int)pow(2, n - 1);

    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++)
            W[i][j] = adjMat[i - 1][j - 1];
    travel();

    printf("선택한 도서 대출의 최단 경로 : ");
    v = 1;

    tour(v, size - 1);

    int tmp_num = selectedBook[v - 1];
    printf("%s", book[tmp_num - 1].book_name);


    return 0;
}