/**
 * This code is created for cs 4341 AI 2013a at WPI. All rights are reserved. 
 */
package referee;

import java.io.*;
import java.util.*;

/**
 * @author lzhu
 *
 */

public class Referee_User {

	Board board;
	int N=4;
	int board_height=6;
	int board_width=7;
	
	Timer autoTimer=null;
	int announceNameTimeLimit=10;
	int moveTimeLimit=60;
	int popOutCount[] = {0,0};
	
	int player1=1;
	int player2=2;
	String player1_name="";		
	String player2_name="";
	Process p1;
	Process p2;
	BufferedReader input1; 
	BufferedReader input2;
	BufferedWriter output1;
	BufferedWriter output2;
	
	int currentPlayer=1;
	int winner=-1;
	
	final int DROP=1;
	final int POPOUT=0;
	final int TIE=0;
	

	
//	BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
	
	
	public Referee_User( String command_to_execute_player1, String command_to_execute_player2, int board_height,int board_width, int N, int announceNameTimeLimit, 	int moveTimeLimit) throws IOException{
		 p1 = Runtime.getRuntime().exec(command_to_execute_player1);
		 p2 = Runtime.getRuntime().exec(command_to_execute_player2);
		 input1 = new BufferedReader(new InputStreamReader(p1.getInputStream()));
		 input2 = new BufferedReader(new InputStreamReader(p2.getInputStream()));
		 output1 = new BufferedWriter(new OutputStreamWriter(p1.getOutputStream()));
		 output2 = new BufferedWriter(new OutputStreamWriter(p2.getOutputStream()));
		 this.board_height=board_height;
		 this.board_width=board_width;
		 this.N=N;
		 this.announceNameTimeLimit=announceNameTimeLimit;
		 this.moveTimeLimit=moveTimeLimit;
		 this.board=new Board(board_height,board_width,N);
	}
	
	/**
	 * Init and run the game
	 * */
	public void start() throws IOException{
		 init();
		 run();
	}
	
	/**
	 * Initialize the game.
	 * */
	public void init() throws IOException{		
	 	readPlayerName();
		currentPlayer= (int)Math.round(Math.random()+1); 
		this.board.printBoard();
		
		
	}
	
	
	/**
	 * Once the players receive game information, the game starts immediately. Game information 
	 * consists of 5 numbers [in this order]: 
	 *   1.board height (#rows), 
	 *   2.board width (#columns), 
	 *   3.number of pieces to win (the N in Connect-N), 
	 *   4.turn of the player (1 indicating 1st player, and 2 indicating 2nd player), 
	 *   5.the time limit to make a move in seconds. 
	 * @throws IOException 
	 */
	
	public void run() throws IOException{
		String s=this.board.height+" "+this.board.width+" "+this.N+" "+this.currentPlayer+" "+this.moveTimeLimit;
		System.out.println(s);
		System.out.println("currentPlayer:"+this.currentPlayer);
		this.tellPlayer1(s);
		this.tellPlayer2(s);
		
		while(winner==-1){			
			countDown(this.moveTimeLimit);
			
            if(this.currentPlayer==this.player1) {
                Scanner scanner = new Scanner(System.in);
                s = scanner.nextLine();
                System.out.println(s);
            } else
				s=input2.readLine();
			
			this.autoTimer.cancel();
			
			List<String> ls=Arrays.asList(s.split(" "));
			if(ls.size()!=2){
				System.out.println("Wrong number of arguments. Each move should have two integers.");
				this.winner= this.currentPlayer==1? 2 : 1;
			}
			else{
				int column=Integer.parseInt(ls.get(0));
				int operation=Integer.parseInt(ls.get(1));
				if(this.isValidMove(column, operation)){
				    makeMove(column, operation);
				      this.board.printBoard();
				  //either tie or someone connect N
				      if(isEnd()){
						   this.currentPlayer = this.currentPlayer==1? 2 : 1;
						   System.out.println("currentPlayer:"+this.currentPlayer);
						   break;
						   }
					   else{
						   this.currentPlayer = this.currentPlayer==1? 2 : 1;
						   sendGameInfo(column+" "+operation);
					   }
				}
				else{
					System.out.println("Invalid Move by Player: " + this.currentPlayer);	
					this.winner= this.currentPlayer==1? 2 : 1;
					System.out.println("Winner is : " + this.winner);
					}
		    }
			
		//	System.out.println("currentPlayer:"+this.currentPlayer);
		}//while
		
		this.gameOver();
		
	}
	

	
	/**
	 * Referee read players' name from input. The players have 10 seconds to announce 
	 * themselves by sending their name to the referee
	 */
	private void readPlayerName() throws IOException{
		System.out.println("Please enter two players user name. You have "+this.announceNameTimeLimit+"s to enter.");
		countDown(this.announceNameTimeLimit);
		
		player1_name=input1.readLine();		 
		player2_name=input2.readLine();
		
		this.autoTimer.cancel();
		
		String s="player1: "+player1_name+" player2: "+player2_name;
		System.out.println(s);
		this.tellPlayer1(s);
		this.tellPlayer2(s);
	}
	
