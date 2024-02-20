#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetCircleResolution(36);

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	vector<glm::vec3> location_list;
	for (int i = 0; i < 200; i++) {

		auto deg = ofRandom(255, 285);
		auto radius = int(ofRandom(720) + ofGetFrameNum() * ofRandom(8, 15)) % 720;
		auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), 250 + radius * sin(deg * DEG_TO_RAD), 0);
		location_list.push_back(location);
	}

	float radius_min = 8;
	ofColor color;
	for (int i = 0; i < location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(location_list[i]);
		ofRotateZ(20);

		color.setHsb(ofRandom(255), 255, 255);

		ofMesh mesh;
		float deg_span = 10;
		float radius_span = 3;
		float radius_max = radius_min * 3.5;
		for (float radius = radius_min; radius <= radius_max; radius += radius_span) {

			for (float deg = 0; deg < 360; deg += deg_span) {

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius + radius_span) * cos((deg + deg_span) * DEG_TO_RAD), (radius + radius_span) * sin((deg + deg_span) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD), 0));
				mesh.addVertices(vertices);

				for (int k = 0; k < vertices.size(); k++) {

					mesh.addColor(ofColor(color, ofMap(glm::length(vertices[k]), radius_min, radius_max + radius_span, 150, 0)));
				}

				mesh.addIndex(mesh.getNumVertices() - 4);
				mesh.addIndex(mesh.getNumVertices() - 3);
				mesh.addIndex(mesh.getNumVertices() - 2);

				mesh.addIndex(mesh.getNumVertices() - 4);
				mesh.addIndex(mesh.getNumVertices() - 1);
				mesh.addIndex(mesh.getNumVertices() - 2);
			}
		}

		mesh.draw();

		ofPopMatrix();
	}

	ofFill();
	for (int i = 0; i < location_list.size(); i++) {

		ofSetColor(255);
		ofDrawCircle(location_list[i], radius_min);
	}

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}