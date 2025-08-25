
#include "pipex.h"

int main(void)
{	
	char *str_segs[] = { "hel", "lo ", "World", "!", NULL};
	char *new_str = ft_strjoin_n(str_segs);
	printf("%s\n", new_str);

}	