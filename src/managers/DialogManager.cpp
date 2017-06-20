#include "DialogManager.hpp"
#include "DialogState.hpp"

template <> DialogManager* Ogre::Singleton<DialogManager>::msSingleton = 0;

DialogManager::DialogManager (): _dialogGUI(nullptr), _exitAnim(false), _next_dialogue(false),
_finish_dialogue(false), _message(false), _speed(false), _dialogue_cont(1), _phase(1),
_moveOut(0), _timeSinceStart(0.0f)
{
}

DialogManager* DialogManager::getSingletonPtr () {
    return msSingleton;
}

DialogManager& DialogManager::getSingleton () {
    assert (msSingleton);
    return *msSingleton;
}

void DialogManager::newIntervention(int phase, int dialogue_cont){
    _phase = phase;
    _dialogue_cont = dialogue_cont;
    _moveOut = 0;
    loadDialogue();
    chargeDialogue();
    _inAnim->start();
}

void DialogManager::chargeDialogue(){
    initCEGUI();
    _next_dialogue = true;
    _speed = false;
    _timeSinceStart = 0.0;
    VELOCITY = 0.08f;
    setDialogue(0.0);
}

void DialogManager::update(float delta) {
    _timeSinceStart += delta;
    if(_message)
        updateText(delta);
}

void DialogManager::hide(){
    if(_dialogGUI){
      _dialogGUI->setVisible(false);
    }
}

void DialogManager::loadDialogue() {
    _data.clear();
    std::string separator = "/";
    std::string file_name = std::string("misc") + separator + std::string("phase") + std::to_string(_phase) + std::string("-") + std::to_string(_dialogue_cont)+ std::string(".txt");
    std::ifstream file(file_name);
    std::string line;
    if (file.is_open()) {
        std::string item;
        while (getline(file, line)) {
            std::stringstream iss;
            iss << line;
            while (std::getline (iss, item, DELIM)) {
                _data.push_back(item);
            }
        }
        file.close();
    }else{
        _finish_dialogue = true;
    }
}

void DialogManager::initCEGUI(){
    if(_dialogGUI==nullptr){
        _dialogGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("dialogue.layout");
        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_dialogGUI);
        _botBarLabel = _dialogGUI->getChild("BotBar/BotBarLabel");
        _botNameLabel = _dialogGUI->getChild("BotBar/NameLabel");
        _botBar = _dialogGUI->getChild("BotBar");
        setupAnimations();
    }else
        _dialogGUI->show();
        _dialogGUI->setVisible(true);
}

void DialogManager::setupAnimations()
{
  CEGUI::AnimationManager& animMgr = CEGUI::AnimationManager::getSingleton();
  animMgr.loadAnimationsFromXML("Animations.anims");

  CEGUI::Animation* botBarAnim = animMgr.getAnimation("BotBarDialogoMoveInAnimation");
  _inAnim = animMgr.instantiateAnimation(botBarAnim);
  _inAnim->setTargetWindow(_botBar);

  CEGUI::Animation* botBarOutAnim = animMgr.getAnimation("BotBarDialogoMoveOutAnimation");
  _outAnim = animMgr.instantiateAnimation(botBarOutAnim);
  _outAnim->setTargetWindow(_botBar);
}

void DialogManager::setDialogue(float delta)
{
    int id;
    std::string name;
    if(_next_dialogue && !_finish_dialogue){
        if (_data.size() > 0) {
            id = std::stoi(_data[0]);
            name = _data[1];
            _text = _data[2];
            _data.erase(_data.begin(), _data.begin() + 3);
            _next_dialogue = false;
            _botNameLabel->setText(name);
        }else{
              _botNameLabel->setText("");
              _text = "";
              _moveOut++;
              if(_moveOut==1){
                  //_outAnim->start();
                  resetDialogue();
                  DialogState::getSingletonPtr()->popState();
              }
        }
    }
    if(_finish_dialogue)
        _botBar->setVisible(false);

    _message = true;
}

void DialogManager::updateText(float delta)
{
    CEGUI::String firstPart, secondPart;
    int limit;
    if(_text.length()>(unsigned)_limit_letter){
        limit = _limit_letter;
        while(_text.at(limit) != ' '){
              limit++;
        }
      firstPart = _text.substr(0,limit);
      secondPart = _text.substr(limit,_text.length());
    }else{
        firstPart = _text;
        secondPart = "";
    }

    if(!_speed)
        _secondStartDelay = firstPart.size()/13.0f;

    CEGUI::String finalText;

    int firstPartTypeProgress = static_cast<int>((_timeSinceStart - _firstStartDelay) / VELOCITY);
    if(firstPartTypeProgress > 0)
        finalText += firstPart.substr(0, std::min<unsigned int>(firstPart.length(), firstPartTypeProgress));

    int secondPartTypeProgress = static_cast<int>((_timeSinceStart - _secondStartDelay) / VELOCITY);
    if(secondPartTypeProgress > 0)
        finalText += "\n" + secondPart.substr(0, std::min<unsigned int>(secondPart.length(), secondPartTypeProgress));

    if(finalText.length()>_text.length())
        _message = false;

    _botBarLabel->setText(finalText);
}

void DialogManager::resetDialogue()
{
    _dialogue_cont = 0;
    if(_dialogGUI){
      _dialogGUI->setVisible(false);
    }
}


void DialogManager::passMessage()
{
    VELOCITY = 0.01f;
    _secondStartDelay = 0.0f;
    _speed = true;
};
