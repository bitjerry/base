#include <stdio.h>
#include <stdlib.h>

static char* TABLE = NULL;
static int BIT = 0;
static int GROUP = 0;
static int N = 0;
static char PAD = '=';

int setTable(char* table, unsigned char len, char pad) {
	if (table != NULL && len != 0){
		TABLE = table;
		while ((len >>= 1) != 0) BIT++;
		GROUP = (BIT != 0 ? ((BIT & 1) == 1 ? BIT << 3 : BIT << (BIT & 2)) : BIT);
		N = GROUP / BIT;
		PAD = pad;
		return 0;
	}
	return -1;
}

int encode(unsigned char* p_str, int len, char* result) {
	if (TABLE != NULL && p_str != NULL && BIT != 0 && GROUP != 0)
	{
		int res_len = (((len <<= 3) - 1) / GROUP + 1) * N;
		if (res_len < _msize(result))
		{
			unsigned int index = 0;
			unsigned char bytes = *p_str;
			int n = res_len - (len - 1) / BIT - 1;
			int j = BIT;
			do {
				for (int i = 0; i < 8; i++) {
					j--;
					if ((signed char)bytes < 0) index += (1 << j);
					if (j == 0) {
						*(result++) = TABLE[index];
						j = BIT;
						index = 0;
					}
					bytes <<= 1;
				}
				bytes = *(++p_str);
				
			} while (len -= 8);
			if (j != 0 && j != BIT) {
				*(result++) = TABLE[index];
			}
			while (n--) {
				*(result++) = PAD;
			}
			return 0;
		}
	}
	return -1;
}