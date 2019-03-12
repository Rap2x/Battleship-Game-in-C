#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>

#define ROWS 10 // Y
#define COLUMNS 10 // X
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
//end of battleship.c functions

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

/*void receiveBoard(char buffer[256], char serverBoard){
	
	shipPlacement(buffer[0] - '0', buffer[1] - '0', buffer[2] - '0', buffer[3], serverBoard);
}*/

void checkHealth(int playerA, int playerB){
	if(playerB <= 0){
		printf("GAMEOVER OPPONENT WIN\n");
		exit(0);
	}
	else if(playerA <=0){
		printf("VICTORY!!!\n");
		exit(0);
	}
}

void submarineAttack(int xPos, int yPos, char board[COLUMNS][ROWS]){
	printf("Enter Y(A-J) & X(1-10): ");
	scanf("%d %d",&xPos, &yPos);

	for(int i=0; i<4; i++){
		if(board[xPos][yPos] == '1' || board[xPos][yPos] == '2' || board[xPos][yPos] == '3' || board[xPos][yPos] == '4' || board[xPos][yPos] == 'O'){
			board[xPos+i][yPos] = 'O';
		}
		else{
			board[xPos+i][yPos] = 'X';
		}
	}
	dispBoard(board);
}

int main(int argc,  char *argv[]){
    
	char clientBoard[COLUMNS][ROWS];
	char serverBoard[COLUMNS][ROWS];
    char battlefieldBoard[COLUMNS][ROWS];
    int xPos, yPos;
    int shipSize = 0;
    char direction;
    int playerA = 15; 
    int playerB = 15;
	char sortie;
	char sortieReceived;
	
	initBoard(clientBoard);
	initBoard(serverBoard);
    initBoard(battlefieldBoard);

    int client_sock,  port_no,  n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
        printf("Usage: %s hostname port_no",  argv[0]);
        exit(1);
    }

    // Create a socket using TCP
    client_sock = socket(AF_INET,  SOCK_STREAM,  0);
    if (client_sock < 0) 
        die_with_error("Error: socket() Failed.");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }

    // Establish a connection to server
    port_no = atoi(argv[2]);
    bzero((char *) &server_addr,  sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,  
         (char *)&server_addr.sin_addr.s_addr, 
         server->h_length);
         
    server_addr.sin_port = htons(port_no);

    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        die_with_error("Error: connect() Failed.");


    // Communicate	
	for(int i = 1; i<= 2; i++){
        shipSize = i;
        do{
			bzero(buffer, 256);
			recv(client_sock, buffer, 255, 0);

			//receiveBoard(buffer,serverBoard);
			shipPlacement(buffer[0] - '0', buffer[1] - '0', buffer[2] - '0', buffer[3], serverBoard);

            printf("Enter X & Y coordinates (0-9) Ship size %d and Direction H(horizontal)|V(Vertical): ", i);
			bzero(buffer, 256);            
			scanf(" %d %d %c",&xPos, &yPos,&direction);
			
			shipPlacement(xPos, yPos, shipSize, direction, clientBoard);
			printf("YOUR BOARD\n");
			dispBoard(clientBoard);			
			sendBoard(buffer, client_sock, xPos, yPos, shipSize,direction);

            //printf("%d %d %c\n",xPos, yPos, direction); // use for debugging
            //shipPlacement(xPos, yPos, shipSize, direction, board);
            
        }while(!correctPlacement(xPos, yPos, shipSize, direction));
	}
    printf("MY BOARD\n");
    dispBoard(clientBoard);
	printf("ENEMY BOARD\n");
	dispBoard(battlefieldBoard);
    
    while(playerA != 0 || playerB != 0){

        bzero(buffer, 256);
		recv(client_sock, buffer, 255, 0);

        xPos = buffer[0] - '0';
        yPos = buffer[1] - '0';
        sortieReceived = buffer[2];
        switch(sortieReceived){
    	case 'd':
    	case 'D':
			if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' || clientBoard[xPos][yPos] == '3' || clientBoard[xPos][yPos] == '4' || clientBoard[xPos][yPos] == '5'){
				clientBoard[xPos][yPos] = 'O';
				playerB = playerB - 1;
			}else{
				clientBoard[xPos][yPos] = 'X';
			}
			checkHealth(playerA, playerB);
    		break;
    	case 'b':
    	case 'B':
    		if(clientBoard[xPos][yPos+1] == '1' || clientBoard[xPos][yPos+1] == '2' || clientBoard[xPos][yPos+1] == '3' || clientBoard[xPos][yPos+1] == '4' || clientBoard[xPos][yPos+1] == '5' || clientBoard[xPos][yPos+1] == 'O'){
				clientBoard[xPos][yPos+1] = 'O';
				playerB = playerB - 1;
			}else{
				clientBoard[xPos][yPos+1] = 'X';
			}
			//middle right
			if(clientBoard[xPos+1][yPos] == '1' || clientBoard[xPos+1][yPos] == '2' || clientBoard[xPos+1][yPos] == '3' || clientBoard[xPos+1][yPos] == '4' || clientBoard[xPos+1][yPos] == '5' || clientBoard[xPos+1][yPos] == 'O'){
				clientBoard[xPos+1][yPos] = 'O';
				playerB = playerB - 1;
			}else{
				clientBoard[xPos+1][yPos] = 'X';
			}
			//middle
			 if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' || clientBoard[xPos][yPos] == '3' || clientBoard[xPos][yPos] == '4' || clientBoard[xPos][yPos] == '5' || clientBoard[xPos][yPos]== 'O'){
				clientBoard[xPos][yPos] = 'O';
				playerB = playerB - 1;
			}else{
				clientBoard[xPos][yPos] = 'X';			
			}
			//middle left
			if(clientBoard[xPos-1][yPos] == '1' || clientBoard[xPos-1][yPos] == '2' || clientBoard[xPos-1][yPos] == '3' || clientBoard[xPos-1][yPos] == '4' || clientBoard[xPos-1][yPos] == '5' || clientBoard[xPos-1][yPos]== 'O'){
				clientBoard[xPos-1][yPos] = 'O';
				playerB = playerB - 1;
			}else{
				clientBoard[xPos-1][yPos] = 'X';			
			}	
			//top
			if(clientBoard[xPos][yPos-1] == '1' || clientBoard[xPos][yPos-1] == '2' || clientBoard[xPos][yPos-1] == '3' || clientBoard[xPos][yPos-1] == '4' || clientBoard[xPos][yPos-1] == 'O' || clientBoard[xPos][yPos-1] == '5'){
				clientBoard[xPos][yPos-1] = 'O';
				playerB = playerB - 1;
			}else{
				clientBoard[xPos][yPos-1] = 'X';
			}
			checkHealth(playerA, playerB);
    		break;
    	}

    	case 's':
    	case 'S': //Submarine
			for(int i=0; i<4; i++){
				if(clientBoard[xPos][yPos] == '1' || clientBoard[xPos][yPos] == '2' || clientBoard[xPos][yPos] == '3' || clientBoard[xPos][yPos] == '4' || clientBoard[xPos][yPos] == 'O' || clientBoard[xPos][yPos] == '5'){
					clientBoard[xPos+i][yPos] = 'O';
					playerB = playerB - 1;
				}
				else{
					clientBoard[xPos+i][yPos] = 'X';
				}
			}
			dispBoard(board);
            break;

        printf("MY BOARD\n");
        dispBoard(clientBoard);
        printf("My Points: %d/15\n", playerB);
		//hit or miss sign
        printf("Enemy Points: %d/15\n", playerA);
        printf(ANSI_COLOR_RED"ENEMY BOARD\n" ANSI_COLOR_RESET);
    	dispBoard(battlefieldBoard);

		//attack mode
		printf("[1]D [2]L [3]S [4]B [4]C: ");
		scanf(" %c", &sortie);

		switch(sortie){
		case 'd':
		case 'D':
			printf("Enter Y(A-J) & X(0-9): ");
			scanf(" %d %d",&xPos, &yPos);
			
			bzero(buffer, 256);
       		buffer[0] = xPos + '0';
        	buffer[1] = yPos + '0';
        	n = send(client_sock, buffer, strlen(buffer), 0);
        
			if(serverBoard[xPos][yPos] == '1' || serverBoard[xPos][yPos] == '2' || serverBoard[xPos][yPos] == '3' || serverBoard[xPos][yPos] == '4' || serverBoard[xPos][yPos] == '5' || serverBoard[xPos][yPos] == 'O'){
    			battlefieldBoard[xPos][yPos] = 'O';
    			playerA = playerA - 1;
    		}else{
    			battlefieldBoard[xPos][yPos] = 'X';
    		}
		    printf("MY BOARD\n");
		    dispBoard(clientBoard);
		    printf("My Points: %d/15\n", playerB);
			printf("Enemy Points: %d/15\n", playerA);
		    printf(ANSI_COLOR_RED"ENEMY BOARD\n" ANSI_COLOR_RESET);
			dispBoard(battlefieldBoard);
				
			checkHealth(playerA,playerB);
			break;
			
		case 'C': //carrier
		case 'c':
			for(int i=0; i<=2; i++){
			printf("Enter Y(A-J) & X(0-9): ");
			scanf(" %d %d",&xPos, &yPos);

			bzero(buffer, 256);
       		buffer[0] = xPos + '0';
        	buffer[1] = yPos + '0';
        	n = send(client_sock, buffer, strlen(buffer), 0);
        	
			if(serverBoard[xPos][yPos] == '1' || serverBoard[xPos][yPos] == '2' || serverBoard[xPos][yPos] == '3' || serverBoard[xPos][yPos] == '4' || serverBoard[xPos][yPos] == 'O'){
				for(int i=0; i<2; i++){
					battlefieldBoard[xPos][yPos] = 'O';
				}
			}else{
				battlefieldBoard[xPos][yPos] = 'X';
				}
			}
			printf("MY BOARD\n");
		    dispBoard(clientBoard);
		    printf("My Points: %d/15\n", playerB);
			printf("Enemy Points: %d/15\n", playerA);
		    printf(ANSI_COLOR_RED"ENEMY BOARD\n" ANSI_COLOR_RESET);
			dispBoard(battlefieldBoard);
				
			checkHealth(playerA,playerB);
            break;
        case 'b':    
		case 'B': //battleship
			printf("Enter Y(A-J) & X(0-9): ");
			scanf("%d %d",&xPos, &yPos);
			
			bzero(buffer, 256);
       		buffer[0] = xPos + '0';
        	buffer[1] = yPos + '0';
        	buffer[2] = sortie;
        	n = send(client_sock, buffer, strlen(buffer), 0);
			 //bottom
			if(serverBoard[xPos][yPos+1] == '1' || serverBoard[xPos][yPos+1] == '2' || serverBoard[xPos][yPos+1] == '3' || serverBoard[xPos][yPos+1] == '4' || serverBoard[xPos][yPos+1] == '5' || serverBoard[xPos][yPos+1] == 'O'){
				battlefieldBoard[xPos][yPos+1] = 'O';
			}else{
				battlefieldBoard[xPos][yPos+1] = 'X';
			}
			//middle right
			if(serverBoard[xPos+1][yPos] == '1' || serverBoard[xPos+1][yPos] == '2' || serverBoard[xPos+1][yPos] == '3' || serverBoard[xPos+1][yPos] == '4' || serverBoard[xPos+1][yPos] == '5' || serverBoard[xPos+1][yPos] == 'O'){
				battlefieldBoard[xPos+1][yPos] = 'O';
			}else{
				battlefieldBoard[xPos+1][yPos] = 'X';
			}
			//middle
			 if(serverBoard[xPos][yPos] == '1' || serverBoard[xPos][yPos] == '2' || serverBoard[xPos][yPos] == '3' || serverBoard[xPos][yPos] == '4' || serverBoard[xPos][yPos] == '5' || serverBoard[xPos][yPos]== 'O'){
				battlefieldBoard[xPos][yPos] = 'O';
			}else{
				battlefieldBoard[xPos][yPos] = 'X';			
			}
			//middle left
			if(serverBoard[xPos-1][yPos] == '1' || serverBoard[xPos-1][yPos] == '2' || serverBoard[xPos-1][yPos] == '3' || serverBoard[xPos-1][yPos] == '4' || serverBoard[xPos-1][yPos] == '5' || serverBoard[xPos-1][yPos]== 'O'){
				battlefieldBoard[xPos-1][yPos] = 'O';
			}else{
				battlefieldBoard[xPos-1][yPos] = 'X';			
			}	
			//top
			if(serverBoard[xPos][yPos-1] == '1' || serverBoard[xPos][yPos-1] == '2' || serverBoard[xPos][yPos-1] == '3' || serverBoard[xPos][yPos-1] == '4' || serverBoard[xPos][yPos-1] == 'O' || serverBoard[xPos][yPos-1] == '5'){
				battlefieldBoard[xPos][yPos-1] = 'O';
			}else{
				battlefieldBoard[xPos][yPos-1] = 'X';
			}
			printf("MY BOARD\n");
			dispBoard(clientBoard);
			printf("My Points: %d/15\n", playerB);
			printf("Enemy Points: %d/15\n", playerA);
			printf(ANSI_COLOR_RED"ENEMY BOARD\n" ANSI_COLOR_RESET);
			dispBoard(battlefieldBoard);
				
			checkHealth(playerA,playerB);
	        break;
		}
    }
    
    return 0;
}

