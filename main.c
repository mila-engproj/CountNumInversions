#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  /* for clrscr */
#include <dos.h>  /* for delay */

const int NUM_NUMS = 100000;
int debug = 0;

unsigned long long sortAndCount(long *arr, long n);
unsigned long long mergeAndCountSplit(long *arr, long n);

int main() {
    char line[80];
    long *arr = malloc(sizeof(long) * NUM_NUMS);
    long i = 0;
    FILE  *fr;

    fr = fopen ("IntegerArray.txt", "rt");

    // get a line, up to 80 chars from fr.  done if NULL
    while(fgets(line, 80, fr) != NULL) {
        sscanf (line, "%ld", arr+i);
        i++;
        if (i > NUM_NUMS) {
            printf("Too many numbers, could not read all\n");
            exit(-1);
        }
    }

    fclose(fr);

    unsigned long long result = sortAndCount(arr, i);
    printf("\nNum Inversions: %llu\n", result);

    free(arr);

    return 0;
}

unsigned long long sortAndCount(long *arr, long n) {
    int i;
    if (n == 1) {
        return 0;
    }

    unsigned long long x = sortAndCount(arr, n/2);
    unsigned long long y = sortAndCount(arr+(n/2), n/2+n%2);

    unsigned long long z = mergeAndCountSplit(arr, n);

    return x + y + z;
}

unsigned long long mergeAndCountSplit(long *arr, long n) {
    long i, j, k;
    unsigned long long numInv = 0;

    long* b = arr;
    long* c = arr+(n/2);

    long* d = malloc(sizeof(long) * n);

    i=0;
    j=0;
    for(k=0; k<n; k++) {
        if(i >= n/2) {
            *(d+k) = *(c+j);
            j++;
        }

        else if(j >= n/2+n%2) {
            *(d+k) = *(b+i);
            i++;
        }

        else if(*(b+i) < *(c+j)) {
            *(d+k) = *(b+i);
            i++;
        }

        else {
            *(d+k) = *(c+j);
            j++;
            numInv = numInv + n/2 - i;

            if(debug) {
                printf("inv at %ld\n", *(c+j-1));
                printf("numInv=%ld n=%ld n/2=%ld i=%ld\n", numInv, n, n/2, i);
            }
        }
    }

    if(debug){
        printf("merged array: ");
    }

    for(i=0; i<n; i++) {
        *(arr+i) = *(d+i);

        if(debug) {
            printf("%ld ", *(arr+i));
        }
    }

    if(debug) {
        printf("\n");
    }

    free(d);

    return numInv;
}
