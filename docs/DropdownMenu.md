# Dropdown Menu
For full examples, see [Dropdown Menu Examples](./examples/Dropdown%20Menu/Basic-Example.md)

## Public static methods
```cpp
static DropdownMenu* create(
    const std::vector<std::string>& options, 
    int defaultElement = -1, 
    const char* defaultText = "Select...", 
    float width = 150.0f, 
    float height = 150.0f, 
    const char* bgTexture = "GJ_square01.png", 
    ccColor3B bgColor = ccc3(255, 255, 255)
)
```

```cpp
static DropdownMenu* create(
    const std::vector<std::string>& options, 
    const std::vector<int>& defaultElements = {}, 
    const char* defaultText = "Select...", 
    float width = 150.0f, 
    float height = 150.0f, 
    const char* bgTexture = "GJ_square01.png", 
    ccColor3B bgColor = ccc3(255, 255, 255)
)
```

**Description:**  
Creates a dropdown menu.

### Parameters

**Required**
- `options` (*const std::vector\<std::string>&*) - The selectable options in the list menu.

**Optional**
- `defaultElement` (*int*) - Index of the default-selected element. -1 for none. **Default:** `-1`
- `defaultElements` (*const std::vector\<int>&*) - Vector of default-selected elements. {} for none. **Default:** `{}`
- `defaultText` (*const char\**) - The text that is displayed if no option is selected. Only visible if defaultElement is -1 or index does not exist in *options*. **Default:** `"Select..."`
- `width` (*float*) - Width of the menu. **Default:** `150.0`
- `height` (*float*) - The height of the list menu when extended. **Default:** `150.0`
- `bgTexture` (*const char\**) - The background texture of the menu, has to be a *CCScale9Sprite*. **Default:** `"GJ_square01.png"`
- `bgColor` (*ccColor3B*) - The color of the menu, tints the bgTexture in this color. **Default:** `ccc3(255, 255, 255)`

### Returns
- `DropdownMenu*` pointer to the created dropdown menu.


## Public member functions
```cpp
void onExpand(CCObject* sender);
```

**Description:**  
Gets called by the arrow button. Expands or collapses the menu, depending on if it is currently expanded or not. The list menu is cleaned up when closing, and recreated when opening.

### Parameters

**Required**
- `sender` (*CCObject\**) - The CCMenuItemSpriteExtra sender.

---

```cpp
void onSelect(CCObject* sender);
```

**Description:**  
Gets called by the menu list squares. Performs visual changes, like highlighting the box and changing the main menu text. Also calls the callback if set.

### Parameters

**Required**
- `sender` (*CCObject\**) - The CCMenuItemSpriteExtra sender.

---

```cpp
void setCallback(std::function<void(int, std::string const&)> cb);
```

**Description:**  
Sets the callback function that is triggered when a menu option is selected. 

There are some default callbacks, like highlighting the option background and replacing the menu text, which you can disable with *m_disableDefaultCallbacks*.

The callback receives
- The index of the selected option.
- The string of the option name.

### Parameters

**Required**
- `cb` (*std::function<void(int, std::string const&)>*) - Function to call when an option is selected.
  - `int` - Index of the selected option.
  - `std::string const&` - The selected option text.

## Fields
```cpp
bool m_isExpanded
```

**Description:**  
Tracks whether the dropdown menu is currently expanded (`true`) or collapsed (`false`).

**Default:** `false`

---

```cpp
std::vector<std::string> m_options;
```

**Description:**  
Provided options inside the menu list.

---

```cpp
float m_width;
```

**Description:**  
Width of the menu.

---

```cpp
float m_height;
```

**Description:**  
Height of the menu.

---

```cpp
const char* m_bgTexture;
```

**Description:**  
File of the background texture of both the main and list menu.

---

```cpp
ccColor3B m_bgColor;
```

**Description:**  
Color of the background. Tints the background texture in this color.

---

```cpp
int m_selected;
```

**Description:**  
Index of the currently selected object. -1 if none, defaultElement on first init.

---

```cpp
std::function<void(int, std::string const&)> m_callback;
```

**Description:**  
The callback that gets called when an option is selected.

---

```cpp
CCLabelBMFont* m_menuText
```

**Description:**  
The label in the main menu, which displays the currently selected element or the default text.

---

```cpp
const char* m_defaultText;
```

**Description:**  
The string of the label in the main menu, which displays the currently selected element or the default text.

---

```cpp
ScrollLayer* m_scrollLayer
```

**Description:**  
The scroll layer inside the menu list, which contains all of the options.

---

```cpp
float m_gap
```

**Description:**  
The gap between the top main menu, and the bottom list menu.

**Default:** `20.0`

---

```cpp
ccColor3B m_selectedColor
```

**Description:**  
The background color of an selected element.

**Default:** `ccc3(255, 170, 85)`

---

```cpp
bool m_growToFit
```

**Description:**  
Changes the height of the menu list to fit all elements exactly. Height value is ignored.

**Default:** `false`

---

```cpp
bool m_disableDefaultCallbacks
```

**Description:**  
Disables the default callbacks on button presses, that change the color of the item background and square button, and sets the text at the main menu.

**Default:** `false`

---

```cpp
bool m_hideScrollbar
```

**Description:**  
Hides the scrollbar. The scrollbar is hidden by default if growToFit is true.

**Default:** `false`

---

```cpp
bool m_allowMultiSelect
```

**Description:**  
Whether to allow several options to be selected at once. Note that the callback still only receives the index of the clicked element, however m_selected contains all currently selected elements.

**Default:** `false`