#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_file(FILE *f, char *name);
int create_file(FILE *f, char *name);
void greetings();
int read_choose();
int process_choose(FILE *f, int choose);
int process_create(FILE *f);
int process_read_all_registers(FILE *f);
int process_update(FILE *f);
int process_delete(FILE *f);

typedef struct {
  char name[50];
  char description[150];
  float price;
  int quantity;
} product;

product create_product(char name[50], char description[150], float price, int quantity);

product create_product(char name[50], char description[150], float price, int quantity) {
  product p;
  strcpy(p.name, name);
  strcpy(p.description, description);
  p.price = price;
  p.quantity = quantity;
  return p;
}

// saves product in file system
int save_product(FILE*dest, product p) {
  fwrite(&p, sizeof(product), 1, dest);
  return 0;
}

int main() {
  FILE *f;
  int choose, result;

  f = fopen("res.txt", "a");

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
  f = fopen(name, "a");
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
      return process_read_all_registers(f);
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

int process_read_all_registers(FILE *f) {
  product p;

  f = fopen("res.txt", "r");
  
  if(f == NULL) {
    printf("an error occurred!");
    return 0;
  }

  while(fread(&p, sizeof(product), 1, f)) {
    printf ("Name = %50s\nDesc = %150s\nPrice = %0.2f\nQuant = %d\n",
              p.name, 
              p.description, 
              p.price,
              p.quantity);
  }

  fclose(f);
}


int process_update(FILE *f) {
  return 0;
}

int process_delete(FILE *f) {
  product p;
  int found = 0;
  char nameToDelete[50];
  FILE *temp = fopen("temp.bin", "w");

  printf("give the name of the product to delete > ");
  scanf("%50s", nameToDelete);

  while (fread(&p, sizeof(product), 1, f) == 1) {
      if (strcmp(nameToDelete, p.name)) {
          found = 1;
          continue;
      }
      fwrite(&p, sizeof(product), 1, temp);
  }
  fclose(f);
  fclose(temp);
  remove("products.txt");
  rename("temp.bin", "products.txt");
  return found;
}
