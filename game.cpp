#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"texture.h"
#include"Board.h"
#include"Player.h"
#include"Die.h"

class Die;

bool mouseIsDragging = false;

Space* selectedProperty;
int selectedPropertyPos;

//set the interface:
bool inTheInterface = true;
int interfaceT;
int startT, ruleT,exitT;
bool startIsPressed = false, overStart = false;
bool ruleIsPressed = false, overRule = false;
bool optionIsPressed = false, overOption = false;
bool exitIsPressed = false, overExit = false;
double X = 650;
double Y = 560;
double W = 170*1.2;
double H = 48*1.2;
double startPos[] = {X-5, Y+60, W, H};
double exitPos[] = {X, Y+ 120, W, H};



//set the page for displaying the information of the player:
bool inTheInformation = false;
int backT, rollingT, developT,mortgageT, infoBackgroundT; 
double infoPos[] = {250, 60, 1000,750}; 
int pageNo = 0;
int id;
int currentPageNo = 0;
double player1Back[] = {40, 6, 85,20};
bool player1IsPressed = false, overPlayer1 = false;
double player2Back[] = {40, 36, 85, 20};
bool player2IsPressed = false, overPlayer2 = false;
bool player1CanPress = false, player2CanPress = false;
int showPlayerInfo;
//put the buttons on the information page:
//the back to the game button:
double infoBackPos[] = {375, 90,105,45};
bool infobackIsPressed = false, overInfoback = false;
//the last page button 
double lastPage[]  = {265,760, 50,50};
bool lastpageIsPressed = false, overLastpage = false, lastpageCanPress = false;
//the next page button:
double nextPage[]  = {1185, 760, 50,50};
bool nextpageIsPressed = false, overNextpage = false, nextpageCanPress = false;
//the develop button:
double develop[] = {600, 90, 105, 45};
bool developIsPressed = false, overDevelop = false;

//set the winner page:
bool inTheWinningPage = false;

bool cardIsPressed = false;

bool onChance=false;
string text1,text2;
int backtoT;
//the dice info
Die dice;
int dice1 = 6;
int dice2 = 6;

int buyT,lastpageT, nextpageT;
//set the x and y coordinates of the displayed card:
int card_x = 180;
int card_y = 170;

//const int Ori_WIDTH = 1600;
//const int Ori_HEIGHT = 900;
int WIDTH = 1600;  // width of the user window (640 + 80)
int HEIGHT = 900;  // height of the user window (480 + 60)
char programName[] = "oleopoly";
int mypicT; // texture IDs

//the id of all spaces
int T01,T03,T05,T06, T08, T09, T11,T12,T13,T14,T15,T16,T18,T19, T21,T23,T24,T25,T26,T27, T28,T29,T31 ,T32 ,T34,T35,T37,T39;

//pictures of the dices:
int dice1T, dice2T, dice3T, dice4T, dice5T, dice6T;

// turn button info
bool buttonIsPressed = false, overButton = false;
double buttonPos[] = { 30, 284,   100, 50 };  // upper left, width, height

//purchase button info
bool purchaseButtonIsPressed= false, overPurchaseButton= false, purchaseButtonCanPress = false;
double purchaseButtonPos[]= {532,700, 100,50};

//back button info
bool backIsPressed = false, overBack = false;
double backPos[] = {26, 790, 80,40};

/*
// textbox info
bool overTextBox = false;
string textInBox = "";
double textBox1[] = { 320, 30,   200, 40 };  // outer box for text
double textBox2[] = { 325, 35,   190, 30 };  // inner box for text
const unsigned int MAX_NUM_CHARS_IN_TEXTBOX = 20;
*/




//set the board:
Board game("boardsetup.txt");

//set the players:

int numPlayers = 2;
extern Player ** playTurn = new Player*[numPlayers];
extern int turnControl = 0;
int player1T, player2T; 


int diceTotal=0;

