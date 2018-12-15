#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* number of digits in password */
#define PASSWORD_LEN 4

#define MAX_DIGIT 6
#define MIN_DIGIT 1

int generate_password();
void begin_game(int password);

int main(){
    int password;
    srand(time(NULL));

    password = generate_password();
    /*  assuming only one difficulty level   */
    begin_game(password);

    return 0;
}


int get_random_digit() {
    return rand()%(MAX_DIGIT-MIN_DIGIT+1)+MIN_DIGIT;
}

int has_digit(int n, int digit) {
    while (n > 0) {
        if (n%10 == digit) {
            return 1;
        }
        n /= 10;
    }
    return 0;
}

int generate_password(){
    int password=0;
    int current_digit;
    int i;

    for (i=0; i<PASSWORD_LEN; i++)
    {
        do {
            current_digit = get_random_digit();
        } while (has_digit(password, current_digit));

        password *= 10;
        password += current_digit;
    }
    return password;
}

int get_num_of_hits(int password, int user_guess) {
    int num_of_hits = 0;
    while (password > 0) {
        /* for a hit, we need the number in index i to be the same in both
         * each time we check the last digit */
        if (password%10 == user_guess%10) {
            num_of_hits++;
        }
        /* remove last digit from both */
        password   /= 10;
        user_guess /= 10;
    }
    return num_of_hits;
}

int is_digit_a_miss(int password, int digit, int offset) {
    int i;
    for (i=0; i < PASSWORD_LEN; i++) {
        if (password%10 == digit && i != offset) {
            return 1;
        }
        password /= 10;
    }
    return 0;
}

int get_num_of_misses(int password, int user_guess) {
    int num_of_misses = 0;
    int i;

    for(i=0; i<PASSWORD_LEN; i++) {
        if (is_digit_a_miss(password, user_guess%10, i)) {
            num_of_misses++;
        }
        user_guess /= 10;
    }
    return num_of_misses;
}

void begin_game(int password) {
    int num_of_hits = 0;
    int num_of_misses = 0;
    int user_guess;

    while (num_of_hits < PASSWORD_LEN) {
        printf("enter your guess:\n");
        scanf("%d", &user_guess);
        num_of_hits = get_num_of_hits(password, user_guess); //get number of hits
        num_of_misses = get_num_of_misses(password, user_guess); //get number of misses
        printf("number of hits: %d\nnumber of misses: %d\n", num_of_hits, num_of_misses);
    }

    printf("you have won!");
}