	/**
	 * Referee keeps passing the opponent's move to the other player depending on the state of the game
	 *    1. [0,(COLS-1)] [0,1] indicating the oponent's move;
     *    2. -1 indicating that the player won the game;
     *    3. -2 indicating that the player lost the game; and
     *    4. -3 indicating a tie.
	 */
	private void sendGameInfo(String s) throws IOException{
		if(s!=null){
			if(this.currentPlayer==this.player1)
				this.tellPlayer1(s);
			else
				this.tellPlayer2(s);
			 return;
		}
		
		if(this.winner==this.currentPlayer){
			if(this.currentPlayer==this.player1){
				this.tellPlayer1("win");	
				this.tellPlayer2("lose");	
			}
							
			else{
				this.tellPlayer2("win");	
				this.tellPlayer1("lose");	
			}
		}
		  
		else if(this.winner==0){
			if(this.currentPlayer==this.player1){
				this.tellPlayer1("draw");	
				this.tellPlayer2("draw");	
			}			
			else{
				this.tellPlayer1("draw");	
				this.tellPlayer2("draw");	
			}		
		}
		else
		{
			if(this.currentPlayer==this.player1){
				this.tellPlayer1("lose");	
				this.tellPlayer2("win");	
			}					
			else{
				this.tellPlayer1("win");	
				this.tellPlayer2("lose");	
			}		
		}
		}

	
	/**
	 * Check current the move is valid. Invalid Moves can be:
	 *   1. Drop a disc on a column that is already completely filled. 
	 *	 2. Choosing an undefined column.
	 *   3. Try to poppout a disc of opponent's from the bottom of a column 
	 * @param column
	 *    		The column in which the current move is going to make. 
	 * @param operation   
	 * 			Indicates dropping a disc by 1, popping out a disc by 0. 
	 * @return if current move is valid
	 */
	private boolean isValidMove(int column, int operation){
		if(operation== DROP)
		  {if(this.board.canDropADiscFromTop(column, operation))
			  return true;
		  else
			  return false;
		  }
		else if(operation== this.POPOUT)
		{if((this.board.canRemoveADiscFromBottom(column, currentPlayer)
				&&(popOutCount[currentPlayer-1]==0)))
			  return true;
		  else
			  return false;
		  }
		else{
			System.out.println("Wrong operation.");
			return false; 
		} 
			
	}
	
	
	
	
	/**
	 * Place a disc from the top of the column or remove from bottom (see method comment)
	 * @param column
	 *    		The column in which the current move is going to make. 
	 * @param operation   
	 * 			Indicates dropping a disc by 1, poping out a disc by 0. 
	 */
	private void makeMove(int column, int operation){
		if(operation==DROP)
			this.board.dropADiscFromTop(column, currentPlayer);
		else{
			this.board.removeADiscFromBottom(column);
			popOutCount[currentPlayer-1]+=1;
		}
		
	}
		

