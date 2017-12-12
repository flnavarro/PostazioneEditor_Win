#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(60);
	screenW = ofGetScreenWidth();
	indexW = float(screenW) / float(1920);
    
	ofSetWindowShape(ofGetWidth(), 807 * indexW);
    
    saveResRatio = 3;

	// FONDO
	panel.load("imgFondo/panelFinal.png");
	sandwich_13.load("imgFondo/sandwich_13.png");
	sandwich_2.load("imgFondo/sandwich_2.png");
	editor.load("imgFondo/post_editor.png");
	postSave.load("imgFondo/post_final.png");

	// TEST- ONLY DEBUG ******
	//imgTest.load("imgTest/question_13.png");
	//imgTest_2.load("imgTest/question_2.png");

	// Fonts
    ofxTrueTypeFontUC::setGlobalDpi(100);
	// question.load("fonts/UniversLTStd-BoldCn.otf", 14, true, false);
	question.load("fonts/UniversLTStd-BoldCn.otf", 13*saveResRatio, true);
	question.setSpaceSize(0.6f);
	answer.load("fonts/UniversLTStd-BoldCn.otf", 12*saveResRatio, true);
	answer.setSpaceSize(0.6f);
	questionGUI.load("fonts/UniversLTStd-BoldCn.otf", int(13*indexW), true);
    questionGUI.setSpaceSize(0.6f*indexW);
	answerGUI.load("fonts/UniversLTStd-BoldCn.otf", int(12*indexW), true);
	answerGUI.setSpaceSize(0.6f*indexW);
	gui.load("fonts/UniversLTStd-LightCn.otf", 16, true, false);
	gui.setSpaceSize(0.6f*indexW);

	setupSaveButton();
	setupPositions();
	setupRightQuestion();
	setupQuestionCircles();
	setupStrings();
	setupSpecialChars();

	bFirst = true;

	// ???
	questionLines = 1;

	// DEBUG ONLY
	squareW = 137;
	squareH = 64;
	squarePos.x = -1;
	squarePos.y = -39;

	editMode = true;
    
    saveButtonCapado = false;
    
    isWindows = false;
}

void ofApp::setupStrings() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			nStringActiveLines[i][j] = 1;
			nStringLine[i][j] = 0;
			ansA_nStringActiveLines[i][j] = 1;
			ansA_nStringLine[i][j] = 0;
			ansB_nStringActiveLines[i][j] = 1;
			ansB_nStringLine[i][j] = 0;
			ansC_nStringActiveLines[i][j] = 1;
			ansC_nStringLine[i][j] = 0;
		}
	}
}

void ofApp::setupSpecialChars() {
	specialChars[0] = "À";
	specialChars[1] = "È";
	specialChars[2] = "É";
	specialChars[3] = "Ì";
	specialChars[4] = "Í";
	specialChars[5] = "Ò";
	specialChars[6] = "Ó";
	specialChars[7] = "Ù";
	specialChars[8] = "Ú";
	ofPoint charPos;
	charPos.x = 75;
	charPos.y = 475;
	charButtonSize = 30;
	for (int i = 0; i < 9; i++) {
		specialCharPos[i] = ofPoint(charPos.x, charPos.y);
		if (i == 2 || i == 5) {
			charPos.x = 75;
			charPos.y += 30 + 10;
		}
		else {
			charPos.x += 30 + 10;
		}
	}
}

void ofApp::updateSpecialChars(int x, int y) {
	for (int i = 0; i < 9; i++) {
		if (x > specialCharPos[i].x*indexW && 
			x < (specialCharPos[i].x + charButtonSize)*indexW &&
			y > specialCharPos[i].y*indexW &&
			y < (specialCharPos[i].y + charButtonSize)*indexW) {
			if (nFill == 0) {
				questionString[nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] += specialChars[i];
			}
			else if (nFill == 1) {
				answerStringA[ansA_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] += specialChars[i];
			}
			else if (nFill == 2) {
				answerStringB[ansB_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] += specialChars[i];
			}
			else if (nFill == 3) {
				answerStringC[ansC_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] += specialChars[i];
			}
			break;
		}
	}
}

