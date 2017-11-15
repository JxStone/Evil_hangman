#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "associative_array.h"

int get_word_length(void);
int get_number_of_guesses(void);
char getGuess(void);
Boolean check_guess(MY_STRING past_guesses, char current_guess);
char play_again(void);
void clear_keyboard_buffer();
void evil_hangman(int word_length, int number_of_guesses);

int main(int argc, char* argv[])
{
  
    int word_length;
    int number_of_guesses;
    
    do
    {
        printf("EVIL HANGMAN GAME !!!\n\n");
        printf("What word length would you like to start with?\n");
        
        word_length = get_word_length();
        number_of_guesses = get_number_of_guesses();
        
        evil_hangman(word_length, number_of_guesses);
    }
    while(play_again() == 'y');
    
    
    
    /*
     MY_STRING old_key1 = my_string_init_c_string("---");
     MY_STRING word1 = my_string_init_c_string("the");
     MY_STRING new_key1 = my_string_init_default();
     get_word_key_value(old_key1, new_key1, word1, 'T');
     printf("%s\n", my_string_c_str(new_key1));
    
     MY_STRING old_key2 = my_string_init_c_string("-----");
     MY_STRING word2 = my_string_init_c_string("Truck");
     MY_STRING new_key2 = my_string_init_default();
     get_word_key_value(old_key2, new_key2, word2, 'r');
     printf("%s\n", my_string_c_str(new_key2));
     
     MY_STRING old_key3 = my_string_init_c_string("--ppy");
     MY_STRING word3 = my_string_init_c_string("happy");
     MY_STRING new_key3 = my_string_init_default();
     get_word_key_value(old_key3, new_key3, word3, 'h');
     printf("%s\n", my_string_c_str(new_key3));
     
     MY_STRING old_key4 = my_string_init_c_string("--e---e");
     MY_STRING word4 = my_string_init_c_string("awesome");
     MY_STRING new_key4 = my_string_init_default();
     get_word_key_value(old_key4, new_key4, word4, 'z');
     printf("%s\n", my_string_c_str(new_key4));
     
     
     my_string_destroy(&new_key1);
     my_string_destroy(&old_key1);
     my_string_destroy(&word1);
     
     my_string_destroy(&new_key2);
     my_string_destroy(&old_key2);
     my_string_destroy(&word2);
     
     my_string_destroy(&new_key3);
     my_string_destroy(&old_key3);
     my_string_destroy(&word3);
     
     my_string_destroy(&new_key4);
     my_string_destroy(&old_key4);
     my_string_destroy(&word4);
    
  */
    return 0;
     
}

int get_word_length(void)
{
    int word_length;
    
    scanf("%d", &word_length);
    clear_keyboard_buffer();
    
    if(word_length <2 || word_length > 29 || word_length == 27 || word_length == 26 || word_length == 23 || word_length == 25)
      {
        printf("Invalid word length! Please enter another length:\n ");
        get_word_length();
      }
    else
      {
	return word_length;
      }
}

int get_number_of_guesses(void)
{
    int number_of_guesses;
    printf("How many guesses would you like to have: \n");
    
    scanf("%d", &number_of_guesses);
    
    clear_keyboard_buffer();

    if (!(number_of_guesses > 0))
    {
        printf("I'm sorry, but you need to choose a positive integer!\n");
        number_of_guesses = get_number_of_guesses();
    }

    return number_of_guesses;
}

