
/*
Software Engineering Project - Cube Tracer
Dylan Kapustka
Dr. Javaher
*/


/*
_________      ___.            ___________
\_   ___ \ __ _\_ |__   ____   \__    ___/___________    ____  ___________
/    \  \/|  |  \ __ \_/ __ \    |    |  \_  __ \__  \ _/ ___\/ __ \_  __ \
\     \___|  |  / \_\ \  ___/    |    |   |  | \// __ \\  \__\  ___/|  | \/
 \______  /____/|___  /\___  >   |____|   |__|  (____  /\___  >___  >__|
		\/          \/     \/                        \/     \/    \/

Software liscence code "@a3d3df" (looks legit)
*/




/*
************IMPORTANT:IMPORTANT:IMPORTANT:IMPORTANT:IMPORTANT:IMPORTANT:*************
*DK*																			 *DK*
	  
	
			Before compiling ensure SFML configurations are set properly.

	If compiling on VisualStudio be sure your paths to the SFML folders are correct

    Check the SFMLConfigurations.txt I've added within the projectfile for setup

	Also when wishing to run the "Cube Tracer.EXE" seperately from compiling. DO NOT run the .exe's

	in the DEBUG folder. The proper .exe is in the "DK-CubeTracer" folder, and run

	the .exe from there. 

*DK  																        *DK*
************************************************************************************

*/
// _____________________START________________________

//Preprocessor Directives
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <windows.h> 
#include<cstdlib>
//Included SFML GUI libraries
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace std; //std lib


//Function Declarations
int mainMenu(); 
void localGame();


// Initialize global SFML objects
sf::RenderWindow renderWindow(sf::VideoMode(1000, 675),//set window size (1000,675 pixels) 
"CubeTracer", sf::Style::Titlebar | sf::Style::Close); //Prevent user from maximizing or changing window size
sf::Texture cursor; //assign texture for cursor image
sf::Texture gamemap; //assign texture for gamemap image
sf::RenderTexture framedata; // background render
sf::Sprite frameholder; //holds "framedata" texture for display 
sf::Event event; //delcares an event to be called when window is open, essential to run with sfml
sf::Music music; //music object for main song
sf::SoundBuffer buffer1; //collects audio-data and attaches to  sound assigned to "selected"
sf::SoundBuffer buffer2; //collects audio-data and attaches to sound assigned to "deselected"
sf::Sound selected;   //sound buffer for mouse click on
sf::Sound deselected; //sound buffer for mouse click off

//Global bools
bool sGameIsRunning = false; //Keeps track whether the main game is open 
bool r = false; //if true, resets the game
bool exitProgram = false; //if true, closes game gracefully, and returns 0


//*CL*,*DK*,*JR*,*AA* (Chris, Dylan, Jose, Abed)
// Struct Playerdata holds the x and y coordiantes for a player.
// It also holds the current directional state as 's'
// score is being kept which will later be shown on titlebar 
struct Playerdata		
{	int x, y = 0;
	char s = ' ';
	int score = 0;
} player1, player2; //Playerdata player1 and player2 intitalized


//Main function Begins
int main()
{
	//*DK*
	if (!music.openFromFile("Origins.ogg"))//load music file "Origins" by Hedflux and Alex Delfont
			return -1; // if error with opening the file close program;

	//set music to loop,reduce volume and play
	music.setLoop(true);
	music.setVolume(15);
	music.play();

	//load other sound assets
	if (!buffer1.loadFromFile("clickon.wav")) //clickon.wav for mouse select
		return -1; //If error with opening close program

	selected.setBuffer(buffer1); //.setBuffer binds the audio data with the assigned sound variable

	if (!buffer2.loadFromFile("clickoff.wav")) // clickoff.wav for mouse deselect
		return -1; //See above
	deselected.setBuffer(buffer2); //See above

//Start Main Loop
while (!exitProgram) //while exitprogram is false, run the program			
	{
		mainMenu();
	}
	return 0; //after while loop ends return 0 to close

}

