#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

typedef struct {
    unsigned int name;
    unsigned int size;
} process;

typedef struct {
    unsigned int pointer;
    unsigned int busy;
    unsigned int size;
    unsigned int size_of_process;
} block_of_memory;

unsigned int count = 0, count_of_blocks = 0;
process* processes = NULL;
block_of_memory* blocks = NULL;
unsigned int *memory = NULL;
unsigned int request = 0, execute_request = 0;
unsigned int size_of_memory = 0;

void table();
void fragmentation();
void allow_mamory();
void add_process();
void free_process();
void info();

int main() {
setlocale(LC_ALL, "rus"); 
    unsigned int logic = 1;

    while ( logic ) {

        printf("Меню:\n");
        printf("1. Установить/сбросить размер памяти.\n");
        printf("2. Добавить новый процесс.\n");
        printf("3. Удалить процесс.\n");
        printf("4. Показать информацию.\n");
        printf("5. Показать таблицу.\n");
        printf("6. Фрагментация/рефрагментация памяти на блоки.\n");
        printf("7. Выход.\n");
        printf("Выбрать: ");

        fflush(stdin);
        switch( getchar() ) {

            case '1' : {
                free(memory);

                printf("Введите размер памяти: ");
                scanf("%d", &size_of_memory);

                memory = (unsigned int *)calloc( size_of_memory, sizeof( unsigned int ) ); // Initialization of Memory

                break;
            }

            case '2' : {
                add_process();

                break;
            }

            case '3' : {
                free_process();

                break;
            }

            case '4' : {
                info();

                break;
            }

            case '5' : {
                table();

                break;
            }

            case '6' : {
                fragmentation();

                break;
            }

            case '7' : {
                logic = 0;

                break;
            }

            default : printf("\nВыберите пункт меню от 1 до 7!\n");

        }
        
        puts("");

    }

    // add_process();

    // info();
    
    // table();

    // free_process();

    // info();
    
    // table();

    // free_process();

    // info();
    
    // table();

    // for (unsigned int i = 0; i < count_of_blocks; i++) {

    //     printf("\n%d. Pointer: %d\n", i + 1, ( blocks + i ) -> pointer);
    //     printf("%d. Size: %d\n", i + 1, ( blocks + i ) -> size);
    //     printf("%d. Busy: %d\n", i + 1, ( blocks + i ) -> busy);

    // }

    free(memory);
    if ( count != 0 ) free(processes);
    free(blocks);

    fflush(stdin);
    getchar();
    return(0);

}

void allow_mamory() {

    if ( count == 0 ) {

        processes = (process*)malloc( 1 * sizeof( process ) );

    } else {

        processes = (process*)realloc( processes, ( count + 1 ) * sizeof( process ) );

    }

    count++;

}

void add_process() {
	setlocale(LC_ALL, "rus"); 

    request++;

    unsigned int name_test = 0, size_test = 0, logic = 1, needed_block = 0, size_of_needed_block = size_of_memory + 1;

    do {

        logic = 0;

        printf("\nВведите имя процесса: ");
        scanf("%d", &name_test );

        for ( unsigned int i = 0; i < size_of_memory; i++ )
            if ( *( memory + i ) == name_test ) {

                printf("Процесс с таким именем существует! Введите другое имя процесса!\n");

                logic = 1;

                break;

            }

    } while ( logic );

    puts("");

    printf("Введите размер процесса: ");
    scanf("%d", &size_test );

    for ( unsigned int i = 0; i < count_of_blocks; i++ )
        if ( ( blocks + i ) -> busy == 0 && ( blocks + i ) -> size >= size_test && ( blocks + i ) -> size - size_test < size_of_needed_block ) {

            needed_block = i;

            size_of_needed_block = ( blocks + i ) -> size - size_test;

        }

    if ( size_of_needed_block != size_of_memory + 1 ) {

        ( blocks + needed_block ) -> busy = 1;

        ( blocks + needed_block ) -> size_of_process = size_test;

        allow_mamory();

        ( ( processes + count - 1 ) -> name ) = name_test;

        ( ( processes + count - 1 ) -> size ) = size_test;

        for ( unsigned int j = ( blocks + needed_block ) -> pointer; j < ( ( blocks + needed_block ) -> pointer + ( blocks + needed_block ) -> size_of_process ); j++ ) {

            *( memory + j ) = name_test;

        }

        execute_request++;

        return;

    }

    printf("Процесс не может быть добавлен! Нет свободного места в памяти!\n");

}

