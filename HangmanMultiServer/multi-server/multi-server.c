#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>

struct sockaddr_in servaddr;

// Tableau 2 lignes, 3 colonnes

const int NB_ROOM = 3;
const int NB_PLAYER = 2;

int multi[NB_ROOM][NB_PLAYER];

//Words
int wordsTotal = 0, wordsFileDescriptor;
char ** wordsList;

void *setUpMulti()
{
    for (int i = 0; i < NB_ROOM; i++)
    {
        for (int j = 0; j < NB_PLAYER; j++)
        {
            multi[i][j] = 0;
        }
    }
}

int isRoomFull(int numRoom)
{
    int count = 0;
    for(int i=0; i<NB_PLAYER; i++){
        if(multi[numRoom][i] != 0){
            count++;
        }
    }

    if(count == NB_PLAYER) {
        return 1;
    }
    return 0;
}

void freeRoom(int room){
    for(int i=0; i<NB_ROOM; i++){
        multi[room][i] = 0;
    }
}

void sendMessageToAllPlayer(int room, char* message){
    for(int j=0; j<NB_PLAYER; j++){
        char tmp[1000];
        sprintf(tmp,"%s\n",message);
        write(multi[room][j], tmp, strlen(message) + 1);
    }
}

void sendMessageToPlayer(int fd, char* message){
    char tmp[1000];
    sprintf(tmp,"%s\n",message);
    write(fd, tmp, strlen(message) + 1);
}

char* getDashedWord(char * word) {
    int i = 0;

    // Get the word length
    size_t wordLength = strlen(word);

    // Allocate same memory to new dashed word
    char * dashedWord = malloc(wordLength * sizeof(char));

    // Dash the word
    for (i = 0; i < strlen(word); i++) {
        dashedWord[i] = '_';
    }

    return dashedWord;
}

int checkAnswer(char letterTyped, char * word, char * dashedWord) {
    size_t wordLength = strlen(word);
    int replacedLetters = 0;

    // Check the answer by looping though the word
    for (int i = 0; i < wordLength; i++) {
        if (word[i] == letterTyped) {
            // The letter exists: does it need to be replaced?
            if (dashedWord[i] == '_') {
                // Replace the letter
                dashedWord[i] = letterTyped;
                replacedLetters++;
            }
        }
    }

    return replacedLetters;
}

    char* getRandomWord(){
        uint32_t random = arc4random_uniform(wordsTotal);
        char* word = wordsList[random];
        printf("Selected word: %s\n", word);
        return word;
}

void threadGame(int room)
{
    printf("threadGame launched.\n");
    // Mise en place de la partie

    char* word = getRandomWord();
    char* dashedWord = getDashedWord(word);
    char message[1000];
    char receiveMessage[100];

    sendMessageToAllPlayer(room,"GAME START");
    while (1){
        for(int i=0; i<NB_PLAYER; i++){
            bzero(receiveMessage, 100);
            sprintf(message,"%s\nType a letter :",dashedWord);
            sendMessageToPlayer(multi[room][i],message);
            printf("wait propostition from : %i\n",multi[room][i]);
            read(multi[room][i], receiveMessage, 100);
            printf("Player type: %s\n", receiveMessage);
            if (checkAnswer(receiveMessage[0],word,dashedWord) > 0){
                sendMessageToPlayer(multi[room][i],"Good job ! :)");
            }else{
                sendMessageToPlayer(multi[room][i],"Bad choice ! :(");
            }

            if(strcmp(word,dashedWord) == 0){
                //Mot trouvé
                sprintf(message,"-The word %s is find !\nGame finish",word);
                sendMessageToAllPlayer(room,message);
                freeRoom(room);
                break;
            }
        }
    }
}

void showMulti(){
    printf("------------\n");
    for(int i=0; i<NB_ROOM; i++){
        for(int j=0; j<NB_PLAYER;j++){
            printf("Multi[%d][%d]: %d\n", i, j, multi[i][j]);
        }
    }
    printf("------------\n\n");
}