void ofApp::drawSpecialChars() {
	ofPushStyle();
	ofSetColor(15, 15, 15, 150);
	// gui.drawString("Special Characters", specialCharPos[0].x-15, specialCharPos[0].y-20);
	for (int i = 0; i < 9; i++) {
		ofSetColor(200, 200, 200, 200);
		ofDrawRectangle(specialCharPos[i].x, specialCharPos[i].y, charButtonSize, charButtonSize);
		ofSetColor(255, 255, 255, 150);
		question.drawString(specialChars[i], specialCharPos[i].x + 8, specialCharPos[i].y + 25);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::update() {
	//    answerStringA = typeStr;
	//    answerStringB = typeStr;
	//    answerStringC = typeStr;

	if (editMode) {
		updateQuestionCircles();
	}
}



//--------------------------------------------------------------
void ofApp::draw() {
	if (editMode) {
		// PANEL (FONDO)
		panel.draw(0, 0, panel.getWidth()*indexW, panel.getHeight()*indexW);

		// Sandwiches (para poner texto dentro)
		sandwich_13.draw(imgPosX_1*indexW, imgPosY_1*indexW, 
			sandwich_13.getWidth()*indexW, sandwich_13.getHeight()*indexW);
		sandwich_13.draw(imgPosX_3*indexW, imgPosY_3*indexW,
			sandwich_13.getWidth()*indexW, sandwich_13.getHeight()*indexW);
		sandwich_2.draw(imgPosX_2*indexW, imgPosY_2*indexW,
			sandwich_2.getWidth()*indexW, sandwich_2.getHeight()*indexW);

		// ONLY DEBUG *****
		// imgTest.draw(imgPosX_1, imgPosY_1);
		// imgTest.draw(imgPosX_3, imgPosY_3);
		// imgTest_2.draw(imgPosX_2, imgPosY_2);
		//    ofPushStyle();
		//    ofSetColor(255, 0, 0, 50);
		//    ofDrawRectangle(marginW + imgPosX_1 + squarePos.x, marginH + squarePos.y, squareW, squareH);
		//    ofPopStyle();
		// *********

		if (activePostazione == 0) {
			marginDraw = ofPoint(imgPosX_1, 0);
			marginPost2[0] = ofPoint(0, 10);
			marginPost2[1] = ofPoint(5, 10);
			marginPost2[2] = ofPoint(5, 10);
			marginPost2[3] = ofPoint(5, 0);
		}
		else if (activePostazione == 1) {
			marginDraw = ofPoint(imgPosX_2, -25);
			marginPost2[0] = ofPoint(20, -15);
			marginPost2[1] = ofPoint(-30, -10);
			marginPost2[2] = ofPoint(-30, 15);
			marginPost2[3] = ofPoint(-30, 35);
		}
		else if (activePostazione == 2) {
			marginDraw = ofPoint(imgPosX_3, 0);
			marginPost2[0] = ofPoint(0, 10);
			marginPost2[1] = ofPoint(5, 0);
			marginPost2[2] = ofPoint(5, 0);
			marginPost2[3] = ofPoint(5, 0);
		}

		// QUESTION
		ofPushStyle();
		ofSetColor(228, 52, 45, 255);
		ofPoint drawPos;
        float totalHeight = 0;
		for (int i = 0; i < nStringActiveLines[activePostazione][activeQuestion]; i++) {
			totalHeight += questionGUI.stringHeight(questionString[i][activePostazione][activeQuestion])*1.3;
		}
		for (int i = 0; i < nStringActiveLines[activePostazione][activeQuestion]; i++) {
			drawPos.x = (marginDraw.x + marginW + squarePos.x + squareW / 2)*indexW - questionGUI.stringWidth(questionString[i][activePostazione][activeQuestion]) / 2 + (marginPost2[0].x)*indexW;
			drawPos.y = (marginDraw.y + marginH + squarePos.y + squareH / 2)*indexW - totalHeight / 3 + i*totalHeight / nStringActiveLines[activePostazione][activeQuestion] + marginPost2[0].y*indexW;
			drawPos.x = drawPos.x;
			drawPos.y = drawPos.y;
            questionGUI.drawString(questionString[i][activePostazione][activeQuestion],
                                   (int)drawPos.x,
                                   (int)drawPos.y);
		}
		ofPopStyle();

		// ANSWERS
		ofPushStyle();
		ofSetColor(0, 0, 0, 255);
		// - a
		totalHeight = 0;
		for (int i = 0; i < ansA_nStringActiveLines[activePostazione][activeQuestion]; i++) {
			totalHeight += answerGUI.stringHeight(answerStringA[i][activePostazione][activeQuestion])*1.2;
		}
		drawPos.x = marginDraw.x + marginW + marginW_a + marginPost2[1].x;
		drawPos.x = drawPos.x*indexW;
		for (int i = 0; i < ansA_nStringActiveLines[activePostazione][activeQuestion]; i++) {
			drawPos.y = (marginDraw.y + marginH + marginH_a + 10)*indexW - totalHeight / 3 + i*totalHeight / ansA_nStringActiveLines[activePostazione][activeQuestion] + marginPost2[1].y*indexW;
			answerGUI.drawString(answerStringA[i][activePostazione][activeQuestion],
                                 int(drawPos.x),
                                 int(drawPos.y));
		}
		// - b
		totalHeight = 0;
		for (int i = 0; i < ansB_nStringActiveLines[activePostazione][activeQuestion]; i++) {
			totalHeight += answerGUI.stringHeight(answerStringB[i][activePostazione][activeQuestion])*1.2;
		}
		drawPos.x = marginDraw.x + marginW + marginW_b + marginPost2[2].x;
		drawPos.x = drawPos.x*indexW;
		for (int i = 0; i < ansB_nStringActiveLines[activePostazione][activeQuestion]; i++) {
			drawPos.y = (marginDraw.y + marginH + marginH_b + 10)*indexW - totalHeight / 3 + i*totalHeight / ansB_nStringActiveLines[activePostazione][activeQuestion] + marginPost2[2].y*indexW;
			answerGUI.drawString(answerStringB[i][activePostazione][activeQuestion],
                                 int(drawPos.x),
                                 int(drawPos.y));
		}
		// - c
		totalHeight = 0;
		for (int i = 0; i < ansC_nStringActiveLines[activePostazione][activeQuestion]; i++) {
			totalHeight += answerGUI.stringHeight(answerStringC[i][activePostazione][activeQuestion])*1.2;
		}
		drawPos.x = marginDraw.x + marginW + marginW_c + marginPost2[3].x;
		drawPos.x = drawPos.x*indexW;
		for (int i = 0; i < ansC_nStringActiveLines[activePostazione][activeQuestion]; i++) {
			drawPos.y = (marginDraw.y + marginH + marginH_c + 10)*indexW - totalHeight / 3 + i*totalHeight / ansC_nStringActiveLines[activePostazione][activeQuestion] + marginPost2[3].y*indexW;
			answerGUI.drawString(answerStringC[i][activePostazione][activeQuestion],
                                 int(drawPos.x),
                                 int(drawPos.y));
		}
		ofPopStyle();

		drawQuestionCircles();

		drawFillInSigns(activePostazione, nFill);

		drawRightQuestion();

		ofPushStyle();
		ofSetColor(255, 255, 255, 255);
		editor.draw(0, 0, editor.getWidth()*indexW, editor.getHeight()*indexW);
		ofPopStyle();

		// drawSpecialChars();

	}
	else {
		postSave.draw(0, 0, postSave.getWidth()*indexW, postSave.getHeight()*indexW);
	}

	drawSaveButton();
}

void ofApp::setupSaveButton() {
	saveButtonW = 100;
	saveButtonH = 50;
	saveButtonPos = ofPoint(1920 - saveButtonW, 807 - saveButtonH);
	saveButtonIsPressed = false;
}

void ofApp::updateSaveButton(int x, int y, string state) {
	if (x > saveButtonPos.x*indexW &&
		x < (saveButtonPos.x + saveButtonW)*indexW &&
		y > saveButtonPos.y*indexW &&
		y < (saveButtonPos.y + saveButtonH)*indexW) {
		if (state == "pressed" && !saveButtonIsPressed) {
			saveButtonIsPressed = true;
		}
	}
}

bool ofApp::checkAllQuestions(){
    if(saveButtonCapado){
        for(int i=0; i<3; i++){
            for(int j=0; j<5; j++){
                if(!completedQuestion[i][j]){
                    return false;
                }
            }
        }
    }
    return true;
}

void ofApp::drawSaveButton() {
	if (editMode) {
        if(checkAllQuestions()){
            ofPushStyle();
            if (saveButtonIsPressed) {
                if (counterButtonPressed < 30) {
                    counterButtonPressed++;
                }
                else {
                    counterButtonPressed = 0;
                    saveButtonIsPressed = false;
                    saveImage();
                    saveXml();
                    editMode = false;
                }
                ofSetColor(0, 97, 150, 150);
            } else {
                ofSetColor(0, 97, 150, 255);
            }
            ofDrawRectangle(saveButtonPos.x*indexW, saveButtonPos.y*indexW, saveButtonW*indexW, saveButtonH*indexW);
            ofSetColor(200, 200, 200, 200);
            questionGUI.drawString("SAVE", saveButtonPos.x*indexW + 30 * indexW, saveButtonPos.y*indexW + 30 * indexW);
            ofPopStyle();
        } else {
            if(saveButtonIsPressed){
                saveButtonIsPressed = false;
            }
        }
	}
	else {
		ofPushStyle();
		if (saveButtonIsPressed) {
			if (counterButtonPressed < 60) {
				counterButtonPressed++;
			}
			else {
				counterButtonPressed = 0;
				saveButtonIsPressed = false;
				editMode = true;
			}
			ofSetColor(100, 100, 100, 200);
		}
		else {
			ofSetColor(200, 200, 200, 200);
		}
		ofDrawRectangle(saveButtonPos.x*indexW, saveButtonPos.y*indexW, saveButtonW*indexW, saveButtonH*indexW);
		ofSetColor(0, 97, 150, 255);
		questionGUI.drawString("EDIT", saveButtonPos.x*indexW + 30 * indexW, saveButtonPos.y*indexW + 30 * indexW);
		ofPopStyle();
	}
}

void ofApp::saveImage() {
	// Delete existing images in relevant folders
	for (int i = 0; i < 2; i++) {
		string delFilesPath;
        if(isWindows){
            delFilesPath = "_OUTPUT_\\media\\imagenFija\\";
        } else {
            delFilesPath = "_OUTPUT_/media/imagenFija/";
        }
		
		if (i == 0) {
            if(isWindows){
                delFilesPath += "preguntas\\";
            } else {
                delFilesPath += "preguntas/";
            }
		}
		else if (i == 1) {
            if(isWindows){
                delFilesPath += "respuestas\\";
            } else {
                delFilesPath += "respuestas/";
            }
		}
		for (int j = 0; j < 3; j++) {
			string posta;
            if(isWindows){
                posta = "postazione_" + ofToString(j + 1) + "\\";
            } else {
                posta = "postazione_" + ofToString(j + 1) + "/";
            }
			if (i == 0) {
				ofDirectory dir;
				while (dir.listDir(delFilesPath + posta) > 0) {
					ofFile file;
					dir.listDir(delFilesPath + posta);
					file.removeFile(dir.getPath(0));
				}
			}
			else if (i == 1) {
				for (int k = 0; k < 5; k++) {
					string suffix;
                    if(isWindows){
                        suffix = "question_" + ofToString(k + 1) + "\\";
                    } else {
                        suffix = "question_" + ofToString(k + 1) + "/";
                                            }
					ofDirectory dir;
					while (dir.listDir(delFilesPath + posta + suffix) > 0) {
						ofFile file;
						dir.listDir(delFilesPath + posta + suffix);
						file.removeFile(dir.getPath(0));
					}
				}
			}
		}
	}

	// Save new images
	ofPoint correctSaveP2[4];
	int correctIconP2;
	for (int j = 0; j < 3; j++) {
		if (j == 0 || j == 2) {
			correctSaveP2[0] = ofPoint(0, 0);
			correctSaveP2[1] = ofPoint(-5, 0);
			correctSaveP2[2] = ofPoint(-5, 0);
			correctSaveP2[3] = ofPoint(-5, 0);
			correctIconP2 = 0;
		}
		else if (j == 1) {
			correctSaveP2[0] = ofPoint(10, -55);
			correctSaveP2[1] = ofPoint(-10, -45);
			correctSaveP2[2] = ofPoint(-10, -20);
			correctSaveP2[3] = ofPoint(-10, 0);
			correctIconP2 = 20;
		}
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 4; i++) {
				ofFbo compose;
				ofPixels pixels;
				if (j == 0 || j == 2) {
					compose.allocate(500*saveResRatio, 768*saveResRatio, GL_RGBA, 64);
                    compose.begin();
                    ofClear(255, 0);
                    compose.end();
					pixels.allocate(500*saveResRatio, 768*saveResRatio, OF_IMAGE_COLOR_ALPHA);
				}
				else if (j == 1) {
					compose.allocate(620*saveResRatio, 768*saveResRatio, GL_RGBA, 64);
					pixels.allocate(620*saveResRatio, 768*saveResRatio, OF_IMAGE_COLOR_ALPHA);
				}

				pixels.clear();

				compose.begin();
				ofClear(255, 0);
				ofSetColor(255, 255, 255, 255);
				// BACKGROUND
				if (j == 0 || j == 2) {
					sandwich_13.draw(0, 0, sandwich_13.getWidth()*saveResRatio, sandwich_13.getHeight()*saveResRatio);
				}
				else if (j == 1) {
					sandwich_2.draw(0, 0, sandwich_2.getWidth()*saveResRatio, sandwich_2.getHeight()*saveResRatio);
				}

				// QUESTION
				ofPushStyle();
				ofSetColor(228, 52, 45, 255);
				ofPoint drawPos;
				float totalHeight = 0;
				for (int line = 0; line < nStringActiveLines[j][k]; line++) {
					totalHeight += question.stringHeight(questionString[line][j][k])*1.4;
				}
				for (int line = 0; line < nStringActiveLines[j][k]; line++) {
                    float fixX = (marginW + squarePos.x + squareW / 2 + marginPost2[0].x + correctSaveP2[0].x) * saveResRatio;
                    float fixY = (marginH + squarePos.y + squareH / 2 + marginPost2[0].y + 20 + correctSaveP2[0].y) * saveResRatio;
					drawPos.x = fixX - question.stringWidth(questionString[line][j][k])/2;
					drawPos.y = fixY - totalHeight/3 + line*totalHeight/nStringActiveLines[j][k];
					question.drawString(questionString[line][j][k],
                                        int(drawPos.x),
                                        int(drawPos.y));
				}
				ofPopStyle();

				// ANSWERS
				ofPushStyle();
				ofSetColor(255, 255, 255, 255);
				// ANSWER - A
				totalHeight = 0;
				for (int line = 0; line < ansA_nStringActiveLines[j][k]; line++) {
					totalHeight += answer.stringHeight(answerStringA[line][j][k])*1.4;
				}
				drawPos.x = (marginW + marginW_a + marginPost2[1].x + 20 + correctSaveP2[1].x) * saveResRatio;
				for (int line = 0; line < ansA_nStringActiveLines[j][k]; line++) {
                    float fixY = (marginH + marginH_a + 10 + marginPost2[1].y + 20 + correctSaveP2[1].y + 5) * saveResRatio;
					drawPos.y = fixY - totalHeight/3 + line*totalHeight/ansA_nStringActiveLines[j][k];
					answer.drawString(answerStringA[line][j][k],
                                      int(drawPos.x),
                                      int(drawPos.y));
				}
				// ANSWER - B
				totalHeight = 0;
				for (int line = 0; line < ansB_nStringActiveLines[j][k]; line++) {
					totalHeight += answer.stringHeight(answerStringB[line][j][k])*1.4;
				}
				drawPos.x = (marginW + marginW_b + marginPost2[2].x + 20 + correctSaveP2[2].x) * saveResRatio;
				for (int line = 0; line < ansB_nStringActiveLines[j][k]; line++) {
                    float fixY = (marginH + marginH_b + 10 + marginPost2[2].y + 20 + correctSaveP2[2].y + 5) * saveResRatio;
					drawPos.y = fixY - totalHeight/3 + line*totalHeight/ansB_nStringActiveLines[j][k];
					answer.drawString(answerStringB[line][j][k],
                                      int(drawPos.x),
                                      int(drawPos.y));
				}
				// ANSWER - C
				totalHeight = 0;
				for (int line = 0; line < ansC_nStringActiveLines[j][k]; line++) {
					totalHeight += answer.stringHeight(answerStringC[line][j][k])*1.4;
				}
				drawPos.x = (marginW + marginW_c + marginPost2[3].x + 20 + correctSaveP2[3].x) * saveResRatio;
				for (int line = 0; line < ansC_nStringActiveLines[j][k]; line++) {
                    float fixY = (marginH + marginH_c + 10 + marginPost2[3].y + 20 + correctSaveP2[3].y + 5) * saveResRatio;
					drawPos.y = fixY - totalHeight/3 + line*totalHeight/ansC_nStringActiveLines[j][k] ;
					answer.drawString(answerStringC[line][j][k],
                                      int(drawPos.x),
                                      int(drawPos.y));
				}

				ofPoint correctFinal;
				if (j == 0) {
					correctFinal = ofPoint(10, 0);
				}
				else if (j == 1) {
					correctFinal = ofPoint(-5, 12);
				}
				else if (j == 2) {
					correctFinal = ofPoint(3, 0);
				}

				// ICONS
				if (i > 0) {
					if (i == nRight[j][k] + 1) {
						ofSetColor(255, 255, 255, 255);
						if (j == 1) {
							right.draw((rightPos[i - 1].x + correctPost2[1][i - 1].x + correctFinal.x) * saveResRatio,
                                       (rightPos[i - 1].y + correctPost2[1][i - 1].y + 20 - 11 + correctFinal.y) * saveResRatio,
                                       rwIconSize * saveResRatio,
                                       rwIconSize * saveResRatio);
						}
						else {
							right.draw((rightPos[i - 1].x + correctFinal.x) * saveResRatio,
                                       (rightPos[i - 1].y + 20 + correctFinal.y) * saveResRatio,
                                       rwIconSize * saveResRatio,
                                       rwIconSize * saveResRatio);
						}
					}
					else {
						ofSetColor(255, 255, 255, 255);
						if (j == 1) {
							wrong.draw((rightPos[i - 1].x + correctPost2[1][i - 1].x + correctFinal.x) * saveResRatio,
                                       (rightPos[i - 1].y + correctPost2[1][i - 1].y + 20 - 11 + correctFinal.y) * saveResRatio,
                                       rwIconSize * saveResRatio,
                                       rwIconSize * saveResRatio);
						}
						else {
							wrong.draw((rightPos[i - 1].x + correctFinal.x) * saveResRatio,
                                       (rightPos[i - 1].y + 20 + correctFinal.y) * saveResRatio,
                                       rwIconSize * saveResRatio,
                                       rwIconSize * saveResRatio);
						}
					}
					ofSetColor(255, 255, 255, 255);
					if (j == 1) {
						selected.draw((selectedPos[i - 1].x + correctPost2[0][i - 1].x + correctIconP2 + 9 + correctFinal.x) * saveResRatio,
                                      (selectedPos[i - 1].y + correctPost2[0][i - 1].y + 20 - 11 + correctFinal.y) * saveResRatio,
                                      selectedIconSize * saveResRatio,
                                      selectedIconSize * saveResRatio);
					}
					else {
						selected.draw((selectedPos[i - 1].x + correctFinal.x) * saveResRatio,
                                      (selectedPos[i - 1].y + 20 + correctFinal.y) * saveResRatio,
                                      selectedIconSize * saveResRatio,
                                      selectedIconSize * saveResRatio);
					}
				}
				ofPopStyle();
				compose.end();

				compose.readToPixels(pixels);

				string path;
                if(isWindows){
                    path = "_OUTPUT_\\media\\imagenFija\\";
                } else {
                    path = "_OUTPUT_/media/imagenFija/";
                }
				if (i == 0) {
                    if(isWindows){
                        path += "preguntas\\";
                    } else {
                        path += "preguntas/";
                    }
				}
                else {
                    if(isWindows){
                        path += "respuestas\\";
                    } else {
                        path += "respuestas/";
                    }
				}
                if(isWindows){
                    path += "postazione_" + ofToString(j + 1) + "\\";
                } else {
                    path += "postazione_" + ofToString(j + 1) + "/";
                }
				if (i == 0) {
					path += "Q" + ofToString(k + 1) + "_0.png";
				}
				else {
					string letter;
					string yesOrNo;
					if (i == 1) {
						letter = "A";
					}
					else if (i == 2) {
						letter = "B";
					}
					else if (i == 3) {
						letter = "C";
					}
					if (nRight[j][k] == i - 1) {
						yesOrNo = "_SI";
					}
					else {
						yesOrNo = "_NO";
					}
					if (answerStringC[0][j][k].length() == 0 
						&& i==3) {
						yesOrNo = "";
					}
                    if(isWindows){
                        path += "question_" + ofToString(k + 1) + "\\";
                    } else {
                        path += "question_" + ofToString(k + 1) + "/";
                    }
					path += "Q" + ofToString(k + 1) + "_" + letter + yesOrNo + ".png";
				}
				ofSaveImage(pixels, path, OF_IMAGE_QUALITY_BEST);
			}
		}
	}
}

