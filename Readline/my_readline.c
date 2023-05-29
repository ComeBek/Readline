#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include <io.h>


int READLINE_READ_SIZE = 1024;
char* SAFE_BUFFER_OUT;
/*------------------------------------------------*/
/*------------------------------------------------*/
typedef enum{
    f,
    r,
    OPTIONSMISTAKES
} paths_t; 
/*------------------------------------------------*/
/*------------------------------------------------*/
int my_strlen(const char* string){
    int longitude;
    longitude = 0;
        for(int i = 0;string[i] != '\0'; i++){
            if(string == NULL){
                return 0;
            }else{
                longitude++;
            }
        }
        return longitude;
}

void my_putchar(char a)
{
    write(1, &a, 1);
}

int my_putstr( char* str )
{
    while (*str)
    {
        my_putchar( *str );
        str++;
    }
    return 0;
}
/*------------------------------------------------*/
/*------------------------------------------------*/

paths_t options_choice(int gc, char **gv){
    
    if(gc > 3)
    {
        return OPTIONSMISTAKES;
    }

    if(gv[1][0] == '-')
    {
        if(my_strlen(gv[1]) == 2)
        {
            switch (gv[1][1])
            {
                case 'r':
                    return r;
                    break;
                case 'f':
                    return f;
                    break;
                default:
                    return OPTIONSMISTAKES;
                    break;
            }
        }else{
            return OPTIONSMISTAKES;
        }
    }
    return OPTIONSMISTAKES;
}
/*------------------------------------------------*/
/*------------------------------------------------*/
void init_my_readline()
{
    SAFE_BUFFER_OUT = malloc( sizeof(char) * READLINE_READ_SIZE);  
}

char* my_readline(int file_discriptor)
{
    if(file_discriptor < 0){
        return NULL;
    }

    init_my_readline();
    if(SAFE_BUFFER_OUT == NULL){
        return NULL;
    }
    int bytes_read = 0;

    while ((bytes_read = read(file_discriptor, SAFE_BUFFER_OUT, READLINE_READ_SIZE)) > 0) {
        write(1, SAFE_BUFFER_OUT, bytes_read);
    }
    free(SAFE_BUFFER_OUT);
    return NULL;
}



/*------------------------------------------------*/
/*------------------------------------------------*/
int main(int argc, char** argv)
{
    int file;
    paths_t path;
    int end_of_file = 0;

    if(argc < 2){
        file = open("Default_file.txt", O_RDONLY);
    }else if(argc >= 2){
        path = options_choice(argc, argv);

        if(path == r){
            my_putstr( "Please enter a line to be read:\n" );
            SAFE_BUFFER_OUT = my_readline(0);
            my_putstr(SAFE_BUFFER_OUT);
            my_putchar('\n');

            free(SAFE_BUFFER_OUT);
            return 0;
        }else if(path == f){
            file = open(argv[2], O_RDONLY);
        }else if(path == OPTIONSMISTAKES){
            my_putstr("Option provided isn't valid.\n");
            return 1;
        }
    }


    if(file < 0){
        my_putstr("File provided isn't exist.\n");
        return 1;
    }
    while (!end_of_file) {
        char* line = my_readline(file);
        if (line == NULL) {
            end_of_file = 1;
        }
        free(line);
    }
    close(file);
    return 0;
}