int openFile(const char * path) {
    int fileDescriptor = open(path, O_RDONLY);

    if (fileDescriptor == -1) {
        printf("Error while opening file\n");
        exit(-1);
    }

    return fileDescriptor;
}

char ** readFile(int fileDescriptor, int * wordsTotal) {
    // Internal variables
    char temp = 0;
    int cursor = 0;
    ssize_t bytesRead;

    // Setting up pointers
    char ** wordsList = malloc(20 * sizeof(char*));
    *wordsTotal = 0;

    // Reading inside file
    do {
        bytesRead = read(fileDescriptor, &temp, sizeof(char));

        if (bytesRead == -1) {
            // Error while reading file
            printf("Error while reading file\n");
            exit(-1);
        } else if (bytesRead >= sizeof(char)) {
            if (cursor == 0) {
                // Allocate some memory to catch the word
                wordsList[*wordsTotal] = (char *) malloc(sizeof(char) * 30);
            }

            if (temp == '\n') {
                // Finish the current word and update the word count
                wordsList[*wordsTotal][cursor] = '\0';

                // Reallocate unused memory
                wordsList[*wordsTotal] = (char*)realloc(wordsList[*wordsTotal], (cursor+1)* sizeof(char));

                // Update the word count
                (*wordsTotal)++;

                // Reset the cursor
                cursor = 0;
            } else {
                // Write the letter and update the cursor
                wordsList[*wordsTotal][cursor++] = temp;
            }
        }
    } while (bytesRead >= sizeof(char));

    // Update the word count
    if (*wordsTotal > 0)
        (*wordsTotal)++;

    return wordsList;
}

void getWords(){
    // Récupération des mots
    wordsFileDescriptor = openFile("words.txt");
    wordsList = readFile(wordsFileDescriptor, &wordsTotal);
    close(wordsFileDescriptor);
}

int main()
{
    printf("Server Online\n");

    getWords();

    setUpMulti();

    char receiveMessage[100];
    int listen_fd;
    fd_set rdfs;


    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    //Settings server
    bzero( &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(8088);

    FD_ZERO(&rdfs);
    FD_SET (listen_fd, &rdfs);

    //Binding
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listen_fd, 20);

    //conn_player1_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

    printf("Waiting ...\n");

    while(1)
    {
        showMulti();

        int conn_player_fd = 0;
        if (select(FD_SETSIZE, &rdfs, NULL, NULL, NULL) > 0)
        {
            printf("New Client Connected\n");
            conn_player_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

            write(conn_player_fd, "Select a room :", strlen("Select a room :") + 1);

            int isInMenu = 0;
            while (isInMenu == 0)
            {
                bzero(receiveMessage, 100);
                read(conn_player_fd, receiveMessage, 100);

                printf("Player choose room: %s\n", receiveMessage);
                int numRoom = atoi(receiveMessage) - 1;

                if (numRoom >= 0 && numRoom < NB_ROOM)
                {
                    //Connection des clients vers les salles de partie
                    int findPlace = 0;
                    for(int i=0; i<NB_PLAYER; i++){
                        if(multi[numRoom][i] == 0){
                            multi[numRoom][i] = conn_player_fd;
                            isInMenu = 1;
                            findPlace = 1;
                            break;
                        }
                    }

                    if(findPlace == 0){
                        printf("Error: ROOM FULL\n");
                        write(conn_player_fd, "Room full. Please choose another room.\n", strlen("Room full. Please choose another room.") + 1);
                        continue;
                    }

                    if (isRoomFull(numRoom) == 1)
                    {
                        printf("GAME START\n");

                        pthread_t gameThread;
                        pthread_create(&gameThread, NULL, (void * (*) (void *)) threadGame, numRoom);
                    }
                    else
                    {
                        write(conn_player_fd, "Waiting for another player.\n", strlen("Waiting for another player.") + 1);
                    }

                }
                else
                {
                    printf("Error this room doesn't exist\n");
                    write(conn_player_fd, "Error this room doesn't exist, please select another room.\n", strlen("Error this room doesn't exist, please select another room.") + 1);
                }
            }
        }
    }
}
