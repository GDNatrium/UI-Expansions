# Dropdown Menu Examples - Basic Setup

For most usecases, you can use the default values for your popup. 

In this example we will create 3 different popups with increasing complexity.

- **Basic Setup** - A dropdown menu that allows you to pick the color of a button.
- [Visuals Setup](Visuals-Example.md) - A visually customized dropdown menu that allows you to select a difficulty.
- [Advanced Setup](Advanced-Example.md) - A highly customized dropdown menu, which changes how callbacks work to allow for multiselection and visual changes.

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
In this example we use default values to create a simply dropdown menu, and set up a callback that changes the color of a button.

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

We first add the button we want to change the color of later.

```cpp
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto button = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
        button->setPosition({winSize.width / 2 + 160, winSize.height / 2});
        button->setID("my-button");
        this->addChild(button);

		return true;
	}
};
```

We now want to add our dropdown menu. For that we first have to set all options we want. For our example, we want red, blue, yellow, and green.

```cpp
std::vector<std::string> colors = {
    "Red",
    "Blue",
    "Yellow",
    "Green"
};
```

We can now pass our colors to the dropdown menu create function and add the returned dropdown to the scene.

```cpp
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto button = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
        button->setPosition({winSize.width / 2 + 160, winSize.height / 2});
        button->setID("my-button");
        this->addChild(button);

        std::vector<std::string> colors = {
            "Red",
            "Blue",
            "Yellow",
            "Green"
        };

        auto dropdown = DropdownMenu::create(colors);
        dropdown->setPosition(winSize / 2);
        this->addChild(dropdown);

		return true;
	}
};
```

The result looks like this.  
<img src="https://cdn.discordapp.com/attachments/923715967589179452/1410972718450475088/image.png?ex=68b2f63e&is=68b1a4be&hm=f6b7941284f50b3392c240048f1cb8f4cd74fb5fabb5060fceb108837022d442&" alt="Default" width="400">


We now only have to set up the callback for changing the button color when an option is selected.

```cpp
void changeColor(int index, const std::string& value) {
    // The index responds to the element in our options parameter.
    // 0 = Red,
    // 1 = Blue
    // ...

    log::debug("The user picked color {}, which has the index {}.", value, index);

    // We get our button to change the color of it.
    auto button = static_cast<CCSprite*>(this->getChildByID("my-button"));

    // We can now use switch to check what color the user picked.
    switch (index) {
    case 0:
        // Red
        button->setColor(ccc3(255, 0, 0));
        break;
    case 1:
        // Blue
        button->setColor(ccc3(0, 0, 255));
        break;
    case 2:
        // Yellow
        button->setColor(ccc3(255, 255, 0));
        break;
    case 3:
        // Green
        button->setColor(ccc3(0, 255, 0));
        break;
    default:
        button->setColor(ccc3(255, 255, 255));
    }
}
```

We now just set our changeColor function as the callback, and we are done.

```cpp
dropdown->setCallback([this](int index, const std::string& value) {
    this->changeColor(index, value);
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

        // Create our button
        auto button = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
        button->setPosition({winSize.width / 2 + 160, winSize.height / 2});
        button->setID("my-button");
        this->addChild(button);

        // Define our options
        std::vector<std::string> colors = {
            "Red",
            "Blue",
            "Yellow",
            "Green"
        };

        // Create the dropdown menu
        auto dropdown = DropdownMenu::create(colors);

        // Set the callback for when an option is selected
        dropdown->setCallback([this](int index, const std::string& value) {
            this->changeColor(index, value);
            });

        dropdown->setPosition(winSize / 2);
        this->addChild(dropdown);

		return true;
	}

    // Our callback function
    void changeColor(int index, const std::string& value) {
        auto button = static_cast<CCSprite*>(this->getChildByID("my-button"));

        switch (index) {
        case 0:
            // Red
            button->setColor(ccc3(255, 0, 0));
            break;
        case 1:
            // Blue
            button->setColor(ccc3(0, 0, 255));
            break;
        case 2:
            // Yellow
            button->setColor(ccc3(255, 255, 0));
            break;
        case 3:
            // Green
            button->setColor(ccc3(0, 255, 0));
            break;
        default:
            button->setColor(ccc3(255, 255, 255));
        }
    }
};
```

The color of the button will now change depending on what option you pick!
<img src="https://cdn.discordapp.com/attachments/923715967589179452/1410979864030220358/image.png?ex=68b2fce6&is=68b1ab66&hm=99ef54b7b2f1127bc1b6cf46fb503d6e6493a346cf60c1e2558e178757293c87&" alt="Callback Finished" width="400">
