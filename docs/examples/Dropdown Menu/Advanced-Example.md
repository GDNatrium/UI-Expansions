# Dropdown Menu Examples - Advanced Setup

For most usecases, you can use the default values for your popup. 

In this example we will create 3 different popups with increasing complexity.

- [Basic Setup](Basic-Example.md) - A dropdown menu that allows you to pick the color of a button.
- [Visuals Setup](Visuals-Example.md) - A visually customized dropdown menu that allows you to select a difficulty.
- **Advanced Setup** - A highly customized dropdown menu, which changes how callbacks work to allow for multiselection and visual changes.

## Setup
For all usecases, you first have to include the API as a dependency in your mod. You can do so by declaring it like this in your `mod.json` file.

```json
{
    "dependencies": [
        {
            "id": "natrium.ui_expansions",
            "version": "1.0.0"
        }
    ]
}
```

After doing so, you can include the DropdownMenu header.
```cpp
#include <natrium.ui_expansions/include/DropdownMenu.hpp>
```

## Example
In this example we disable default callbacks and set up our own ones to allow us to pick several elements from the list. We will also customize the menu visually.

This example is more advanced, and will put more focus on the custom callbacks instead of customization. For almost all usecases, you only need the [Basic Setup](Basic-Example.md) and the [Visuals Setup](Visuals-Example.md).

For this example, we create a very basic calculator, which adds up all selected numbers.

**Note:** I have removed some elements from MenuLayer, which is not included in the code example. This is not related to how the dropdown menu works, and is only a visual choice for the images.

```cpp
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include <natrium.ui_expansions/include/DropdownMenu.hpp> // Make sure to include this header!

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Window size for easier placement later.
        auto winSize = CCDirector::sharedDirector()->getWinSize();


        return true;
    }
};
```

Let's start by setting up our number options and passing them to the create function.

```cpp
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

        std::vector<std::string> digits = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

        auto dropdown = DropdownMenu::createWithDefaultElement(digits);
        dropdown->setPosition(winSize / 2);
        this->addChild(dropdown);

		return true;
	}
};
```

While we are at it, let's change the visuals of the menu.
```cpp
DropdownMenu::createWithDefaultElement(digits, -1, "Numbers", 150, 150, "GJ_square04.png");
```

<img src="https://cdn.discordapp.com/attachments/923715967589179452/1410995699159400459/image.png?ex=68b30ba5&is=68b1ba25&hm=84d7fd149e5b810c62a570b7625a77f9ec2ff0306d55fbe7f2832c68f84790c3&" alt="Default" width="400">

Now, instead of displaying "Numbers" at the top, we want to add up all selected numbers! To achieve this, we first need to disable the default callback, which sets the main text.

```cpp
auto dropdown = DropdownMenu::createWithDefaultElement(digits, -1, "Numbers", 150, 150, "GJ_square04.png");
dropdown->m_disableDefaultCallbacks = true;
```

However, this comes with a downside. The default callback is also in charge of coloring the squares green when selected, and changing the background color.

Because of this, we have to reimplement some of its functionality in our own callback.

```cpp
void addUpNumbers(int index, const std::string& value, DropdownMenu* dropdown) {
    // Since we need some fields from our dropdown menu, we also pass it as a parameter.

    // Even though we disabled the default callback, it still checks if the selected option is within the options size, so we don't have to worry about invalid indices.

    // Note that we also disabled the check if the option is already selected. You can also reimplement that here if needed.

    // Set the "Numbers" text so be at full opacity
    dropdown->m_menuText->setOpacity(255);

    // Get all of the options from the scroll layer
    auto options = dropdown->m_scrollLayer->m_contentLayer->getChildren();

    // Get the background and the button
    auto node = static_cast<CCNode*>(options->objectAtIndex(index));
    auto bg = node->getChildByType<CCScale9Sprite>(0);
    auto checkbox = node->getChildByType<CCMenu>(0)->getChildByType<CCMenuItemSpriteExtra>(0)->getChildByType<CCScale9Sprite>(0);

    // Change the colors
    checkbox->setColor(ccc3(0, 255, 0));
    bg->setOpacity(255);
    bg->setColor(dropdown->m_selectedColor);
}
```

The options now get colored like before! Now, let's set up our number calculation. For this, we can simply get the current value from the main menu text, and add on the selected number.

```cpp
void addUpNumbers(int index, const std::string& value, DropdownMenu* dropdown) {
    ...

    // Get the current value. If not a number, value is 0.
    int current = numFromString<int>(dropdown->m_menuText->getString()).unwrapOr(0);

    // Add the selected value. Note that in our case we can use the index, since it aligns with our numbers. However, you could also use value or get the number by checking the selected index.
    int newValue = current + index;

    // Set the main text to the new number
    dropdown->m_menuText->setString(std::to_string(newValue).c_str());

    }
```

Awesome, now we just need to set our addUpNumbers function as the callback for our dropdown menu.

```cpp
dropdown->setCallback([this, dropdown](int index, const std::string& value) {
    this->addUpNumbers(index, value, dropdown);
    });
```

## Full Example
```cpp
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include <natrium.ui_expansions/include/DropdownMenu.hpp> // Make sure to include this header!

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

        std::vector<std::string> digits = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

        auto dropdown = DropdownMenu::createWithDefaultElement(digits, -1, "Numbers", 150, 150, "GJ_square04.png");
        dropdown->m_disableDefaultCallbacks = true;
        dropdown->setCallback([this, dropdown](int index, const std::string& value) {
            this->addUpNumbers(index, value, dropdown);
        });

        dropdown->setPosition(winSize / 2);
        this->addChild(dropdown);

		return true;
	}

    void addUpNumbers(int index, const std::string& value, DropdownMenu* dropdown) {
        dropdown->m_menuText->setOpacity(255);

        auto options = dropdown->m_scrollLayer->m_contentLayer->getChildren();

        auto node = static_cast<CCNode*>(options->objectAtIndex(index));
        auto bg = node->getChildByType<CCScale9Sprite>(0);
        auto checkbox = node->getChildByType<CCMenu>(0)->getChildByType<CCMenuItemSpriteExtra>(0)->getChildByType<CCScale9Sprite>(0);

        checkbox->setColor(ccc3(0, 255, 0));
        bg->setOpacity(255);
        bg->setColor(dropdown->m_selectedColor);

        int current = numFromString<int>(dropdown->m_menuText->getString()).unwrapOr(0);

        int newValue = current + index;

        dropdown->m_menuText->setString(std::to_string(newValue).c_str());
    }
};
```

**Note:** The selected options are put into a vector, allowing for all to get reselected on menu reopen, even though we defined the default element as an int.

<img src="https://cdn.discordapp.com/attachments/923715967589179452/1411001938392383580/image.png?ex=68b31175&is=68b1bff5&hm=208ef47bdb934005abc6ad69539df1379c276d7db3634586fdd54d58300766d2&" alt="Default" width="400">