# Dropdown Menu Examples - Visuals Setup

For most usecases, you can use the default values for your popup. 

In this example we will create 3 different popups with increasing complexity.

- [Basic Setup](Basic-Example.md) - A dropdown menu that allows you to pick the color of a button.
- **Visuals Setup** - A visually customized dropdown menu that allows you to select a difficulty.
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
In this example we customize the visuals of other popup. This will not include setting up callbacks, check the [Basic Setup](Basic-Example.md) for that.

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

We now want to add our dropdown menu. For that we first have to set all options we want. For our example, we want red, blue, yellow, and green.

```cpp
std::vector<std::string> difficulty = {
    "Easy",
    "Normal",
    "Hard",
    "Harder",
    "Insane",
    "Demon"
};
```

We can now pass our difficulty variable to the dropdown menu create function and add the returned dropdown to the scene.

```cpp
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::sharedDirector()->getWinSize();

        std::vector<std::string> difficulty = {
            "Easy",
            "Normal",
            "Hard",
            "Harder",
            "Insane",
            "Demon"
        };

        auto dropdown = DropdownMenu::create(difficulty);
        dropdown->setPosition(winSize / 2);
        this->addChild(dropdown);

		return true;
	}
};
```

This will create the dropdown menu in the default look.
<img src="https://cdn.discordapp.com/attachments/923715967589179452/1410983813957554187/image.png?ex=68b30094&is=68b1af14&hm=8eab2ea5513f160acd1cee7121514853a322af59d266b657315be459a27d51a8&" alt="Default" width="400">

We now want to customize the look to fit our needs. 

First, we want to set a default element. For example, we want the menu to have "Easy" selected by default. To do so, we can pass the index of "Easy" to our DropdownMenu::create function as the defaultElement.

In our case, "Easy" is the first element, so its index is 0.

```cpp
DropdownMenu::create(difficulty, 0);
```

We can also change the default text, for when no element is selected. By default it is "Select...", but for our use case "Difficulty" is more fitting.

```cpp
DropdownMenu::create(difficulty, 0, "Difficulty");
```

Next, we want to change the size of our menu. We can pass values for width and height to the create function.

```cpp
DropdownMenu::create(difficulty, 0, "Difficulty", 180, 200);
```

Lastly, we want to change the background. The default brown one doesn't fit our needs, and the white outlines are ugly. Let's use a white background, and set the color ourselves!

```cpp
DropdownMenu::create(difficulty, 0, "Difficulty", 180, 240, "GJ_square06.png", ccc3(44, 145, 255));
```

Our menu looks like this now.  
<img src="https://cdn.discordapp.com/attachments/923715967589179452/1410987378792992768/image.png?ex=68b303e5&is=68b1b265&hm=0baf00eeeeb3010de5276ea4f2dc432e37805786a1f8f72459c3f1eb2e4c1ce2&" alt="Progress" width="400">

Well, that has several issues!

- First, the highlight color for when an option is selected doesn't really fit our background color. 
- Second, we have a lot of empty space at the bottom of our list, which we don't need. It would be ideal to just size the menu to fit all content.
- Third, the gap between the main menu and the bottom menu is too big, it looks disconnected.

Lucky for us, we can use fields to fix these issues.

```cpp
auto dropdown = DropdownMenu::create(difficulty, 0, "Difficulty", 180, 240, "GJ_square06.png", ccc3(44, 145, 255));
// Change the color of selected elements
dropdown->m_selectedColor = ccc3(44, 255, 255); 

// Change the gap between the menus from 20.0 to 15.0
dropdown->m_gap = 15.f;

// Change the height to fit all elements. 
// Note that this also hides the scrollbar. If you want to hide the scrollbar without growToFit, you can use m_hideScrollbar.
dropdown->m_growToFit = true; 
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

        std::vector<std::string> difficulty = {
            "Easy",
            "Normal",
            "Hard",
            "Harder",
            "Insane",
            "Demon"
        };

        auto dropdown = DropdownMenu::create(difficulty, 0, "Difficulty", 180, 240, "GJ_square06.png", ccc3(44, 145, 255));
        dropdown->m_selectedColor = ccc3(44, 255, 255); 
        dropdown->m_gap = 15.f;
        dropdown->m_growToFit = true; 

        dropdown->setPosition(winSize / 2);
        this->addChild(dropdown);

		return true;
	}
};
```

Now that's more like it! We changed the visuals of the dropdown menu to fit our needs.


<img src="https://cdn.discordapp.com/attachments/923715967589179452/1410989576331333756/image.png?ex=68b305f1&is=68b1b471&hm=1befaa12f65ae8cd3d2dd3904bfd1c7f0a589afa392af0b2b8fef5266718a503&" alt="Finished Example" width="400">