#include "types.h"
#include "user.h"

#define SIZE 0444444444

short* table;
int melds[17], e[9];

int have(int m, int s)
{
	for (int i = 0; i < 9; i++)
		if (((m >> i * 3) & 7) < ((s >> i * 3) & 7))
			return 0;
	return 1;
}
void set(int n, int d, int p)
{
	int i;
	if (n)
	{
		for (i = 0; i<17; i++)
			if (have(p, melds[i]))
				set(n - 1, d + melds[i], p - melds[i]);
	}
	else
	{
		table[d] |= 1;
		for (i = 0; i<9; i++)
			if (have(p, e[i]))
				table[d + e[i]] |= 3;
	}
}

int init()
{
	int i;
	table = (short*)calloc(SIZE, sizeof(short));
	if (!table)
		return 0;
	
	melds[0] = 0;;
	for (i = 0; i<9; i++)
		melds[i+1] = (3 << i * 3);
	for (i = 0; i<7; i++)
		melds[i+1+9] = (73 << i * 3);
	for (i = 0; i<9; i++)
		e[i] = (2 << i * 3);
	set(4, 0, SIZE);
	
    printf(1, "init done\n");
	return 1;
}
short clac(int a, int b, int c)
{
	if(table[a]&table[b]&table[c]&1)
		return ((table[a]|table[b]|table[c])&2);
	return -1;
}
int main(int argc, char *argv[])
{
    if(!init())
        exit();
    
    int a ,b, c;
	printf(1, "輸入萬 筒 條各數字張數\n");
	printf(1, "例子: 111002 300 11100 => 一萬一萬四萬五萬六萬 三筒三筒三筒 三條四條五條\n");
    scanf(0, "%o %o %o", &a, &b, &c);
    
    while(1)
    {
		if(clac(a, b, c) > 0)
			printf(1, "\n可以胡牌\n");
		else
			printf(1, "\n無法胡牌\n");
		printf(1, "---------------------------------\n\n\n");
		printf(1, "輸入萬 筒 條各數字張數\n");
        scanf(0, "%o %o %o", &a, &b, &c); 
    }
}