# debug-inl
debugging with color(in C)
##test colors in your console 
#include "debug-inl.h"
void main(void)
{
    test_colors();
}

##print debug infomation with color
#include "debug-inl.h"
int main(int argc, char **argv)
{
    dbg_print("%d-%s\n", 1, "debug color");
    inf_print("%d-%s\n", 2, "information color");
    war_print("%d-%s\n", 3, "waring color");
    err_print("%d-%s\n", 4, "error color");
}

##config
/* config start */

#define HAVE_COLOR  1       /*< use color or not */
#define HAVE_PREFIX 1       /*< default like FILENAME:LINE */

/* if you want to redirect to a file without debug infomation,
 * you can replace stdout to stderr */
#define _print(x...)      fprintf(stdout, x)

/* config end */