void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
  glVertex2f(x, y);  // upper left
  glVertex2f(x, y + height);  // lower left
  glVertex2f(x + width, y + height);  // lower right
  glVertex2f(x + width, y);  // upper right
  glEnd();
}


void drawBox(double *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

void drawText(double x, double y, const char *text)
{
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}

void drawNumber(double x, double y, double num)
{
  stringstream oss;
  oss << num; oss.flush();
  drawText(x, y, oss.str().c_str());
}

void drawSpace(int position, int x, int y, int w, int h)
{
  switch (position)
    {
    case 1:
      drawTexture(T01, x, y, w, h);
      break;
    case 3:
      drawTexture(T03, x, y, w, h);
      break;
    case 5:
      drawTexture(T05, x, y, w, h);
      break;
    case 6:
      drawTexture(T06, x, y, w, h);
      break;
    case 8:
      drawTexture(T08, x, y, w, h);
      break;
    case 9:
      drawTexture(T09, x, y, w, h);
      break;
    case 11:
      drawTexture(T11, x, y, w, h);
      break;
    case 12:
      drawTexture(T12, x, y, w, h);
      break;
    case 13:
      drawTexture(T13, x, y, w, h);
      break;
    case 14:
      drawTexture(T14, x, y, w, h);
      break; 
    case 15:
      drawTexture(T15, x, y, w, h);
      break;
    case 16:
      drawTexture(T16, x, y, w, h);
      break;  
    case 18:
      drawTexture(T18, x, y, w, h);
      break;  
    case 19:
      drawTexture(T19, x, y, w, h);
      break;  
    case 21:
      drawTexture(T21, x, y, w, h);
      break;  
    case 23:
      drawTexture(T23, x, y, w, h);
      break;  
    case 24:
      drawTexture(T24, x, y, w, h);
      break;
    case 25:
      drawTexture(T25, x, y, w, h);
      break;
    case 26:
      drawTexture(T26, x, y, w, h);
      break;
    case 27:
      drawTexture(T27, x, y, w, h);
      break;
    case 28:
      drawTexture(T28, x, y, w, h);
      break;
    case 29:
      drawTexture(T29, x, y, w, h);
      break;
    case 31:
      drawTexture(T31, x, y, w, h);
      break;
    case 32:
      drawTexture(T32, x, y, w, h);
      break;
    case 34:
      drawTexture(T34, x, y, w, h);
      break;
    case 35:
      drawTexture(T35, x, y, w, h);
      break;
    case 37:
      drawTexture(T37, x, y, w, h);
      break;
    case 39:
      drawTexture(T39, x, y, w, h);
      break;
    }

}

void drawDice1(int diceNo)
{
  switch (diceNo)
    {
    case 1:
      drawTexture(dice1T, 52, 352, 60, 60);
      break;
    case 2:
      drawTexture(dice2T, 52, 352, 60, 60);
      break;
    case 3:
      drawTexture(dice3T, 52, 352, 60, 60);
      break;
    case 4:
      drawTexture(dice4T, 52, 352, 60, 60);
      break;
    case 5:
      drawTexture(dice5T, 52, 352, 60, 60);
      break;
    case 6:
      drawTexture(dice6T, 52, 352, 60, 60);
      break;
    }
}

void drawDice2(int diceNo)
{
  switch (diceNo)
    {
    case 1:
      drawTexture(dice1T, 52, 425, 60, 60);
      break;
    case 2:
      drawTexture(dice2T, 52, 425, 60, 60);
      break;
    case 3:
      drawTexture(dice3T, 52, 425, 60, 60);
      break;
    case 4:
      drawTexture(dice4T, 52, 425, 60, 60);
      break;
    case 5:
      drawTexture(dice5T, 52, 425, 60, 60);
      break;
    case 6:
      drawTexture(dice6T, 52, 425, 60, 60);
      break;
    }
}

void displayDice(int d1, int d2){
  dice1=d1;
  dice2=d2;
  glutPostRedisplay();
}


void exitAll()
{
  int win = glutGetWindow();
  glutDestroyWindow(win);
  exit(0);
}


void drawWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw stuff
 
  if (inTheInterface)
    {
      drawTexture(interfaceT, 0, 0, WIDTH, HEIGHT);
      //the rule button:
      
      //we draw the button start:
      if (startIsPressed ||overStart ) drawTexture(startT,X-5+2,Y+60+2,W,H,0.5);
      else drawTexture(startT,X-5,Y+60,W,H);
      //the exit button:
      if (exitIsPressed || overExit) drawTexture(exitT, X+2,Y+120+2, W,H,0.5);
      else drawTexture(exitT, X,Y+120, W,H);
    }
 
  else
    {
      drawTexture(mypicT,   0,0, WIDTH,HEIGHT);
      drawTexture(player1T, playTurn[0]->x, playTurn[0]->y, playTurn[0]->width, playTurn[0]->height); 
      drawTexture(player2T, playTurn[1]->x, playTurn[1]->y, playTurn[1]->width, playTurn[1]->height);
      
     
      //draw all the button!
      if ( buttonIsPressed ) drawTexture(rollingT, 32,286,100,50,0.5);  // make it red
      else drawTexture(rollingT, 30,285,100,50);


      // draw the purchase button
      if (game.board[playTurn[turnControl]->position]-> propertySpace && game.board[playTurn[turnControl]->position]->owner<0)
	{
	  purchaseButtonCanPress = true;
	  if ( purchaseButtonIsPressed ) drawTexture(buyT,534,702,100,50,0.5);
	  else drawTexture(buyT,532,700,100,50);
	}
      else purchaseButtonCanPress = false;

      //draw the back button:
      if ( backIsPressed ) drawTexture(backtoT,790-2,80,40,0.5); 
      else  drawTexture(backtoT,26,790,80,40); 
      
      //draw the spaces:
      drawSpace(playTurn[turnControl]->position, card_x, card_y, 403, 507);

      //draw the dice pic on the screen:
      drawDice1(dice1);
      drawDice2(dice2);
      //draw the button on the player information:
      if (player1CanPress)
	{
	  if (player1IsPressed)glColor3f(0.75,0.75,0.75);
	  else if (overPlayer1) glColor3f(0.75,0.75,0.75);
	  else glColor3f(0.,0.,0.);
	  drawBox(player1Back);
	 
	}
      if (player1IsPressed) glColor3f(0,0,0);
      else glColor3f(1,1,1);
      drawText(46,20,"Player1:   $");
      drawNumber(156, 20, playTurn[0] -> balance);
      if (player2CanPress)
	{
	  if (player2IsPressed) glColor3f(1.,1.,1.);
	  else if (overPlayer2) glColor3f(0.75,0.75,0.75);
	  else glColor3f(0.,0.,0.);
	  drawBox(player2Back);  
	 
	}
      if (player2IsPressed) glColor3f(0,0,0);
      else glColor3f(1,1,1);
      drawText(46,50,"Player2:   $");    
	  drawNumber(156,50, playTurn[1] -> balance);
	 
      //draw the player information:
     
      //draw the small lion to show the current player:
      if (turnControl == 0)
	drawTexture(player1T, 30,5,-20,23);
      else if (turnControl == 1)
	drawTexture(player1T, 30, 33, -20, 23);
   
      if(onChance){
	char* line1= (char*)text1.c_str();
	char* line2= (char*)text2.c_str();
	drawText(284,418, line1);
	drawText(284,430, line2);
      onChance=false;
      }

      //draw the info window
      if (inTheInformation)
	{
	  drawTexture(infoBackgroundT, 250,60, 1000,750);
	  if (backIsPressed) drawTexture(backT, 375,90,70,30,0.5);
	  else  drawTexture(backT, 375,90,70,30);
	  if (developIsPressed) drawTexture(developT, 600, 90, 70,30,0.5);
	  else drawTexture(developT, 600, 90, 70,30);
	  int count = 0;
	  for (int i = 0; i < 40; i++)
	    {
	      if (playTurn[showPlayerInfo] -> myProperties[i] == true)
		{
		  if (count >= currentPageNo*6 && count <(currentPageNo+1)*6)	    
		    drawSpace(i, 340+count%3*270,130+(count/3-currentPageNo*2)*340,254,320);
		  pageNo = count/6;
		  count ++;	
		}
	      if (currentPageNo < pageNo)
		{
		  nextpageCanPress = true;
		  if (nextpageIsPressed) drawTexture(nextpageT, 1190,772-15,50,50,0.5);
		  else drawTexture(nextpageT, 1188,770-15,50,50);
        
		}
	      else nextpageCanPress = false;
	      if (currentPageNo > 0)
		{
		  lastpageCanPress = true;
		  if (lastpageIsPressed)  drawTexture(lastpageT,267,772-15,50,50,0.5);
		  else drawTexture(lastpageT, 265,770-15,50,50);
        
		}
	      else lastpageCanPress = false;
	    }
	}
 
    }

  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}



// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
  int win = glutGetWindow();
  /*
  if ( overTextBox ) { // intercept keyboard press, to place in text box
    if ( 27==c ) exitAll();  // escape terminates the program, even in textbox
    if ( 13==c ) {
      cout << "textBox content was: " << textInBox << endl;
      textInBox = "";
    } else if ( '\b'==c || 127==c ) { // handle backspace
      if ( textInBox.length() > 0 ) textInBox.erase(textInBox.end()-1);
    } else if ( c >= 32 && c <= 126 ) { // check for printable character
      // check that we don't overflow the box
      if ( textInBox.length() < MAX_NUM_CHARS_IN_TEXTBOX ) textInBox += c;
    }
    } else {*/
    switch(c) {
    case 'q':
    case 'Q':
    case 27:
      // get rid of the window (as part of shutting down)
      glutDestroyWindow(win);
      exit(0);
      break;
    default:
      break;
   }
//}
  glutPostRedisplay();
}


bool onButton(int x, int y, double button[])
{
  return x >= button[0]  && y >= button[1] &&
    x <= button[0] + button[2] &&
    y <= button[1] + button[3];
}


void winGame(Player* winner){
  cout<<"GAME OVER"<<endl;
  exitAll();
}

Space* getSelectedSpace(int pos){
  return game.board[pos];
}