	/**
	 * The game ends in any of the following scenarios: 
	 *   1. One of the players gets N checkers in a row (horizontally, vertically or diagonally).
	 *   2. The board is full but none of the players managed to get N checkers in a row.
	 *   3. One player makes an illegal move, in this case the other player wins.  
	 *   4. If one player fails to respond within the time limit, then the other player wins. 
	 * This method only check 1 and 2 scenarios
	 * @return the value of winner. If winner=-1, nobody win and game continues; If winner=0/TIE, it's a tie;
	 * 			If winner=1, player1 wins; If winner=2, player2 wins. 
	 */
	
	private boolean isEnd(){
		//if somebody connectN, he is the winner, else if the board is full, game ends with tie
//		if(this.board.isFull())
//		{
//			winner=this.TIE;
//			return true;
//		}
		winner=this.board.isConnectN();
		if(winner!=-1)
			return true;
		else if(this.board.isFull())
			{ winner=this.TIE;
			return true;}
		else
			return false;
	}
	
	private void tellPlayer1(String s) throws IOException{
		 output1.write(s);
		  output1.newLine(); 
		  output1.flush();
	}
	
	private void tellPlayer2(String s) throws IOException{
		 output2.write(s);
		  output2.newLine(); 
		  output2.flush();
	}

	/**
	 * End the game by printing game status
	 *  
	 * 
	 * @throws IOException 
	 */	
	private void gameOver() throws IOException{
		if(this.player1_name=="" || this.player2_name==""){
			System.out.println("Cannot set up a game without two players.");
			
		}
		
		this.sendGameInfo(null);
		this.printGameOverSign();	
		System.exit(0);
	}
	

	
	private void printGameOverSign(){
		System.out.println("****************************************");
		System.out.println("*             Game Over!               *");
		System.out.println("****************************************");
	}
	
	
	
	/**
	 *
	 * */
	private void countDown(int seconds){
		if (seconds > 0) {
		if (this.autoTimer != null) {
			this.autoTimer.cancel();
		}
		this.autoTimer = new Timer();
		this.autoTimer.schedule(new TimerTask() {
            public void run() {
            	System.out.println("Time Out!");
            	 winner=  currentPlayer==1? 2 : 1;
            	try {
					gameOver();
					
				} catch (IOException e) {
					e.printStackTrace();
				}
			
           }
        }, seconds * 1000);
    }
		}
	
	//test pop out
//	private void test1(){
//		this.makeMove(1, 1);
//		this.makeMove(1, 1);
//		this.makeMove(1, 1);
//		this.makeMove(1, 1);;
//		this.makeMove(1, 1);
//		this.makeMove(1, 1);
//		this.board.printBoard();
//		this.currentPlayer=1;
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//		if(this.isValidMove(1, 0))
//			this.makeMove(1, 0);
//		this.board.printBoard();
//			
//	}
	
	
	public static void main(String [] arg) throws IOException{
 
		String command_to_execute_player1=arg[0];
  		String command_to_execute_player2=arg[1];
		int board_height=Integer.parseInt(arg[2]);
		int board_width= Integer.parseInt(arg[3]);
		int N=Integer.parseInt(arg[4]);
		int announceNameTimeLimit =Integer.parseInt(arg[5]);
		int moveTimeLimit=Integer.parseInt(arg[6]); 
		Referee_User ref=new Referee_User( command_to_execute_player1, command_to_execute_player2, board_height, board_width,  N,  announceNameTimeLimit,  moveTimeLimit);
		
// 		String command_to_execute_player1=arg[0];
// 		String command_to_execute_player2=arg[1];
// 		Referee ref=new Referee(command_to_execute_player1,command_to_execute_player2);
		
//		String command_to_execute_player1="java -jar C:" + File.separator +"courses2013fall" + File.separator +"testPlayer1.jar";
//    	String command_to_execute_player2="java -jar C:" + File.separator +"courses2013fall" + File.separator +"testPlayer2.jar";
//    	Referee ref=new Referee(command_to_execute_player1,command_to_execute_player2,6,7,3,10,10);
    	
   
 		ref.start();
 	//	ref.test1();

	}
	
}