void ofApp::setupPositions() {
	// Posición para imágenes sandwich sobre panel
	imgPosX_1 = 300;
	imgPosY_1 = -20;
	imgPosX_2 = 800;
	imgPosY_2 = -10;
	imgPosX_3 = 1350;
	imgPosY_3 = -20;

	// Posiciones para el texto Q y A
	marginW = 194;
	marginH = 194;
	marginW_a = 36;
	marginH_a = 90;
	marginW_b = 36;
	marginH_b = 158;
	marginW_c = 36;
	marginH_c = 227;
}

void ofApp::setupQuestionCircles() {
	ofPoint pos;
	pos.x = marginW + imgPosX_1;
	pos.y = 750;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			circlePos[i][j].x = pos.x;
			circlePos[i][j].y = pos.y;
			pos.x += 30;
		}
		pos.x += 400;
	}
}

void ofApp::inputQuestionCircles(int x, int y) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (ofDist(circlePos[i][j].x*indexW, circlePos[i][j].y*indexW, x, y) < 15 * indexW) {
				nFill = 0;
				activeQuestion = j;
				activePostazione = i;
				break;
			}
		}
	}
}

void ofApp::updateQuestionCircles() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (questionString[0][i][j].length() > 0
				&& answerStringA[0][i][j].length() > 0
				&& answerStringB[0][i][j].length() > 0) {
				if (nRight[i][j] != 2 || answerStringC[0][i][j].length() > 0) {
					completedQuestion[i][j] = true;
				}
				else {
					completedQuestion[i][j] = false;
				}
			}
			else {
				completedQuestion[i][j] = false;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::drawQuestionCircles() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			ofPushStyle();
			if (i == activePostazione && j == activeQuestion) {
				if (completedQuestion[i][j]) {
					ofSetColor(0, 155, 0, 255);
				}
				else {
					ofSetColor(155, 0, 0, 255);
				}
			}
			else {
				if (completedQuestion[i][j]) {
					ofSetColor(0, 155, 0, 100);
				}
				else {
					ofSetColor(155, 0, 0, 100);
				}
			}
			answerGUI.drawString("Q" + ofToString(j + 1), circlePos[i][j].x*indexW - 10 * indexW, circlePos[i][j].y*indexW - 20 * indexW);
			ofDrawCircle(circlePos[i][j].x*indexW, circlePos[i][j].y*indexW, 15 * indexW);
			ofPopStyle();
		}
	}
}

