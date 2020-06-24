
# intal
C implementation of integer of arbitrary length library. CS255 Mini-Project  

## Execution
```
gcc -Wall -lm -ggdb3 intal.c intal_sampletest.c -o a.out -g
./a.out
make run_unit_tests //testing
```
*for debugging --- valgrind ./a.out; gdb ./a.out; time ./a.out*

### INTRODUCTION:

- Intal stands for Integer of Arbitrary length.
- short, unsigned short, long, unsigned long are all limited by the storage size allocated to them, be it
  2,4 or 8 bytes.
- But in practical situation there exists cases where certain arithmetic and logical operations have to be performed
  on numbers exceeding the limits bounded by the int and long int data types in C, including storage of such numbers.
  
- Hence intal is a solution to the shortcomings of the int data type in C language. Intal uses a string
  format to store a very large number. Hence arithmetic and logical operations on the same have to be such that each
  number is extracted from the string, converted into an int data type and then an operation is performed. The result
  is also a number represented as a string.
- Applications: Encryption methods for secure communication.
                They can be used to form the numerator and denominator of rational numbers.
                Can be used basically by anyone who wants to validate or perform operation on a set of huge numbers,
                     and where the platform or machine is limited to its hardware.


### APPROACH:


static char *rem_lead_zero(char *str) 
    - Function to remove all starting unwanted zeroes.
    
static char* str_reverse(const char* str) 
    - return a new allocated char* reversed str.


1. <b>intal_add(const char* intal1,const char* intal2)</b>
    - This operation is performed just as how addition was performed, by aligning the digits in their respective place
      values.
    - Digits are extracted one at a time from the ending of each intal and are then converted into integers.
    - x + y + carry is computed. If the sum exceeded 10, then a carry is generated which has to be added to the next
      corresponding, subsequent digits of the two intals.
    - The sum%10 is converted into an integer and stored in the result intal from the end.
    - A '\0' is inserted at the end of this resulting intal to mark the end of the string/intal and then returned.


2. <b>intal_compare(const char* intal1, const char* intal2)</b>
    - The length of the two intals are computed.
    - In their respective order if lengths of intal1 > intal2 , 1 is returned. If lengths of intal1 < intal2 -1 is returned.
    - In case the lengths are the same, corresponding digits from each of the intals are compared.
    - If a digit of intal1 > intal2, 1 is returned, else -1 is returned.
    - If control exits the for loop, it means the intals are identical/equal and hence 0 is returned.


3. <b>intal_diff(const char* intal1, const char* intal2)</b>
    - It is made sure that the pointer 'num1' holds the largest string in terms of value.
    - An integer 'miss' calculates how many digits off, the greater number is from the smaller number in terms of length.
    - Suppose the intals are "1234" and "39", miss = 4-2 = 2
    - The digits of each of the intals are retrieved from the last. num1[1+2] - num2[1] - borrow = 4-9-0 = -5.
    - Since the result is less than 10, a value of -5+10 = 5 is inserted at the beginning of the result intal. Borrow = 1.
    - Next step 3-3-1 = -1. since this is less tahn 10, 10-1 = 9 is inserted in the next block of result intal. Borrow = 1.
    - Remaining digits of num1 are taken into consideration along with the borrow. 2-1 = 1 is inserted.
    - Finally 1 is inserted.
    - In case of leftover digits in num1 with 0 as a digit and 1 as borrow, 9 is directly inserted into result intal.
    - Final result intal is reversed and returned.

4. <b>intal_multiply(const char* intal1,const char* intal2)</b>
    - Both the intals are reversed initially and 'rev_intal1' is ensured to be the greatest in length.
    - 'count' variable is equivalent to the blank spaces or '+' we were accustomed to put while multiplying by hand on book
      in school days.
    - values from rev_intal2 are extracted from beginning and multiplied with each value of the rev_intal1.
    - These values are stored into return intal.
    - The next digit of rev_intal2 is taken and again multiplied with each digit(j from 0 to len1-1) of rev_intal1 and  
      'count + j' digits are skipped and result intal is updated or 'replaced'.
    - The above step is repeated until all digits of rev_intal2 are used.
    - Eg: "123", "45" -> "321","54"
            321*5 = 516 is inserted. count =1;
            4*3 + 0(carry) + 1(from 516) = 13 => carry = 1 and 1(from 516) is replaced with 3 now result intal = 536
            4*2 + 1(carry) + 6(from 536) = 15, 5 is replaced with 6 result = 535
            4*1 + 1(carry)  = 5 is inserted in the end result = 5355
            5355 is reverse and 5535 is returned.


5. <b>intal_mod(const char* intal1, const char* intal2)</b>
    - O(log intal1) implementation.
    - Earlier inefficient attempts include exhaustively subtracting intal2 from intal1, binary search on the multiplier.
    - Logic of implementation is similar to long division(same as in elementary division).
    - Numbers are grouped from dividend(intal1) until it is greater than divisor(intal2).
    - After the mod(remainder, by subtracting repeatedly) is found out, the next element from intal1 is brought down. 
    - Hence this process continues and stops after no more elements from intal1 exists or mod length = intal1 length. 
    - Instead of doing remainder*10 + intal1's_next_digit which will be computationally expensive, the next intal1's digit is inserted into
      the next memory location of the remainder array(ret_mod).
    

