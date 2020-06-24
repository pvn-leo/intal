#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "intal.h"

//00157
static char *rem_lead_zero(char *str);
static char* str_reverse(const char* str);
static int partition(char **arr, int low, int high);
static void quicksort(char **arr, int low, int high);

static char *rem_lead_zero(char *str) //rem all starting unwanted zeroes
{
    int len = strlen(str);
    int i=0;
    for(; i < len; i++)
        if(str[i]!='0') break;
    if(i!=0)
    {
    	int j = i;
    	while(j <= len)
    	{
    		str[j - i] = str[j];
    		++j;
    	}
    }
    return str;
}

static char* str_reverse(const char* str) //return a char* reversed string
{ 
	int len = strlen(str); 
	char *rev_str = (char*)calloc((len+1), sizeof(char));
	strcpy(rev_str, str);  char temp;
    int i =0,j = len-1;
    while(i<j) 
	{
        temp = rev_str[i];
        rev_str[i++] = rev_str[j];
        rev_str[j--] = temp;
    }      
	return rev_str; 
} 


char* intal_add(const char* intal1,const char* intal2)
{
    int len1 = strlen(intal1), len2 = strlen(intal2);
    int len3 = len1>len2?len1:len2;
    char *ret_add = (char*)calloc((len3+2), sizeof(char));
    int i,j, k = len3, x,y,sum, carry=0;
    for(i = len1-1, j = len2-1; i >= 0 && j >=0; i--, j--, k-- )
    {
        y = intal2[j] - '0'; x = intal1[i] - '0'; //eg: if its 23
        sum = (x+y+carry)%10; //3
        carry = (x+y+carry)/10; //2
        ret_add[k] = sum + '0';
    }
    for(;i>=0;i--,k--) //intal1 has the more digits than intal2
    {
        //take the carry and keep adding it to the leftover digits of intal1 subsequently
        x = intal1[i] - '0';
        sum = (x+carry)%10;
        carry = (x+carry)/10;
        ret_add[k] = sum + '0';
    }
    for(;j>=0;j--,k--) //intal2 has the more digits than intal1
    {
        //take the carry and keep adding it to the leftover digits of intal2 subsequently
        y = intal2[j] - '0';
        sum = (y+carry)%10;
        carry = (y+carry)/10;
        ret_add[k] = sum + '0';
    }
    ret_add[k] = carry + '0';
    ret_add[len3+1] = '\0';
    //printf("strlen: %ld  add: %s\n",strlen(ret_add),ret_add);
    //printf("ret_add: %s\n",ret_add);
    char *check =  rem_lead_zero(ret_add);
    char *zero = (char*)calloc(2,sizeof(char));
    if(strlen(check) ==   0) // to handle  cases when ans = "0" only
    {
        strncpy (zero, "0", 2);
        free(check);
        return zero;
    }
    free(zero);
    return check;

}


int intal_compare(const char* intal1, const char* intal2) //no mem leaks
{
    int len1 = strlen(intal1), len2 = strlen(intal2);
    if( len1 > len2 ) return 1;
    else if( len1 < len2 ) return -1;
    else
    {
        for(int i =0; i< len1; i++)
        {
            if((intal1[i] - '0') > (intal2[i] -'0')) return 1;
            else if( (intal1[i] - '0') < (intal2[i] -'0') ) return -1;
        }
    }
    return 0;
}