void evil_hangman(int word_length, int number_of_guesses)
{
    GENERIC_VECTOR current_word_list = generic_vector_init_default(my_string_assignment, my_string_destroy);
    MY_STRING hString = my_string_init_default();
    MY_STRING initial_key = my_string_init_default();
    MY_STRING used_letters = my_string_init_default();
    MY_STRING update_key;
    GENERIC_VECTOR temp = NULL;
    
    int i;
    int guesses_remaining = number_of_guesses;
    char current_guess;
    
    TREE word_groups;
    
    FILE* fp;
    fp = fopen("dictionary.txt", "r");
    
    i = 0;
    while(my_string_extraction(hString,fp))
    {
        if(my_string_get_size(hString) == word_length)
        {
            generic_vector_push_back(current_word_list, hString);
        }
    }

    fclose(fp);
    my_string_destroy(&hString);
    
    
    for(i = 0; i < word_length; i++)
    {
        my_string_push_back(initial_key, '-');
    }
    
    
    while(guesses_remaining > 0)
    {
        printf("The Computer has %d possibilities remaining.\n\n", generic_vector_get_size(current_word_list));
        printf("You have %d guesses left.\n", guesses_remaining);
        printf("Used Letters: ");
        
        for(i = 0; i < my_string_get_size(used_letters); i++)
        {
            printf("%c ", *my_string_at(used_letters, i));
        }
        
        printf("\nWord: ");
        my_string_insertion(initial_key, stdout);
        printf("\n");
        
        do{
            current_guess = getGuess();
        }while(check_guess(used_letters, current_guess));
        
        printf("\n\n\n");
        
        my_string_push_back(used_letters, current_guess);
        
        word_groups = tree_init_default();
	update_key = my_string_init_default();

        for(i = 0; i < generic_vector_get_size(current_word_list); i++)
 	{
	  get_word_key_value(initial_key, update_key, generic_vector_at(current_word_list, i), current_guess);
            
	  tree_add(word_groups, update_key, generic_vector_at(current_word_list, i));
            
	  my_string_insertion(generic_vector_at(current_word_list, i), stdout);
	  printf(":  ");
	  my_string_insertion(update_key, stdout);
	  printf("\n");
        }
        
        printf("\n");
        temp = tree_largest_word_bin(word_groups);
        
        generic_vector_destroy(&current_word_list);
        tree_destroy(&word_groups);
	my_string_destroy(&update_key);

        current_word_list = generic_vector_init_default(my_string_assignment, my_string_destroy);
        update_key = my_string_init_default();
        
        for(i = 0; i < generic_vector_get_size(temp); i++)
        {
            generic_vector_push_back(current_word_list, generic_vector_at(temp, i));
        }

	generic_vector_destroy(&temp);
        
        get_word_key_value(initial_key, update_key, generic_vector_at(current_word_list, 0), current_guess);
        
        if (my_string_compare(initial_key, update_key) == 0)
        {
            printf("I'm sorry, there was no %c's in the word.\n", current_guess);
            guesses_remaining--;
        }
        
        my_string_assignment(&initial_key, update_key);
        my_string_destroy(&update_key);
        
        if(guesses_remaining <= 0)
        {
            printf("Sorry! You have lost!");
            printf("The chosen word was '%s'.\n\n", my_string_c_str(generic_vector_at(current_word_list, 0)));
            break;
        }
        
        if(my_string_compare(generic_vector_at(current_word_list, 0), initial_key) == 0)
        {
            printf("Congratulation! You won!\n");
            printf("The word was '%s'.\n\n", my_string_c_str(generic_vector_at(current_word_list, 0)));
            guesses_remaining = 0;
        }
    }
    
    generic_vector_destroy(&current_word_list);
    my_string_destroy(&used_letters);
    my_string_destroy(&initial_key);
}

char getGuess(void)
{
    char c;
    
    printf("Please guess a character: ");
    scanf("%c", &c);
    clear_keyboard_buffer();

    if (isalpha(c))
    {
        if (isupper(c))
        {
            c = tolower(c);
        }
	
	return c;
    }
    else
      {
	printf("Please enter a valid character guess:\n");
	getGuess();
      }
}

Boolean check_guess(MY_STRING past_guesses, char current_guess)
{
    String* temp = (String*)past_guesses;
    int i;
    for(i = 0; i < temp->size; i++)
    {
        if(temp->data[i] == current_guess)
        {
            return TRUE;
        }
    }
    return FALSE;
}

char play_again(void)
{
    char play_again;
    
    printf("Would you like to play again?(y/n)\n");
    scanf("%c", &play_again);
    clear_keyboard_buffer();
    
    return play_again;
}

void clear_keyboard_buffer()
{
    char c;
    
    do
    {
        scanf("%c", &c);
    }while(c != '\n');
}
