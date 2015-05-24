/**
* See http://en.wikipedia.org/wiki/ANSI_escape_code
* git clone https://github.com/78623842/debug-inl
* if NDEBUG defined, then do nothing.
* support windows but vc6
*/
#ifndef _HAVE_DEBUG_INLINE_H
#define _HAVE_DEBUG_INLINE_H

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CSI         "\x1B["

/* config start */

#define HAVE_COLOR  1       /*< use color or not */
#define HAVE_PREFIX 1       /*< default like FILENAME:LINE */

/* if you want to redirect to a file without debug infomation,
 * you can replace stdout to stderr */
#define _print(...)      fprintf(stdout,## __VA_ARGS__)

	/* config end */

#ifdef HAVE_COLOR
#ifndef _WIN32
#define COLOR(x)    CSI#x
#else
	#include <Windows.h>
	static char * SetConsoleColor(char *clr)
	{
		int light = 0, color = 30;
		sscanf_s(clr, "%d;%dm", &light, &color);
		light = light ? FOREGROUND_INTENSITY : 0;
		switch (color)
		{
		case 30:color = 0;														break;
		case 31:color = FOREGROUND_RED;											break;
		case 32:color = FOREGROUND_GREEN;										break;
		case 33:color = FOREGROUND_RED | FOREGROUND_GREEN;						break;
		case 34:color = FOREGROUND_BLUE;										break;
		case 35:color = FOREGROUND_RED | FOREGROUND_BLUE;						break;
		case 36:color = FOREGROUND_GREEN | FOREGROUND_BLUE;						break;
		case 37://no break
		default:color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;	break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), light | color);
		return "";
	}
#define COLOR(x)	SetConsoleColor(#x)
#endif
#else
#define COLOR(x)	""
#endif /* !HAVE_COLOR */

#define cBLK COLOR(0;30m)   /*< Black */
#define cRED COLOR(0;31m)   /*< Red */
#define cGRN COLOR(0;32m)   /*< Green */
#define cBRN COLOR(0;33m)   /*< Brown/yellow */
#define cBLU COLOR(0;34m)   /*< Blue */
#define cMGN COLOR(0;35m)   /*< Magenta */
#define cCYA COLOR(0;36m)   /*< Cyan */
#define cNOR COLOR(0;37m)   /*< Normal */
/* Brigth/light */
#define cGRA COLOR(1;30m)   /*< Dark Gray */
#define cLRD COLOR(1;31m)   /*< Red */
#define cLGN COLOR(1;32m)   /*< Green */
#define cYEL COLOR(1;33m)   /*< Yellow */
#define cLBL COLOR(1;34m)   /*< Blue */
#define cPIN COLOR(1;35m)   /*< Pink */
#define cLCY COLOR(1;36m)   /*< Cyan */
#define cBRI COLOR(1;37m)   /*< White */
#define cRST COLOR(0;0m)    /*< Reset */

#ifdef NDEBUG
#define clr_print(color, ...)
#else
#define clr_print(color, ...) do { \
	_print(color);\
    _print(__VA_ARGS__); \
    _print(cRST); \
}while(0)
#endif /* !NDEBUG */

#ifdef HAVE_PREFIX
#define GETFILENAME(x)  (strrchr(x,'/')?strrchr(x,'/')+1:x)
#define SHOW_PREFIX clr_print(cRST,"%s:%-3d ",GETFILENAME(__FILE__),__LINE__)
#else
#define SHOW_PREFIX
#endif

#define dbg_print(...) SHOW_PREFIX;clr_print(cGRN,## __VA_ARGS__)
#define inf_print(...) SHOW_PREFIX;clr_print(cLCY,## __VA_ARGS__)
#define war_print(...) SHOW_PREFIX;clr_print(cYEL,## __VA_ARGS__)
#define err_print(...) SHOW_PREFIX;clr_print(cLRD,## __VA_ARGS__)

//* simple test
#define TEST_COLOR(x) clr_print(x,#x"\n")
	static void test_colors(void)
	{
		clr_print(cGRA, "Test color in console...\n");
		TEST_COLOR(cBLK);
		TEST_COLOR(cRED);
		TEST_COLOR(cGRN);
		TEST_COLOR(cBRN);
		TEST_COLOR(cBLU);
		TEST_COLOR(cMGN);
		TEST_COLOR(cCYA);
		TEST_COLOR(cNOR);
		TEST_COLOR(cGRA);
		TEST_COLOR(cLRD);
		TEST_COLOR(cLGN);
		TEST_COLOR(cYEL);
		TEST_COLOR(cLBL);
		TEST_COLOR(cPIN);
		TEST_COLOR(cLCY);
		TEST_COLOR(cBRI);
		TEST_COLOR(cRST);

		dbg_print("%d-%s\n", 1, "debug color");
		inf_print("%d-%s\n", 2, "information color");
		war_print("%d-%s\n", 3, "waring color");
		err_print("%d-%s\n", 4, "error color");
	}
//test end */

#ifdef __cplusplus
}
#endif

#endif /* ! _HAVE_DEBUG_INLINE_H */
