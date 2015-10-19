#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

int main ()
{
    printf("-----------------Procedure Information-----------------------\n");

    int pid;
    printf("Please enter a valid PID: ");
    scanf("%d", &pid);
    string aStr = "this is pretty funny" + ((long long)pid);
    cout << aStr << endl;
    // printf("You entered pid: %s\n", aStr.c_str());

}
