#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char* name;
} id_names;


int main()
{
    FILE* file_num;
    FILE* names;
    names = fopen("id_names.txt", "r+");
    file_num = fopen("num.txt", "r");
    int num_of_users = 0;

    fscanf(file_num, "%d", &num_of_users);
    
    fclose(file_num);

    id_names ids[num_of_users];

    for(int i = 0; i < num_of_users; i++)
    {
        fscanf(names, "%d %ms", &(ids[i].id), &(ids[i].name));
    }

    int uid = 0;
    uid = getuid();

    bool in_list = false;

    for(int i = 0; i < num_of_users; i++)
    {
        if(ids[i].id == uid)
        {
            printf("Hello %s", ids[i].name);
            in_list = true;
            break;
        }
    }

    for(int i = 0; i < num_of_users; i++)
    {
        free(ids[i].name);
    }

    if(!in_list)
    {
        char* name;
        scanf("%ms", &name); 
        printf("Hello %s", name);
        fprintf(names, "\n%d %s\n", uid, name);
        free(name);
        num_of_users++;
    }

    file_num = fopen("num.txt", "w");

    fprintf(file_num, "%d", num_of_users);
}