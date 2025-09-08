
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int main(void)
{

    printf("=========== {ft_atoi} TEST START =========\n");
    char *s0 = "\t\n\r\v\fd469 \n";
    char *s1 = "\n234";
    char *s2 = "\e475";
    char *s3 = "\n\n\n  -46\b9 \n5d6";
    char *s4 = "\t\n\r\v\f  469 \n";

    printf("ft_atoi: %d\n", ft_atoi(s0));
    printf("atoi:    %d\n\n", atoi(s0));
    
    printf("ft_atoi: %d\n", ft_atoi(s1));
    printf("atoi:    %d\n\n", atoi(s1));
 
    printf("ft_atoi: %d\n", ft_atoi(s2));
    printf("atoi:    %d\n\n", atoi(s2));
    
    printf("ft_atoi: %d\n", ft_atoi(s3));
    printf("atoi:    %d\n\n", atoi(s3));
    
    printf("ft_atoi: %d\n", ft_atoi(s4));
    printf("atoi:    %d\n\n", atoi(s4));
    printf("=========== {ft_atoi} TEST FINISH =========\n");
	printf("=========== {ft_itoa} TEST START =========\n");
	int n0 = 0;
    int n1 = -2147483648;
    int n2 = -50;
    int n3 = -1101;

    printf("digit: %d\nstring: %s\n\n", n0, ft_itoa(n0));
    printf("digit: %d\nstring: %s\n\n", n1, ft_itoa(n1));
    printf("digit: %d\nstring: %s\n\n", n2, ft_itoa(n2));
    printf("digit: %d\nstring: %s\n\n", n3, ft_itoa(n3));
	printf("=========== {ft_itoa} TEST FINISH =========\n");

	printf("=========== PREPARE BONUS =================\n");
	printf("=========== {ft_lstnew.c} TEST FINISH =========\n");


	printf("=========== {ft_atof} TEST START =========\n");
    char *sf0 = "\t\n\r\v\fd469 \n";
    char *sf1 = "\n234.03";
    char *sf2 = "\e475,03";
    char *sf3 = "\n\n\n  -46\b9 \n5d6";
    char *sf4 = "\t\n\r\v\f  469.0304567890 \n";

    printf("ft_atof: %f\n", ft_atof(sf0));
    printf("atof:    %f\n\n", atof(sf0));
    
    printf("ft_atof: %f\n", ft_atof(sf1));
    printf("atof:    %f\n\n", atof(sf1));
 
    printf("ft_atof: %f\n", ft_atof(sf2));
    printf("atof:    %f\n\n", atof(sf2));
    
    printf("ft_atof: %f\n", ft_atof(sf3));
    printf("atof:    %f\n\n", atof(sf3));
    
    printf("ft_atof: %f\n", ft_atof(sf4));
    printf("atof:    %f\n\n", atof(sf4));

	printf("=========== {ft_atof} TEST FINISH =========\n");
	

    return (0);
}