//Mainmenu Function
int mainMenu()
{ 

	
	//*FA* (Festus)
	//Hide mouse, Key adjustment and upload custom png image
	renderWindow.setKeyRepeatEnabled(false); //Prevents key spam from single key pressed
	renderWindow.setMouseCursorVisible(false); // When window open, cursor is automatically hidden
	if (!cursor.loadFromFile("prettycursor.png")) //load custom cursor I found online and check if open
	{
		cout << "this file cannot open";//print error if file cannot load
	}
	sf::Sprite mouse(cursor);//initialize a sprite to hold the loaded custom cursor


	//Menu Textures and Sprite assignment
	//Get everyone up to speed with loading/assigning textures in SFML
	//gamemenu image
	sf::Texture gamemenu;//Texture declared as gamemenu
	gamemenu.setSmooth(true);//smooth set true to makes pixel boundaries less visable (get rid of the sharp edges)
	gamemenu.loadFromFile("gamemenu.jpg");//load game menu image. (ensure image is within project file)
	sf::Sprite sprite(gamemenu); //Sprite declared as "sprite" set Texture "gamemenu" as "sprite" to draw it to the screen


	//Look at comments above for loadfile,setsmooth etc.
	//helpmenu image
	sf::Texture helpmenu; 
	helpmenu.setSmooth(true); 
	helpmenu.loadFromFile("helpmenu.jpg"); // load help menu image. (Menu instructions created in paint by AA). 
	sf::Sprite sprite1(helpmenu); 

	//Ipmenu (not yet released in this implementation, but menu is done for once the server is finalized)
	sf::Texture ipmenu;
	ipmenu.setSmooth(true);
	ipmenu.loadFromFile("ipmenu.jpg"); //load ip menu image. (Ip placement created in paint by AA) 
	sf::Sprite sprite2(ipmenu);

	//volume on and off toggle using manipulation of images
	//similar process to code above except volumeon.png and volumeoff.png will not be taking up the entire screen
	//therefore we will need to set the position of the assigned sprite
	sf::Texture volumeon; 
	volumeon.setSmooth(true);
	volumeon.loadFromFile("volumeon.png");  
	sf::Sprite sprite3(volumeon);
	sprite3.move(sf::Vector2f(5.f, 10.f));  //Set the position of the sprite by returning the x and y value as SFML object type Vector2f
											//5.f is X and and 10.f is Y
										   //repeat the same process and same position for volume off
	sf::Texture volumeoff;
	volumeoff.setSmooth(true);
	volumeoff.loadFromFile("volumeoff.png");
	sf::Sprite sprite4(volumeoff);
	sprite4.move(sf::Vector2f(5.f, 10.f));





	//Menu Text
	sf::Font font1; //set SFML Font as font1

	if (!font1.loadFromFile("zorque.ttf")) //upload font from ttf with failsafe
	{
		std::cout << "Error loading fonts" << endl; //if font doesnt load, cout the message

		system("pause");
	}

	string str; //delcared to gather and output user input into ipmenu placement
	//SFML text is creating individual instances where text is being drawn
	sf::Text title; //text for cube tracer title on main menu
	sf::Text start; //text for start button
	sf::Text help; //text for help button
	sf::Text ipprompt; //text for enter ip menu
	sf::Text enterip; //actual user input manipulated into uploaded text font


	//Assign the font to text delcarations
	//In this instance font1 = zorque.ttf
	//assign all declarations to the same font format
	//for example, the title font which will state "Cube Tracer" is set to font1 or zorque.ttf
	//all fonts will be the same for aesthetics and convience
	ipprompt.setFont(font1); 
	title.setFont(font1);
	start.setFont(font1);
	help.setFont(font1);
	enterip.setFont(font1);

	//Text size, position, color, style, outline color, and position all being set for declaration enterip
	//enterip will be passed through as user input for the ipmenu
	//concept*(user input in ip format will be stored as string and passed into the server)*
	//server not implemented in this build, text exists for concept feature only

	enterip.setPosition(345, 555); //sets text position according to window frame..Window size is 1000x675 text is printed (x,y) (345,555)
	enterip.setCharacterSize(35); //sets size of text
	enterip.setFillColor(sf::Color::Green); //sets color of text
	enterip.setStyle(sf::Text::Style::Bold); //sets textstyle of text (Bold)
	enterip.setOutlineColor(sf::Color::Black); //outline color of text (Black)
	enterip.setOutlineThickness(1); //outline thickness set a 1..very minimal

	//**Repeat this process for all SFML Text declartations**

	ipprompt.setString("ENTER IP ADDRESS"); //Texted outputted will say the following in " "
	ipprompt.setPosition(88, 0); //set position is set to (x,y) (88,0) because it is positioned where the first character begins 
	ipprompt.setCharacterSize(90); //everything else is similar to enterip above
	ipprompt.setFillColor(sf::Color::White);
	ipprompt.setStyle(sf::Text::Style::Bold);
	ipprompt.setOutlineColor(sf::Color::Black);
	ipprompt.setOutlineThickness(1);

	
	title.setString("CUBE TRACER");
	title.setPosition(193, 0);
	title.setCharacterSize(90);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Style::Bold);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(1);


	start.setString("Start");
	start.setPosition(431, 559);
	start.setCharacterSize(50);
	start.setFillColor(sf::Color::White);
	start.setStyle(sf::Text::Style::Bold);
	start.setOutlineColor(sf::Color::Black);
	start.setOutlineThickness(1);

	help.setString("Help");
	help.setPosition(900, 630);
	help.setCharacterSize(30);
	help.setFillColor(sf::Color::White);
	help.setStyle(sf::Text::Style::Bold);
	help.setOutlineColor(sf::Color::Black);
	help.setOutlineThickness(1);
