#include<stdio.h>
#include<bit>
#include<iostream>

int is64LE() {
	int a = 4;
	return sizeof(char*) == 8 && (*(char*)&a) == 4; 
}

int main() {
	return is64LE();
}
