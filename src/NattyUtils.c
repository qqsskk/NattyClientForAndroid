/*
 *  Author : WangBoJing , email : 1989wangbojing@gmail.com
 * 
 *  Copyright Statement:
 *  --------------------
 *  This software is protected by Copyright and the information contained
 *  herein is confidential. The software may not be copied and the information
 *  contained herein may not be used or disclosed except with the written
 *  permission of Author. (C) 2016
 * 
 *
 
****       *****
  ***        *
  ***        *                         *               *
  * **       *                         *               *
  * **       *                         *               *
  *  **      *                        **              **
  *  **      *                       ***             ***
  *   **     *       ******       ***********     ***********    *****    *****
  *   **     *     **     **          **              **           **      **
  *    **    *    **       **         **              **           **      *
  *    **    *    **       **         **              **            *      *
  *     **   *    **       **         **              **            **     *
  *     **   *            ***         **              **             *    *
  *      **  *       ***** **         **              **             **   *
  *      **  *     ***     **         **              **             **   *
  *       ** *    **       **         **              **              *  *
  *       ** *   **        **         **              **              ** *
  *        ***   **        **         **              **               * *
  *        ***   **        **         **     *        **     *         **
  *         **   **        **  *      **     *        **     *         **
  *         **    **     ****  *       **   *          **   *          *
*****        *     ******   ***         ****            ****           *
                                                                       *
                                                                      *
                                                                  *****
                                                                  ****


 *
 */




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "NattyUtils.h"
#include "NattyProtocol.h"

#if 0
TimeStamp* ntyGetSystemTime(void) {
	time_t timer;
	TimeStamp *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);

	return tblock;
}

void ntyTimeCheckStamp(U8 *buf) {
	struct tm *tblock = ntyGetSystemTime();

	buf[NTY_PROTO_TIMECHECK_YEAR_IDX] = (U8)(tblock->tm_year % 100);
	buf[NTY_PROTO_TIMECHECK_MONTH_IDX] = (U8)(tblock->tm_mon);
	buf[NTY_PROTO_TIMECHECK_DAY_IDX] = (U8)(tblock->tm_mday);
	buf[NTY_PROTO_TIMECHECK_WDAY_IDX] = (U8)(tblock->tm_wday);
	buf[NTY_PROTO_TIMECHECK_HOUR_IDX] = (U8)(tblock->tm_hour);
	buf[NTY_PROTO_TIMECHECK_MINUTE_IDX] = (U8)(tblock->tm_min);
	buf[NTY_PROTO_TIMECHECK_SECOND_IDX] = (U8)(tblock->tm_sec);
}


void ntyDisplayLetter(char *LogStr, int length) {
	int i,j,k;
	//int len = strlen(LogStr)-1;
	char u8FontCode = 0x0;

	for (i = 0;i < 32;i ++) {
#if 0
		for (j = 0;j < 8;j ++) {
			if (((*(Font[FontCode]+2*i)) >> j) & 0x01) {
				//lcd_240240_draw_point(x+j,y+i,1);
				ntylog("*");
			} else {
				ntylog(" ");
			}
		}
		for (j = 0;j < 8;j ++) {
			if (((*(Font[FontCode]+2*i+1)) >> j) & 0x01) {
				//lcd_240240_draw_point(x+8+j,y+i,1);
				ntylog("*");
			} else {
				ntylog(" ");
			}
		}
#else
		for (k = 0;k < length;k ++) {
			if (*(LogStr+k) >= 0x41 && *(LogStr+k) <= 0x5A) {
				u8FontCode = *(LogStr+k)-0x41 + DB_LETTER_BIG_START;
			} else if (*(LogStr+k) >= 0x61 && *(LogStr+k) <= 0x7A) {
				u8FontCode = *(LogStr+k)-0x61 + DB_LETTER_SMALL_START;
			} else {
				u8FontCode = DB_LETTER_SMALL_START;
			}
			for (j = 0;j < 8;j ++) {				
				if (((*(Font[u8FontCode]+2*i)) >> j) & 0x01) {
					//lcd_240240_draw_point(x+j,y+i,1);
					ntydbg("*");
				} else {
					ntydbg(" ");
				}
			}
			for (j = 0;j < 8;j ++) {
				if (((*(Font[u8FontCode]+2*i+1)) >> j) & 0x01) {
					//lcd_240240_draw_point(x+8+j,y+i,1);
					ntydbg("*");
				} else {
					ntydbg(" ");
				}
			}
		}
#endif
		ntydbg("\n");
	}

	ntydbg("\n\n\n\n\n");
}


void ntyDisplay(void) {
#if 0
	ntyDisplayLetter(DB_LETTER_N);
	ntyDisplayLetter(DB_LETTER_A);
	ntyDisplayLetter(DB_LETTER_T);
	ntyDisplayLetter(DB_LETTER_T);
	ntyDisplayLetter(DB_LETTER_Y);
#else
	char *LogStr = "Natty";	
	ntyDisplayLetter(LogStr, 5);

	ntydbg(" Author : WangBoJing , email : 1989wangbojing@gmail.com \n");
	ntydbg(" This software is protected by Copyright and the information contained\n");
	ntydbg(" herein is confidential. The software may not be copied and the information\n");
	ntydbg(" contained herein may not be used or disclosed except with the written\n");
	ntydbg(" permission of Author. (C) 2016\n\n\n");
	//ntydbg("--------------------------------------------------------------------\n");
#endif
}

