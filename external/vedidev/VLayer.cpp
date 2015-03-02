/*
 * VLayer.cpp
 *
 *  Created on: Sep 19, 2012
 *      Author: vedi
 */

#include "VLayer.h"

VLayer::VLayer() {
}

VLayer::~VLayer() {
}

void VLayer::cleanup() {
    this->setAnimationManager(NULL);
    this->setAnimationManagers(NULL);

    CCLayer::cleanup();
}

void VLayer::keyBackClicked() {
	onBack(NULL);
}

void VLayer::onEnter() {
	CCLayer::onEnter();
	this->setKeypadEnabled(true);
}
