#include <iostream>
#include <string>
#include <vector>
using namespace std;

//player is O 
//computer is X
//code is based on computer

//display board
void display(string board){
  for (int i=0;i<9;++i){
    cout << " " << board[i] << " ";
    if (i%3 == 2){
      cout << "\n";
      if (i != 8) cout << "---+---+---\n";
    }else {
      cout << "|";
    }
  }
}

//return a vector of boards after the next move
vector<string> moveCombinations(string board, char player){
  vector<string> combinations;
  for (int i=0;i<9;++i){
    if (board[i] == ' '){
      string combination = board;
      combination[i] = player;
      combinations.push_back(combination);
    }
  }
  return combinations;
}

//returns the board result if ended, else return 2
int result(string board){
  //result is based on computer (1 for win)
  //check horizontal match
  for (int i=0;i<9;i+=3){
    //check if there is no pieces on the position
    if (board[i]==' ') continue;
    //check if the whole row is the same
    if (board[i]==board[i+1] && board[i]==board[i+2]){
      return (board[i]=='X')? 1 : -1; 
    }
  }
  //check for vertical match
  for (int i=0;i<9;++i){
    //check if there is no pieces on the position
    if (board[i]==' ') continue;
    //check if the whole column is the same
    if (board[i]==board[i+3] && board[i]==board[i+6]){
      return (board[i]=='X')? 1 : -1; 
    }
  }
  //check for diagonal match
  if (board[4]!=' '){
    if ((board[0]==board[4]&&board[0]==board[8])||(board[2]==board[4]&&board[2]==board[6])){
      return board[4]=='X' ? 1 : -1;
    }
  }
  //check if game not end
  for (char i : board){
    if (i==' ') return 2;
  }
  //draw
  return 0;
}

//minimax function, used to find the best move
//X is the maximizing player
int minimax(string board, char player){
  //if the board has ended, return the result
  if (result(board)!=2) return result(board);
  //if not, find the max/min result of the next move combination
  int result = player =='X' ? -1:1;
  for (string moves : moveCombinations(board,player)){
    // if maximizing player
    if (player == 'X'){
      int next_result =  minimax(moves,'O');
      if (next_result>result)result = next_result;
      if (next_result==1) return result;
    }else{
      int next_result =  minimax(moves,'X');
      if (next_result<result) result = next_result;
      if (next_result==-1) return result;
    }
  }
  return result;
}

//return next best move with minimax
string nextBestMove(string board){
  int board_result = minimax(board,'X');
  //expected is X
  for (string move : moveCombinations(board,'X')){
    if (minimax(move,'O')==board_result) return move;
  }
  return "";
}

int main(){
  char first_player = 'O';
  while (true){
    char player = first_player;
    string board = "         ";
    while (result(board)==2){
      if (player=='X'){
        board = nextBestMove(board);
        player = 'O';
        continue;
      }
      display(board);
      int player_move;
      do{
        cin >> player_move;
      }while (board[player_move-1]!=' ' || player_move<1 || player_move>10);
      board[player_move-1] = 'O';
      player = 'X';
    }
    display(board);
    if (result(board)==0){
      cout << "DRAW";
    }else if (result(board)==1){
      cout << "YOU LOSE";
    }else {
      cout << "YOU WON";
    }
    cout << "\n";
    first_player = first_player=='X' ? 'O' : 'X';
  }
  return 0;
}
