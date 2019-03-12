#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>

#define ROWS 10 // Y
#define COLUMNS 10 // X

#define ANSI_COLOR_YELLOW "\x1b[1;33m"
#define ANSI_COLOR_RED "\x1b[1;31m"
#define ANSI_COLOR_BLUE "\x1b[1;34m"
#define ANSI_COLOR_RESET "\x1b[1;0m"
#define ANSI_COLOR_CYAN	 "\x1b[1;36m"

bool correctPlacement(int xPos, int yPos, int shipSize, char direction){ // return true if the placement is correct
    if(direction == 'H' || direction == 'h'){
        if(xPos+shipSize <= ROWS){
            return true;
        }else{
            return false;
        }
    }else if(direction == 'V' || direction == 'v'){
        if(yPos+shipSize <= COLUMNS){
            return true;
        }else{
            return false;
        }
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Not Yet Implemented~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool isHit(int xPos, int yPos, char board[COLUMNS][ROWS]){ //checks if the selected coordinate is hit
    if(board[xPos][yPos] == '0'){
        return true;
    }else{
        return false;
    }
}

void shipDamaged(int playerHealth,bool isHit){
    if(isHit){
        playerHealth -= 1;
    }
}

void wideBomb(int xPos, int yPos, char board[COLUMNS][ROWS]){ // missile that has a radius of 1

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void shipPlacement(int xPos, int yPos, int shipSize, char direction, char board[COLUMNS][ROWS]){ //combined horizontal and vertical placement
    if(direction == 'H' || direction == 'h'){
        if(correctPlacement(xPos, yPos, shipSize, direction)){
            for(int i = xPos; i < xPos+shipSize; i++){
                board[i][yPos] = shipSize + '0';
            }
    }

    }else if(direction == 'V' || direction == 'V'){
        if(correctPlacement(xPos, yPos, shipSize, direction)){
            for(int i = yPos; i < yPos+shipSize; i++){
                board[xPos][i] = shipSize + '0';
            }
        }
    }
}

void initBoard(char board[COLUMNS][ROWS]){
    for(int i = 0; i < COLUMNS; i++){
        for(int j = 0; j < ROWS; j++){
            board[j][i] = '~';
        }
    }
}

void dispBoard(char board[COLUMNS][ROWS]){
	char letter[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'F', 'G', 'H', 'I'};
	for(int a = 0;a < COLUMNS; a++){
		if(a == 0){
			printf("    %d", a);
		}else
		printf("   %d", a);
	}
	printf("\n");
    for(int i = 0; i < COLUMNS; i++){
		printf("  ");
		for(int k = 0; k< COLUMNS; k++){
			printf(ANSI_COLOR_BLUE "+---");
		}
		printf("+\n" ANSI_COLOR_RESET);
        printf("%c ", letter[i]);
        for(int j = 0; j < ROWS; j++){
        	printf(ANSI_COLOR_BLUE "| " ANSI_COLOR_RESET);
			printf(ANSI_COLOR_CYAN"%c "ANSI_COLOR_RESET, board[j][i]);
        }
        printf(ANSI_COLOR_BLUE "|\n" ANSI_COLOR_RESET);
		if(i == COLUMNS-1){
			printf("  ");
			for(int h = 0; h< COLUMNS; h++){
				printf(ANSI_COLOR_BLUE "+---");
			}
			printf("+\n" ANSI_COLOR_RESET);
		}
    }
}

void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}

void sendBoard(char buffer[256], int client_sock, int xPos, int yPos, int shipSize, char direction){
	buffer[0] = xPos + '0';
	buffer[1] = yPos + '0';
	buffer[2] = shipSize + '0';
	buffer[3] = direction;

	send(client_sock, buffer, strlen(buffer), 0);
}

void checkHealth(int playerA, int playerB){
	if(playerA <= 0){
       	printf("GAMEOVER OPPONENT WIN\n");
		exit(0);
    }else if(playerB <= 0){
       	printf("VICTORY!!!\n");
		exit(0);
    }
}


void destroyerAttack(int xPos, int yPos, char enemyBoard[COLUMNS][ROWS], char battlefieldBoard[COLUMNS][ROWS], int playerB){
    if(enemyBoard[xPos][yPos] == '1' || enemyBoard[xPos][yPos] == '2' || enemyBoard[xPos][yPos] == '3' || enemyBoard[xPos][yPos] == '4' || enemyBoard[xPos][yPos] == '5'){
		battlefieldBoard[xPos][yPos] = 'O';
        enemyBoard[xPos][yPos] = 'O';
		playerB = playerB - 1;
	}else{
		battlefieldBoard[xPos][yPos] = 'X';
	}
}

void submarineAttack(){
}


int main(int argc, char *argv[]){

	char serverBoard[COLUMNS][ROWS];
	char clientBoard[COLUMNS][ROWS];

	char battlefieldBoard[COLUMNS][ROWS]; // this board will be displayed instead of clientBoard

    int xPos, yPos;
    int shipSize = 0;
	char direction;

    int playerA = 15;
    int playerB = 15;

	char sortie;
	char sortieReceived;

	initBoard(serverBoard);
	initBoard(clientBoard);
    initBoard(battlefieldBoard);

    int server_sock, client_sock, port_no, client_size, n;
    char buffer[256];

    struct sockaddr_in server_addr, client_addr;
    if (argc < 2) {
        printf("Usage: %s port_no", argv[0]);
        exit(1);
    }

    // Create a socket for incoming connections
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
       die_with_error("Error: socket() Failed.");

    // Bind socket to a port
    bzero((char *) &server_addr, sizeof(server_addr));
    port_no = atoi(argv[1]);
    server_addr.sin_family = AF_INET; // Internet address
    server_addr.sin_addr.s_addr = INADDR_ANY; // Any incoming interface
    server_addr.sin_port = htons(port_no); // Local port

    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
       die_with_error("Error: bind() Failed.");

    // Mark the socket so it will listen for incoming connections
    listen(server_sock, 5);

    // Accept new connection
    client_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_size);
    if (client_sock < 0)
        die_with_error("Error: accept() Failed.");

    // Communicate

	for(int i = 1; i<= 2; i++){
        shipSize = i;
        do{
            printf("Enter X & Y coordinates (1-10) Ship size %d and Direction H(horizontal)|V(Vertical): ", i);
			bzero(buffer, 256);
			scanf(" %d %d %c",&xPos, &yPos,&direction);


			sendBoard(buffer, client_sock, xPos, yPos, shipSize,direction);
			shipPlacement(xPos, yPos, shipSize, direction, serverBoard);
			dispBoard(serverBoard);

            //printf("%d %d %c\n",xPos, yPos, direction); // use for debugging
            //shipPlacement(xPos, yPos, shipSize, direction, board);

			bzero(buffer, 256);
			recv(client_sock, buffer, 255, 0);

			shipPlacement(buffer[0] - '0', buffer[1] - '0', buffer[2] - '0', buffer[3], clientBoard);
        }while(!correctPlacement(xPos, yPos, shipSize, direction));


    }

	printf("MY BOARD\n");
	dispBoard(serverBoard);
	printf("ENEMY BOARD\n");
	dispBoard(battlefieldBoard);


    while(playerA != 0 || playerB != 0){
		printf("[1]D [2]L [3]S [4]B [4]C: ");
		scanf(" %c", &sortie);

		switch(sortie){
		case 'D':
		case 'd':
			printf("Enter X & Y coordinates (0-9): ");
			scanf(" %d %d",&xPos, &yPos);

		    bzero(buffer, 256);
		    buffer[0] = xPos + '0';
		    buffer[1] = yPos + '0';
			buffer[2] = sortie;
		    n = send(client_sock, buffer, strlen(buffer), 0);

			if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' || clientBoard[xPos][yPos] == '3' || clientBoard[xPos][yPos] == '4' || clientBoard[xPos][yPos] == '5'){
				battlefieldBoard[xPos][yPos] = 'O';
				clientBoard[xPos][yPos] = 'O';
				playerB = playerB - 1;

			}else{
				battlefieldBoard[xPos][yPos] = 'X';
			}

			checkHealth(playerA, playerB);

		    printf("MY BOARD\n");
		    dispBoard(serverBoard);
		    printf("My Points: %d/15\n", playerA);
			printf("Enemy Points: %d/15\n", playerB);
		    printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);
		    dispBoard(battlefieldBoard);
			break;
		case 'b':
		case 'B':
			printf("Enter Y(A-J) & X(1-10): ");
			scanf("%d %d",&xPos, &yPos);

			bzero(buffer, 256);
		    buffer[0] = xPos + '0';
		    buffer[1] = yPos + '0';
			buffer[2] = sortie;
		    n = send(client_sock, buffer, strlen(buffer), 0);

			//Center
			if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' ||clientBoard[xPos][yPos] == '3' ||clientBoard[xPos][yPos] == '4' ||clientBoard[xPos][yPos] == '5' ||clientBoard[xPos][yPos] == 'O'){
				battlefieldBoard[xPos][yPos] = 'O';
				playerB = playerB -1;
			}else{
				battlefieldBoard[xPos][yPos] = 'X';
			}
			//Left
			if(clientBoard[xPos-1][yPos] == '1' || clientBoard[xPos-1][yPos] == '2' ||clientBoard[xPos-1][yPos] == '3' ||clientBoard[xPos-1][yPos] == '4' ||clientBoard[xPos-1][yPos] == '5' ||clientBoard[xPos-1][yPos] == 'O'){
				battlefieldBoard[xPos-1][yPos] = 'O';
				playerB -= 1;
			}else{
				battlefieldBoard[xPos-1][yPos] = 'X';
			}
			//Right
			if(clientBoard[xPos+1][yPos] == '1' || clientBoard[xPos+1][yPos] == '2' ||clientBoard[xPos+1][yPos] == '3' ||clientBoard[xPos+1][yPos] == '4' ||clientBoard[xPos+1][yPos] == '5' ||clientBoard[xPos+1][yPos] == 'O'){
				battlefieldBoard[xPos+1][yPos] = 'O';
				playerB -= 1;
			}else{
				battlefieldBoard[xPos+1][yPos] = 'X';
			}

			//Top

			if(clientBoard[xPos][yPos-1] == '1' || clientBoard[xPos][yPos-1] == '2' ||clientBoard[xPos][yPos-1] == '3' ||clientBoard[xPos][yPos-1] == '4' ||clientBoard[xPos][yPos-1] == '5' ||clientBoard[xPos][yPos-1] == 'O'){
				battlefieldBoard[xPos][yPos-1] = 'O';
				playerB -= 1;
			}else{
				battlefieldBoard[xPos][yPos-1] = 'X';
			}
			//Bottom
			if(clientBoard[xPos][yPos+1] == '1' || clientBoard[xPos][yPos+1] == '2' ||clientBoard[xPos][yPos+1] == '3' ||clientBoard[xPos][yPos+1] == '4' ||clientBoard[xPos][yPos+1] == '5' ||clientBoard[xPos][yPos+1] == 'O'){
				battlefieldBoard[xPos][yPos+1] = 'O';
				playerB -= 1;
			}else{
				battlefieldBoard[xPos][yPos+1] = 'X';
			}
			checkHealth(playerA, playerB);

		    printf("MY BOARD\n");
		    dispBoard(serverBoard);
		    printf("My Points: %d/15\n", playerA);
			printf("Enemy Points: %d/15\n", playerB);
		    printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);

			dispBoard(battlefieldBoard);
            break;

		case 'C':
		case 'c':
			for(int i=0; i<=2; i++){
			printf("Enter Y(A-J) & X(1-10): ");
			scanf(" %d %d",&xPos, &yPos);

			if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' || clientBoard[xPos][yPos] == '3' || clientBoard[xPos][yPos] == '4' || clientBoard[xPos][yPos] == 'O' || clientBoard[xPos][yPos] == '5'){
				for(int i=0; i<2; i++){
					battlefieldBoard[xPos][yPos] = 'O';
				}
			}else{
				battlefieldBoard[xPos][yPos] = 'X';
				}
			}

			checkHealth(playerA, playerB);

		    printf("MY BOARD\n");
		    dispBoard(serverBoard);
		    printf("My Points: %d/15\n", playerA);
			printf("Enemy Points: %d/15\n", playerB);
		    printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);
		    dispBoard(battlefieldBoard);
			break;
		case 's':
		case 'S':
			printf("Enter Y(A-J) & X(1-10): ");
			scanf("%d %d",&xPos, &yPos);

			for(int i=0; i<4; i++){
				if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' || clientBoard[xPos][yPos] == '3' || clientBoard[xPos][yPos] == '4' || clientBoard[xPos][yPos] == 'O'|| clientBoard[xPos][yPos] == '5'){
					battlefieldBoard[xPos+i][yPos] = 'O';
				}
				else{
					battlefieldBoard[xPos+i][yPos] = 'X';
				}
			}
			dispBoard(board);
	        break;
		}

        bzero(buffer, 256);
        recv(client_sock, buffer, 255, 0);
        xPos = buffer[0] - '0';
        yPos = buffer[1] - '0';
		sortieReceived = buffer[2];
		
		switch(sortieReceived){
		case 'd':
		case 'D':
			if(serverBoard[xPos][yPos] == '1' || serverBoard[xPos][yPos] == '2' || serverBoard[xPos][yPos] == '3' || serverBoard[xPos][yPos] == '4' || serverBoard[xPos][yPos] == '5'){
				serverBoard[xPos][yPos] = 'O';
				playerA = playerA - 1;
			}else{
				serverBoard[xPos][yPos] = 'X';
			}
			break;
		case 'B':
		case 'b':
			//Center
			if(serverBoard[xPos][yPos] == '1' || serverBoard[xPos][yPos] == '2' ||serverBoard[xPos][yPos] == '3' ||serverBoard[xPos][yPos] == '4' ||serverBoard[xPos][yPos] == '5' ||serverBoard[xPos][yPos] == 'O'){
				serverBoard[xPos][yPos] = 'O';
				playerA = playerA - 1;
			}else{
				serverBoard[xPos][yPos] = 'X';
			}
			//Left
			if(serverBoard[xPos-1][yPos] == '1' || serverBoard[xPos-1][yPos] == '2' ||serverBoard[xPos-1][yPos] == '3' ||serverBoard[xPos-1][yPos] == '4' ||serverBoard[xPos-1][yPos] == '5' ||serverBoard[xPos-1][yPos] == 'O'){
				serverBoard[xPos-1][yPos] = 'O';
				playerA = playerA - 1;
			}else{
				serverBoard[xPos-1][yPos] = 'X';
			}
			//Right
			if(serverBoard[xPos+1][yPos] == '1' || serverBoard[xPos+1][yPos] == '2' ||serverBoard[xPos+1][yPos] == '3' ||serverBoard[xPos+1][yPos] == '4' ||serverBoard[xPos+1][yPos] == '5' ||serverBoard[xPos+1][yPos] == 'O'){
				serverBoard[xPos+1][yPos] = 'O';
				playerA = playerA - 1;
			}else{
				serverBoard[xPos+1][yPos] = 'X';
			}

			//Top

			if(serverBoard[xPos][yPos-1] == '1' || serverBoard[xPos][yPos-1] == '2' ||serverBoard[xPos][yPos-1] == '3' ||serverBoard[xPos][yPos-1] == '4' ||serverBoard[xPos][yPos-1] == '5' ||serverBoard[xPos][yPos-1] == 'O'){
				serverBoard[xPos][yPos-1] = 'O';
				playerA = playerA - 1;
			}else{
				serverBoard[xPos][yPos-1] = 'X';
			}
			//Bottom
			if(serverBoard[xPos][yPos+1] == '1' || serverBoard[xPos][yPos+1] == '2' ||serverBoard[xPos][yPos+1] == '3' ||serverBoard[xPos][yPos+1] == '4' ||serverBoard[xPos][yPos+1] == '5' ||serverBoard[xPos][yPos+1] == 'O'){
				serverBoard[xPos][yPos+1] = 'O';
				playerA = playerA - 1;
			}else{
				serverBoard[xPos][yPos+1] = 'X';
			}
			break;
		}
		checkHealth(playerA, playerB);

        printf("MY BOARD\n");
        dispBoard(serverBoard);
        printf("My Points: %d\n", playerA);
		printf("Enemy Points: %d\n", playerB);
        printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);
        dispBoard(battlefieldBoard);

		

    }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*while(1){

	printf("< ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = send(client_sock, buffer, strlen(buffer), 0);
    if (n < 0) die_with_error("Error: send() Failed.");

    bzero(buffer, 256);
    n = recv(client_sock, buffer, 255, 0);
    if (n < 0) die_with_error("Error: recv() Failed.");
    printf("[client] > %s", buffer);


	}*/
    close(client_sock);

    close(server_sock);

    return 0;
}