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
#define ANSI_COLOR_GREEN "\x1b[1;32m"

/*
    D = Destroyer (1 Shot)
    B = BattleShip(Cross Shot)
    S = Submarine(Straight Line Shot)
    C = Carrier(3 Shots)
*/

void title(){
	printf("\n");
	printf(ANSI_COLOR_YELLOW"\tBBBBBBBBBBB                A            TTTTTTTTTTTTTTT   TTTTTTTTTTTTTTT   LLL              EEEEEEEEEEEE  \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB     BBBB              AAA           TTTTTTTTTTTTTTT   TTTTTTTTTTTTTTT   LLL              EEEEEEEEEEEE  \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB       BBB            AA AA                TTT               TTT         LLL              EEE           \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB       BBB           AA   AA               TTT               TTT         LLL              EEE           \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB     BBBB           AA     AA              TTT               TTT         LLL              EEE           \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBBBBBBBBBB           AA       AA             TTT               TTT         LLL              EEEEEEEE      \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBBBBBBBBBB          AAAAAAAAAAAAA            TTT               TTT         LLL              EEEEEEEE      \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB      BBBB       AAA         AAA           TTT               TTT         LLL              EEE           \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB        BBB     AAA           AAA          TTT               TTT         LLL              EEE           \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB        BBB    AAA             AAA         TTT               TTT         LLL              EEE           \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBB      BBBB    AAA               AAA        TTT               TTT         LLLLLLLLLLLLLL   EEEEEEEEEEEE  \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\tBBBBBBBBBBBB    AAA                 AAA       TTT               TTT         LLLLLLLLLLLLLL   EEEEEEEEEEEE  \n"ANSI_COLOR_RESET);
	printf("\n\n");
	printf(ANSI_COLOR_YELLOW"\t             SSSSSSSSS     HHH         HHH     IIII     PPPPPPPPPPPP                                  \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t           SSSSSSSSSS      HHH         HHH     IIII     PPPPPPPPPPPPP               +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t          SSSSS            HHH         HHH     IIII     PPP      PPPPP              +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t         SSSS              HHH         HHH     IIII     PPP        PPP              +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t         SSSS              HHH         HHH     IIII     PPP        PPP              +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t          SSSSS            HHHHHHHHHHHHHHH     IIII     PPP      PPPPP       +++++++++++++++++      \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t           SSSSSSSSSS      HHHHHHHHHHHHHHH     IIII     PPPPPPPPPPPPP        +++++++++++++++++      \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t                 SSSSS     HHH         HHH     IIII     PPPPPPPPPPP                 +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t                   SSSS    HHH         HHH     IIII     PPP                         +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t                   SSSS    HHH         HHH     IIII     PPP                         +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t                 SSSSS     HHH         HHH     IIII     PPP                         +++                \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t           SSSSSSSSSS      HHH         HHH     IIII     PPP                                             \n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"\t          SSSSSSSSS        HHH         HHH     IIII     PPP                                             \n"ANSI_COLOR_RESET);
	printf("\n\n");
	printf(ANSI_COLOR_GREEN"\t\t\tPresented by: "ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN" Frederick Daluro"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN" Ralph Eufracio "ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN" Kyle Nolan\n\n"ANSI_COLOR_RESET);
	
	
}

void instruction(){
		system("clear");
		printf("\tLegend: [X] = MISS\n");
		printf("\t\t[O] = HIT\n");
		printf("\t\t[?] = A SHIP IS NEAR\n");
		printf("\t\t[D]Destroyer = ATTACKS ONE TILE\n");
		printf("\t\t[L]Cruiser = DETECTS IF ENEMY SHIP IS NEARBY \n");
		printf("\t\t[S]Submarine = ATTACKS FOUR TILES HORINONTALLY\n");
		printf("\t\t[B]Battleship = ATTACKS TILES IN A PLUS POSITION  \n");
		printf("\t\t[C]Carrier = ATTACKS ONE TILE THREE TIMES\n");
		printf("\t\tNUMBER = POSITION OF SHIP\n");
}


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

    }else if(direction == 'V' || direction == 'v'){
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
	char letter[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
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
				if(board[j][i] == 'X' || board[j][i] == 'x'){
					printf(ANSI_COLOR_RED"%c "ANSI_COLOR_RESET, board[j][i]);
				}
				else if(board[j][i] == 'O' || board[j][i] == 'o'){
					printf(ANSI_COLOR_YELLOW"%c "ANSI_COLOR_RESET, board[j][i]);
				}
				else if(board[j][i] == '1' || board[j][i] == '2' || board[j][i] == '3' || board[j][i] == '4' || board[j][i] == '5' || board[j][i] == '?'){
					printf(ANSI_COLOR_GREEN"%c "ANSI_COLOR_RESET, board[j][i]);
				}
				else{
					printf(ANSI_COLOR_CYAN"%c "ANSI_COLOR_RESET, board[j][i]);
				}
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

void sendBoard(char buffer[256], int client_sock, int xPos, char yPos, int shipSize, char direction){
	buffer[0] = xPos + '0';
	buffer[1] = yPos;
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

int chartoInt(char yPos){
	if(yPos == 'A' || yPos == 'a'){
		return 0;
	}else if (yPos == 'B' || yPos == 'b'){
		return 1;
	}else if (yPos == 'C' || yPos == 'c'){
		return 2;
	}else if (yPos == 'D' || yPos == 'd'){
		return 3;
	}else if (yPos == 'E' || yPos == 'e'){
		return 4;
	}else if (yPos == 'F' || yPos == 'f'){
		return 5;
	}else if (yPos == 'G' || yPos == 'g'){
		return 6;
	}else if (yPos == 'H' || yPos == 'h'){
		return 7;
	}else if (yPos == 'I' || yPos == 'i'){
		return 8;
	}else if (yPos == 'J' || yPos == 'j'){
		return 9;
	}
}

int main(int argc, char *argv[]){

	char serverBoard[COLUMNS][ROWS];
	char clientBoard[COLUMNS][ROWS];

	char battlefieldBoard[COLUMNS][ROWS]; // this board will be displayed instead of clientBoard

    int xPos;
	char yPos;
    int shipSize = 0;
	char direction;

    int playerA = 15;
    int playerB = 15;

	char sortie;
	char sortieReceived;

    int cdBattleship = 0; // if zero the skill is available for use.
    int cdSubmarine = 0;
    int cdDestroyer = 0;
    int cdCarrier = 0;
    int cdCruiser = 0;

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
	system("clear");

	TITLE:
	title();

	char choice;
	char command;

	printf("\tY = Play  N = EXIT  I = Instructions\n\n");
	printf("Press Y/N/I: ");
	scanf(" %c", &choice);
	
	switch(choice){
		case 'n':
		case 'N':
			exit(0);
		break;

		case 'i':
		case 'I':
			instruction();
			printf("\tY = Play  N = EXIT\n\n");
			printf("Press Y/N: ");
			scanf(" %c", &command);
			if(command == 'n' || command == 'N'){
				system("clear");
				goto TITLE;
			}else{
				system("clear");
				goto GAME;
			}
		break;

		case 'y':
		case 'Y':
	 		//continue
			system("clear");
		break;
	}

	GAME:for(int i = 1; i<= 5; i++){
        shipSize = i;
        do{
			printf("\tPlace your ships in the board\n");
			dispBoard(serverBoard);
            printf("Enter X & Y coordinates (1-10) Ship size %d and Direction H(horizontal)|V(Vertical): ", i);
			bzero(buffer, 256);
			scanf(" %c %d %c", &yPos,&xPos,&direction);

			sendBoard(buffer, client_sock, xPos, yPos, shipSize,direction);
			shipPlacement(xPos, chartoInt(yPos), shipSize, direction, serverBoard);
			system("clear");
			dispBoard(serverBoard);

            //printf("%d %d %c\n",xPos, yPos, direction); // use for debugging
            //shipPlacement(xPos, yPos, shipSize, direction, board);
			printf("Waiting for opponents turn...\n");
			bzero(buffer, 256);
			recv(client_sock, buffer, 255, 0);

			shipPlacement(buffer[0] - '0', chartoInt(buffer[1]), buffer[2] - '0', buffer[3], clientBoard);
			system("clear");

        }while(!correctPlacement(xPos, chartoInt(yPos), shipSize, direction));


    }
	system("clear");
	printf("MY BOARD\n");
	dispBoard(serverBoard);
	printf("My Points: %d/15\n", playerA);
    printf("Enemy Points: %d/15\n", playerB);
	printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);
	dispBoard(battlefieldBoard);

    while(playerA != 0 || playerB != 0){

        cdBattleship = cdBattleship - 1;
        cdCarrier = cdCarrier -1;
        cdCruiser = cdCruiser -1;
        cdSubmarine = cdSubmarine -1;

        if(cdBattleship <= 0){
            cdBattleship = 0;
        }if(cdCarrier <= 0){
            cdCarrier = 0;
        }if(cdDestroyer <= 0){
            cdDestroyer = 0;
        }if(cdCruiser <= 0){
            cdCruiser = 0;
        }if(cdSubmarine <= 0){
            cdSubmarine = 0;
        }

        do{
            printf("[%d]D [%d]L [%d]S [%d]B [%d]C: ", cdDestroyer, cdCruiser, cdSubmarine, cdBattleship, cdCarrier);
            scanf(" %c", &sortie);

            if((sortie == 'd' || sortie == 'D') && cdDestroyer == 0){
                goto ATTACK;
            }else if((sortie == 'b' || sortie == 'B') && cdBattleship == 0){
                goto ATTACK;
            }else if((sortie == 's' || sortie == 'S') && cdSubmarine == 0){
                goto ATTACK;
            }else if((sortie == 'c' || sortie == 'C') && cdCarrier == 0){
                goto ATTACK;
            }else if((sortie == 'l' || sortie == 'L') && cdCruiser == 0){
                goto ATTACK;
            }
        }while(true);

		ATTACK:switch(sortie){
		case 'D':
		case 'd':
			printf("Enter Y(A-J) & X coordinates (0-9): ");
			scanf(" %c %d", &yPos, &xPos);

		    bzero(buffer, 256);
		    buffer[0] = xPos + '0';
		    buffer[1] = yPos;
			buffer[2] = sortie;

		    n = send(client_sock, buffer, strlen(buffer), 0);

			if(clientBoard[xPos][chartoInt(yPos)] == '1' || clientBoard[xPos][chartoInt(yPos)] == '2' || clientBoard[xPos][chartoInt(yPos)] == '3' || clientBoard[xPos][chartoInt(yPos)] == '4' || clientBoard[xPos][chartoInt(yPos)] == '5' || clientBoard[xPos][chartoInt(yPos)] == 'O'){
				if(clientBoard[xPos][chartoInt(yPos)] == 'O'){
					battlefieldBoard[xPos][chartoInt(yPos)] = 'O';
				}else{
					battlefieldBoard[xPos][chartoInt(yPos)] = 'O';
					clientBoard[xPos][chartoInt(yPos)] = 'O';
					playerB = playerB - 1;
				}
			}else{
				battlefieldBoard[xPos][chartoInt(yPos)] = 'X';
			}
			break;
		case 'b':
		case 'B':
			printf("Enter Y(A-J) & X(0-9): ");
			scanf(" %c %d", &yPos,&xPos);

			bzero(buffer, 256);
		    buffer[0] = xPos + '0';
		    buffer[1] = yPos;
			buffer[2] = sortie;
		    n = send(client_sock, buffer, strlen(buffer), 0);

			//Center
			if(clientBoard[xPos][chartoInt(yPos)] == '1' || clientBoard[xPos][chartoInt(yPos)] == '2' ||clientBoard[xPos][chartoInt(yPos)] == '3' ||clientBoard[xPos][chartoInt(yPos)] == '4' ||clientBoard[xPos][chartoInt(yPos)] == '5' || clientBoard[xPos][chartoInt(yPos)] == 'O'){
				if(clientBoard[xPos][chartoInt(yPos)] == 'O'){
					clientBoard[xPos][chartoInt(yPos)] = 'O';
				}else{
					battlefieldBoard[xPos][chartoInt(yPos)] = 'O';
		            clientBoard[xPos][chartoInt(yPos)] = 'O';
					playerB = playerB -1;
				}
			}else{
				battlefieldBoard[xPos][chartoInt(yPos)] = 'X';
			}
			//Left
			if(clientBoard[xPos-1][chartoInt(yPos)] == '1' || clientBoard[xPos-1][chartoInt(yPos)] == '2' ||clientBoard[xPos-1][chartoInt(yPos)] == '3' ||clientBoard[xPos-1][chartoInt(yPos)] == '4' ||clientBoard[xPos-1][chartoInt(yPos)] == '5' || clientBoard[xPos-1][chartoInt(yPos)] == 'O'){
				if(clientBoard[xPos-1][chartoInt(yPos)] == 'O'){
					clientBoard[xPos-1][chartoInt(yPos)] == 'O';
				}else{
					battlefieldBoard[xPos-1][chartoInt(yPos)] = 'O';
                	clientBoard[xPos-1][chartoInt(yPos)] = 'O';
					playerB = playerB -1;
				}
			}else{
				battlefieldBoard[xPos-1][chartoInt(yPos)] = 'X';
			}
			//Right
			if(clientBoard[xPos+1][chartoInt(yPos)] == '1' || clientBoard[xPos+1][chartoInt(yPos)] == '2' ||clientBoard[xPos+1][chartoInt(yPos)] == '3' ||clientBoard[xPos+1][chartoInt(yPos)] == '4' ||clientBoard[xPos+1][chartoInt(yPos)] == '5' || clientBoard[xPos+1][chartoInt(yPos)] == 'O' ){
				if(clientBoard[xPos+1][chartoInt(yPos)] == 'O'){
					clientBoard[xPos+1][chartoInt(yPos)] == 'O'; 
				}else{
					battlefieldBoard[xPos+1][chartoInt(yPos)] = 'O';
		            clientBoard[xPos+1][chartoInt(yPos)] = 'O';
					playerB = playerB -1;
				}
			}else{
				battlefieldBoard[xPos+1][chartoInt(yPos)] = 'X';
			}

			//Top

			if(clientBoard[xPos][chartoInt(yPos)-1] == '1' || clientBoard[xPos][chartoInt(yPos)-1] == '2' ||clientBoard[xPos][chartoInt(yPos)-1] == '3' ||clientBoard[xPos][chartoInt(yPos)-1] == '4' ||clientBoard[xPos][chartoInt(yPos)-1] == '5' || clientBoard[xPos][chartoInt(yPos)-1] == 'O' ){
				if(clientBoard[xPos][chartoInt(yPos)-1] == 'O'){
					clientBoard[xPos][chartoInt(yPos)-1] == 'O';
				}else{
					battlefieldBoard[xPos][chartoInt(yPos)-1] = 'O';
		            clientBoard[xPos][chartoInt(yPos)-1] = 'O';
					playerB = playerB -1;
				}
			}else{
				battlefieldBoard[xPos][chartoInt(yPos)-1] = 'X';
			}
			//Bottom
			if(clientBoard[xPos][chartoInt(yPos)+1] == '1' || clientBoard[xPos][chartoInt(yPos)+1] == '2' ||clientBoard[xPos][chartoInt(yPos)+1] == '3' ||clientBoard[xPos][chartoInt(yPos)+1] == '4' ||clientBoard[xPos][chartoInt(yPos)+1] == '5' || clientBoard[xPos][chartoInt(yPos)+1] == 'O'){
				if(clientBoard[xPos][chartoInt(yPos)+1] == 'O'){
					clientBoard[xPos][chartoInt(yPos)+1] == '5';
				}else{
					battlefieldBoard[xPos][chartoInt(yPos)+1] = 'O';
		            clientBoard[xPos][chartoInt(yPos)+1] = 'O';
					playerB = playerB -1;
				}
			}else{
				battlefieldBoard[xPos][chartoInt(yPos)+1] = 'X';
			}

            cdBattleship = 5;
            break;

		case 'C':
		case 'c':
		//    0       1       2       3       4       5       6
		//| xPos1 | yPos1 | xPos2 | yPos2 | xPos3 | yPos3 | sortie |
		// 0 + (2 * i) / 1 + (2 * i)
		bzero(buffer, 256);
			for(int i = 0; i <= 2; i++){
				printf("Enter Y(A-J) & X(0-9): ");
				scanf(" %c %d", &yPos,&xPos);
				
				buffer[0+(2 * i)] = xPos + '0';
				buffer[1+(2 * i)] = yPos;
			}	
				buffer[6] = sortie;	
				
				n = send(client_sock, buffer, strlen(buffer), 0);

			for(int i = 0; i<= 2; i++){
				if(clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == '1' || clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == '2' || clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == '3' || clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == '4' || clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == '5' || clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == 'O'){
					if(clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == 'O'){
						clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] == 'O';
					}else{
						battlefieldBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] = 'O';
						clientBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] = 'O';
						playerB = playerB - 1;
					}
				}else{
					battlefieldBoard[buffer[0+(2 * i)] - '0'][chartoInt(buffer[1+(2 * i)])] = 'X';
				}
			}

            cdCarrier = 5;
			break;
		case 's':
		case 'S':
			printf("Enter Y(A-J) & X(0-9): ");
			scanf(" %c %d", &yPos,&xPos);

            bzero(buffer, 256);
		    buffer[0] = xPos + '0';
		    buffer[1] = yPos;
			buffer[2] = sortie;
		    n = send(client_sock, buffer, strlen(buffer), 0);

			for(int i=0; i<4; i++){
				if(clientBoard[xPos+i][chartoInt(yPos)] == '1' || clientBoard[xPos+i][chartoInt(yPos)] == '2' || clientBoard[xPos+i][chartoInt(yPos)] == '3' || clientBoard[xPos+i][chartoInt(yPos)] == '4' || clientBoard[xPos+i][chartoInt(yPos)] == '5' || clientBoard[xPos+i][chartoInt(yPos)] == 'O'){
					if(clientBoard[xPos+i][chartoInt(yPos)] == 'O'){
						clientBoard[xPos+i][chartoInt(yPos)] == 'O';
					}else{
						battlefieldBoard[xPos+i][chartoInt(yPos)] = 'O';
		                clientBoard[xPos+i][chartoInt(yPos)] = 'O';
		                playerB = playerB - 1;
					}
				}
				else{
					battlefieldBoard[xPos+i][chartoInt(yPos)] = 'X';
				}
			}
            cdSubmarine = 5;
	        break;
		case 'l':
		case 'L':
			printf("Enter Y(A-J) & X(0-9): ");
			scanf(" %c %d",&yPos, &xPos);

			bzero(buffer, 256);
		    buffer[0] = xPos + '0';
		    buffer[1] = yPos;
			buffer[2] = sortie;
		    n = send(client_sock, buffer, strlen(buffer), 0);
			
			if(clientBoard[xPos][chartoInt(yPos)] == '1' || clientBoard[xPos][chartoInt(yPos)] == '2' || clientBoard[xPos][chartoInt(yPos)] == '3' || clientBoard[xPos][chartoInt(yPos)] == '4' || clientBoard[xPos][chartoInt(yPos)] == '5'){
				if(clientBoard[xPos][chartoInt(yPos)] == 'O'){
					battlefieldBoard[xPos][chartoInt(yPos)] = 'O';
				}else{
					battlefieldBoard[xPos][chartoInt(yPos)] = 'O';
					playerB = playerB - 1;
				}
			}else if(clientBoard[xPos-1][chartoInt(yPos)-1] == '1' || clientBoard[xPos-1][chartoInt(yPos)] == '1' || clientBoard[xPos-1][chartoInt(yPos)+1] == '1' || 	//Top
					clientBoard[xPos-1][chartoInt(yPos)-1] == '2' || clientBoard[xPos-1][chartoInt(yPos)] == '2' || clientBoard[xPos-1][chartoInt(yPos)+1] == '2' ||
					clientBoard[xPos-1][chartoInt(yPos)-1] == '3' || clientBoard[xPos-1][chartoInt(yPos)] == '3' || clientBoard[xPos-1][chartoInt(yPos)+1] == '3' ||
					clientBoard[xPos-1][chartoInt(yPos)-1] == '4' || clientBoard[xPos-1][chartoInt(yPos)] == '4' || clientBoard[xPos-1][chartoInt(yPos)+1] == '4' ||
					clientBoard[xPos-1][chartoInt(yPos)-1] == '5' || clientBoard[xPos-1][chartoInt(yPos)] == '5' || clientBoard[xPos-1][chartoInt(yPos)+1] == '5'){
					
					battlefieldBoard[xPos][chartoInt(yPos)] = '?';
			
			}else if(clientBoard[xPos][chartoInt(yPos)-1] == '1' || clientBoard[xPos][chartoInt(yPos)] == '1' || clientBoard[xPos][chartoInt(yPos)+1] == '1' || 	//Mid
					clientBoard[xPos][chartoInt(yPos)-1] == '2' || clientBoard[xPos][chartoInt(yPos)] == '2' || clientBoard[xPos][chartoInt(yPos)+1] == '2' ||
					clientBoard[xPos][chartoInt(yPos)-1] == '3' || clientBoard[xPos][chartoInt(yPos)] == '3' || clientBoard[xPos][chartoInt(yPos)+1] == '3' ||
					clientBoard[xPos][chartoInt(yPos)-1] == '4' || clientBoard[xPos][chartoInt(yPos)] == '4' || clientBoard[xPos][chartoInt(yPos)+1] == '4' ||
					clientBoard[xPos][chartoInt(yPos)-1] == '5' || clientBoard[xPos][chartoInt(yPos)] == '5' || clientBoard[xPos][chartoInt(yPos)+1] == '5'){
					
					battlefieldBoard[xPos][chartoInt(yPos)] = '?';

			}else if(clientBoard[xPos+1][chartoInt(yPos)-1] == '1' || clientBoard[xPos+1][chartoInt(yPos)] == '1' || clientBoard[xPos+1][chartoInt(yPos)+1] == '1' || 	//Bot
					clientBoard[xPos+1][chartoInt(yPos)-1] == '2' || clientBoard[xPos+1][chartoInt(yPos)] == '2' || clientBoard[xPos+1][chartoInt(yPos)+1] == '2' ||
					clientBoard[xPos+1][chartoInt(yPos)-1] == '3' || clientBoard[xPos+1][chartoInt(yPos)] == '3' || clientBoard[xPos+1][chartoInt(yPos)+1] == '3' ||
					clientBoard[xPos+1][chartoInt(yPos)-1] == '4' || clientBoard[xPos+1][chartoInt(yPos)] == '4' || clientBoard[xPos+1][chartoInt(yPos)+1] == '4' ||
					clientBoard[xPos+1][chartoInt(yPos)-1] == '5' || clientBoard[xPos+1][chartoInt(yPos)] == '5' || clientBoard[xPos+1][chartoInt(yPos)+1] == '5'){
					
					battlefieldBoard[xPos][chartoInt(yPos)] = '?';
			}else{
				battlefieldBoard[xPos][chartoInt(yPos)] = 'X';
			}
			cdCruiser = 4;
			break;
		}
		system("clear");
        checkHealth(playerA, playerB);

        printf("MY BOARD\n");
        dispBoard(serverBoard);
        printf("My Points: %d/15\n", playerA);
        printf("Enemy Points: %d/15\n", playerB);
        printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);
        dispBoard(battlefieldBoard);
		
		printf("PREPARE FOR IMPACT!!!\n");
		bzero(buffer, 256);
		recv(client_sock, buffer, 255, 0);
		xPos = buffer[0] - '0';
		yPos = buffer[1];
		
		if(strlen(buffer) > 3){
			sortieReceived = buffer[6];
		}else{
			sortieReceived = buffer[2];
		}

		switch(sortieReceived){
            case 'd':
            case 'D':

                if(serverBoard[xPos][chartoInt(yPos)] == '1' || serverBoard[xPos][chartoInt(yPos)] == '2' || serverBoard[xPos][chartoInt(yPos)] == '3' || serverBoard[xPos][chartoInt(yPos)] == '4' || serverBoard[xPos][chartoInt(yPos)] == '5' || serverBoard[xPos][chartoInt(yPos)] == 'O'){
					if(serverBoard[xPos][chartoInt(yPos)] == 'O'){
						serverBoard[xPos][chartoInt(yPos)] = 'O';
					}else{
		                serverBoard[xPos][chartoInt(yPos)] = 'O';
		                playerA = playerA - 1;
					}
                }else{
                    serverBoard[xPos][chartoInt(yPos)] = 'X';
                }
                break;
            case 'B':
            case 'b':
                //Center
                if(serverBoard[xPos][chartoInt(yPos)] == '1' || serverBoard[xPos][chartoInt(yPos)] == '2' ||serverBoard[xPos][chartoInt(yPos)] == '3' ||serverBoard[xPos][chartoInt(yPos)] == '4' ||serverBoard[xPos][chartoInt(yPos)] == '5' || serverBoard[xPos][chartoInt(yPos)] == 'O'){
					if(serverBoard[xPos][chartoInt(yPos)] == 'O'){
						serverBoard[xPos][chartoInt(yPos)] == 'O';
					}else{
		                serverBoard[xPos][chartoInt(yPos)] = 'O';
		                playerA = playerA - 1;
					}
                }else{
                    serverBoard[xPos][chartoInt(yPos)] = 'X';
                }
                //Left
                if(serverBoard[xPos-1][chartoInt(yPos)] == '1' || serverBoard[xPos-1][chartoInt(yPos)] == '2' ||serverBoard[xPos-1][chartoInt(yPos)] == '3' ||serverBoard[xPos-1][chartoInt(yPos)] == '4' ||serverBoard[xPos-1][chartoInt(yPos)] == '5' || serverBoard[xPos-1][chartoInt(yPos)] == 'O'){
					if(serverBoard[xPos-1][chartoInt(yPos)] == 'O'){
						serverBoard[xPos-1][chartoInt(yPos)] == 'O';
					}else{
		                serverBoard[xPos-1][chartoInt(yPos)] = 'O';
		                playerA = playerA - 1;
					}
                }else{
                    serverBoard[xPos-1][chartoInt(yPos)] = 'X';
                }
                //Right
                if(serverBoard[xPos+1][chartoInt(yPos)] == '1' || serverBoard[xPos+1][chartoInt(yPos)] == '2' ||serverBoard[xPos+1][chartoInt(yPos)] == '3' ||serverBoard[xPos+1][chartoInt(yPos)] == '4' ||serverBoard[xPos+1][chartoInt(yPos)] == '5' || serverBoard[xPos+1][chartoInt(yPos)] == '5'){
					if(serverBoard[xPos+1][chartoInt(yPos)] == 'O'){
						serverBoard[xPos+1][chartoInt(yPos)] == 'O';
					}else{
		                serverBoard[xPos+1][chartoInt(yPos)] = 'O';
		                playerA = playerA - 1;
					}
                }else{
                    serverBoard[xPos+1][chartoInt(yPos)] = 'X';
                }

                //Top

                if(serverBoard[xPos][chartoInt(yPos)-1] == '1' || serverBoard[xPos][chartoInt(yPos)-1] == '2' ||serverBoard[xPos][chartoInt(yPos)-1] == '3' ||serverBoard[xPos][chartoInt(yPos)-1] == '4' ||serverBoard[xPos][chartoInt(yPos)-1] == '5' || serverBoard[xPos][chartoInt(yPos)-1] == 'O'){
					if(serverBoard[xPos][chartoInt(yPos)-1] == 'O'){
						serverBoard[xPos][chartoInt(yPos)-1] == 'O';
					}else{
		                serverBoard[xPos][chartoInt(yPos)-1] = 'O';
		                playerA = playerA - 1;
					}
                }else{
                    serverBoard[xPos][chartoInt(yPos)-1] = 'X';
                }
                //Bottom
                if(serverBoard[xPos][chartoInt(yPos)+1] == '1' || serverBoard[xPos][chartoInt(yPos)+1] == '2' ||serverBoard[xPos][chartoInt(yPos)+1] == '3' ||serverBoard[xPos][chartoInt(yPos)+1] == '4' ||serverBoard[xPos][chartoInt(yPos)+1] == '5' || serverBoard[xPos][chartoInt(yPos)+1] == 'O'){
					if(serverBoard[xPos][chartoInt(yPos)+1] == 'O'){
						serverBoard[xPos][chartoInt(yPos)+1] == 'O';
					}else{
		                serverBoard[xPos][chartoInt(yPos)+1] = 'O';
		                playerA = playerA - 1;
					}
                }else{
                    serverBoard[xPos][chartoInt(yPos)+1] = 'X';
                }
                break;
            case 's':
            case 'S':

                for(int i=0; i<4; i++){
                    if(serverBoard[xPos+i][chartoInt(yPos)] == '1' || serverBoard[xPos+i][chartoInt(yPos)] == '2' || serverBoard[xPos+i][chartoInt(yPos)] == '3' || serverBoard[xPos+i][chartoInt(yPos)] == '4' || serverBoard[xPos+i][chartoInt(yPos)] == '5' || serverBoard[xPos+i][chartoInt(yPos)] == 'O'){
						if(serverBoard[xPos+i][chartoInt(yPos)] == 'O'){
							serverBoard[xPos+i][chartoInt(yPos)] == 'O';
						}else{
		                    serverBoard[xPos+i][chartoInt(yPos)] = 'O';
		                    playerA = playerA - 1;
						}
                    }
                    else{
                        serverBoard[xPos+i][chartoInt(yPos)] = 'X';
                    }
                }
            	break;

			case 'C':
			case 'c':
			sortieReceived = buffer[6];
				for(int i =0; i <=2; i++){
					if(serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == '1' || serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == '2' || serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == '3' || serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == '4' || serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == '5' || serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == 'O'){
						if(serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == 'O'){
							serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] == 'O';
						}else{
							serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] = 'O';
							playerA = playerA -1;
						}
					}else{
						serverBoard[buffer[0+(2*i)] - '0'][chartoInt(buffer[1+(2*i)])] = 'X';
						}
				}
				break;
			case 'l':
			case 'L':
				
				if(serverBoard[xPos][chartoInt(yPos)] == '1' || serverBoard[xPos][chartoInt(yPos)] == '2' || serverBoard[xPos][chartoInt(yPos)] == '3' || serverBoard[xPos][chartoInt(yPos)] == '4' || serverBoard[xPos][chartoInt(yPos)] == '5'){
					if(serverBoard[xPos][chartoInt(yPos)] == 'O'){
						serverBoard[xPos][chartoInt(yPos)] = 'O';
					}else{
						serverBoard[xPos][chartoInt(yPos)] = 'O';
						playerA = playerA - 1;
					}
				}else if(serverBoard[xPos-1][chartoInt(yPos)-1] == '1' || serverBoard[xPos-1][chartoInt(yPos)] == '1' || serverBoard[xPos-1][chartoInt(yPos)+1] == '1' || 	//Top
						serverBoard[xPos-1][chartoInt(yPos)-1] == '2' || serverBoard[xPos-1][chartoInt(yPos)] == '2' || serverBoard[xPos-1][chartoInt(yPos)+1] == '2' ||
						serverBoard[xPos-1][chartoInt(yPos)-1] == '3' || serverBoard[xPos-1][chartoInt(yPos)] == '3' || serverBoard[xPos-1][chartoInt(yPos)+1] == '3' ||
						serverBoard[xPos-1][chartoInt(yPos)-1] == '4' || serverBoard[xPos-1][chartoInt(yPos)] == '4' || serverBoard[xPos-1][chartoInt(yPos)+1] == '4' ||
						serverBoard[xPos-1][chartoInt(yPos)-1] == '5' || serverBoard[xPos-1][chartoInt(yPos)] == '5' || serverBoard[xPos-1][chartoInt(yPos)+1] == '5'){
						
						serverBoard[xPos][chartoInt(yPos)] = '?';
				
				}else if(serverBoard[xPos][chartoInt(yPos)-1] == '1' || serverBoard[xPos][chartoInt(yPos)] == '1' || serverBoard[xPos][chartoInt(yPos)+1] == '1' || 	//Mid
						serverBoard[xPos][chartoInt(yPos)-1] == '2' || serverBoard[xPos][chartoInt(yPos)] == '2' || serverBoard[xPos][chartoInt(yPos)+1] == '2' ||
						serverBoard[xPos][chartoInt(yPos)-1] == '3' || serverBoard[xPos][chartoInt(yPos)] == '3' || serverBoard[xPos][chartoInt(yPos)+1] == '3' ||
						serverBoard[xPos][chartoInt(yPos)-1] == '4' || serverBoard[xPos][chartoInt(yPos)] == '4' || serverBoard[xPos][chartoInt(yPos)+1] == '4' ||
						serverBoard[xPos][chartoInt(yPos)-1] == '5' || serverBoard[xPos][chartoInt(yPos)] == '5' || serverBoard[xPos][chartoInt(yPos)+1] == '5'){
						
						serverBoard[xPos][chartoInt(yPos)] = '?';

				}else if(serverBoard[xPos+1][chartoInt(yPos)-1] == '1' || serverBoard[xPos+1][chartoInt(yPos)] == '1' || serverBoard[xPos+1][chartoInt(yPos)+1] == '1' || 	//Bot
						serverBoard[xPos+1][chartoInt(yPos)-1] == '2' || serverBoard[xPos+1][chartoInt(yPos)] == '2' || serverBoard[xPos+1][chartoInt(yPos)+1] == '2' ||
						serverBoard[xPos+1][chartoInt(yPos)-1] == '3' || serverBoard[xPos+1][chartoInt(yPos)] == '3' || serverBoard[xPos+1][chartoInt(yPos)+1] == '3' ||
						serverBoard[xPos+1][chartoInt(yPos)-1] == '4' || serverBoard[xPos+1][chartoInt(yPos)] == '4' || serverBoard[xPos+1][chartoInt(yPos)+1] == '4' ||
						serverBoard[xPos+1][chartoInt(yPos)-1] == '5' || serverBoard[xPos+1][chartoInt(yPos)] == '5' || serverBoard[xPos+1][chartoInt(yPos)+1] == '5'){
						
						serverBoard[xPos][chartoInt(yPos)] = '?';
				}else{
					serverBoard[xPos][chartoInt(yPos)] = 'X';
				}
				break;
		}
		system("clear");
		checkHealth(playerA, playerB);

        printf("MY BOARD\n");
        dispBoard(serverBoard);
        printf("My Points: %d/15\n", playerA);
		printf("Enemy Points: %d/15\n", playerB);
        printf(ANSI_COLOR_RED"ENEMY BOARD\n"ANSI_COLOR_RESET);
        dispBoard(battlefieldBoard);

    }
    close(client_sock);

    close(server_sock);

    return 0;
}