char* intal_diff(const char* intal1, const char* intal2)
{
    char *num1 = (char*)intal1; int len1 = strlen(intal1);
    char *num2 = (char*)intal2; int len2 = strlen(intal2);
    char *num3; char *zero = (char*)calloc(2,sizeof(char));
    if(intal_compare(num1, num2) == 0)
    {
        zero[0] = '0';
        zero[1] = '\0';
        return zero;
    }

    //make intal1 as the biggest number
    if(intal_compare(num1, num2)!= 1 && intal_compare(num1, num2)!= 0)//if 0 no swap, else swap
    {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }
    len1 = strlen(num1);
    len2 = strlen(num2);

    num3 = (char*)calloc(len1+1, sizeof(char)); //len1 is already the bigger number
    int miss = len1 - len2 ,borrow=0,k=0,sub;
    for(int i = len2 -1; i>=0; i--)
    {
        sub = (num1[i+miss]-'0') - (num2[i]-'0') - borrow;
        if(sub < 0)//face value of num1 < face value of num2. Need to take a borrow
		    {sub=sub+10;borrow=1;}		
		else
			borrow=0;
        num3[k++]=sub + '0';
    }
    for(int i=len1-len2-1; i >= 0; i--)
	{
		if(num1[i]=='0' && borrow)
		{
			num3[k++]='9';
            continue;
		}
		sub=(num1[i] - '0') - borrow;
		if(i > 0 || sub > 0)
		{

            num3[k++] = sub + '0';
            num3[k] = '\0';
		}
		borrow=0;

	}
    num3[k]='\0'; 
    char *num3_rev = str_reverse(num3);
    free(num3); free(zero);
    return rem_lead_zero(num3_rev);
}


char* intal_multiply(const char* intal1,const char* intal2)
{
    int len1 = strlen(intal1), len2 = strlen(intal2);
    char *ret_mult = (char*)calloc((len1+len2+2), sizeof(char));
    char *rev_intal1 = str_reverse(intal1);
    char *rev_intal2 = str_reverse(intal2);
    for (int k = 0; k <= len1 + len2; k++) 
		ret_mult[k] = '0';
    char *temp1; int len;
    if(strlen(intal2) >  strlen(intal1))
    {
        temp1 = rev_intal1; len = len1;
        rev_intal1 = rev_intal2; len1 = len2;
        rev_intal2 = temp1; len2 = len;
    }
    int i=0,j=0,count=0,carry=0,temp,k;
    //count -> similar to leaving spaces/ '+' while multiplying on paper
    for(; i < len2 ; i++,count++)
    {
        j=0;
        carry = 0;
        for(; j< len1; j++)
        {
            temp = (ret_mult[count + j] - '0') + (rev_intal1[j] - '0')*(rev_intal2[i] - '0') + carry;
            carry = temp/10;
            k = temp%10;
            ret_mult[count + j] = k + '0';
        }
        temp = (ret_mult[count +j] - '0') + carry;
		carry = temp/10;
		k = temp%10;
        ret_mult[count + j] = k + '0';
		j++;
		if (carry != 0) 
				ret_mult[j + count] = carry +'0';
    }
    ret_mult[j+count-1] = '\0';
    char *temp_ret_mult = str_reverse(ret_mult);
    ret_mult = (char*)realloc(ret_mult,(len1+len2+2));
    strcpy(ret_mult, temp_ret_mult);
    free(rev_intal1);
    free(rev_intal2);
    free(temp_ret_mult);
    int cp = 0; i=0;
    while( ret_mult[i] == '0' )
    {
        cp++;
        i++;
    }
    i = 0;
	for (; i < (strlen(ret_mult) - cp); i++) 
			ret_mult[i] = ret_mult[i + cp];
    if (ret_mult[0] != '0') 
		ret_mult[i] = '\0';
	else 
		ret_mult[1] = '\0';
	
	return ret_mult;
}


char* intal_mod(const char* intal1, const char* intal2)//still need to free lb here
{
	int len1 = strlen(intal1);
	char *ret_mod,*temp;
 	if(intal_compare(intal2,"1")==0) //if intal2 return 0
	{
		char *zero = (char*)calloc(2,sizeof(char));
		strncpy (zero, "0", 2);
		return zero;
	}
	
	int rem_len,i=0;
	ret_mod = (char*)calloc(2,sizeof(char));
	char ch; ch = intal1[0];
	ret_mod[0] = ch; ret_mod[1] = '\0';
	while(i < len1)
	{
		while(intal_compare(ret_mod,intal2) != -1) //keep calculating diff until it become less than intal2
		{
			temp=ret_mod;
			ret_mod = intal_diff(temp,intal2);
			free(temp);	
		}
		if(i+1 == len1) //done with finding the max possible mod
		{
			break;
		}
		rem_len = strlen(ret_mod)+1;
		if(ret_mod[0] == '0' && rem_len-1 == 1)
			ret_mod[0] = intal1[i+1];
		else
		{
			ret_mod = (char*)realloc(ret_mod,rem_len+1);
			ret_mod[rem_len-1] = intal1[i+1];	
			ret_mod[rem_len] = '\0';		
		}
		++i;
	}
	return ret_mod;
}