//Text manipulation ends.. 


//Bools for drawing Menu State
	bool helpcheck = false; //if true, draw help menu
	bool ipcheck = false; //if true, draw ip menu 
	bool mutesound = false; //if true, draw mute sound image

	//While window is open do logic for menus
	while (renderWindow.isOpen())
	{
		//*FA* (Festus)
		//Used for custom cursor, typecasting position of the mouse to a vector2f
		//Sets position accordingly to wherever the mouse is moved on the screen
		mouse.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(renderWindow))); 
		//Grab mouse position every frame or (each iteration through the while loop)
		sf::Vector2i position = sf::Mouse::getPosition(renderWindow);
		

		//The following if statements are using sfml's implementation of getkeydown
		//if Escape is pressed, the help menu and ipmenu will close
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		{
			helpcheck = false; //close
			ipcheck = false; //close

		}

		//If left mouse botton is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			
			//Drawing invisible frame around text on screen for selection purposes
			//If clicked within bounds, return command within if statement
			//Setting the position around the volumeon.png and volumeoff.png 
			//Creating command to toggle when the sprite is being drawn to screen
			//Position within if statement is sectionalized around the area the image is located
			if ((position.x > 0 && position.x < 50) && (position.y > 0 && position.y < 50)) 
			{
				
				if (!mutesound)
				{
					selected.play(); //"selected" is the imported wav file that mimics a mouse click noise
					selected.setVolume(3); //volume is set to 3
					mutesound = true; // sound muted if left button is clicked within drawn frame
					music.setVolume(0); //mute sound. set the volume to zero
					Sleep(120); //Sleep to prevent key repeats from toggling mute and unmute repeatedly
				}
				else
				{

					mutesound = false; //Sound is unmuted when user clicks within the same frame again
					deselected.play(); //"deselected" is the imported wav file that mimics a mouse un-click noise
					deselected.setVolume(3); //volume of sound set to 3
					music.setVolume(15); //music volume is increased back to it's original state
					Sleep(120); //sleep to prevent multiple toggles back and forth
				}

			}
			
			//Setting the position around the "Start" text
			if ((position.x > 431 && position.x < 580) && (position.y > 559 && position.y < 620))
			{
				selected.play(); //mouse click sound
				selected.setVolume(3);
				sGameIsRunning = true; //if clicked within position frame, game window will render
				localGame(); //game starts
				return 0; //exit this function

			}
			
			//Setting the position around the "help" text
			if ((position.x > 900 && position.x < 980) && (position.y > 625 && position.y < 670))
			{
				selected.play(); //mouse click sound
				selected.setVolume(3);
				if (ipcheck==false) //failsafe to prevent ipwindow and help window form flickering
					helpcheck = true; //open help menu
			}



		} 

		//Nested While-loop for SFML events
		while (renderWindow.pollEvent(event))
		{
			//If the Close button 'X' in the titlebar is pressed, then close the program and window
			if (event.type == sf::Event::EventType::Closed)
			{
				exitProgram = true; renderWindow.close();  //program close, and windowclose function called to end
			}

			
			//Though this code is functional and working, it doesn't call anything in this project build
			//If ipmenu is open
			if (ipcheck == true)
			{
				//If Key is entered
				if (event.type == sf::Event::TextEntered)
				{
					// Handle ASCII characters only (If the key entered is within the ASCII range)
					if (event.text.unicode < 128) 
					{
						int limit = 17; //17 characters is the limit set for ip user input
						if (event.text.unicode == 13)
						{
							/*DK*/
							//this is the 'Enter' Key ASCII value
							//Our future build will pass the string entered into the TCP connect function on a new thread
							// and call the game window
						}
						else {

							if (event.text.unicode == '\b')  // \b stored as 'Delete' 
							{
								//Prevents text limit from being reached
								if (str.size() != 0)
								{	
									//remove the last element of the string
									str.pop_back();
								}

							}
							else {

								//If string input size is less then limit
								if (str.size() < limit)
								{

									str += static_cast<char>(event.text.unicode); //type-casts the int to a character
																				  //concatenates the entered character to the user input string 
								}
							}

							enterip.setString(str); //sets Text declared "enterip" as user input string 
						}
					}
				}

			}
			else 
			{
				//Easter egg functions for quick access when testing
				if (event.type == sf::Event::TextEntered)
					// Handle ASCII characters only
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == 's') //opens game
						{
							sGameIsRunning = true;
							localGame();
							return 0;
						}
						if (event.text.unicode == 'm') //open multiplayer ip menu
						{
							ipcheck = true;

						}
					}
			}

		}
		if (ipcheck == true) //If true Draw Ip menu
		{

			//*Remember* render order when drawing to screen matters
			//Example: If renderWindow.draw(mouse) is drawn before the sound icon "sprite3"
			//the mouse will uderlay the icon, rather than hovering it. aka.. a e s t h e t i c  M 3 s S.
			renderWindow.clear(); //clear screen
			renderWindow.draw(sprite2); //draw assigned sprite2 image
			renderWindow.draw(ipprompt); //draw ipprompt text to set position
			renderWindow.draw(enterip); //draw user input to screen to set position
			if (mutesound) { renderWindow.draw(sprite4); } //draw the correct sound toggle icon.
														  //example, if sound is muted, carryover red muted symbol to menu drawn
			else
			renderWindow.draw(sprite3); //if sound is not muted, draw normal sound icon
			renderWindow.draw(mouse); //custom cursor is drawn
			renderWindow.display(); //display drawn content
		}

		if (helpcheck == true) //If true, Draw Help menu
		{
			//Reference to code above
			renderWindow.clear(); 
			renderWindow.draw(sprite1);
			if (mutesound) { renderWindow.draw(sprite4); }
			else
				renderWindow.draw(sprite3);
			renderWindow.draw(mouse);
			renderWindow.display();
		}

		//If the following processes above are not selected
		//Draw main menu
		if (!helpcheck && !ipcheck)
		{
			
			renderWindow.clear();
			renderWindow.draw(sprite);
			if (mutesound) { renderWindow.draw(sprite4); }
			else
				renderWindow.draw(sprite3);
			renderWindow.draw(title);
			renderWindow.draw(start);
			renderWindow.draw(help);
			renderWindow.draw(mouse);
			renderWindow.display();
		}




	} //While-loop ends
}
//End of Main Menu


