#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp{
	public:
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
    
        bool editMode;
        bool saveButtonCapado;

		int screenW, screenH;
		float indexW, indexH;
    
        // Panel y background
        ofImage panel;
        ofImage sandwich_13;
        ofImage sandwich_2;
        ofImage editor;
        ofImage postSave;
    
        // Fonts
        ofxTrueTypeFontUC question;
        ofxTrueTypeFontUC answer;
		ofxTrueTypeFontUC questionGUI;
		ofxTrueTypeFontUC answerGUI;
        ofxTrueTypeFontUC gui;
    
        // Strings
        void setupStrings();
        string questionString[3][3][5];
        int nStringActiveLines[3][5];
        int nStringLine[3][5];
        string answerStringA[5][3][5];
        int ansA_nStringActiveLines[3][5];
        int ansA_nStringLine[3][5];
        string answerStringB[5][3][5];
        int ansB_nStringActiveLines[3][5];
        int ansB_nStringLine[3][5];
        string answerStringC[5][3][5];
        int ansC_nStringActiveLines[3][5];
        int ansC_nStringLine[3][5];
    
        // Special characters
        void setupSpecialChars();
        void updateSpecialChars(int x, int y);
        void drawSpecialChars();
        string specialChars[9];
        ofPoint specialCharPos[9];
        int charButtonSize;
    
        ofImage imgTest;
        ofImage imgTest_2;
    
        bool bFirst;
        string typeStr;
        int questionLines;
    
    
    
        int squareW;
        int squareH;
        ofPoint squarePos;
    
    
        void setupPositions();
        // Posici—n para im‡genes sandwich sobre panel
        int imgPosX_1;
        int imgPosY_1;
        int imgPosX_2;
        int imgPosY_2;
        int imgPosX_3;
        int imgPosY_3;
        // Posiciones para el texto Q y A
        int marginW;
        int marginH;
        int marginW_a;
        int marginH_a;
        int marginW_b;
        int marginH_b;
        int marginW_c;
        int marginH_c;
        ofPoint marginDraw;
        ofPoint marginPost2[4];
    
        void setupQuestionCircles();
        void inputQuestionCircles(int x, int y);
        void updateQuestionCircles();
        void drawQuestionCircles();
        ofPoint circlePos[3][5];
        bool completedQuestion[3][5];
        int activeQuestion = 0;
        int activePostazione = 0;

    
        void updateFillInSigns(int x, int y);
        void drawFillInSigns(int nPostazione, int nFill);
        bool fillInSignsActive = true;
        int nFill = 0;
        ofPoint fillInPos;
    
        // SAVE
        bool checkAllQuestions();
        void setupSaveButton();
        void updateSaveButton(int x, int y, string state);
        void drawSaveButton();
        ofPoint saveButtonPos;
        int saveButtonW;
        int saveButtonH;
        int counterButtonPressed;
        bool saveButtonIsPressed;
        void saveImage();
    
        void setupRightQuestion();
        void updateRightQuestion(int x, int y);
        void drawRightQuestion();
        int marginRightQuestion;
        ofPoint correctPost2[2][3];
        ofImage right;
        ofImage wrong;
        ofImage selected;
        ofPoint selectedPos[3];
        ofPoint rightPos[3];
        int nRight[3][5];
        int selectedIconSize;
        int rwIconSize;
    
        //XML
        void saveXml();
};
