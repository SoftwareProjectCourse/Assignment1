#include <stdio.h>

#define MINIMUM_BASE 2
#define MAXIMUM_BASE 16

#define MAX_DIGIT_NUMBER 32

int checkNumber(const char const *str, int base);
void getResult(const char const *str, char *desiredBaseNumber, int inputBase, int desiredBase);
int charValue(char c);
int power(int base, int exp);
char intToChar(int number);


int main()
{
	int inputBase, desiredBase;
	char inputBaseNumber[MAX_DIGIT_NUMBER];
	char desiredBaseNumber[MAX_DIGIT_NUMBER];
	
	printf("Please enter the number's base:\n");
	if(scanf("%d", &inputBase) != 1 || 
		(inputBase<MINIMUM_BASE || inputBase>MAXIMUM_BASE) )
	{
		printf("Invalid input base\n");
		return -1;
	}

	printf("Please enter the desired base:\n");
	if(scanf("%d", &desiredBase) != 1 || 
		(desiredBase<MINIMUM_BASE || desiredBase>MAXIMUM_BASE))
	{
		printf("Invalid desired base\n");
		return -1;
	}

	printf("Please enter a number in base %d:\n",inputBase);
	scanf("%s", inputBaseNumber);
	if(checkNumber(inputBaseNumber, inputBase) == -1)
	{
		printf("Invalid number!\n");
		return -1;
	}

	getResult(inputBaseNumber, desiredBaseNumber, inputBase, desiredBase);
	printf("The result is : %s\n", desiredBaseNumber);
	return 0;
}

int checkNumber(const char const *str, int base)
{
	for(const char* ch = str; *ch; ch++)
	{
		int val = charValue(*ch);
		if(val<0  || val >= base)
			return -1;
	}

	return 1;
}

void getResult(const char const *str, char *desiredBaseNumber, int inputBase, int desiredBase)
{
	int decimalNumber = 0; 
	int digitNumber = 1;
	int currentPower;
	
	for (const char* ch = str; *ch; ch++)
		decimalNumber = decimalNumber*inputBase + charValue(*ch);	
	
	while (power(desiredBase, digitNumber) < decimalNumber)
		digitNumber++;
	
	for (int i = --digitNumber; i > -1 ; i--)
	{
		currentPower = power(desiredBase, i);
		desiredBaseNumber[digitNumber-i] = intToChar(decimalNumber/currentPower);
		decimalNumber = decimalNumber%currentPower;
	}
}

int power(int base, int exp)
{
    int i, result = 1;
    for (i = 0; i < exp; i++)
        result *= base;
    
    return result;
 }

char intToChar(int number)
{
	if (number>-1 && number<10) //if it's a digit
		return '0'+number;
	else if (number>9 && number<16) //if it's 
		return 'A' + number - 10;
	 
	return '\0';
}

int charValue(char c)
{
	if (c>='A' && c<='F') //capital letter
		return 10 + c - 'A';
	else if (c>= 'a' && c<='f') //small letter
		return 10 + c - 'a';
	if (c >= '0' && c <= '9') //digit
		return c-'0';
	else
		return -1;
}