char* intal_pow(const char* intal1, unsigned int n) //O(logn) logic x^n = x^(n/2) * x^(n/2) * x(if n is odd only)
{
    //char *one;
    if(n==0)
    {
        char *one = (char*)calloc(2,sizeof(char));
        one[0] = '1';
        one[1] = '\0';
        return one;
    }
    char *y = intal_pow(intal1,n/2);
    char *z = intal_multiply(y,y);
    free(y);
    if(1 == (n&1))//(n%2 == 1)
    {
        char *hold = intal_multiply(z,intal1);
        free(z);
        z = hold;
    }
    //free(one);
    return z;
}


char* intal_fibonacci(unsigned int n) //Tine - O(n)  Space - O(1) DP-Sliding window 3
{
    char *a = (char*)calloc(2, sizeof(char)); strncpy (a, "0", 2);
    char *b = (char*)calloc(2, sizeof(char)); strncpy (b, "1", 2);
    unsigned int i = 0;
    while(i < n) 
    {
        char *c = intal_add(a, b);
        a = (char*)realloc(a, strlen(b)+1);
        strncpy (a, b, strlen(b)+1);
        b = (char*)realloc(b, strlen(c)+1);
        strncpy (b, c, strlen(c)+1);
        free(c);
        i++;
    }
    free (b);
    return a;
}


char* intal_gcd(const char* intal1, const char* intal2)
{
    if(!strcmp(intal2,"0"))
    {
        char *ret_intal1 = (char*)calloc((strlen(intal1)+1), sizeof(char));
        strcpy(ret_intal1, intal1);
        return ret_intal1;
    }
    //printf("intal1: %s    intal2: %s\n",intal1,intal2);
    char *hold_mod = intal_mod(intal1, intal2);
    char *ret_gcd = intal_gcd(intal2, hold_mod );
    free(hold_mod);
    return ret_gcd;
}


char* intal_factorial(unsigned int n)
{
    char *ret_fact = (char*)calloc(2, sizeof(char));
    strncpy (ret_fact, "1", 2);
    if(n==0)
    {
        //strncpy (ret_fact, "1", 2);
        return ret_fact;
    }
    char *add = (char*)calloc(2, sizeof(char));strncpy (add, "0", 2);
    char *hold_mult; char *hold_add;
    for(unsigned int i = 1;i<=n;i++)
    {
        hold_add = intal_add(add,"1");
        add = (char*)realloc(add,strlen(hold_add)+1);
        strncpy(add, hold_add, strlen(hold_add)+1);
        free(hold_add);
        hold_mult = intal_multiply(ret_fact, add);
        ret_fact = (char*)realloc(ret_fact, strlen(hold_mult)+1);
        strncpy(ret_fact, hold_mult, strlen(hold_mult)+1);
        free(hold_mult);
        //char *ret_fact_hold = intal_multiply(ret_fact, add);
        //free(ret_fact); ret_fact = ret_fact_hold;
    }
    free(add);
    return rem_lead_zero(ret_fact);
}


char* intal_bincoeff(unsigned int n, unsigned int k) //Time O(n*k) Space O(k)
{
    char **dp = (char**)calloc(k+1, sizeof(char*));
    if((n-k) < k) k = n-k;
    dp[0] = (char*)calloc(2, sizeof(char)); strncpy (dp[0], "1", 2);
    for (unsigned int i=1; i<k+1; ++i) 
    {
        dp[i] = (char*)calloc(2, sizeof(char));
        strcpy (dp[i], "0");
    }
    
    unsigned int i,j,l;
    char *hold_add;
    for (i = 1; i <= n; i++) 
    {
        l = k>i?i:k;
        for (j = l ; j > 0; j--) 
        {
            hold_add = dp[j];
            dp[j] = intal_add(dp[j], dp[j-1]);
            free (hold_add); //to clear 0's and so on
        }
    }
    //
    char *ret_bin_coeff = (char*)calloc(strlen(dp[k])+1, sizeof(char)); //necessary in order to free(dp) overall
    strncpy (ret_bin_coeff, dp[k], strlen(dp[k])+1);
    i =0;
    for (; i<k+1; ++i)
		free (dp[i]);
	free (dp);
    return ret_bin_coeff;
}


