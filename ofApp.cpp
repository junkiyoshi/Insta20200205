#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(300, 4);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		auto index = this->mesh.getNumVertices();
		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(glm::vec4(avg * 0.01, ofGetFrameNum() * 0.005));
		auto noise_radius = 0;
		
		if (noise_value >= 0 && noise_value < 0.55) {

			noise_radius = 200;
		}
		else if (noise_value >= 0.55 && noise_value < 0.6) {

			noise_radius = ofMap(noise_value, 0.55, 0.6, 200, 300);
		}
		else {

			noise_radius = 300;
		}

		mesh.addVertex(glm::normalize(triangle.getVertex(0)) * noise_radius);
		mesh.addVertex(glm::normalize(triangle.getVertex(1)) * noise_radius);
		mesh.addVertex(glm::normalize(triangle.getVertex(2)) * noise_radius);

		mesh.addIndex(index + 0); mesh.addIndex(index + 1); mesh.addIndex(index + 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	ofSetColor(239);
	this->mesh.draw();

	ofSetColor(39);
	this->mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}