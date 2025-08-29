#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
	#ifdef UI_EXPANSIONS_EXPORTING
		#define UI_EXPANSIONS_DLL __declspec(dllexport)
	#else
		#define UI_EXPANSIONS_DLL __declspec(dllimport)
	#endif
#else
	#define UI_EXPANSIONS_DLL __attribute__((visibility("default")))
#endif

class UI_EXPANSIONS_DLL DropdownMenu : public CCLayer {

public:
	/// Create the dropdown menu.
	/// @param options - The selectable options
	/// @param defaultElement - Index of the default-selected element. -1 for none.
	/// @param defaultText - The text that gets shown if no option is selected. Only visible if defaultElement is -1
	/// @param width - The width of the menu
	/// @param height - The height of the list menu when extended
	/// @param bgTexture - The texture of the menu, has to be a CCScale9Sprite
	/// @param bgColor - The color of the menu, tints the bgTexture
	/// @returns The created DropdownMenu
	static DropdownMenu* create(const std::vector<std::string>& options, int defaultElement = -1, const char* defaultText = "Select...", float width = 150, float height = 150, const char* bgTexture = "GJ_square01.png", ccColor3B bgColor = ccc3(255, 255, 255));

	/// Create the dropdown menu.
	/// @param options - The selectable options
	/// @param defaultElements - Index of the default-selected elements. Empty for none.
	/// @param defaultText - The text that gets shown if no option is selected. Only visible if defaultElement is -1
	/// @param width - The width of the menu
	/// @param height - The height of the list menu when extended
	/// @param bgTexture - The texture of the menu, has to be a CCScale9Sprite
	/// @param bgColor - The color of the menu, tints the bgTexture
	/// @returns The created DropdownMenu
	static DropdownMenu* create(const std::vector<std::string>& options, const std::vector<int>& defaultElements = {}, const char* defaultText = "Select...", float width = 150, float height = 150, const char* bgTexture = "GJ_square01.png", ccColor3B bgColor = ccc3(255, 255, 255));

	/// Expands or shrinks the menu, depending on if it is currently expanded or not.
	void onExpand(CCObject* sender);

	/// Gets called when an option is selected, also calls the callback if one exists.
	void onSelect(CCObject* sender);

	/// Sets a callback that gets called when an option is selected. Function parameters are the option index and option text.
	/// There are some default callbacks, like highlighting the option background and replacing the menu text, which you can disable with m_disableDefaultCallbacks.
	void setCallback(std::function<void(int, std::string const&)> cb);

	/// Whether the menu is currently expanded or not
	bool m_isExpanded = false;

	/// Provided options inside the menu list
	std::vector<std::string> m_options;

	/// Width of both the main and list menu
	float m_width;

	/// Height of the expanded list view, not including the main menu
	float m_height;

	/// Background texture of both the main and list menu
	const char* m_bgTexture;

	/// Background color of both the main and list menu
	ccColor3B m_bgColor;

	/// Index of the currently selected object. -1 if none, defaultElement on first init.
	std::vector<int> m_selected;

	/// The callback function
	std::function<void(int, std::string const&)> m_callback;

	/// The text at the top menu, defaultText if no element is selected
	CCLabelBMFont* m_menuText = nullptr;

	/// The scroll layer inside the menu list
	ScrollLayer* m_scrollLayer = nullptr;

	/// Gap between the main menu and the list, 20.0 by default
	float m_gap = 20;

	/// Background color of a selected element
	ccColor3B m_selectedColor = ccc3(255, 170, 85);

	/// Changes the height of the menu list to fit all elements exactly. Height value is ignored.
	bool m_growToFit = false;

	/// Disables the default callbacks on button presses, that change the color of the item background and square button, and sets the text at the main menu
	bool m_disableDefaultCallbacks = false;

	/// Hides the scrollbar, hidden if growToFit by default
	bool m_hideScrollbar = false;

	// The default text string
	const char* m_defaultText;

	// Whether to allow multiple options to be selected or not
	bool m_allowMultiSelect = false;

private:
	bool init(const std::vector<std::string>& options, const std::vector<int>& defaultElements, const char* defaultText, float width, float height, const char* bgTexture, ccColor3B bgColor);
	ScrollLayer* createScrollLayer(std::vector<std::string> options);
};