void ofApp::updateFillInSigns(int x, int y) {
	if (ofDist(fillInPos.x*indexW, fillInPos.y*indexW, x, y) < 10) {
		if (nFill < 3) {
			nFill++;
		}
		else {
			nFill = 0;
		}
	}
}

void ofApp::drawFillInSigns(int nPostazione, int nFill) {
	int marginFill;
	int correctPost2_X;
	int correctPost2_Y[4];
	ofPushStyle();
	ofSetColor(0, 150, 0, 150);
	if (nPostazione == 0) {
		marginFill = imgPosX_1;
		correctPost2_X = 0;
		correctPost2_Y[0] = 0;
		correctPost2_Y[1] = 10;
		correctPost2_Y[2] = 10;
		correctPost2_Y[3] = 10;
	}
	else if (nPostazione == 1) {
		marginFill = imgPosX_2;
		correctPost2_X = -30;
		correctPost2_Y[0] = -10;
		correctPost2_Y[1] = -30;
		correctPost2_Y[2] = -5;
		correctPost2_Y[3] = 20;
	}
	else if (nPostazione == 2) {
		marginFill = imgPosX_3;
		correctPost2_X = 0;
		correctPost2_Y[0] = 0;
		correctPost2_Y[1] = 10;
		correctPost2_Y[2] = 10;
		correctPost2_Y[3] = 10;
	}
	if (nFill == 0) {
		fillInPos.x = marginFill + marginW - 40 + correctPost2_X;
		fillInPos.y = marginH + correctPost2_Y[nFill];
	}
	else if (nFill == 1) {
		fillInPos.x = marginFill + marginW + marginW_a - 75 + correctPost2_X;
		fillInPos.y = marginH + marginH_a + correctPost2_Y[nFill];
	}
	else if (nFill == 2) {
		fillInPos.x = marginFill + marginW + marginW_b - 75 + correctPost2_X;
		fillInPos.y = marginH + marginH_b + correctPost2_Y[nFill];
	}
	else if (nFill == 3) {
		fillInPos.x = marginFill + marginW + marginW_c - 75 + correctPost2_X;
		fillInPos.y = marginH + marginH_c + correctPost2_Y[nFill];
	}
	ofDrawCircle(fillInPos.x*indexW, fillInPos.y*indexW, 10);
	ofPopStyle();
}

