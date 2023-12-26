#ifndef PRODUCTS_H

#define PRODUCTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[50];
  char description[150];
  float price;
  int quantity;
} product;

int save_product(FILE *dest, product p);
product create_product(char name[50], char description[150], float price, int quantity);

#endif