void free_process() {
setlocale(LC_ALL, "rus"); 
    unsigned int name_of_process = 0, pointer = 0;

    printf("\nВведите имя процесса: ");
    scanf("%d", &name_of_process);

    for ( unsigned int i = 0; i < count; i++ )
        if ( name_of_process == ( processes + i ) -> name ) {

            for ( unsigned int j = i; i < count - 1; i++ ) {

                ( processes + i ) -> name = ( processes + i + 1 ) -> name;

                ( processes + i ) -> size = ( processes + i + 1 ) -> size;

            }

            if ( count > 1 ) processes = (process*)realloc(processes, ( count - 1 ) * sizeof( process ) );
                else {

                    free(processes);

                    processes = NULL;

                }

            count--;

            for ( unsigned int i = 0; i < count_of_blocks; i++ )
                if ( *( memory + ( blocks + i ) -> pointer ) == name_of_process ) {

                    for ( unsigned int j = ( blocks + i ) -> pointer; j < ( ( blocks + i ) -> pointer + ( blocks + i ) -> size_of_process ); j++ )
                        *( memory + j ) = 0;

                    ( blocks + i ) -> busy = 0;
                    ( blocks + i ) -> size_of_process = 0;

                }

            return;

        }

    printf("Процесса с таким именем не существует!\n");

}

void info() {
	setlocale(LC_ALL, "rus"); 

    unsigned int number = 1, count_of_free_memory = 0;

    printf("\nОбщий объем свободной памяти составляет %d байт..\n", size_of_memory);

    for ( unsigned int i = 0; i < count_of_blocks; i++ )
        printf("\nБлок памяти с номером %d имеет %d свободных байтов.\n", i + 1, ( blocks + i ) -> size - ( blocks + i ) -> size_of_process );

    printf("\nЗапросы: %d | Выполнять запросы: %d%c\n", request, (unsigned int)( (float)execute_request / request * 100 ), '%' );

}

void fragmentation() {

    unsigned int random_size = 0, pointer_on_memory = 0, remake_random = 0;

    for ( unsigned int i = time(NULL); i < time(NULL) + 100; i++ ) {

        remake_random += rand() % rand();

    }

    srand( remake_random );

    count_of_blocks = 0;

    free(blocks);

    while ( pointer_on_memory < size_of_memory ) {

        random_size = rand() % 19 + 1;

        if ( random_size + pointer_on_memory <= size_of_memory ) {

            if ( count_of_blocks == 0 ) blocks = (block_of_memory*)malloc( 1 * sizeof( block_of_memory ) );
                else blocks = (block_of_memory*)realloc( blocks, ( count_of_blocks + 1 ) * sizeof( block_of_memory ) );

            ( blocks + count_of_blocks ) -> pointer = pointer_on_memory;
            ( blocks + count_of_blocks ) -> size = random_size;
            ( blocks + count_of_blocks ) -> busy = 0;
            ( blocks + count_of_blocks ) -> size_of_process = 0;

            count_of_blocks++;

            pointer_on_memory += random_size;

        }

    }

}

void table() {

    for ( unsigned int i = 0; i < count_of_blocks; i++ ) {

        printf("\n\n");

        printf("Блок %d\n", i + 1);

        printf("");
        for ( unsigned int j = 0; j < ( blocks + i ) -> size - 1; j++ ) printf("____");
        printf("____\n");

        for ( unsigned int j = 0; j < ( blocks + i ) -> size; j++ ) printf("|%3d", *( memory + ( blocks + i ) -> pointer + j ) );
        printf("|\n");
        
        printf("_____________");
        for ( unsigned int j = 0; j < ( blocks + i ) -> size - 1; j++ ) {
            
            printf("___");

        }
        printf("\n");

    }

}


