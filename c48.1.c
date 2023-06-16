#include <stdio.h>
#define TEAMS 6
char teamName[ TEAMS ] = {'A', 'B', 'C', 'D', 'E', 'F'};

typedef struct _winloss {
    int score[TEAMS][2];
    int win;
    int loss;
    int even;
    int diff;
} WINLOSS;

int GetTeamIndex( char team )
{
    int i;
    for ( i = 0; i < TEAMS; i++) {
        if ( teamName[i] == team ) {
            break;
        }
    }
    return i;
}

void InitTable(WINLOSS table[])
{
    int i, j;
    for ( i = 0;i < TEAMS; i++ ) {
        for ( j = 0; j < TEAMS; j++ ) {
            table[i].score[j][0] = -1;
            table[i].score[j][1] = -1;
        }
    table[i].win = 0;
    table[i].loss = 0;
    table[i].even = 0;
    table[i].diff = 0;
    }
}

void ReadResult(WINLOSS table[])
{
    FILE *fp;
    char buffer[80], team[2];
    int score[2], i, j;

    fp = fopen("result.txt", "r");
    while ( fgets(buffer, sizeof buffer, fp) != NULL) {
        sscanf(buffer, "%c %c %d %d", &team[0], &team[1], &score[0], &score[1]);
        i = GetTeamIndex(team[0]);
        j = GetTeamIndex(team[1]);
        table[i].score[j][0] = score[0];
        table[i].score[j][1] = score[1];
        table[j].score[i][0] = score[1];
        table[j].score[i][1] = score[0];
    }
    fclose(fp);
}

void MakeTable(WINLOSS table[])
{
    int i, j;

    for ( i = 0; i < TEAMS; i++ ) {
        for ( j = 0; j < TEAMS; j++ ){
            if ( i == j ) {
                continue;
            }
            if ( table[i].score[j][0] > table[i].score[j][1]) {
                table[i].win++;
            } else if ( table[i].score[j][0] < table[i].score[j][1]) {
                table[i].loss++;
            } else {
                table[i].even++;
            }
            table[i].diff += table[i].score[j][0] + table[i].score[j][1];

        }
    }
}

void DisplayTable(WINLOSS table[])
{
    int i, j;

    printf("    | ");
    for ( i = 0; i < TEAMS; i++ ) {
        printf("    %c  ", teamName[i]);
    }
    printf("| W L E    D\n");
    for ( i = 0; i < 73; i++ ) {
        printf("-");
    }
    printf("\n");

    for ( i = 0; i < TEAMS; i++ ) {
        printf(" %c | ", teamName[i]);
        for ( j = 0; j < TEAMS; j++ ) {
            if ( i == j ){
            printf("    x     ");
            } else {
                printf("%2d - %2d ", table[i].score[j][0], table[i].score[j][1]);
            }
        }
        printf("| %d %d %d %3d\n", table[i].win, table[i].loss, table[i].even, table[i].diff);

    }
}

int main ( void )
{
    WINLOSS table[TEAMS];

    InitTable(table);
    ReadResult(table);
    MakeTable(table);
    DisplayTable(table);

    return 0;
}
