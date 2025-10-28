#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nop, m = 0;
char prod[10][10], res[10];
int visited_follow[26] = {0};
//int visited_first[26]={0};

void FIRST(char c);
void FOLLOW(char c);
void result(char c);
void FIND_FIRST(char c); // new separate FIRST finder

int main()
{
	int i;
	int choice;
	char c;
	int option;

	printf("Enter the no. of productions : ");
	scanf("%d", &nop);
	puts("\nEnter the production string like \"E=E+T\" \nand epsilon as #\n");

	for (i = 0; i < nop; ++i)
	{
		printf("Enter production Number %d : ", i + 1);
		scanf("%s", prod[i]);
	}

	do
	{
		printf("\nChoose operation:\n1. Find FIRST\n2. Find FOLLOW\nEnter choice: ");
		scanf("%d", &option);

		m = 0;
		memset(res, 0 , sizeof(res));

		printf("\nEnter the symbol: ");
		scanf(" %c", &c);

		if (!isupper(c))
		{
			printf("Not Possible");
			return 0;
		}

		if (option == 1)
		{
			FIND_FIRST(c);
			printf("FIRST(%c) = { ", c);
		}
		else if (option == 2)
		{
			memset(visited_follow, 0, sizeof(visited_follow));
            //memset(visited_first, 0, sizeof(visited_first));

            FOLLOW(c);
			printf("FOLLOW(%c) = { ", c);
		}
		else
		{
			printf("Invalid option!");
			return 0;
		}

		for (i = 0; i < m; ++i)
			printf("%c ", res[i]);
		puts(" }");

		printf("\nDo you want to continue (Press 1 to continue...)? ");
		scanf("%d", &choice);

	} while (choice == 1);

	return 0;
}

// ---------------------- FOLLOW (unchanged) ----------------------
void FOLLOW(char c)
{
    int i, j;
    if (visited_follow[c - 'A']) return;
    visited_follow[c - 'A'] = 1;

    // Rule 1: Start symbol → add $
    if (prod[0][0] == c)
        result('$');

    // Rule 2: For all productions
    for (i = 0; i < nop; ++i)
    {
        int len = strlen(prod[i]);
        for (j = 2; j < len; ++j)
        {
            if (prod[i][j] == c)
            {
                // Case 1: If not last symbol
                if (j + 1 < len)
                {
                    char next = prod[i][j + 1];
                    if (isupper(next))
                        FIRST(next);
                    else
                        result(next);
                }

                // Case 2: If at end OR next can produce epsilon
                if (j + 1 == len || prod[i][j + 1] == '#')
                {
                    if (prod[i][0] != c)
                        FOLLOW(prod[i][0]); // propagate FOLLOW of LHS
                }
            }
        }
    }
}

// ---------------------- Original FIRST (used by FOLLOW only) ----------------------
void FIRST(char c)
{
	int k;
	if (!(isupper(c)))
		result(c);
	for (k = 0; k < nop; ++k)
	{
		if (prod[k][0] == c)
		{
			if (prod[k][2] == '#')
				FOLLOW(prod[k][0]);
			else if (prod[k][2] == c)
				return;
			else if (islower(prod[k][2]))
				result(prod[k][2]);
			else
				FIRST(prod[k][2]);
		}
	}
	return;
}

// ---------------------- NEW FUNCTION: FIND_FIRST ----------------------
void FIND_FIRST(char c)
{
	int i, j;

	// If it's a terminal, add it directly
	if (!isupper(c))
	{
		result(c);
		return;
	}

	for (i = 0; i < nop; i++)
	{
		if (prod[i][0] == c)
		{
			// if epsilon
			if (prod[i][2] == '#')
				result('#');

			// if next is terminal
			else if (islower(prod[i][2]) || !isupper(prod[i][2]))
				result(prod[i][2]);

			// if next is non-terminal
			else if (isupper(prod[i][2]))
				FIND_FIRST(prod[i][2]);
		}
	}
}

// ---------------------- result helper ----------------------
void result(char c)
{
	int i;
	for (i = 0; i <= m; ++i)
		if (res[i] == c)
			return;
	res[m++] = c;
}