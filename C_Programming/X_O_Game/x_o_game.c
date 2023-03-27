/** @file x_o_game.c
 *  @brief Mini Console X-O game with 2 players. *
 *  @author Hossam Elwahsh
 *  @bug No known bugs.
 */

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

#define DEBUG 0

// returns player config index
#define GET_PLYR_INDEX(playerNumber) (playerNumber - 1)

// returns opposite player config index
#define GET_OPP_PLYR_INDEX(playerNumber) (playerNumber == 1?1:0)

void drawBoard(uint8_t *board); // draws X-O board to console
void updateBoard(uint8_t *board, uint8_t position, uint8_t value);
void setPlayerConfig(uint8_t *configArray);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t * symbol);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t *board, uint8_t *gameState);

// global vars
uint8_t configArray[2] = {' ', ' '};
uint8_t board[] = "123456789";
uint8_t gameState = 2;
uint8_t currentPlayer = 1;

//region Board
/**
 * @brief Prints given X-O board to console
 *
 *  @param board pointer to board data
 *  @return void
 */
void drawBoard(uint8_t *board){

    printf("%s", "\n=============");
    printf("%s", "\n=    X/O    =");
    printf("%s", "\n=============\n");
    for (int i = 0; i < 9; i += 3) {
        printf("| %c | %c | %c |\n", board[i], board[i+1], board[i+2]);
    }
    printf("%s", "=============\n");
}

/**
 * @brief Updates a given XO board with a value in a given position.
 *
 *  @param board pointer to XO board
 *  @param position the position on board
 *  @param value the value (char) to put in position
 *  @return void
 */
void updateBoard(uint8_t *board, uint8_t position, uint8_t value) {
#if DEBUG
    printf("\n\n** Updated board pos %u = %c**\n\n", position, value);
#endif
    board[position] = value;
}
//endregion


//region Players Config
/**
 * @brief This function will take player number and asks the player to choose between 'X' and 'O' (case insensitive)
 *
 *  @param playerNumber 1 or 2
 *  @param symbol 'X' or 'O' (case insensitive)
 *  @return
 *      0: when the input symbol is not wrong and/or was not chosen before\n
 *      1: when the input symbol is wrong and/or was chosen before
 */
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t *symbol) {

    char chosenSymbol;

    // Prompt player<num> to choose symbol until a valid symbol is entered
    printf("Player %d, choose your preferred symbol (X or O): ", playerNumber);
    fflush(stdin);
    scanf(" %c", &chosenSymbol);

    // Convert input symbol to uppercase to simplify checking
    chosenSymbol = toupper(chosenSymbol);

    // Check if input symbol is valid
    if (chosenSymbol == 'X' || chosenSymbol == 'O') {

        // Check if input symbol has already been chosen by the other player
        if (chosenSymbol != (symbol[GET_OPP_PLYR_INDEX(playerNumber)]))
        {
            // Save input symbol as chosen symbol for the player
            symbol[GET_PLYR_INDEX(playerNumber)] = chosenSymbol;
            return 0;
        } else {
            // Symbol is in use / chosen before
            return 1;
        }
    } else {
        // Invalid symbol not X or O
        return 1;
    }

}

/**
 * This function will prompt and asks each user about their preferred symbols and saves it in the configArray
 *  Deliver these two functions as requested and without changing
 * @param configArray
 */
void setPlayerConfig(uint8_t *configArray){

    for (uint8_t playerNumber = 1; playerNumber <= 2; playerNumber++) {
        while (1)
        {
            uint8_t res = getPlayerSymbol(playerNumber, configArray);
            if(res == 0)
            {
                system("cls");
                printf("Symbol set for playerNumber (%u): %c\n\n", playerNumber, configArray[GET_PLYR_INDEX(playerNumber)]);
                break;
            }else{
                system("cls");
                printf("input symbol is wrong and/or was chosen before, try again\n");
            }
        }
    }
    system("cls");
    printf("\n------------");
    printf("\n- Symbols  -");
    printf("\n------------");
    printf("\nPlayer 1: %c", configArray[0]);
    printf("\nPlayer 2: %c", configArray[1]);
    printf("\n------------");

}
//endregion