int intal_max(char **arr, int n)
{
    if( !(n >= 1 && n <= 1000))
        return -1;
    int idx = 0; int k;
    for(int i=1; i<n; i++)
    {
        //printf("str: %s\n", *(arr+i));
        k = intal_compare(*(arr+idx),*(arr+i) );
        if(k == -1) //arr[i] is greater
            idx = i;
    }
    return idx;
}


int intal_min(char **arr, int n)
{
    if( !(n >= 1 && n <= 1000))
        return -1;
    int idx = 0; int k;
    for(int i=1; i<n; i++)
    {
        //printf("str: %s\n", *(arr+i));
        k = intal_compare(*(arr+idx),*(arr+i) );
        if(k == 1) //arr[idx] is  greater
            idx = i;
    }
    return idx;
}


int intal_search(char **arr, int n, const char* key)
{
    if( !(n >= 1 && n <= 1000))
        return -1;
    int k;
    for(int i=0; i<n; i++)
    {
        //printf("str: %s\n", *(arr+i));
        k = intal_compare(*(arr+i),key );
        if(k == 0) //arr[idx] is  greater
            return i;
    }
    return -1;
}


int intal_binsearch(char **arr, int n, const char* key)
{
    int lb = 0, ub = n-1; int mid;
    int k;
    while (lb <= ub) 
    { 
        mid = lb + (ub - lb) / 2; 
        //printf("mid: %s   key: %s  ",*(arr+mid),key);
        k = intal_compare(*(arr+mid),key );
        //printf("lb: %d  ub: %d  mid : %d  k: %d \n",lb,ub,mid,k);
        if (( mid == 0 || intal_compare(key,arr[mid-1]) == 1) && k == 0 ) 
            return mid; 
        if (k == -1)  // If key greater, leave left half 
            lb = mid + 1;
        else// If x is smaller, leave right half 
            ub = mid - 1; 
    } 
    return -1;
}


static int partition(char **arr, int low, int high)
{
    char *cp = *(arr+high); int i = low-1; char *temp;
    for(int j = low; j <= high-1 ; j++)
    {
        if(intal_compare(*(arr+j),cp) == -1)
        {
            i++;
            temp = *(arr+i);
            *(arr+i) = *(arr+j);
            *(arr+j) = temp;
        }
    }
    temp = *(arr+(i+1));
    *(arr+(i+1)) = *(arr+high);
    *(arr+high) =  temp;
    return(i+1);
}


static void quicksort(char **arr, int low, int high)
{
    if(low < high)
    {
        int s;
        s = partition(arr, low, high);
        quicksort(arr, low , s-1);
        quicksort(arr, s+1, high);       
    }
}


void intal_sort(char **arr, int n) //Quicksort O(nlogn)
{
   quicksort(arr, 0, n-1);   
}


char* coin_row_problem(char **arr, int n) 
{
	char *next;
	char *curr = (char*)calloc((strlen(arr[0]) + 1), sizeof(char));
	char *prev = (char*)calloc(2, sizeof(char));
	strncpy(curr, arr[0], strlen(arr[0]) + 1);
	strncpy(prev,"0",2);
	char *hold_z; int k;
	for (int i = 2; i <= n; i++) 
	{
		hold_z = intal_add(arr[i - 1], prev);
		k = intal_compare(hold_z, curr);
		if (k != 1) 
		{
			free(prev);
			prev = curr;
			curr = intal_add(curr, "0");
		} 
		else 
		{
			next = prev;
			prev = curr;
			curr = intal_add(arr[i - 1], next);
			free(next);
		}
		free(hold_z);
	}
	free(prev);
	return curr;
}
