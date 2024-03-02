#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

	// Let's create our buttons
	RedButton = new Button(ofGetWindowWidth() / 2 - 20, ofGetWindowHeight() / 2 - 260, 302, 239, "images/RedButton.png", "sounds/RedButton.mp3");
	BlueButton = new Button(ofGetWindowWidth() / 2 + 35, ofGetWindowHeight() / 2 - 10, 236, 290, "images/BlueButton.png", "sounds/BlueButton.mp3");
	YellowButton = new Button(ofGetWindowWidth() / 2 - 260, ofGetWindowHeight() / 2 + 40, 287, 239, "images/YellowButton.png", "sounds/YellowButton.mp3");
	GreenButton = new Button(ofGetWindowWidth() / 2 - 260, ofGetWindowHeight() / 2 - 260, 234, 294, "images/GreenButton.png", "sounds/GreenButton.mp3");
	RecordAndPlayGM = new Button(ofGetWindowWidth() / 2 - 500, ofGetWindowHeight() / 2 - 450, 300, 300, "images/recordAndPlay.png", "sounds/RedButton.mp3");
	MultiplayerGM = new Button(ofGetWindowWidth() - 192, ofGetWindowHeight() / 2 - 385, 150, 150, "images/multiplayerButtonImage.png", "sounds/RedButton.mp3");
	LightningGM = new Button(ofGetWindowWidth()/2 - 500, ofGetWindowHeight() - 235, 250, 200, "images/lightning.png", "sounds/RedButton.mp3");
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
	GameOverScreenEdited.load("images/Gameover.png");
	SpaceBar.load("images/SpaceBar.png");
	playButton.load("images/playButton.png");

	// Load Music
	backgroundMusic.load("sounds/BackgroundMusic.mp3");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	// gamemodeSound.load("sounds/clickGMButton.mp3");

	// Initial State

	gameState = StartUp;

	// Loads Font
	highscoreStr.load("fonts/PlayfairDisplay-Black.ttf", 32);
	titleHighscoreStr.load("fonts/PlayfairDisplay-Black.ttf", 52);
}
//--------------------------------------------------------------
void ofApp::update()
{

	// We will tick the buttons, aka constantly update them
	// while expecting input from the user to see if anything changed
	if (gameState == RecordAndPlay || gameState == Record)
	{
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();
	}

	if (gameState == StartUp)
	{
		RecordAndPlayGM->tick();
		MultiplayerGM->tick();
		LightningGM->tick();
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

	if (gameState == lightningInput)
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
			reduce += 4;
			if(reduce >= 29){
				reduce = 29;
			}
			round++;
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = lightningSequence;
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
			if (!fail2)
			{
				player1turn = false;
				MultiplayerSequenceDuration = 0;
				gameState = MultiplayerSequence;
			}
			else
			{
				gameState = MultiplayerSequence;
				generateSequence();
				player1Index = 0;
				MultiplayerSequenceDuration = 0;
			}
		}
		if (player2Index == player2SequenceLim && player1turn == false)
		{
			if (!fail1)
			{
				player1turn = true;
				player1Index = 0;
			}
			gameState = MultiplayerSequence;
			generateSequence();
			player2Index = 0;
			MultiplayerSequenceDuration = 0;
		}
	}
	// This will take care of turning on the lights after a few
	// ticks so that they dont stay turned on forever or too long
	if (gameState == MultiGameOver)
	{
		MultiplayerSequenceDuration++;
	}
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

	if(gameState == PlayerInput || gameState==PlayingSequence){
		highscoreStr.drawString("Classic Mode", 75,ofGetWindowHeight() - 50);
	}
	if (gameState == Record)
	{
		highscoreStr.drawString("Record/Play Mode", 75,ofGetWindowHeight() - 50);
		recordingIndicator.draw(ofGetWindowWidth() / 2 - 450, ofGetWindowHeight() / 2 - 350, 200, 165);
	}

	if(gameState == Play){
		highscoreStr.drawString("Record/Play Mode", 75,ofGetWindowHeight() - 50);
		playButton.draw(ofGetWindowWidth() / 2 - 400, ofGetWindowHeight() / 2 - 300, 100, 65);
	}

	if(gameState == RecordAndPlay){
		highscoreStr.drawString("Record/Play Mode", 75,ofGetWindowHeight() - 50);
	}

	if(gameState == lightningInput || gameState==lightningSequence){
		highscoreStr.drawString("Lightning Mode", 75,ofGetWindowHeight() - 50);
		highscoreStr.drawString("Round: " + ofToString(round), 50, 100);
	}

	if (gameState == StartUp)
	{
		RecordAndPlayGM->render();
		MultiplayerGM->render();
		LightningGM->render();
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

	if (gameState == lightningSequence)
	{

		showingSequenceDuration++;
		if (showingSequenceDuration == 120)
		{
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30-reduce;
		}

		if (showingSequenceDuration == 150-reduce)
		{
			lightOff(color);
			showingSequenceDuration = 60+reduce;
			userIndex++;
		}
		if (userIndex == sequenceLimit)
		{
			lightOff(color);
			userIndex = 0;
			gameState = lightningInput;
		}
	}

	if (gameState == Play)
	{
		RecordAndPlayDuration++;
		if (RecordAndPlayDuration == 120)
		{
			color = RecordAndPlaySequence[RecordAndPlayCounter];
			lightOn(color);
			lightDisplayDuration = 30;
		}

		if (RecordAndPlayDuration == 140)
		{
			lightOff(color);
			RecordAndPlayDuration = 60;
			RecordAndPlayCounter++;
		}
		if (RecordAndPlayCounter == RecordAndPlayLim)
		{
			gameState = RecordAndPlay;
		}
	}

	if (gameState == MultiplayerSequence)
	{
		MultiplayerSequenceDuration++;
		highscoreStr.drawString("Multiplayer Mode", 75,ofGetWindowHeight() - 50);
		if (MultiplayerSequenceDuration == 120 && player1turn == true && !fail1)
		{

			color = Player1Seq[player1Index];

			lightOn(color);

			lightDisplayDuration = 30;
		}
		if (MultiplayerSequenceDuration == 140 && player1turn == true && !fail1)
		{
			lightOff(color);
			MultiplayerSequenceDuration = 60;
			player1Index++;
		}
		if (player1Index == player1SequenceLim && player1turn == true && !fail1)
		{
			lightOff(color);
			player1Index = 0;
			gameState = MultiplayerInput;
		}
		if (MultiplayerSequenceDuration == 120 && player1turn == false && !fail2)
		{

			color = Player2Seq[player2Index];

			lightOn(color);

			lightDisplayDuration = 30;
		}
		if (MultiplayerSequenceDuration == 140 && player1turn == false && !fail2)
		{
			lightOff(color);
			MultiplayerSequenceDuration = 60;
			player2Index++;
		}
		if (player2Index == player2SequenceLim && player1turn == false && !fail2)
		{
			lightOff(color);
			player2Index = 0;
			gameState = MultiplayerInput;
		}
	}

	if (gameState == MultiplayerSequence || gameState == MultiplayerInput)
	{
		highscoreStr.drawString("Multiplayer Mode", 75,ofGetWindowHeight() - 50);
		if (player1turn == true)
		{
			highscoreStr.drawString("Player 1 Turn:", 25, 100);
			highscoreStr.drawString("Score: " + ofToString(p1Score), ofGetWindowWidth() - 275, 100);
		}
		else if (player1turn == false)
		{
			highscoreStr.drawString("Player 2 Turn:", 25, 100);
			highscoreStr.drawString("Score: " + ofToString(p2Score), ofGetWindowWidth() - 275, 100);
		}
	}

	if (gameState == MultiGameOver)
	{
		if (MultiplayerSequenceDuration <= 120)
		{
			GameOverScreenEdited.draw(0, 0, 1024, 768);
		}
		else
		{
			SpaceBar.draw(0, 0, 1024, 768);
			if (p1Score > p2Score)
			{
				titleHighscoreStr.drawString("Player 1 Wins!", ofGetWindowWidth() / 2 - 232, 100);
			}
			else if (p1Score == p2Score)
			{
				titleHighscoreStr.drawString("Tie!", ofGetWindowWidth() / 2 - 70, 100);
			}
			else
			{
				titleHighscoreStr.drawString("Player 2 Wins!", ofGetWindowWidth() / 2 - 232, 100);
			}
			titleHighscoreStr.drawString("Stats:", ofGetWindowWidth() / 2 - 100, 200);
			highscoreStr.drawString("Player 1 Score: " + ofToString(p1Score), ofGetWindowWidth() / 2 - 175, 300);
			highscoreStr.drawString("Player 2 Score: " + ofToString(p2Score), ofGetWindowWidth() / 2 - 175, 400);
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
	if (logoIsReady && gameState != MultiGameOver)
	{
		logo.draw(ofGetWindowWidth() / 2 - 160, ofGetWindowHeight() / 2 - 150, 330, 330);
	}

	// Draw the game over screen
	if (gameState == GameOver)
	{
		gameOverScreen.draw(0, 0, 1024, 768);
	}
	
	if (gameState == lightGameOver)
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
	if (gameState == Multiplayer)
	{
		lightOff(RED);
		lightOff(BLUE);
		lightOff(YELLOW);
		lightOff(GREEN);
		Player1Seq.clear();
		Player2Seq.clear();
		gameState = MultiplayerSequence;
		player1Index = 0;
		player2Index = 0;
		fail1 = false;
		fail2 = false;
		p1Score = 0;
		p2Score = 0;
		player1turn = true;
		generateSequence();
		MultiplayerSequenceDuration = 0;
	}
	else if(gameState == Lightning){
		lightOff(RED);
		lightOff(BLUE);
		lightOff(YELLOW);
		lightOff(GREEN);
		Sequence.clear();
		gameState = lightningSequence;
		generateSequence();
		userIndex = 0;
		showingSequenceDuration = 0;
		reduce = 0;
		round = 1;
	}
	else
	{
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
	if (gameState == MultiplayerSequence)
	{
		random = ofRandom(4);
		if (player1turn == true)
		{
			if (random == 0)
			{

				Player1Seq.push_back(RED);
			}
			else if (random == 1)
			{

				Player1Seq.push_back(GREEN);
			}
			else if (random == 2)
			{

				Player1Seq.push_back(YELLOW);
			}
			else if (random == 3)
			{

				Player1Seq.push_back(BLUE);
			}
			if (!fail2)
			{
				player1turn = false;
			}
			player1SequenceLim = Player1Seq.size();
		}
		random = ofRandom(4);
		if (player1turn == false)
		{
			if (random == 0)
			{
				Player2Seq.push_back(RED);
			}
			else if (random == 1)
			{
				Player2Seq.push_back(GREEN);
			}
			else if (random == 2)
			{
				Player2Seq.push_back(YELLOW);
			}
			else if (random == 3)
			{
				Player2Seq.push_back(BLUE);
			}
			player2SequenceLim = Player2Seq.size();
			if (!fail1)
			{
				player1turn = true;
			}
		}
	}
	else if(gameState == lightningSequence){
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
	else
	{
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
	if (gameState == MultiplayerInput)
	{
		if (Player1Seq[player1Index] == input && player1turn == true)
		{
			return true;
		}
		else if (player1turn == true)
		{
			return false;
		}
		if (Player2Seq[player2Index] == input && player1turn == false)
		{
			return true;
		}
		else if (player1turn == false)
		{
			return false;
		}
	}
	else
	{
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
	if ((!idle || gameState == GameOver) && tolower(key) == ' ' && gameState != RecordAndPlay && gameState != Record && gameState != Play && gameState != Multiplayer && gameState != MultiplayerSequence && gameState != MultiplayerInput && gameState != MultiGameOver && gameState != Lightning && gameState != lightningSequence && gameState != lightningInput && gameState != lightGameOver)
	{
		GameReset();
	}
	if(gameState == lightGameOver && tolower(key) == ' '){
		gameState = Lightning;
		GameReset();
	}
	if (key == OF_KEY_BACKSPACE)
	{
		gameState = StartUp;
	}
	if (gameState == RecordAndPlay || gameState == Record || gameState == Play)
	{
		if (tolower(key) == 'r' && RecordAndPlayCounter == 0 && gameState != Record)
		{
			gameState = Record;
		}
		else if (tolower(key) == 'r' && gameState == Record)
		{
			gameState = RecordAndPlay;
		}
		else if (tolower(key) == 'r' && RecordAndPlayCounter != 0)
		{
			RecordAndPlaySequence.clear();
			RecordAndPlayCounter = 0;
			gameState = Record;
		}
	}
	if (tolower(key) == 'p' && RecordAndPlayCounter != 0 )
	{
		gameState = Play;
		RecordAndPlayDuration = 60;
		RecordAndPlayLim = RecordAndPlaySequence.size();
		RecordAndPlayCounter = 0;
	}
	if (gameState == MultiGameOver && tolower(key) == ' ' && MultiplayerSequenceDuration > 120)
	{
		gameState = Multiplayer;
		GameReset();
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

	if (gameState == StartUp)
	{
		RecordAndPlayGM->setPressed(x, y);
		MultiplayerGM->setPressed(x, y);
		LightningGM->setPressed(x,y);
		if (RecordAndPlayGM->wasPressed())
		{
			// gamemodeSound.play();
			idle = false;
			gameState = RecordAndPlay;
		}
		else if (MultiplayerGM->wasPressed())
		{
			// gamemodeSound.play();
			gameState = Multiplayer;
			GameReset();
		}
		else if(LightningGM->wasPressed()){
			gameState = Lightning;
			GameReset();
		}
	}

	if (gameState == Record)
	{
		RedButton->setPressed(x, y);
		BlueButton->setPressed(x, y);
		YellowButton->setPressed(x, y);
		GreenButton->setPressed(x, y);

		if (RedButton->wasPressed())
		{
			color = RED;
			RecordAndPlaySequence.push_back(RED);
			RecordAndPlayCounter++; // Counts how many timwes we pressed the color.
		}
		else if (BlueButton->wasPressed())
		{
			color = BLUE;
			RecordAndPlaySequence.push_back(BLUE);
			RecordAndPlayCounter++;
		}
		else if (YellowButton->wasPressed())
		{
			color = YELLOW;
			RecordAndPlaySequence.push_back(YELLOW);
			RecordAndPlayCounter++;
		}
		else if (GreenButton->wasPressed())
		{
			color = GREEN;
			RecordAndPlaySequence.push_back(GREEN);
			RecordAndPlayCounter++;
		}
		lightOn(color);
		lightDisplayDuration = 15;
	}

	if (gameState == RecordAndPlay)
	{
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

	if (!idle && gameState == PlayerInput)
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
	if (gameState == lightningInput)
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
			gameState = lightGameOver;
		}
	}
	if (gameState == MultiplayerInput)
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
		if (player1turn == true && checkUserInput(color) && !fail1)
		{
			player1Index++;
			p1Score += 1;
		}
		else if (player1turn == true)
		{
			player1Index = player1SequenceLim;
			fail1 = true;
		}
		else if (player1turn == false && checkUserInput(color) && !fail2)
		{
			player2Index++;
			p2Score += 1;
		}
		else if (player1turn == false)
		{
			player2Index = player2SequenceLim;
			fail2 = true;
		}
		// If not, then we will terminate the game by
		// putting it in the GameOver state.
		if (fail1 && fail2)
		{
			gameState = MultiGameOver;
			MultiplayerSequenceDuration = 0;
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
