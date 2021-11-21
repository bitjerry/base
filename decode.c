#include <stdio.h>
#include <stdlib.h>

static unsigned char* TABLE = NULL;
static int GROUP = 0;
static int BIT = 0;
static int DIFFER = 0;
static char PAD = '=';

int buildTable(char* table, unsigned char len, char pad) {
	if (table != NULL && len != 0){
		TABLE = (unsigned char*)malloc(93 * sizeof(char));
		for (unsigned char i = 0; i < len; i++) {
			TABLE[*(table++) - 33] = i;
		}
		while ((len >>= 1) != 0) BIT++;
		GROUP = (BIT != 0 ? ((BIT & 1) == 1 ? BIT << 3 : BIT << (BIT & 2)) : BIT);
		DIFFER = 8 - BIT;
		PAD = pad;
		return 0;
	}
	return -1;
}

int decode(unsigned char* p_str, int len, unsigned char* result) {
	if (TABLE != NULL && p_str != NULL && BIT != 0 && GROUP != 0 && (len *= BIT) / 8 < _msize(result)){
		unsigned char n = 0;
		unsigned char p = 0;
		int index = 0;
		for (int i = 0; i < len; i++) {
			index = *p_str - 33;
			if (*(p_str++) == PAD || index < 0 || index > 93) {
				break;
			}
			else {
				p = TABLE[index];
			}
			if (n >= BIT) {
				n -= BIT;
				*(result - 1) += (p << n);
			}
			else {
				if (n > 0) {
					*(result - 1) += p >> (BIT - n);
				}
				*result = p << (DIFFER + n);
				result++;
				n += DIFFER;
			}
		}
		return 0;
	}
	return -1;
}