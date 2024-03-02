#pragma once

#include "ofMain.h"
#include "Button.h"

class ofApp : public ofBaseApp
{

	// enums to represent game states
	enum GameState
	{
		StartUp,
		PlayingSequence,
		PlayerInput,
		GameOver,
		RecordAndPlay,
		Record,
		Play,
		MultiplayerSequence,
		Multiplayer,
		MultiplayerInput,
		MultiGameOver,
		Lightning,
		lightningSequence,
		lightningInput,
		lightGameOver
	};

public:
	// Some OpenFrameworks must-have functions
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// Functions for our game
	void lightOn(Buttons color);
	void lightOff(Buttons color);
	void generateSequence();
	bool checkUserInput(Buttons c);
	void GameReset();
	void startUpSequence(int count);

private:
	// This vector will basically act as list of button enums
	// for us to be able to store the sequences
	vector<Buttons> Sequence;
	vector<Buttons> RecordAndPlaySequence;
	vector<Buttons> Player1Seq;
	vector<Buttons> Player2Seq;

	// Let's declare the buttons we will use
	Button *RedButton;
	Button *BlueButton;
	Button *YellowButton;
	Button *GreenButton;
	Button *RecordAndPlayGM;
	Button *MultiplayerGM;
	Button *LightningGM;

	// These will be mere images which we will draw on top
	// of the actual buttons to give the mere illusion
	// that the original buttons are lighting up
	ofImage redLight;
	ofImage blueLight;
	ofImage yellowLight;
	ofImage greenLight;
	ofImage logo;
	ofImage logoLight;
	ofImage startUpScreen;
	ofImage gameOverScreen;
	ofImage recordingIndicator;
	ofImage GameOverScreenEdited;
	ofImage SpaceBar;
	ofImage playButton;

	// Few variables we'll need
	ofSoundPlayer backgroundMusic;
	ofSoundPlayer gamemodeSound;
	int sequenceLimit = 1;
	int userIndex = 1;
	int showingSequenceDuration = 0;
	int lightDisplayDuration = -1;
	Buttons color;
	GameState gameState;
	bool logoIsReady = false;
	int logoCounter = 0;
	bool idle = true;
	int RecordAndPlayCounter = 0;
	int RecordAndPlayLim;
	int RecordAndPlayDuration = 0;
	int MultiplayerSequenceDuration = 0;
	bool player1turn = true;
	int player1Index = 0;
	int player2Index = 0;
	int player1SequenceLim;
	int player2SequenceLim;
	int p1Score = 0;
	int p2Score = 0;
	bool fail1 = false;
	bool fail2 = false;
	int reduce = 0;
	int round = 1;

	// Font
	ofTrueTypeFont highscoreStr;
	ofTrueTypeFont titleHighscoreStr;
};