/**
 * This function will take player's number then load his config, asks him for the position then updates the board
 * @param playerNumber 1 or 2
 */
void loadAndUpdate(uint8_t playerNumber) {

    // load config
    int8_t pos = 0;

    // ask for position
    while(1) {
        fflush(stdin);
        printf("\nPlayer %u (%c) turn, Choose a pos: ", playerNumber, configArray[GET_PLYR_INDEX(playerNumber)]);
        scanf("%d", &pos);
         if(pos < 1 || pos > 9 || board[pos-1] == 'X' || board[pos-1] == 'O')
         {
             printf("\nIncorrect position, try again");
             continue;
         }else{
             updateBoard(board, pos-1, configArray[GET_PLYR_INDEX(playerNumber)]);
             break;
         }
    }

    // update board
    //updateBoard(board, pos, configVal);

}

/**
 * This function will check after each move if there is a win, draw or continue playing.
 * @param gameState
 * @return sets gameState\n
 *  0: for winning \n
 *  1: for draw \n
 *  2: for continue
 */
void getGameState(uint8_t *board, uint8_t *gameState){

    // check for rows
    for (int i = 0; i < 9; i += 3) {
        if((board[i] == 'X' || board[i] == 'O'))
        {
            if(board[i] == board[i+1] && board[i+1] == board[i+2])
            {
                *gameState = 0; // win
                return;
            }
        }
    }

    // check for cols
    for (int i = 0; i < 3; i++) {
        if((board[i] == 'X' || board[i] == 'O'))
        {
            if(board[i] == board[i+3] && board[i+3] == board[i+6])
            {
                *gameState = 0; // win
                return;
            }
        }
    }


    // check for diags
    // diag 1
    if((board[4] == 'X' || board[4] == 'O')) // center
    {
        if((board[0] == board[4] && board[4] == board[8]) ||
           (board[2] == board[4] && board[4] == board[6]))
        {
            *gameState = 0; // win
            return;
        }
    }

    // check for continue
    for (int i = 0; i < 9; ++i) {
        if(board[i] != 'X' && board[i] != 'O')
        {
            *gameState = 2; // continue
            return;
        }
    }

    *gameState = 1; // draw
}

void RestartGame()
{
    gameState = 2;
    for (int i = 0; i < 9; i++) {
        board[i] = '1'+i;
    }
    currentPlayer = 1;
}

void play()
{
    // start with player 1
    currentPlayer = 1;

    // start game
    drawBoard(board);

    while(gameState != 0 && gameState != 1)
    {
        // Player `currentPlayer` move
        loadAndUpdate(currentPlayer);

        system("cls");
        drawBoard(board);

        // Game State Check
        getGameState(board, &gameState);

        if (gameState == 0) {
            printf("Player %u (%c) Wins\n", currentPlayer, configArray[GET_PLYR_INDEX(currentPlayer)]);
        }
        else if (gameState == 1) {
            printf("Game over, it's a draw!\n");
        }
        else if (gameState == 2) {
            // switch players
            currentPlayer = (currentPlayer == 1 ? 2 : 1);
        }
    }

    system("pause");
}

// Implement the main flow according to your understanding of the game
int main() {
    gameState = 2;
    // prompt for players configuration
    setPlayerConfig(configArray);

    uint8_t playAgain = 1;

    while (1)
    {
        system("cls");
        RestartGame();
        play();

        printf("type (y) to play again, or anything to exit:");
        fflush(stdin);
        scanf("%c", &playAgain);

        if(playAgain == 'y')
        {
            continue;
        }
        else{
            break;
        }

    }
}