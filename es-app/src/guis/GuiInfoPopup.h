//
// Created by xizor on 30/03/18.
//

#pragma once

#include "GuiComponent.h"
#include "components/NinePatchComponent.h"
#include "components/ComponentGrid.h"
#include "Window.h"
#include "Log.h"



class GuiInfoPopup : public GuiComponent, public Window::InfoPopup
{
public:
	GuiInfoPopup(Window* window, std::string message, int duration, std::string icon);
	GuiInfoPopup(Window* window, std::string message, int duration);
	~GuiInfoPopup();
	void render(const Eigen::Affine3f& parentTrans) override;
	inline void stop() { running = false; };
private:
	std::string mMessage;
	int mDuration;
	int alpha;
	unsigned int maxAlpha;
	unsigned int mFrameColor;
	bool updateState();
	int mStartTime;
	ComponentGrid* mGrid;
	NinePatchComponent* mFrame;
	bool running;
};