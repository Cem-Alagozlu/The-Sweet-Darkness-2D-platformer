#pragma once
#include "Texture.h"
#include "MenuMain.h"


class MenuQuit
{
public:
	MenuQuit(MenuManager& manager);
	MenuQuit(const MenuQuit&) = delete;
	MenuQuit& operator=(const MenuQuit&) = delete;
	~MenuQuit() = default;

	void Draw() const;

	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e) const;

private:

	Point2f m_MousePos;

	MenuManager& m_Manager;
	std::vector<std::unique_ptr<Texture>> m_pMenuQuitText;
};
