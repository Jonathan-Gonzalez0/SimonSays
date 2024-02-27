#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

	// Let's create our buttons
	RedButton = new Button(ofGetWindowWidth() / 2 - 20, ofGetWindowHeight() / 2 - 260, 302, 239, "images/RedButton.png", "sounds/RedButton.mp3");
	BlueButton = new Button(ofGetWindowWidth() / 2 + 35, ofGetWindowHeight() / 2 - 10, 236, 290, "images/BlueButton.png", "sounds/BlueButton.mp3");
	YellowButton = new Button(ofGetWindowWidth() / 2 - 260, ofGetWindowHeight() / 2 + 40, 287, 239, "images/YellowButton.png", "sounds/YellowButton.mp3");
	GreenButton = new Button(ofGetWindowWidth() / 2 - 260, ofGetWindowHeight() / 2 - 260, 234, 294, "images/GreenButton.png", "sounds/GreenButton.mp3");
	NewGameMode = new Button(ofGetWindowWidth() / 2 - 500, ofGetWindowHeight() / 2 - 400, 225, 200, "images/freeTap.png", "sounds/GreenButton.mp3");
	MultiplayerGM = new Button(ofGetWindowWidth() / 2 - 440, ofGetWindowHeight() / 2 - 250, 150, 150, "images/multiplayerButtonImage.png", "sounds/YellowButton.mp3");

	// Load the glowing images for the buttons
	redLight.load("images/RedLight.png");
	blueLight.load("images/BlueLight.png");
	yellowLight.load("images/YellowLight.png");
	greenLight.load("images/GreenLight.png");

	// Load other images
	logo.load("images/Logo.png");
	logoLight.load("images/LogoLight.png");
	startUpScreen.load("images/StartScreen.png");
	gameOverScreen.load("images/GameOverScreen.png");
	recordingIndicator.load("images/recordIndicator.png");

	// Load Music
	backgroundMusic.load("sounds/BackgroundMusic.mp3");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	// Initial State
	
	gameState = StartUp;
}
//--------------------------------------------------------------
void ofApp::update()
{

	// We will tick the buttons, aka constantly update them
	// while expecting input from the user to see if anything changed
	if ( gameState == FreeTap || gameState == Record)
	{
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();
	}

	if (gameState == PlayerInput)
	{
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();

		// If the amount of user input equals the sequence limit
		// that means the user has successfully completed the whole
		// sequence and we can proceed with the next level
		if (userIndex == sequenceLimit)
		{
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = PlayingSequence;
		}
	}

	if (gameState == MultiplayerInput)
	{
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();

		// If the amount of user input equals the sequence limit
		// that means the user has successfully completed the whole
		// sequence and we can proceed with the next level
		if (player1Index == player1SequenceLim && player1turn == true)
		{
			player1turn = false;
			MultiplayerSequenceDuration= 0;
			gameState = MultiplayerSequence;

		}
		if(player2Index == player2SequenceLim && player1turn == false){
			player1turn = true;
			gameState = MultiplayerSequence;
			generateSequence();
			player1Index = 0;
			player2Index = 0;
			MultiplayerSequenceDuration = 0;

		}
	}
	// This will take care of turning on the lights after a few
	// ticks so that they dont stay turned on forever or too long
	if (lightDisplayDuration > 0)
	{
		lightDisplayDuration--;
		if (lightDisplayDuration <= 0)
		{
			lightOff(RED);
			lightOff(BLUE);
			lightOff(YELLOW);
			lightOff(GREEN);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Create the background
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

	// Draw the buttons
	ofSetColor(255, 0, 0);
	RedButton->render();
	BlueButton->render();
	YellowButton->render();
	GreenButton->render();

	if(gameState == Record){
		recordingIndicator.draw(ofGetWindowWidth() / 2 - 500, ofGetWindowHeight() / 2 - 400, 225, 200);
	}

	if(gameState == StartUp){
		NewGameMode->render();
		MultiplayerGM->render();
	}

	// This whole if statement will take care of showing
	// the sequence to the user before accepting any input
	if (gameState == PlayingSequence)
	{
		
		showingSequenceDuration++;
		if (showingSequenceDuration == 120)
		{
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}

		if (showingSequenceDuration == 140)
		{
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if (userIndex == sequenceLimit)
		{
			lightOff(color);
			userIndex = 0;
			gameState = PlayerInput;
		}
	}

	if(gameState == Play)
	{
		FreeTapDuration++;
		if(FreeTapDuration ==120)
		{
			color = FreeTapSequence[FreeTapCounter];
			lightOn(color);
			lightDisplayDuration = 30;
			
		}
			
		if (FreeTapDuration ==140)
		{
			lightOff(color);
			FreeTapDuration = 60;
			FreeTapCounter++;
		}
			if (FreeTapCounter == FreeTapLim)
		{
			gameState = FreeTap;
		}
		


}	
	if(gameState == MultiplayerSequence){
		MultiplayerSequenceDuration++;

		if(MultiplayerSequenceDuration==120 && player1turn==true){

			color=Player1Seq[player1Index];

			lightOn(color);

			lightDisplayDuration=30;
		}
		if (MultiplayerSequenceDuration == 140 && player1turn == true)
		{
			lightOff(color);
			MultiplayerSequenceDuration = 60;
			player1Index++;
		}
		if (player1Index == player1SequenceLim &&  player1turn == true)
		{
			lightOff(color);
			player1Index = 0;
			gameState = MultiplayerInput;
		}
		if(MultiplayerSequenceDuration==120 && player1turn == false){

			color=Player2Seq[player2Index];

			lightOn(color);

			lightDisplayDuration=30;
		}
		if (MultiplayerSequenceDuration == 140 && player1turn == false)
		{
			lightOff(color);
			MultiplayerSequenceDuration = 60;
			player2Index++;
		}
		if (player2Index == player2SequenceLim && player1turn == false)
		{
			lightOff(color);
			player2Index = 0;
			gameState = MultiplayerInput;
		}

	}
	

	// StartUP (You dont need to pay much attention to this)
	//(This is only to create a animation effect at the start of the game)
	if (gameState == StartUp)
	{
		showingSequenceDuration++;
		startUpSequence(showingSequenceDuration);
	}

	// If the statements to see see if the buttons should be lit up
	// If they are then we will draw the glowing images on top of them
	if (RedButton->GetIsLightUp())
	{
		redLight.draw(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2 - 305, 376, 329);
	}
	if (BlueButton->GetIsLightUp())
	{
		blueLight.draw(ofGetWindowWidth() / 2 + 5, ofGetWindowHeight() / 2 - 60, 309, 376);
	}
	if (YellowButton->GetIsLightUp())
	{
		yellowLight.draw(ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() / 2 + 5, 374, 318);
	}
	if (GreenButton->GetIsLightUp())
	{
		greenLight.draw(ofGetWindowWidth() / 2 - 307, ofGetWindowHeight() / 2 - 295, 315, 356);
	}

	// Part of the Start Up
	if (logoIsReady)
	{
		logo.draw(ofGetWindowWidth() / 2 - 160, ofGetWindowHeight() / 2 - 150, 330, 330);
	}

	// Draw the game over screen
	if (gameState == GameOver)
	{
		gameOverScreen.draw(0, 0, 1024, 768);
	}

	// This will draw the "Press to Start" screen at the beginning
	else if (!idle && gameState == StartUp)
	{
		startUpScreen.draw(20, 0, 1024, 768);
	}
}
//--------------------------------------------------------------
void ofApp::GameReset()
{
	// This function will reset the game to its initial state
	// and generate a new sequence
	if(gameState == Multiplayer){
		lightOff(RED);
		lightOff(BLUE);
		lightOff(YELLOW);
		lightOff(GREEN);
		Player1Seq.clear();
		Player2Seq.clear();
		gameState = MultiplayerSequence;
		player1Index = 0;
		player2Index = 0;
		generateSequence();
		MultiplayerSequenceDuration = 0;
		
		
		
	}else{
		lightOff(RED);
		lightOff(BLUE);
		lightOff(YELLOW);
		lightOff(GREEN);
		Sequence.clear();
		generateSequence();
		userIndex = 0;
		gameState = PlayingSequence;
		showingSequenceDuration = 0;
	}	
}

//--------------------------------------------------------------
void ofApp::generateSequence()
{
	// This function will generate a random number between 0 and 3
	int random = ofRandom(4);
	if(gameState == MultiplayerSequence){
		random = ofRandom(4);
		if(player1turn==true){
			if(random==0){

				Player1Seq.push_back(RED);

			}else if (random == 1){	

				Player1Seq.push_back(GREEN);

			}else if (random == 2){

				Player1Seq.push_back(YELLOW);

			}else if (random == 3){

				Player1Seq.push_back(BLUE);

			}
			player1turn = false;
			player1SequenceLim = Player1Seq.size();
		}
		random = ofRandom(4);
		if(player1turn==false){
				if(random==0){
					Player2Seq.push_back(RED);
				}else if (random == 1){	
					Player2Seq.push_back(GREEN);
				}else if (random == 2){
					Player2Seq.push_back(YELLOW);
				}else if (random == 3){
					Player2Seq.push_back(BLUE);
				}
			player2SequenceLim = Player1Seq.size();
			player1turn = true;
		}
	}else{
		// Depending on the random number, we will add a button to the sequence
		if (random == 0)
		{
			Sequence.push_back(RED);
		}
		else if (random == 1)
		{
			Sequence.push_back(GREEN);
		}
		else if (random == 2)
		{
			Sequence.push_back(YELLOW);
		}
		else if (random == 3)
		{
			Sequence.push_back(BLUE);
		}

			// We will adjust the sequence limit to the new size of the Sequence list
		sequenceLimit = Sequence.size();
	}
	
	
	
}
//--------------------------------------------------------------
bool ofApp::checkUserInput(Buttons input)
{
	// This function will varify if the user input matches the color
	// of the sequence at the current index
	if(gameState == MultiplayerInput){
		if (Player1Seq[player1Index] == input && player1turn == true)
		{
			return true;
		}
		else if(player1turn == true)
		{
			return false;
		}
		if (Player2Seq[player2Index] == input && player1turn == false)
		{
			return true;
		}
		else if(player1turn == false)
		{
			return false;
		}
	}else{
		if (Sequence[userIndex] == input)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
//--------------------------------------------------------------
void ofApp::lightOn(Buttons color)
{
	// This function will take care of toggling the "isLightUp" variable to
	// true for the button that matches the color, and also play the button sound
	if (color == RED)
	{
		RedButton->toggleLightOn();
		RedButton->playSound();
	}
	else if (color == BLUE)
	{
		BlueButton->toggleLightOn();
		BlueButton->playSound();
	}
	else if (color == YELLOW)
	{
		YellowButton->toggleLightOn();
		YellowButton->playSound();
	}
	else if (color == GREEN)
	{
		GreenButton->toggleLightOn();
		GreenButton->playSound();
	}
}

//--------------------------------------------------------------
void ofApp::lightOff(Buttons color)
{
	// This function will take care of toggling the "isLightUp" variable to false
	if (color == RED)
	{
		RedButton->toggleLightOff();
	}
	else if (color == BLUE)
	{
		BlueButton->toggleLightOff();
	}
	else if (color == YELLOW)
	{
		YellowButton->toggleLightOff();
	}
	else if (color == GREEN)
	{
		GreenButton->toggleLightOff();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	// As long as we're not in Idle OR the gameState is GameOver;
	// AND we press the SPACEBAR, we will reset the game
	if ((!idle || gameState == GameOver) && tolower(key) == ' ')
	{
		GameReset();
	}
	if(key == OF_KEY_BACKSPACE){
		gameState = StartUp;
	}
	if(gameState== FreeTap || gameState == Record || gameState == Play){
		if(tolower(key) =='r' && FreeTapCounter ==0 && gameState != Record){
			gameState = Record;
		}
		else if(tolower(key) == 'r' && gameState == Record){
			gameState = FreeTap;
		}
		else if(tolower(key) == 'r' && FreeTapCounter != 0){
			FreeTapSequence.clear();
			FreeTapCounter = 0;
			gameState = Record;
		}
	}
	if(tolower(key) == 'p'){
		gameState = Play;
		FreeTapDuration = 60;
		FreeTapLim = FreeTapSequence.size();
		FreeTapCounter = 0;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int mouseX, int mouseY)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

	if(gameState == StartUp){
		NewGameMode->setPressed(x, y);
		MultiplayerGM->setPressed(x, y);
		if(NewGameMode->wasPressed()){
			idle = false; //Why?
			gameState = FreeTap;
		}else if(MultiplayerGM->wasPressed()){
			gameState = Multiplayer;
			GameReset();
		}
	}

	if(gameState == Record){
		RedButton->setPressed(x, y);
		BlueButton->setPressed(x, y);
		YellowButton->setPressed(x, y);
		GreenButton->setPressed(x, y);

		if (RedButton->wasPressed())
		{
			color = RED;
			FreeTapSequence.push_back(RED);
			FreeTapCounter++; //Counts how many timwes we pressed the color.
		
		}
		else if (BlueButton->wasPressed())
		{
			color = BLUE;
			FreeTapSequence.push_back(BLUE);
			FreeTapCounter++;
		}
		else if (YellowButton->wasPressed())
		{
			color = YELLOW;
			FreeTapSequence.push_back(YELLOW);
			FreeTapCounter++;
		}
		else if (GreenButton->wasPressed())
		{
			color = GREEN;
			FreeTapSequence.push_back(GREEN);
			FreeTapCounter++;
		}
		lightOn(color);
		lightDisplayDuration = 15;

	}

	if(gameState == FreeTap){
		RedButton->setPressed(x, y);
		BlueButton->setPressed(x, y);
		YellowButton->setPressed(x, y);
		GreenButton->setPressed(x, y);

		if (RedButton->wasPressed())
		{
			color = RED;
		
		}
		else if (BlueButton->wasPressed())
		{
			color = BLUE;
		}
		else if (YellowButton->wasPressed())
		{
			color = YELLOW;
		}
		else if (GreenButton->wasPressed())
		{
			color = GREEN;
		}
		lightOn(color);
		lightDisplayDuration = 15;
	} 

	if(!idle && gameState == PlayerInput)
	{
		// We mark the pressed button as "pressed"
		RedButton->setPressed(x, y);
		BlueButton->setPressed(x, y);
		YellowButton->setPressed(x, y);
		GreenButton->setPressed(x, y);

		// We check which button got pressed
		if (RedButton->wasPressed())
		{
			color = RED;
		}
		else if (BlueButton->wasPressed())
		{
			color = BLUE;
		}
		else if (YellowButton->wasPressed())
		{
			color = YELLOW;
		}
		else if (GreenButton->wasPressed())
		{
			color = GREEN;
		}
		// Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
		// If the user input is correct, we can continue checking
		if (checkUserInput(color))
		{
			userIndex++;
		}
		// If not, then we will terminate the game by
		// putting it in the GameOver state.
		else
		{
			gameState = GameOver;
		}
	}
	if( gameState == MultiplayerInput)
	{
		// We mark the pressed button as "pressed"
		RedButton->setPressed(x, y);
		BlueButton->setPressed(x, y);
		YellowButton->setPressed(x, y);
		GreenButton->setPressed(x, y);

		// We check which button got pressed
		if (RedButton->wasPressed())
		{
			color = RED;
		}
		else if (BlueButton->wasPressed())
		{
			color = BLUE;
		}
		else if (YellowButton->wasPressed())
		{
			color = YELLOW;
		}
		else if (GreenButton->wasPressed())
		{
			color = GREEN;
		}
		// Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
		// If the user input is correct, we can continue checking
		if (player1turn == true && checkUserInput(color))
		{
			player1Index++;
		}
		else if (player1turn == false && checkUserInput(color))
		{
			player2Index++;
		}
		// If not, then we will terminate the game by
		// putting it in the GameOver state.
		else
		{
			gameState = GameOver;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
//--------------------------------------------------------------

// You may honestly ignore this function, shouldnt be something you need
// to change or anything. It's only for the start up animation. But ofc,
// If you wish to make something out of it or make it better, be my guest.
void ofApp::startUpSequence(int count)
{

	if (count < 200)
	{
		GreenButton->toggleLightOn();
	}
	else if (count >= 200 && count < 260)
	{
		GreenButton->toggleLightOff();
		RedButton->toggleLightOn();
	}
	else if (count >= 260 && count < 320)
	{
		RedButton->toggleLightOff();
		BlueButton->toggleLightOn();
	}
	else if (count >= 320 && count < 380)
	{
		BlueButton->toggleLightOff();
		YellowButton->toggleLightOn();
	}
	else if (count >= 380 && count < 440)
	{
		YellowButton->toggleLightOff();
	}
	else if (count >= 440 && count < 500)
	{
		GreenButton->toggleLightOn();
		RedButton->toggleLightOn();
		YellowButton->toggleLightOn();
		BlueButton->toggleLightOn();
	}
	else if (count >= 500 && count < 560)
	{
		GreenButton->toggleLightOff();
		RedButton->toggleLightOff();
		YellowButton->toggleLightOff();
		BlueButton->toggleLightOff();
	}
	else if (count >= 560)
	{
		showingSequenceDuration = 400;
	}

	// Logo Drawing
	if (logoIsReady && logoCounter > 0)
	{
		logoCounter--;
		ofSetColor(256, 256, 256, logoCounter);
		logoLight.draw(ofGetWindowWidth() / 2 - 160, ofGetWindowHeight() / 2 - 150, 330, 330);
		ofSetColor(256, 256, 256);
	}
	if ((count > 375) && !logoIsReady)
	{
		logoCounter++;

		ofSetColor(256, 256, 256, logoCounter);
		logoLight.draw(ofGetWindowWidth() / 2 - 160, ofGetWindowHeight() / 2 - 150, 330, 330);

		ofSetColor(256, 256, 256, logoCounter);
		logo.draw(ofGetWindowWidth() / 2 - 160, ofGetWindowHeight() / 2 - 150, 330, 330);

		ofSetColor(256, 256, 256);
	}
	if (logoCounter >= 255)
	{
		logoIsReady = true;
		idle = false;
	}
}