6. <b>intal_pow(const char* intal1, unsigned int n)</b>
    - O(logn) implementation.
    - Suppose 8^101 has to be computed, recursively value of 8^50 is computed.
    - Then 8^50 is multiplied with 8^50 to get 8^100.
    - since 101%2 !=0,  8^100 * 8 is computed to get 8^101.
    - Of course each smaller number like 50 is divided into 25, then into 12 and so on recursively.


7. <b>intal_fibonacci(unsigned int n)</b>
    - Tine - O(n)  Space - O(1) logic has been implemented using the concept of sliding window.
    - Cases with n = 0 and 1 are handled.
    - Fn = Fn-1 + Fn-2, where c = Fn, a = Fn-1 and b = Fn-2 are used and values are computed iteratively.
    - c = Fn is returned finally(takes care of n >=1 here).


8. <b>intal_gcd(const char* intal1, const char* intal2)</b>
    - Euclid algorithm has been implemented.
    - Recursive calls are made to this function using the basic step, return gcd(b, a%b). where a and b are two numbers.


9. <b>intal_factorial(unsigned int n)</b>
    - Case of n == 0 is handled explicitly.
    - A loop with i from 1 to n is run and it multiplies the product of each step with i.
    - This product is then returned in the end.


10. <b>intal_bincoeff(unsigned int n, unsigned int k)</b>
    - Time- O(n*k) and Auxiliary Space - O(k) has been implemented by using dynamic programming.
    - First element in the dp table is initialised to 1.
    - For optimization if (n-k) < k then k is changed to n-k.
    - Outer for loop iterates from 1 to n and the inner loop iterates down from min(i,k) to 1.
    - dp[j] = dp[j] + dp[j-1] where Pascal's identity => C(n,k) = C(n-1,k) + C(n-1,k-1) has been implemented.
    - Using a dp table ensures  the same subproblem calculation is avoided.
    
    
11. <b>intal_max(char **arr, int n)</b>
    - Finds the index of the maximum intal in an array, going through sequentially or in a linear fashion.
    - Initially the first intal in the array is assumed to be greater.
    - After successful intal_compare() between max intal and current intal, the index is updated correspondingly.
    - Finally the index of the maximum intal is returned.


12. <b>intal_min(char **arr, int n)</b>
    - Finds the index of the minimum intal in an array, going through sequentially or in a linear fashion.
    - Initially the first intal in the array is assumed to be the minimum intal.
    - After successful intal_compare() between min intal and current intal, the index is updated correspondingly.
    - Finally the index of the minimum intal is returned.


13. <b>intal_search(char **arr, int n, const char* key)</b>
    - Time - O(n) complexity is used.
    - The array is traversed from i = 0 to n, sequentially.
    - If intal_compare() of the current intal and the key, return 0 then upon success, return the index of the intal.
    - If control exits the for loop, then return -1 indicating no element was found.


14. <b>intal_binsearch(char **arr, int n, const char* key)</b>
    - Array has to be sorted(non-decreasing order) for this function to work.
    - The middle index is calculated using (upper_bound(ub) + lower_bound(lb))/2.
    - Until the lb<=ub the loop is run.
    - If intal_compare(intal_mid,key) returns 0, then element has been found and return mid index.
    - If intal_compare returns -1 then, key might lie further to the right of mid and hence lb = mid +1.
    - else , key might lie further to the left and ub = mid -1.
    - If control exits the loop then -1 is returned.


15. <b>intal_sort(char **arr, int n)</b>
    - Uses quicksort(char **arr, int low, int high) and partition(char **arr, int low, int high). Quicksort logic.
    - O(n log n) algorithm
    - The partition function:
        Takes the last element as the pivot and places the pivot in the *correct position in the sorted array* such that
        all smaller elements than the pivot lies to the left and all elements greater are placed to the right. The array
        now is sorted in this fashion and the index of the pivot is returned.
    - The quicksort function:
        Once the array is sorted, in a manner with respect to the pivot element, this function is called recursively
        from lower_index to pivot_index-1 and then from pivot_index+1 to higher_index+1. Hence for every subarray, the
        pivot element's index is computed and correpondingly that left and right halves are sorted until low<high is true.


16. <b>coin_row_problem(char **arr, int n)</b>
    - The basic recursion formula f(n) = max{ cn-1 + f(n-2), f(n-1) } for n > 1, where f(0) = 0, f(1) = c0
    - Backtracking, Exhaustive search and Memoization could be used but have their own diadvantages like increase in time
      and space complexity, recursions etc. Hence dynamic programming with a sliding window of 3 looks promising.
    - Time - O(n) Space - O(1).
    - prev is initialised with 0 and curr with the first arr[0].
    - A for loop runs from 2 to n and the value of pointer next is updated to the max of (curr and prev+arr[i-1]).
    - Then pointers of prev and curr are also updated.
    - The final intal pointed by curr is returned.
    



### FUTURE WORK:

- Definitely implement intal_divide as well.
- If possible implement logical functions such as NOT, AND, OR.
- Extend intal functionalities to negative numbers as well.
- Find roots of very huge numbers.
- Factorisation/Prime Factorisation of large numbers both of which can be used for better encryption in secure communication and information transfer.