void ntyFree(void *p) {
	if (p != NULL) {
		free(p);
	}
}

void *ntyMalloc(size_t size) {
	return malloc(size);
}
#endif

#if 1
void ntyBuildNext(const char *pattern, U32 length, U32 *next) {
	U32 i = 1 ,t = 0;

	next[1] = 0;
	while (i < length + 1) {
		while (t > 0 && pattern[i-1] != pattern[t-1]) {
			t = next[t];
		}

		++ t;
		++ i;
		if (pattern[i-1] == pattern[t-1]) {
			next[i] = next[t];
		} else {
			next[i] = t;
		}
	}

	while (t > 0 && pattern[i-1] != pattern[t-1]) {
		t = next[t];
	}

	++ t;
	++ i;

	next[i] = t;
}

#define PATTERN_LENGTH_COUNT 32

U32 ntyKMP(const char *text,const U32 text_length, const char *pattern,const U32 pattern_length, U32 *matches) {
	U32 i,j,n;
	U32 next[PATTERN_LENGTH_COUNT];

	ntyBuildNext(pattern, pattern_length, next);

	i = 0;
	j = 1;
	n = 0;
	
	while (pattern_length + 1 - j <= text_length - i) {
		if (text[i] == pattern[j-1]) {
			++ i;
			++ j;
			if (j == pattern_length + 1) {
				matches[n++] = i - pattern_length;
				j = next[j];
			}
		} else {
			j = next[j];
			if (j == 0) {
				++i;
				++j;
			}
		}
	}

	return n;
}

#endif

#if 1 //string operator


U16 ntyU8ArrayToU16(U8 *buf) {
	U16 dat1 = 0;
	int i = 0;

	for (i = 0;i < sizeof(U16);i ++) {
		dat1 |= (buf[i] << 8*i);
	}

	return dat1;
}


U32 ntyU8ArrayToU32(U8 *buf) {
	U32 dat2 = 0;
	int i = 0;

	for (i = 0;i < sizeof(U32);i ++) {
		dat2 |= (buf[i] << 8*i);
	}

	return dat2;
}
#if 0
C_DEVID ntyU8ArrayToU64(U8 *buf) {
	C_DEVID id = 0;
	int i = 0;

	ntylog(" ntyU8ArrayToU64 --> ");
	for (i = 0;i < sizeof(C_DEVID);i ++) {
		ntylog(" %2x", buf[i]);
	}
	ntylog("\n");
#if 0
	for (i = 0;i < sizeof(C_DEVID);i ++) {
		id |= (buf[i] << 8*i);
	}
#elif 1
	memcpy(&id, buf, sizeof(C_DEVID));
#elif 0
	id = *(C_DEVID*)buf;
#endif
	ntylog("ntyU8ArrayToU64 --> id : %lld\n", id);
	return id;
}
#else

void ntyU8ArrayToU64(U8 *buf, C_DEVID *id) {
	memcpy(id, buf, sizeof(C_DEVID));
}
#endif

#endif



#if 1

#define ITEM_SIZE		64

int ntySeparation(char ch, const char *sequence, int length, char ***pChTable, int *Count) {
	int i = 0, j = 0;
	int len = length;
	char ChArray[ITEM_SIZE] = {0};
	char **pTable = *pChTable;
	
	*Count = 0;

	for (i = 0;i < len;i ++) {
		if (sequence[i] == ch) {
			pTable[*Count] = (char*)malloc((j+1) * sizeof(char));
			memcpy(pTable[*Count], ChArray, j+1);
			(*Count) ++;

			//OslMfree(pTable);
			//pTable = (char**)OslMalloc((*Count+1) * sizeof(char**));
			pTable = (char**)realloc(pTable, (*Count+1) * sizeof(char**));
			j = 0;
			memset(ChArray, 0, ITEM_SIZE);

			continue;
		} 
		ChArray[j++] = sequence[i];
	}
	
	pTable[*Count] = (char*)malloc((j+1) * sizeof(char));
	memcpy(pTable[*Count], ChArray, j+1);
	(*Count) ++;
	
	memset(ChArray, 0, ITEM_SIZE);

	*pChTable = pTable;

	return 0;
}

void ntyFreeTable(unsigned char ***table, int count) {
	int i = 0;
	unsigned char **pTable = *table;

	for (i = 0;i < count;i ++) {
		free(pTable[i]);
	}
	
}
#endif

char ntyIsAvailableNum(char *phnum) {
	while(*phnum != 0) 	{
		if (   *phnum != '0'
			&& *phnum != '1'
			&& *phnum != '2'
			&& *phnum != '3'
			&& *phnum != '4'
			&& *phnum != '5'
			&& *phnum != '6'
			&& *phnum != '7'
			&& *phnum != '8'
			&& *phnum != '9')
		{
			return 0;
		}
		phnum++;
	}
	return 1;
}