//Game Function
void localGame()
{
	
	//---------------------------------------------------------------------------------------------
	//Game Map background image, screen size, framedata, and frame holding
	gamemap.loadFromFile("grid1.jpg"); //load file "grid1.jpg" for gamewindow background

	renderWindow.setFramerateLimit(144); //set framecap at 144hz
	sf::Sprite sBackground(gamemap); //Converting gamemap texture to sprite and declaring it as "sBackground"
	framedata.create(1000, 675); //setting texture to the size of the window
	framedata.draw(sBackground); //drawing background "gamemap" onto the framedata texture
	framedata.setSmooth(true); //remove sharp edges
	frameholder.setTexture(framedata.getTexture()); //placing framedata into the frameholder

	renderWindow.draw(frameholder); //draw frameholder to the window
	renderWindow.display(); //draw frame
	//---------------------------------------------------------------------------------------------

	
	//---------------------------------------------------------
	//Create two 2D squares for player 1 and 2
	sf::RectangleShape p1(sf::Vector2f(10, 10));
	sf::RectangleShape p2(sf::Vector2f(10, 10));

	//Sets square size to 10x10 pixels
	p1.setSize(sf::Vector2f(10, 10));
	p2.setSize(sf::Vector2f(10, 10));
	//Set color of player 1 and 2 using standard RGB format
	p1.setFillColor(sf::Color(0, 0, 255)); //Blue
	p2.setFillColor(sf::Color(255, 0, 0)); //Red
	//---------------------------------------------------------

  
  //-----------------------------------------------------------------
	//Set player position and intial directions
	//Positions scaled to middle left and middle right
	//Set in accordance with our renderedwindow of (1000,675)
	player1.x = 100;
	player1.y = 337;
	player2.x = 900;
	player2.y = 337;
	player1.s = 'r'; //directional state for player 1 (right)
	player2.s = 'l'; //directional state for player 2 (left)

	//Set position of drawn squares to position assigned for each player
	p1.setPosition(sf::Vector2f(player1.x, player1.y));  // setting square postition to (x,y) (100,337)
	p2.setPosition(sf::Vector2f(player2.x, player2.y)); // setting square position to (x,y) (900,337)

	

	//Initialize SFML event
	sf::Event event;

	//Used to store all previous positions 
	bool mem[1000][675] = { false };
//-------------------------------------------------------------------

	//Game loop
	while (renderWindow.isOpen() && sGameIsRunning)
	{
		
		//-----------------------------------------------------------------------
		//Detect Collisions 
		//if player1 is out of bounds on x axis reset and give score to player2
		if (player1.x < 0 || player1.x > 1000 - 10)
		{	
			player2.score++;
			//reset
			r = true;
		}
		//if player1 is out of bounds along the y axis reset and score to player2
		if (player1.y < 0 || player1.y > 675 - 10)
		{
			player2.score++;
			//reset
			r = true;
		}
		//repeats same process as player1
		if (player2.x < 0 || player2.x > 1000 - 10)
		{
			player1.score++;
			//reset
			r = true;
		}
		//repeats same process as player1
		if (player2.y < 0 || player2.y > 675 - 10)
		{
			player1.score++;
			//reset
			r = true;
		}
		//Crosschecking previously stored positions against player 1's current position
		//accessing bool mem at index player1.x and player1.y
		// if true, then reset and score
		if (mem[player1.x][player1.y])
		{
			player2.score++;
			//reset
			r = true;
		}

		if (mem[player2.x][player2.y])
		{
			player1.score++;
			//reset
			r = true;
		}
		//-----------------------------------------------------------------------


/*		Abstract collision detection understanding

		Every pixel within the bool array of 675,000 pixels is set to false.
		before player positions are updated we set their position to true on the grid.
		to understand this, look at the binary layout below.
		The 0's represent false


		Say we have an array for our x and y values:
		x  y
		bool mem = [6][11] = (false);

		this would set our entire 2D array to false.
		Each index of 2D array represents 1 pixel or possible player position

		The zero's in this box represent false
		or in this case, untouched player positions


			---------------------------
	y ->0	|0000000000000000000000000|
		1	|0000000000000000000000000|
		2	|0000000000000000000000000|
		3	|0000000000000000000000000|
		4	|0000000000000000000000000|
		5	|0000000000000000000000000|
		6	|0000000000000000000000000|
			---------------------------
		x -> 0 1 2 3 4 5 6 7 8 9 10 11

		Now visualize that all of these 0's within this box BELOW are still present
		Meaning, the empty space in this box is still all entirely false
		Notice how we have the player positions drawn for player 1 and player 2 within this box.
		on the left we have player 1 and on the right we have player 2
		As player 1 and player 2 are moving, the pixels they are crossing over, are being set to true.
		We see that player 2 is making a wrong turn and crashing into player 1's path.
		The pathing of player2 has resulted in a collision with player1's tracer meaning that the if-statements, regarding hit
		detection will reset with window and give score to player 1.



		 ---------------------------
		0|						   |
		1|                         |
		2|         +++++++++++ P2  |
		3|         +               |
		4| P1 **********           |
		5|             *           |
		6|                         |
		---------------------------
		0 1 2 3 4 5 6 7 8 9 10 11 12


*/

		//While loop for events within game window
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //Check if event closed
			{
				//close the program
				sGameIsRunning = false;
				renderWindow.close();
				exitProgram = true;
				return;
			}
			//Keypress event
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 27) //ASCII value of 27 is 'ESC' 
				{
					sGameIsRunning = false; // if user hits ESC. exits game loop, causing a return to menu

				}
				// Handle ASCII characters only (If the key entered is within the ASCII range)
				if (event.text.unicode < 128)
				{
					//*CL* (Chris)
					//Grab keypress and set player directional state
					//The first if-statement is grabbing and comparing the pressed keys 'W' 'A' 'S' 'D'
					//written as ASCII decimal value
					//The second if-statement is setting the direction state of the player
					//but preventing the user from reversing back into themseleves
					if (event.text.unicode == 115) { if (player1.s != 'u')player1.s = 'd'; } 
					if (event.text.unicode == 119) { if (player1.s != 'd')player1.s = 'u'; }
					if (event.text.unicode == 97) { if (player1.s != 'r')player1.s = 'l'; }
					if (event.text.unicode == 100) { if (player1.s != 'l')player1.s = 'r'; }

					//Same logic happening here, but for keys 'J' 'K' 'L' 'I'
					if (event.text.unicode == 107) { if (player2.s != 'u')player2.s = 'd'; }
					if (event.text.unicode == 105) { if (player2.s != 'd')player2.s = 'u'; }
					if (event.text.unicode == 106) { if (player2.s != 'r')player2.s = 'l'; }
					if (event.text.unicode == 108) { if (player2.s != 'l')player2.s = 'r'; }


				}
			}



		}

		
		//If statement for reset
		if (r)

		{	
			//For loop resets the mem 2D array to false
			for (int i = 0; i < 1000; i++)  //loop reiterates until all pixels within 2D array are set to 0 along x axis
			{
				for (int i2 = 0; i2 < 675; i2++)  //loop reiterates until all pixels within 2D array are set to 0 along y axis

					mem[i][i2] = false; //2D array x,y is entirely 0 and false
			}
			//*JR* (Jose)
			//Resetting player states and positions to original placement
			//Redrawing screen
			player1.s = 'r';
			player2.s = 'l';
			player1.x = 100;
			player1.y = 337;
			player2.x = 900;
			player2.y = 337;
			framedata.clear(); //clearing framedata texture
			framedata.draw(sBackground); //setting background
			renderWindow.clear(); //clear window
			renderWindow.draw(frameholder); //draw frameholder
			renderWindow.display(); //draw game
			r = false; //prevent infinite resetting
			
			//*AA* (Abed)
			//Creating a title variable to display in the titlebar of the game
			stringstream title;
			//Player scores are passed into title variable
			title << "blue player: " << player1.score << "                                                              red player:" << player2.score;
			renderWindow.setTitle(title.str()); //Print title variable to title bar

		}

		else {
			
			//Setting player positions to true
			mem[player1.x][player1.y] = true;
			mem[player2.x][player2.y] = true;

			
			//move player positions
			//player 1 or player 2's directional state is being read
			// .s is a property of the struct existing in our global declarations
			//move player in the correct direction according to their state
			if (player1.s == 'd') { player1.y = player1.y - 1; } // if player1's state is down then move down 1 pixel
			if (player1.s == 'u') { player1.y = player1.y + 1; } // if player1's state is up then move up 1 pixel
			if (player1.s == 'l') { player1.x = player1.x - 1; } // if player1's state is left then move left 1 pixel
			if (player1.s == 'r') { player1.x = player1.x + 1; } // if player1's state is right then move right 1 pixel

			//repeat for player2
			if (player2.s == 'd') { player2.y = player2.y - 1; }
			if (player2.s == 'u') { player2.y = player2.y + 1; }
			if (player2.s == 'l') { player2.x = player2.x - 1; }
			if (player2.s == 'r') { player2.x = player2.x + 1; }

			//Setting square positions to player positions
			p1.setPosition(sf::Vector2f(player1.x, player1.y));
			p2.setPosition(sf::Vector2f(player2.x, player2.y));
			framedata.draw(p1); //draw player1 square to frame data
			framedata.draw(p2); //draw player2 square to frame data
			renderWindow.clear(); //clear
			renderWindow.draw(frameholder); //draw frameholder
			renderWindow.display(); //draw game
		}

	}



	return; //End
}

//AP
//To be continued...	