void ofApp::setupRightQuestion() {
	right.load("icons/right.png");
	wrong.load("icons/wrong.png");
	selected.load("icons/selected.png");
	selectedPos[0] = ofPoint(marginW + marginW_a - 51, marginH + marginH_a - 8);
	selectedPos[1] = ofPoint(marginW + marginW_b - 51, marginH + marginH_b - 10);
	selectedPos[2] = ofPoint(marginW + marginW_c - 51, marginH + marginH_c - 14);
	rightPos[0] = ofPoint(marginW + marginW_a + 165, marginH + marginH_a - 6);
	rightPos[1] = ofPoint(marginW + marginW_b + 150, marginH + marginH_b - 8);
	rightPos[2] = ofPoint(marginW + marginW_c + 125, marginH + marginH_c - 12);
	correctPost2[0][0] = ofPoint(-36, -45);
	correctPost2[0][1] = ofPoint(-36, -20);
	correctPost2[0][2] = ofPoint(-36, 10);
	correctPost2[1][0] = ofPoint(75, -45);
	correctPost2[1][1] = ofPoint(90, -20);
	correctPost2[1][2] = ofPoint(90, 10);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			nRight[i][j] = 0;
		}
	}
	selectedIconSize = 50;
	rwIconSize = 40;
}

void ofApp::updateRightQuestion(int x, int y) {
	for (int i = 0; i < 3; i++) {
		if (activePostazione != 1) {
			if (x > (selectedPos[i].x + marginRightQuestion)*indexW  && 
				x < (selectedPos[i].x + marginRightQuestion + 60)*indexW &&
				y > (selectedPos[i].y)*indexW &&
				y < (selectedPos[i].y + 60)*indexW) {
				nRight[activePostazione][activeQuestion] = i;
				break;
			}
		}
		else {
			if (x > (selectedPos[i].x + marginRightQuestion + correctPost2[0][i].x)*indexW &&
				x < (selectedPos[i].x + marginRightQuestion + correctPost2[0][i].x + 60)*indexW &&
				y > (selectedPos[i].y + correctPost2[0][i].y)*indexW &&
				y < (selectedPos[i].y + correctPost2[0][i].y + 60)*indexW) {
				nRight[activePostazione][activeQuestion] = i;
				break;
			}
		}
	}
}

