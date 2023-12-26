#include <stdio.h>
#include <stdlib.h>
#include "products.h"

int open_file(FILE *f, char *name);
int create_file(FILE *f, char *name);
void greetings();
int read_choose();
int process_choose(FILE *f, int choose);
int process_create(FILE *f);
int process_read(FILE *f);
int process_update(FILE *f);
int process_delete(FILE *f);

int main() {
  FILE *f;
  int choose, result;

  f = fopen("res.dat", "a");

  if (f == NULL) {
    return -1;
  }
  
  do {
    greetings();
    choose = read_choose();
    result = process_choose(f, choose);

    if(result < 0) {
      printf("failed operation");
      return -1;
    }

  } while(choose != 5);

  fclose(f);

  return 0;
}

int  open_file(FILE *f, char* name) {
  f = fopen(name, "ab");
  if (f == NULL) {
    return -1;
  }
  return 0;
}

void greetings() {
  printf("=========================================\n");
  printf("            **** WELCOME ****            \n");
  printf("=========================================\n");
  printf("\t1\tCREATE PRODUCT                      \n");
  printf("\t2\tREAD PRODUCT                        \n");
  printf("\t3\tUPDATE PRODUCT                      \n");
  printf("\t4\tDELETE PRODUCT                      \n");
  printf("\t5\tEXIT                                \n");
  printf("=========================================\n");
}

int read_choose() {
  int c;
  scanf("%d", &c);
  return c;
}

int process_choose(FILE *f, int choose) {
  switch(choose) {
    case 1:
      return process_create(f);
    case 2:
      return process_read(f);
    case 3:
      return process_update(f);
    case 4:
      return process_delete(f);
    case 5:
      return 5;
  }
  return 0;
}

int process_create(FILE *f) {
  product p;
  char name[50], description[150];
  float price;
  int quantity;

  printf("insert the product's name > ");
  scanf("%49s", name);

  printf("insert the product's description > ");
  scanf("%149s", description);

  printf("insert the product's price > ");
  scanf("%f", &price);

  printf("insert the product's quantity > ");
  scanf("%d", &quantity);

  p = create_product(name, description, price, quantity);
  fwrite(&p, sizeof(product), 1, f);
  fflush(f);
  printf("File position after write: %ld\n", ftell(f));

  if (ferror(f)) {
    perror("Error writing to file");
    return -1;
  }

  printf("Product created successfully\n");

  return 0;  
}

int process_read(FILE *f) {
  return 0;
}

int process_update(FILE *f) {
  return 0;
}

int process_delete(FILE *f) {
  return 0;
}
