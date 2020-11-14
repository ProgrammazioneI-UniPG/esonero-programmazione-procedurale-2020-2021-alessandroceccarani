#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void gen_random_key(char key[], int key_length);

int main(void) {

  char plaintext[128];
  char key[128];
  char cyphertext[128];
  char decrypted[128];

  printf("insert plaintext: ");
  fgets(plaintext, 128, stdin);

  printf("choose key generation method\n");
  printf("[1] enter key manually\n");
  printf("[2] generate random key\n");

  int menu_option;

  // Asks for menu option until it is valid
  while(menu_option != 1 && menu_option != 2) {
    printf("-> ");
    scanf("%d", &menu_option);
  }

  switch(menu_option) {
    case 1:
      printf("the key must be >= plaintext(%ld)\n", strlen(plaintext));
      do {
        printf("insert key: ");
        fgets(key, 128, stdin);
      } while(strlen(key) < strlen(plaintext));
      break;
    case 2:
      gen_random_key(key, strlen(plaintext));
      break;
    default:
      printf("not a valid option\n");
      exit(1);
  }

  // XOR encryption
  for(int i = 0; i < strlen(plaintext); i++) {
    cyphertext[i] = (char)(plaintext[i] ^ key[i]);
  }

  // XOR decryption
  for(int i = 0; i < strlen(cyphertext); i++) {
    decrypted[i] = (char)(cyphertext[i] ^ key[i]);
  }

  printf("plaintext: %s", plaintext);
  printf("key: %s\n", key);
  printf("cyphertext: %s\n", cyphertext);
  printf("decrypted: %s\n", decrypted);

  return 0;
}

// Generate random key using current timestamp
void gen_random_key(char key[], int key_length) {
  time_t t;
  srand((unsigned) time(&t));

  // Generates random number between 32 and 127
  for(int i = 0; i < key_length; i++) {
    key[i] = rand() % (127 + 1 - 32) + 32;
  }
}