void ofApp::drawRightQuestion() {
	if (activePostazione == 0) {
		marginRightQuestion = imgPosX_1;
	}
	else if (activePostazione == 1) {
		marginRightQuestion = imgPosX_2;
	}
	else if (activePostazione == 2) {
		marginRightQuestion = imgPosX_3;
	}
	ofPushStyle();
	for (int i = 0; i < 3; i++) {
		ofSetColor(255, 255, 255, 255);
		if (i == nRight[activePostazione][activeQuestion]) {
			if (activePostazione == 1) {
				right.draw((marginRightQuestion + rightPos[i].x + correctPost2[1][i].x)*indexW, 
					(rightPos[i].y + correctPost2[1][i].y)*indexW, 
					rwIconSize*indexW,
					rwIconSize*indexW);
			}
			else {
				right.draw((marginRightQuestion + rightPos[i].x)*indexW,
					rightPos[i].y*indexW,
					rwIconSize*indexW,
					rwIconSize*indexW);
			}
			ofSetColor(255, 255, 255, 200);
		}
		else {
			ofSetColor(255, 255, 255, 200);
			if (activePostazione == 1) {
				wrong.draw((marginRightQuestion + rightPos[i].x + correctPost2[1][i].x)*indexW,
					(rightPos[i].y + correctPost2[1][i].y)*indexW,
					rwIconSize*indexW,
					rwIconSize*indexW);
			}
			else {
				wrong.draw((marginRightQuestion + rightPos[i].x)*indexW,
					rightPos[i].y*indexW,
					rwIconSize*indexW,
					rwIconSize*indexW);
			}
			ofSetColor(255, 255, 255, 100);
		}
		if (activePostazione == 1) {
			selected.draw((marginRightQuestion + selectedPos[i].x + correctPost2[0][i].x)*indexW,
				(selectedPos[i].y + correctPost2[0][i].y)*indexW,
				selectedIconSize*indexW,
				selectedIconSize*indexW);
		}
		else {
			selected.draw((marginRightQuestion + selectedPos[i].x)*indexW,
				selectedPos[i].y*indexW,
				selectedIconSize*indexW,
				selectedIconSize*indexW);
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (editMode) {
		if (fillInSignsActive) {
			if (nFill == 0) {
				if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
					questionString[nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] = questionString[nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].substr(0, questionString[nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() - 1);
					if (questionString[nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() == 0) {
						if (nStringLine[activePostazione][activeQuestion] > 0) {
							nStringLine[activePostazione][activeQuestion]--;
							nStringActiveLines[activePostazione][activeQuestion]--;
						}
					}
				}
				else if (key == OF_KEY_RETURN) {
					if (nStringLine[activePostazione][activeQuestion] < 2) {
						nStringLine[activePostazione][activeQuestion]++;
						nStringActiveLines[activePostazione][activeQuestion]++;
					}
				}
				else if (key == 2304 || key == 2305 || key == 2306 || key == 186 || key == 768 || key == 769 ||
					key == 180 || key == 231 || key == 1280 || key == 1281 || key == 1282 || key == 4352 || 
					key == 4353 || key == 356 || key == 357 || key == 358 || key == 359) {

				}
				else {
					if (bFirst) {
						typeStr.clear();
						bFirst = false;
					}
					ofAppendUTF8(questionString[nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion], key);
				}
			}
			else if (nFill == 1) {
				if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
					answerStringA[ansA_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] = answerStringA[ansA_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].substr(0, answerStringA[ansA_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() - 1);
					if (answerStringA[ansA_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() == 0) {
						if (ansA_nStringLine[activePostazione][activeQuestion] > 0) {
							ansA_nStringLine[activePostazione][activeQuestion]--;
							ansA_nStringActiveLines[activePostazione][activeQuestion]--;
						}
					}
				}
				else if (key == OF_KEY_RETURN) {
					if (ansA_nStringLine[activePostazione][activeQuestion] < 4) {
						ansA_nStringLine[activePostazione][activeQuestion]++;
						ansA_nStringActiveLines[activePostazione][activeQuestion]++;
					}
				}
				else if (key == 2304 || key == 2305 || key == 2306 || key == 186 || key == 768 || key == 769 ||
					key == 180 || key == 231 || key == 1280 || key == 1281 || key == 1282 || key == 4352 ||
					key == 4353 || key == 356 || key == 357 || key == 358 || key == 359) {

				}
				else {
					if (bFirst) {
						typeStr.clear();
						bFirst = false;
					}
					ofAppendUTF8(answerStringA[ansA_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion], key);
				}
			}
			else if (nFill == 2) {
				if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
					answerStringB[ansB_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] = answerStringB[ansB_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].substr(0, answerStringB[ansB_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() - 1);
					if (answerStringB[ansB_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() == 0) {
						if (ansB_nStringLine[activePostazione][activeQuestion] > 0) {
							ansB_nStringLine[activePostazione][activeQuestion]--;
							ansB_nStringActiveLines[activePostazione][activeQuestion]--;
						}
					}
				}
				else if (key == OF_KEY_RETURN) {
					if (ansB_nStringLine[activePostazione][activeQuestion] < 4) {
						ansB_nStringLine[activePostazione][activeQuestion]++;
						ansB_nStringActiveLines[activePostazione][activeQuestion]++;
					}
				}
				else if (key == 2304 || key == 2305 || key == 2306 || key == 186 || key == 768 || key == 769 ||
					key == 180 || key == 231 || key == 1280 || key == 1281 || key == 1282 || key == 4352 ||
					key == 4353 || key == 356 || key == 357 || key == 358 || key == 359) {

				}
				else {
					if (bFirst) {
						typeStr.clear();
						bFirst = false;
					}
					ofAppendUTF8(answerStringB[ansB_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion], key);
				}
			}
			else if (nFill == 3) {
				if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
					answerStringC[ansC_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion] = answerStringC[ansC_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].substr(0, answerStringC[ansC_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() - 1);
					if (answerStringC[ansC_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion].length() == 0) {
						if (ansC_nStringLine[activePostazione][activeQuestion] > 0) {
							ansC_nStringLine[activePostazione][activeQuestion]--;
							ansC_nStringActiveLines[activePostazione][activeQuestion]--;
						}
					}
				}
				else if (key == OF_KEY_RETURN) {
					if (ansC_nStringLine[activePostazione][activeQuestion] < 4) {
						ansC_nStringLine[activePostazione][activeQuestion]++;
						ansC_nStringActiveLines[activePostazione][activeQuestion]++;
					}
				}
				else if (key == 2304 || key == 2305 || key == 2306 || key == 186 || key == 768 || key == 769 ||
					key == 180 || key == 231 || key == 1280 || key == 1281 || key == 1282 || key == 4352 ||
					key == 4353 || key == 356 || key == 357 || key == 358 || key == 359) {

				}
				else {
					if (bFirst) {
						typeStr.clear();
						bFirst = false;
					}
					ofAppendUTF8(answerStringC[ansC_nStringLine[activePostazione][activeQuestion]][activePostazione][activeQuestion], key);
				}
			}
		}
	}
}

void ofApp::saveXml() {
	ofXml gameSettings;
	string correctAnswer;
	int nPossibleAnswers;

	// Game Settings
	gameSettings.addChild("gameSettings");
	gameSettings.setTo("gameSettings");
	gameSettings.addValue("guiActive", "NO");
	gameSettings.addValue("showRemainingTime", "NO");
	gameSettings.addValue("sequenceFPS", "18");
	gameSettings.addValue("maxAnswerTime", "15");
	gameSettings.addValue("lastSecondsTime", "5");
	gameSettings.addValue("toNextQuestionTime", "5");
	gameSettings.addValue("pointsTime", "10");
	gameSettings.addValue("pointsToPass", "60");

	// Postazione 1
	gameSettings.addChild("postazione1");
	gameSettings.setTo("postazione1");
	// P1 - Q1
	if (nRight[0][0] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[0][0] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[0][0] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][0][0].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question1");
	gameSettings.setTo("question1");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P1 - Q2
	if (nRight[0][1] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[0][1] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[0][1] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][0][1].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question2");
	gameSettings.setTo("question2");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P1 - Q3
	if (nRight[0][2] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[0][2] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[0][2] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][0][2].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question3");
	gameSettings.setTo("question3");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P1 - Q4
	if (nRight[0][3] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[0][3] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[0][3] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][0][3].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question4");
	gameSettings.setTo("question4");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P1 - Q5
	if (nRight[0][4] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[0][4] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[0][4] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][0][4].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question5");
	gameSettings.setTo("question5");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	gameSettings.setTo("../");

	// Postazione 2
	gameSettings.addChild("postazione2");
	gameSettings.setTo("postazione2");
	// P2 - Q1
	if (nRight[1][0] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[1][0] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[1][0] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][1][0].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question1");
	gameSettings.setTo("question1");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P2 - Q2
	if (nRight[1][1] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[1][1] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[1][1] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][1][1].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question2");
	gameSettings.setTo("question2");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P2 - Q3
	if (nRight[1][2] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[1][2] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[1][2] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][1][2].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question3");
	gameSettings.setTo("question3");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P2 - Q4
	if (nRight[1][3] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[1][3] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[1][3] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][1][3].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question4");
	gameSettings.setTo("question4");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P2 - Q5
	if (nRight[1][4] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[1][4] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[1][4] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][1][4].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question5");
	gameSettings.setTo("question5");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	gameSettings.setTo("../");

	// Postazione 3
	gameSettings.addChild("postazione3");
	gameSettings.setTo("postazione3");
	// P3 - Q1
	if (nRight[2][0] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[2][0] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[2][0] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][2][0].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question1");
	gameSettings.setTo("question1");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P3 - Q2
	if (nRight[2][1] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[2][1] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[2][1] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][2][1].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question2");
	gameSettings.setTo("question2");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P3 - Q3
	if (nRight[2][2] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[2][2] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[2][2] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][2][2].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question3");
	gameSettings.setTo("question3");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P3 - Q4
	if (nRight[2][3] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[2][3] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[2][3] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][2][3].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question4");
	gameSettings.setTo("question4");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);
	gameSettings.setTo("../");
	// P3 - Q5
	if (nRight[2][4] == 0) {
		correctAnswer = "A";
	}
	else if (nRight[2][4] == 1) {
		correctAnswer = "B";
	}
	else if (nRight[2][4] == 2) {
		correctAnswer = "C";
	}
	if (answerStringC[0][2][4].length() == 0) {
		nPossibleAnswers = 2;
	}
	else {
		nPossibleAnswers = 3;
	}
	gameSettings.addChild("question5");
	gameSettings.setTo("question5");
	gameSettings.addValue("correctAnswer", correctAnswer);
	gameSettings.addValue("numPossibleAnswers", nPossibleAnswers);

	gameSettings.save("_OUTPUT_/xmlSettings/gameSettings.xml");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (editMode) {
		updateFillInSigns(x, y);
		updateRightQuestion(x, y);
		inputQuestionCircles(x, y);
		updateSpecialChars(x, y);
	}
	updateSaveButton(x, y, "pressed");
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	updateSaveButton(x, y, "released");
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}