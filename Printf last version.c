#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int my_strlen(char* string) //size of string
{
    int len = 0;
    while (string[len] != '\0')
    {
    len++;
    }
    return len;
}

char* reverse_string(char* string)  //reverse
{
    int length = my_strlen(string);
    int i;
    char* res = (char*)malloc((length+1) * sizeof(char));
    for(i = 0; i < length; i++)
    {
        res[i] = string[length-1-i];
    }
    res[i] = '\0';
    return res;
}

char* my_strcat(char* dest, char* src) //strcat
{
    int j =  my_strlen(dest);
    for(int i = 0; src[i] != '\0'; i++)
    {
        dest[j] = src[i];
        j++;
    }
    dest[j] = '\0';
    return dest;
}

char *my_strcpy(char *dest, char *src) //strcpy
{
    int i;
    for(i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *int_to_str(int n) //decimal
{
    char string[12];
    int i = 0;
    int negative = 0;
    
    if (n < 0) 
    {
        negative = 1;
        n = -n; //-100 = 100    
    }
    if(n == 0)
    {
        return "0";
    }
    while(n > 0)
    {
        string[i] = n % 10 + 48;
        n = n / 10;
        i++;
    }     
    if(negative == 1)
    {
        string[i] = '-';
        i++;
    }
    string[i] = '\0';
    return reverse_string(string);
}

char *int_to_octal_str(int n) //octal
{
    char string[12];
    int i = 0;
        while(n > 0)
        {
            string[i] = n % 8 + 48;
            n = n / 8;
            i++;
        }
        string[i] = '\0';
        return reverse_string(string);
}

char *hexa_to_str(int n) //for hexa
{
    char string[12];
    int i = 0;
    while(n != 0)
    {
        if(n % 16 < 10) 
            string[i] = n % 16 + 48;
        else 
            string[i] = n % 16 + 87;
        n = n / 16;
        i++;
    }
    string[i] = '\0';
    return reverse_string(string);
}

char* char_to_str(char n) //'c' //"c\0" //char
{
    char* res = (char*) malloc(sizeof(char)*2);
    res [0] = n; //*res = n;
    res [1] = '\0'; //*(res + 1) = '\0';
    return res;
}

char *ptr_to_str(void *input)  //pointers
{
    long int n = (long int)input; 
    char *address = (char*) malloc(sizeof(char)*20); // for 0x
    char string[12];
    int i = 0;
    while(n != 0)
    {
        if(n % 16 < 10) 
            string[i] = n % 16 + 48;
        else 
            string[i] = n % 16 + 87;
        n = n / 16;
        i++;
    }
    string[i] = '\0';
    my_strcat(address, string);
    my_strcat(address, "x0");
    return reverse_string(address);
}

int my_printf(char *stroka, ...)
{
    va_list ap; // is a type to hold information about variable arguments
    va_start(ap, stroka); // it must be called before accessing variable argument list // ap - argument pointer
    int length = my_strlen(stroka); 
    int size = 0;
    for (int index = 0; index < length; index++)
    {
        if (stroka[index] == '%')
        {
            index++; 
            char* str;
            char* param_1;
            char type = stroka[index];          
            switch(type) 
            {
                case 'd': param_1 = int_to_str(va_arg(ap, int));
                        break;
                
                case 'o': param_1 = int_to_octal_str(va_arg(ap, int));
                        break;

                case 'x': param_1 = hexa_to_str(va_arg(ap, int));
                        break;

                case 'c': param_1 = char_to_str(va_arg(ap, int));
                        break;

                case 'p': param_1 = ptr_to_str(va_arg(ap, void *));
                        break;

                case 's': str = va_arg(ap, char *);
                        if (str == NULL)
                        {
                            param_1 = malloc(8);
                            my_strcpy(param_1, "(null)");
                        }
                        else 
                        {
                            param_1 = malloc(my_strlen(str) + 1);
                            param_1 = my_strcpy(param_1, str);
                            param_1[my_strlen(str)] = 0;
                        }
                        break;                             
            }           
            write(1, param_1, my_strlen(param_1));
            size = size + my_strlen(param_1);
        }
        else 
        {
            char* param_2 = char_to_str(stroka[index]);
            write(1, param_2, 1);
            size = size + my_strlen(param_2);
            free(param_2);
        }
    }
    va_end(ap);
    return size;
}

// int main() 
// { 
//     int decimal = 100; //decimal //-100
//     int octal = 100; //octal
//     int hexa = 100; //hexa
//     char character = 'a'; //char
//     int input = 100; //pointers
//     int *pointer = &input; //pointers
//     char* string = "world"; //string
//     int a = my_printf("Hello %d %o %x %c %p\n", decimal, octal, hexa, character, pointer); 
//     int c = printf("Hello %d %o %x %c %p\n", decimal, octal, hexa, character, pointer); 
//     my_printf("%d %d %s\n", 10, 0, string);
//     printf("%d, %d \n", a, c);
//     my_printf("%s\n", (char*)NULL);
//     return 0; 
// }