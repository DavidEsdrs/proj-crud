#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "products.h"

#define FILE_NAME "res.data"

product create_product(char name[50], char description[150], float price, int quantity) {
  product p;
  strcpy(p.name, name);
  strcpy(p.description, description);
  p.price = price;
  p.quantity = quantity;
  return p;
}

// saves product in file system
int save_product(FILE *dest, product p) {
  fwrite(&p, sizeof(product), 1, dest);
  return 0;
}