int showPosition()
{
  //control is the order of the property that player is bought, for example, if control is 7, then we need the 7th of the property that bought by this player:
  int control = (currentPageNo *6 +id)+1;
  int count = 0;
  int i = 0;
  while (i < 40 && count < control)
    {
      if (playTurn[showPlayerInfo] -> myProperties[i])
        count++;
      i++;
    }
  return (i-1);
}


bool onPosition(int x, int y, int X, int Y)
{
  return x >= X && y >= Y && x<= X+254 && y <= Y+320;
}

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  WIDTH = w; HEIGHT = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == button ) 
    {
      if ( GLUT_DOWN == state ) 
	{
	  //the user just press down the on the mouse-- do something:
	  if (inTheInterface)
	    {	  
	      if (onButton(x, y, startPos)) startIsPressed = true;
	      else startIsPressed = false;	 
	      if (onButton(x, y, exitPos)) exitIsPressed = true;
	      else exitIsPressed = false;
	    }
	 
	  else
	    {
	      if ( onButton(x,y,buttonPos) ) buttonIsPressed = true;
	      else buttonIsPressed = false;
	      if (onButton(x,y,purchaseButtonPos)) purchaseButtonIsPressed=true;
	      else purchaseButtonIsPressed=false;
	      mouseIsDragging = true;
	      if (onButton (x, y, backPos)) backIsPressed = true;
	      else backIsPressed = false;
	      if (onButton(x, y, player1Back)) player1IsPressed = true;
	      else player1IsPressed = false;
	      if (onButton(x, y, player2Back)) player2IsPressed = true;
	      else player2IsPressed = false;
	      if (onButton(x, y, infoBackPos)) infobackIsPressed = true;
	      else infobackIsPressed = false;
	      if (onButton(x, y, nextPage)) nextpageIsPressed = true;
	      else nextpageIsPressed = false;
	      if (onButton(x, y, lastPage)) lastpageIsPressed = true;
	      else lastpageIsPressed = false;
	      if (onButton(x, y, develop)) developIsPressed = true;
	      else developIsPressed = false;
	      if (onPosition(x, y, 340,130) || onPosition(x,y,610,130)|| onPosition(x,y,880,130) || onPosition(x,y,340,470) || onPosition(x,y,610,470) ||onPosition(x,y,880,470))
		cardIsPressed = true;
	      else cardIsPressed = false;

	    }
	  // the user just pressed down on the mouse-- do something
	}
      else
	{
	  if (inTheInterface)
	    {	  
	      if (onButton(x, y, startPos) && startIsPressed)	
		inTheInterface = false;
	      startIsPressed = false;
		 	
	    
	      optionIsPressed = false;
	      if(onButton(x, y, exitPos) && exitIsPressed)
		exitAll();
	      exitIsPressed = false;
	    }
	
	  else if (inTheInformation)
	    {
	      if (nextpageCanPress)
		{
		  if (onButton(x, y, nextPage) && nextpageIsPressed)
		    currentPageNo += 1;
		}
	      if (lastpageCanPress)
		{
		  if (onButton(x, y, lastPage) && lastpageIsPressed)
		    currentPageNo -= 1;
		}
	      selectedPropertyPos=1;
	      if (onPosition(x, y, 340,130) && cardIsPressed)
		{id = 0;	      
		  selectedPropertyPos= showPosition();}
	      else if(onPosition(x,y,610,130) && cardIsPressed)
		{
		  id = 1;
		  selectedPropertyPos= showPosition();
		}
	      else if(onPosition(x,y,880,130) && cardIsPressed)
		{id = 2;
		  selectedPropertyPos= showPosition();}
	      else if(onPosition(x,y,340,470) && cardIsPressed)
		{id = 3;
		  selectedPropertyPos= showPosition();}
	      else  if(onPosition(x,y,610,470) && cardIsPressed)
		{id = 4;
		  selectedPropertyPos= showPosition();}
	      else if(onPosition(x,y,880,470) && cardIsPressed)
		{id = 5;
		  selectedPropertyPos= showPosition();}

	      
	      if (onButton(x, y, develop) && developIsPressed)
		{
		  selectedProperty=getSelectedSpace(selectedPropertyPos);
		  selectedProperty->develop(playTurn[showPlayerInfo]);
		}

	      if (onButton(x, y, infoBackPos) && infobackIsPressed)
		inTheInformation = false;
	      infobackIsPressed = false;
	      // the user just let go the mouse-- do something
	    
	    }
	      else 
	    {
	      if ( onButton(x,y, buttonPos) && buttonIsPressed )
		{
		  if(playTurn[0]->balance<0)
		    winGame(playTurn[1]);
		  if(playTurn[1]->balance<0)
		    winGame(playTurn[0]);
		  cout << "button is pressed" << endl;
		  //Moves to next player int the array
		  //Circles back to beginning of the array
		  if(turnControl<numPlayers-1)
		    turnControl++;
		  else
		    turnControl=0;
		  playTurn[turnControl]->takeTurn(game);
		  if (turnControl == 2)
		    turnControl = 0;
		}
	      buttonIsPressed = false;
	      
	      //we press on the purchseButton:
	      if (purchaseButtonCanPress)
		{
		  if ( onButton(x,y, purchaseButtonPos) && purchaseButtonIsPressed )
		    {
		      cout<<"TurnControl: "<<turnControl<<endl;
		      playTurn[turnControl]->buyProperty(playTurn[turnControl]->position, game);
		      cout<<"Purchase"<<endl;
		      if (playTurn[0] -> getPropertyNo() >0) player1CanPress = true;
		      if (playTurn[1] -> getPropertyNo() > 0) player2CanPress = true;
		    }
		}	   
	      purchaseButtonIsPressed = false;

	      //we press on the back-to-main-menu button:
	      if (onButton(x, y, backPos) && backIsPressed)
		inTheInterface = true;
	      backIsPressed = false;
	    
	      if (player1CanPress)
		{
		  //we press on the player1 back button:
		  if (onButton(x, y, player1Back) && player1IsPressed)
		    {
		      inTheInformation = true;
		      showPlayerInfo = 0;
		      currentPageNo = 0;
		    }
		  player1IsPressed = false;
		}
	      //we press on player2:
	      if (player2CanPress)
		{
		  if (onButton(x, y, player2Back) && player2IsPressed)
		    {
		      inTheInformation = true;
		      showPlayerInfo = 1;
		      currentPageNo = 0;
		    }
		  player2IsPressed = false;
		}
	      //we press on the exit-information-window-button	     
	    }
	}
    }
    else if ( GLUT_RIGHT_BUTTON == button ) 
    {
    }
