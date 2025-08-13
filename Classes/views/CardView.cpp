#include "CardView.h"
#include "utils/Utils.h"

USING_NS_CC;


bool CardView::init()
{
    if (!Node::init()) return false;

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);

    _touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    return true;
}

bool CardView::initViewWithModel(const std::shared_ptr<CardModel>& cardModel)
{
    if (cardModel->id == 0) return false;

    _cardModel = cardModel;

    this->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->setPosition(_cardModel->position);

    std::string colorStr = (_cardModel->suit == CST_CLUBS || _cardModel->suit == CST_SPADES) ? "black" : "red";
    std::string faceStr = Utils::cardFaceToStr(_cardModel->face);
    std::string suitStr = Utils::cardSuitToStr(_cardModel->suit);

    std::string backgroundPath = "card_general.png";
    std::string mainNumberPath = StringUtils::format("number/big_%s_%s.png", colorStr.c_str(), faceStr.c_str());
    std::string topLeftNumberPath = StringUtils::format("number/small_%s_%s.png", colorStr.c_str(), faceStr.c_str());
    std::string topRightSuitPath = StringUtils::format("suits/%s.png", suitStr.c_str());

    _background = Sprite::create(backgroundPath);
    _mainNumber = Sprite::create(mainNumberPath);
    _topLeftNumber = Sprite::create(topLeftNumberPath);
    _topRightSuit = Sprite::create(topRightSuitPath);


    if (!_background || !_mainNumber || !_topLeftNumber || !_topRightSuit) {
        CCLOG("Error loading card textures");
        return false;
    }

    this->addChild(_background);
    this->setContentSize(_background->getContentSize());

    _mainNumber->setAnchorPoint(Vec2(0.5f, 0.5f));
    _mainNumber->setPosition(_background->getContentSize().width * 0.5f, 
        _background->getContentSize().height * 0.5f - 20.0f);
    _background->addChild(_mainNumber);

    _topLeftNumber->setAnchorPoint(Vec2(0.0f, 1.0f));
    _topLeftNumber->setPosition(20.0f, 
        _background->getContentSize().height - 20.0f);
    _background->addChild(_topLeftNumber);

    _topRightSuit->setAnchorPoint(Vec2(1.0f, 1.0f));
    _topRightSuit->setPosition(_background->getContentSize().width - 20.0f,
        _background->getContentSize().height - 20.0f);
    _background->addChild(_topRightSuit);

    return true;
}

bool CardView::onTouchBegan(Touch* touch, Event* evnet)
{
    Vec2 touchLocation = this->convertToNodeSpace(touch->getLocation());
    Rect rect(Vec2::ZERO, this->getContentSize());

    _isTouchInArea = rect.containsPoint(Vec2(touchLocation.x + this->getContentSize().width * 0.5f, touchLocation.y + this->getContentSize().height * 0.5f));
    return _isTouchInArea;
}

void CardView::onTouchEnded(Touch* touch, Event* event)
{
    if (_isTouchInArea && _clickCallback)
    {
        _clickCallback();
    }
}

void CardView::moveToPos(cocos2d::Vec2 position)
{
    
    auto moveTo = cocos2d::MoveTo::create(2, position);
    this->runAction(moveTo);
}