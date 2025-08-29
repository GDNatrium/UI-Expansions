#include "../include/DropdownMenu.hpp"

DropdownMenu* DropdownMenu::create(const std::vector<std::string>& options) {
    auto ret = new DropdownMenu;
    if (ret->init(options, {}, "Select...", 150, 150, "GJ_square01.png", ccc3(255, 255, 255))) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

DropdownMenu* DropdownMenu::createWithDefaultElement(const std::vector<std::string>& options, int defaultElement, const char* defaultText, float width, float height, const char* bgTexture, ccColor3B bgColor) {
    auto ret = new DropdownMenu;

    std::vector<int> defaultElements;
    if (defaultElement < 0 || defaultElement >= options.size()) defaultElements = {};
    else defaultElements = { defaultElement };

    if (ret->init(options, defaultElements, defaultText, width, height, bgTexture, bgColor)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

DropdownMenu* DropdownMenu::createWithDefaultElements(const std::vector<std::string>& options, const std::vector<int>& defaultElements, const char* defaultText, float width, float height, const char* bgTexture, ccColor3B bgColor) {
    auto ret = new DropdownMenu;
    if (ret->init(options, defaultElements, defaultText, width, height, bgTexture, bgColor)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool DropdownMenu::init(const std::vector<std::string>& options, const std::vector<int>& defaultElements, const char* defaultText, float width, float height, const char* bgTexture, ccColor3B bgColor) {
    if (!CCLayer::init()) return false;
    
    // Maybe later add multiselect option

    m_options = options;
    m_width = width;
    m_height = height;
    m_bgTexture = bgTexture;
    m_bgColor = bgColor;
    m_selected = defaultElements;
    m_defaultText = defaultText;

    auto menuBtnSpr = CCScale9Sprite::create(bgTexture);
    menuBtnSpr->setContentSize({ width, 35 });
    menuBtnSpr->setColor(bgColor);
    this->addChild(menuBtnSpr);

    auto mainMenu = CCMenu::create();
    mainMenu->setContentSize(menuBtnSpr->getContentSize());
    menuBtnSpr->addChildAtPosition(mainMenu, Anchor::Center);

    auto arrowBg = CCScale9Sprite::create("square02_small.png");
    arrowBg->setContentSize({ menuBtnSpr->getContentHeight() - 3, menuBtnSpr->getContentHeight() - 5});
    arrowBg->setScale(0.75);
    arrowBg->setOpacity(60);

    auto arrow = CCSprite::createWithSpriteFrameName("edit_downBtn_001.png");
    arrowBg->addChildAtPosition(arrow, Anchor::Center);

    auto expandBtn = CCMenuItemSpriteExtra::create(arrowBg, this, menu_selector(DropdownMenu::onExpand));
    mainMenu->addChildAtPosition(expandBtn, Anchor::Right, ccp(-5 - arrowBg->getScaledContentWidth() / 2, 0));

    if (defaultElements.size() == 0) {
        m_menuText = CCLabelBMFont::create(defaultText, "bigFont.fnt");
        m_menuText->limitLabelWidth(width - arrowBg->getContentWidth() - 8, 0.65, 0.1);
        m_menuText->setOpacity(175);
        menuBtnSpr->addChildAtPosition(m_menuText, Anchor::Center, ccp(-arrowBg->getScaledContentWidth() / 2, 1.5));
    }

    if (defaultElements.size() == 1) {
        m_menuText = CCLabelBMFont::create(options[defaultElements[0]].c_str(), "bigFont.fnt");
        m_menuText->limitLabelWidth(width - arrowBg->getContentWidth() - 8, 0.65, 0.1);
        menuBtnSpr->addChildAtPosition(m_menuText, Anchor::Center, ccp(-arrowBg->getScaledContentWidth() / 2, 1.5));
    }

    if (defaultElements.size() >= 2) {
        m_menuText = CCLabelBMFont::create(defaultText, "bigFont.fnt");
        m_menuText->limitLabelWidth(width - arrowBg->getContentWidth() - 8, 0.65, 0.1);
        menuBtnSpr->addChildAtPosition(m_menuText, Anchor::Center, ccp(-arrowBg->getScaledContentWidth() / 2, 1.5));
    }

    return true;
}

void DropdownMenu::onExpand(CCObject* sender) {
    auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto arrow = btn->getChildByType<CCScale9Sprite>(0)->getChildByType<CCSprite>(0);

    arrow->setFlipY(!m_isExpanded);

    if (!m_isExpanded) {
        // open it
        auto bg = CCScale9Sprite::create(m_bgTexture);
        bg->setContentSize({ m_width, m_height });
        bg->setAnchorPoint(ccp(0.5, 1));
        bg->setPositionY(-m_gap);

        auto red = m_bgColor.r;
        if (red <= 40) red = 0;
        else red -= 40;

        auto green = m_bgColor.g;
        if (green <= 40) green = 0;
        else green -= 40;

        auto blue = m_bgColor.b;
        if (blue <= 40) blue = 0;
        else blue -= 40;

        bg->setColor({red, green, blue });
        bg->setID("list");
        this->addChild(bg);

        auto list = createScrollLayer(m_options);
        list->scrollToTop();
        bg->addChildAtPosition(list, Anchor::BottomLeft, ccp(5, 5));

        if (!m_growToFit && !m_hideScrollbar) {
            auto scrollbar = Scrollbar::create(list);
            bg->addChildAtPosition(scrollbar, Anchor::Right, ccp(5, 0));
        }
    }
    else {
        auto list = this->getChildByID("list");
        if (list) list->removeFromParent();
    }

    m_isExpanded = !m_isExpanded;
}

ScrollLayer* DropdownMenu::createScrollLayer(std::vector<std::string> options) {

    if(!m_growToFit) m_scrollLayer = ScrollLayer::create({m_width - 10, m_height - 10 });
    else {
        float height = options.size() * 30 + options.size() - 1 * 1;
        m_scrollLayer = ScrollLayer::create({ m_width - 10.f, height });
        this->getChildByType<CCScale9Sprite>(1)->setContentHeight(height + 10);
    }

    m_scrollLayer->m_contentLayer->setLayout(
        ColumnLayout::create()
        ->setAxisAlignment(AxisAlignment::End)
        ->setGap(1)
        ->setAxisReverse(true)
        ->setAutoGrowAxis(m_scrollLayer->getContentHeight())
    );

    bool bgOpacity = false;

    for (int i = 0; i < options.size(); ++i) {
        auto node = CCNode::create();
        node->setContentSize({ m_scrollLayer->getContentWidth(), 30 });

        auto menu = CCMenu::create();
        menu->setContentSize(node->getContentSize());
        menu->setZOrder(5);
        node->addChildAtPosition(menu, Anchor::Center);

        auto bg = CCScale9Sprite::create("square02b_small.png");
        bg->setColor(std::find(m_selected.begin(), m_selected.end(), i) != m_selected.end() ? m_selectedColor : ccc3(0, 0, 0));
        bg->setContentSize(node->getContentSize());
        if(!(std::find(m_selected.begin(), m_selected.end(), i) != m_selected.end())) bg->setOpacity(bgOpacity ? 50 : 25);
        bg->ignoreAnchorPointForPosition(false);
        node->addChildAtPosition(bg, Anchor::Center);

        auto text = CCLabelBMFont::create(options[i].c_str(), "bigFont.fnt");
        text->limitLabelWidth(node->getContentWidth() - 40, 0.55, 0.1);
        text->setAnchorPoint(ccp(0, 0.5));
        node->addChildAtPosition(text, Anchor::Left, ccp(10, 1));

        auto activeSpr = CCScale9Sprite::create("square02c_001.png");
        activeSpr->setContentSize({ 40, 40 });
        activeSpr->setScale(0.45);
        activeSpr->setColor(std::find(m_selected.begin(), m_selected.end(), i) != m_selected.end() ? ccc3(0, 255, 0) : ccc3(255, 255, 255));

        auto clickable = CCMenuItemSpriteExtra::create(activeSpr, this, menu_selector(DropdownMenu::onSelect));
        clickable->setTag(i);
        menu->addChildAtPosition(clickable, Anchor::Right, ccp(-15, 0));

        m_scrollLayer->m_contentLayer->addChild(node);

        bgOpacity = !bgOpacity;
    }

    m_scrollLayer->m_contentLayer->updateLayout();
    m_scrollLayer->scrollToTop();

    return m_scrollLayer;
}

void DropdownMenu::onSelect(CCObject* sender) {
    auto index = sender->getTag();

    if (index < 0 || index >= m_options.size()) return;

    if (m_allowMultiSelect) {
        auto it = std::find(m_selected.begin(), m_selected.end(), index);
        if (it == m_selected.end()) {
            m_selected.push_back(index);
        }
        else {
            m_selected.erase(it);
        }
    }
    else {
        m_selected.clear();
        m_selected.push_back(index);
    }

    if (m_callback) {
        m_callback(index, m_options[index]);
    }

    if (m_disableDefaultCallbacks) return;

    m_menuText->setOpacity(m_selected.size() > 0 ? 255 : 175);

    if (m_selected.empty()) {
        m_menuText->setString(m_defaultText);
    }
    else if (!m_allowMultiSelect && m_selected.size() == 1) {
        m_menuText->setString(m_options[m_selected[0]].c_str());
    }
    else if (m_allowMultiSelect && m_selected.size() == 1) {
        m_menuText->setString(m_options[m_selected[0]].c_str());
    }
    else {
        m_menuText->setString(m_defaultText);
    }

    m_menuText->limitLabelWidth(m_width - 36, 0.65, 0.1);

    auto options = m_scrollLayer->m_contentLayer->getChildren();
    bool bgOpacity = false;

    for (int i = 0; i < options->count(); ++i) {
        auto node = static_cast<CCNode*>(options->objectAtIndex(i));
        auto bg = node->getChildByType<CCScale9Sprite>(0);
        auto checkbox = node->getChildByType<CCMenu>(0)
            ->getChildByType<CCMenuItemSpriteExtra>(0)
            ->getChildByType<CCScale9Sprite>(0);

        bool isSelected = std::find(m_selected.begin(), m_selected.end(), i) != m_selected.end();

        if (isSelected) {
            checkbox->setColor(ccc3(0, 255, 0));
            bg->setOpacity(255);
            bg->setColor(m_selectedColor);
        }
        else {
            checkbox->setColor(ccc3(255, 255, 255));
            bg->setOpacity(bgOpacity ? 50 : 25);
            bg->setColor(ccc3(0, 0, 0));
        }

        bgOpacity = !bgOpacity;
    }
}


void DropdownMenu::setCallback(std::function<void(int, std::string const&)> cb) {
    m_callback = std::move(cb);
}