glutPostRedisplay();

}

// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x,int y)
{
  if (buttonIsPressed){
  }
  else if(purchaseButtonIsPressed)
    {
    }
  else
    {
      if (onButton(x, y, startPos)) overStart = true;
      else overStart = false;
    
      if (onButton(x, y, exitPos)) overExit = true;
      else overExit = false;
      //if ( onButton(x,y,textBox1) ) overTextBox = true;
      //else overTextBox = false;	 
      if(onButton(x, y, backPos)) overBack = true;
      else overBack = false;  
      if(onButton(x, y, player1Back)) overPlayer1 = true;
      else overPlayer1 = false;
      if(onButton(x, y, player2Back)) overPlayer2 = true;
      else overPlayer2 = false; 
      if (onButton(x, y, infoBackPos)) overInfoback = true;
      else overInfoback = false;
      if (onButton(x, y, nextPage)) overNextpage = true;
      else overNextpage = false;
      if (onButton(x, y, lastPage)) overLastpage = true;
      else overLastpage = false;
      if (onButton(x, y, develop)) overDevelop = true;
      else overDevelop = false;
    }


  // the mouse button is pressed, and the mouse is moving....
  glutPostRedisplay();
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // welcome message
  //cout << "Welcome to " << programName << "." << endl;
}


// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window()
{
  char *argv[] = { programName };
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  mypicT = loadTexture("mypic.pam");
  player1T = loadTexture("player1.pam");
  player2T = loadTexture("player2.pam");
  T01 = loadTexture("space/01.pam");
  T03 = loadTexture("space/03.pam");
  T05 = loadTexture("space/05.pam");
  T06 = loadTexture("space/06.pam");
  T08 = loadTexture("space/08.pam");
  T09 = loadTexture("space/09.pam");
  T11 = loadTexture("space/11.pam");
  T12 = loadTexture("space/12.pam");
  T13 = loadTexture("space/13.pam");
  T14 = loadTexture("space/14.pam");
  T15 = loadTexture("space/15.pam");
  T16 = loadTexture("space/16.pam");
  T18 = loadTexture("space/18.pam");
  T19 = loadTexture("space/19.pam");
  T21 = loadTexture("space/21.pam");
  T23 = loadTexture("space/23.pam");
  T24 = loadTexture("space/24.pam");
  T25 = loadTexture("space/25.pam");
  T26 = loadTexture("space/26.pam");
  T27 = loadTexture("space/27.pam");
  T28 = loadTexture("space/28.pam");
  T29 = loadTexture("space/29.pam");
  T31 = loadTexture("space/31.pam");
  T32 = loadTexture("space/32.pam");
  T34 = loadTexture("space/34.pam");
  T35 = loadTexture("space/35.pam");
  T37 = loadTexture("space/37.pam");
  T39 = loadTexture("space/39.pam");
  //load the picture for dice 
  dice1T = loadTexture("dice/1.pam");
  dice2T = loadTexture("dice/2.pam");
  dice3T = loadTexture("dice/3.pam");
  dice4T = loadTexture("dice/4.pam");
  dice5T = loadTexture("dice/5.pam");
  dice6T = loadTexture("dice/6.pam");
  //load the interface infomation:
  interfaceT = loadTexture("cover/cover.pam");

  startT = loadTexture("cover/1n.pam");
  exitT =  loadTexture("cover/4n.pam");

  //load the button:
  backT =  loadTexture("back.pam");
  rollingT = loadTexture("rolling.pam");
  developT =  loadTexture("develop.pam");
  mortgageT = loadTexture("mortgage.pam");
  infoBackgroundT = loadTexture("infoBackground.pam");
  lastpageT = loadTexture("lastpage.pam");
  nextpageT = loadTexture("nextpage.pam");
  buyT = loadTexture("buy.pam");
  backtoT = loadTexture("backto.pam");

  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutMainLoop();
}



