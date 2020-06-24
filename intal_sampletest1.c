#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"


void printer(char *func, char *result1)
{
    printf("%s :: %s\n",func,result1);
    free(result1);
}
int main(int argc, char const *argv[]) 
{
	int n = 12;
	char **a = (char**) malloc(n * sizeof(char*));
	for(int i = 0; i < n; i++) {
		a[i] = (char*) malloc(1001 * sizeof(char));
	}
	
	strcpy(a[0], "1234512345123451234512345");
	strcpy(a[1], "543215432154321543215432154321");
	strcpy(a[2], "0");
	strcpy(a[3], "1234512345123451234512345");
	strcpy(a[4], "1234512345123451234512344");
	strcpy(a[5], "12");
	strcpy(a[6], "265252859812191058636308480000000");
	strcpy(a[7], "265252859812191058636308480000000");
	strcpy(a[8], "5432154321543215432154321");
	strcpy(a[9], "3");
	strcpy(a[10], "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	strcpy(a[11], "1230231922161117176931558813276752514640713895736833715766118029160058800614672948775360067838593459582429649254051804908512884180898236823585082482065348331234959350355845017413023320111360666922624728239756880416434478315693675013413090757208690376793296658810662941824493488451726505303712916005346747908623702673480919353936813105736620402352744776903840477883651100322409301983488363802930540482487909763484098253940728685132044408863734754271212592471778643949486688511721051561970432780747454823776808464180697103083861812184348565522740195796682622205511845512080552010310050255801589349645928001133745474220715013683413907542779063759833876101354235184245096670042160720629411581502371248008430447184842098610320580417992206662247328722122088513643683907670360209162653670641130936997002170500675501374723998766005827579300723253474890612250135171889174899079911291512399773872178519018229989376");
	char *result1;
	int index1; 
    int k;

    result1 = intal_add("0", "0");
    printer("add",result1);
    result1 = intal_add("00099", "100");
    printer("add",result1);
    result1 = intal_diff("1234", "9876");
    printer("diff",result1);
    result1 = intal_diff("0", "1");
    printer("diff",result1);
    result1 = intal_diff("0", "1");
    printer("diff",result1);
    k = intal_compare("0", "1");
    printf("compare: %d\n",k);
    k = intal_compare("1", "1");
    printf("compare: %d\n",k);
    k = intal_compare("1", "0");
    printf("compare: %d\n",k);
    result1 = intal_multiply("0","1");
    printer("mult",result1);
    result1 = intal_multiply("987","12");
    printer("mult",result1);
    result1 = intal_mod("23","2");
    printer("mod",result1);
    result1 = intal_mod("24","2");
    printer("mod",result1);
    result1 = intal_mod("99","124");
    printer("mod",result1);
    printf("\n");
    result1 = intal_mod(a[10],a[1]);
    
    //result1 = intal_mod("123","9");
    printer("mod",result1);
    printf("\n");
    result1 = intal_pow("456",0);
    printer("pow",result1);
    result1 = intal_pow("0",2);
    printer("pow",result1);
    result1 = intal_pow("345",1);
    printer("pow",result1);
    result1 = intal_pow("23",23);
    printer("pow",result1);
    result1 = intal_fibonacci(0);
    printer("fib",result1);
    result1 = intal_fibonacci(1);
    printer("fib",result1);
    result1 = intal_fibonacci(69);
    printer("fib",result1);
    result1 = intal_gcd("0", "0");
    printer("gcd", result1);
    result1 = intal_gcd("69", "18896877");
    printer("gcd", result1);
    result1 = intal_gcd("18896877", "69");
    printer("gcd", result1);
    result1 = intal_gcd("0", "123");
    printer("gcd", result1);
    result1 = intal_gcd("1", "0");
    printer("gcd", result1);
    result1 = intal_factorial(0);
    printer("factorial", result1);
    result1 = intal_factorial(1);
    printer("factorial", result1);
    result1 = intal_factorial(10);
    printer("factorial", result1);
    result1 = intal_factorial(69);
    printer("factorial", result1);
    result1 = intal_bincoeff(0,0);
    printer("factorial", result1);
    result1 = intal_bincoeff(0,123);
    printer("factorial", result1);
    result1 = intal_bincoeff(100,90);
    printer("factorial", result1);
    result1 = intal_bincoeff(123,1);
    printer("factorial", result1);
    index1 = intal_max(a, n);
    printf("max: %d\n", index1);
    index1 = intal_min(a, n);
    printf("min: %d\n", index1);
    index1 = intal_search(a, n, a[7]);
    printf("search: %d\n", index1);
    index1 = intal_search(a, n, "6969");
    printf("search: %d\n", index1);
    intal_sort(a,n);
    for(int i = 0; i < n; i++)
		printf("%d: %s\n",i,a[i]);
    index1 = intal_binsearch(a, n, "1234512345123451234512345");
    printf("bin search: %d\n", index1);
    index1 = intal_binsearch(a, n, "265252859812191058636308480000000");
    printf("bin search: %d\n", index1);
    result1 = coin_row_problem(a, n);
    printer("COIN row",result1);
    result1 = intal_fibonacci(500);
    printer("fib",result1);
    
char *arr[100] = {"0", 
                      "0", 
                      "0",
                      "0",
                      "0",
                      "0",
                      "0",
                      "0",
                      "0",
                      "0",
                      "0",
                      "0",
                      "0"};
                      int size = 13;
                      printf("COIN: %s\n", coin_row_problem(arr, size));


    for(int i = 0; i < n; i++) {
		free(a[i]);
	}
	
	free(a);



}
