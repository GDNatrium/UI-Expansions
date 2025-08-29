# UI Expansions
Geode API that adds a lot of highly customizable UI elements to Geometry Dash.

**This API adds:**
- Dropdown Menus
...

## Usage
You can use this API as a dependency by declaring it in your ``mod.json`` file:
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

After doing so, you can include the header you want. For example, the dropdown menu would be included like so:
```cpp
#include <natrium.ui_expansions/include/DropdownMenu.hpp>
```

## Documentation & Examples
You can find documentation of everything in the docs folder. The folder also contains several examples.

### Dropdown Menu
- [**Documentation**](./docs/DropdownMenu.md)
- [Setup Example](./docs/examples/Dropdown%20Menu/Basic-Example.md)
- [Visuals Example](./docs/examples/Dropdown%20Menu/Visuals-Example.md)