void chance(Player *p){
  srand(static_cast<unsigned int>(time(0)));
  int randValue = rand() %7;
  switch(randValue){
  case 0:
    text1="Advance to Go.";
    text2="Collect $200.";
    p->position=0;
    break;
  case 1:
    text1="Go To Pause Dance";
    text2="Advance Token To The Lion's Pause.";
    p->position=39;
    break;
  case 2:
    text1="Software Design Class";
    text2="Advance Token To Regent's Hall";
    p->position=26;
    break;
  case 3:
    text1="Get out of Jail free.";
    text2="This card may be kept until needed.";
    p->GOOJailFree=true;
    break;
  case 4:
    text1="Go to jail - go directly to jail.";
    text2="Do not pass Go, do not collect $200.";
    p->position=10;
    break;
  case 5:
    text1="Pay School Fee of $150";
    text2="";
    p->adjustBalance(-150);
    break;
  case 6:
    text1="Care Package From Home.";
    text2="Collect $75";
    p->adjustBalance(75);
    break;
  }
  cout<<"Chance"<<endl;
  cout<<text1<<endl<<text2<<endl<<endl;

  //  char* line1= (char*)text1.c_str();
  //  char* line2= (char*)text2.c_str();
  onChance=true;
  glutPostRedisplay();
}

void communityChest(Player *p){
  srand(static_cast<unsigned int>(time(0)));
  int randValue = rand() %7;
  switch(randValue){
  case 0:
    text1="Advance to Go.";
    text2="Collect $200.";
    p->position=0;
    break;
  case 1:
    text1="Scholarship.";
    text2="Collect $500.";
    p->adjustBalance(500);
    break;
  case 2:
    text1="Doctor's fees.";
    text2="Pay $50.";
    p->adjustBalance(-50);
    break;
  case 3:
    text1="Get out of Jail free.";
    text2="This card may be kept until needed.";
    p->GOOJailFree=true;
    break;
  case 4:
    text1="Go to jail - go directly to jail.";
    text2="Do not pass Go, do not collect $200.";
    p->position=10;
    break;
  case 5:
    text1="Pay School Fee of $150";
    text2="";
    p->adjustBalance(-150);
    break;
  case 6:
    text1="Care Package From Home.";
    text2="Collect $75";
    p->adjustBalance(75);
    break;
  }
  cout<<"Community Chest"<<endl;
  cout<<text1<<endl<<text2<<endl<<endl;

 
  onChance=true;
  glutPostRedisplay();
}


int main()
{
  for (int i = 0; i < 2; i++)
    playTurn[i] = new Player(game);
  cout<<"Beginning"<<endl;
  init_gl_window(); 
}
