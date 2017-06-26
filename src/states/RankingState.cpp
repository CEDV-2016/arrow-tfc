#include <sstream>

#include "RankingState.hpp"
#include "SoundFXManager.hpp"

template<> RankingState* Ogre::Singleton<RankingState>::msSingleton = 0;

RankingState::RankingState() {
  _rankingGUI = NULL;
  _rankingManager = new RankingManager;
}

void
RankingState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("MainCamera");
  createGUI();

  SoundFXManager::getSingletonPtr()->load("menu_item.wav")->play();

  _exitGame = false;
}

void
RankingState::exit ()
{
  _rankingGUI->hide();
}

void
RankingState::pause ()
{
}

void
RankingState::resume ()
{
}

bool
RankingState::frameStarted
(const Ogre::FrameEvent& evt)
{
  CEGUI::System::getSingleton().injectTimePulse( evt.timeSinceLastFrame );

  return true;
}

bool
RankingState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
  return false;

  return true;
}

void
RankingState::keyPressed
(const OIS::KeyEvent &e)
{
}

void
RankingState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE)
  {
    popState();
  }
}

void
RankingState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
RankingState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
RankingState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

RankingState*
RankingState::getSingletonPtr ()
{
  return msSingleton;
}

RankingState&
RankingState::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void RankingState::createGUI()
{
  if(_rankingGUI == NULL){
    //Config Window
    _rankingGUI = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("ranking.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_rankingGUI);

    //Config Buttons
    CEGUI::Window* backButton = _rankingGUI->getChild("BackButton");
    backButton->subscribeEvent(CEGUI::PushButton::EventClicked,
      CEGUI::Event::Subscriber(&RankingState::back, this));
    _layout1 = _rankingGUI->getChild("Layout1");
    _layout2 = _rankingGUI->getChild("Layout2");
    _layout3 = _rankingGUI->getChild("Layout3");
    _layout4 = _rankingGUI->getChild("Layout4");
    _layout5 = _rankingGUI->getChild("Layout5");

      std::vector<std::string> ranking = _rankingManager->getRanking();
      std::string name, score, layout;
      for (unsigned int i=0; i<ranking.size(); i+=2){
        name = std::string("Name") + std::to_string(i/2+1);
        score = std::string("Point") + std::to_string(i/2+1);
        layout = std::string("Layout") + std::to_string(i/2+1);
        CEGUI::Window* layout_record = _rankingGUI->getChild(layout);
        CEGUI::Window* name_record = layout_record->getChild(name);
        name_record->setText(ranking[i]);
        CEGUI::Window* score_record = layout_record->getChild(score);
        score_record ->setText(ranking[i+1]);
      }
  } else{
    std::vector<std::string> ranking = _rankingManager->getRanking();
    std::string name, score, layout;
    for (unsigned int i=0; i<ranking.size(); i+=2){
      name = std::string("Name") + std::to_string(i/2+1);
      score = std::string("Point") + std::to_string(i/2+1);
      layout = std::string("Layout") + std::to_string(i/2+1);
      CEGUI::Window* layout_record = _rankingGUI->getChild(layout);
      CEGUI::Window* name_record = layout_record->getChild(name);
      name_record->setText(ranking[i]);
      CEGUI::Window* score_record = layout_record->getChild(score);
      score_record ->setText(ranking[i+1]);
    }
    _rankingGUI->show();
  }
  setupAnimations();
}

void RankingState::setupAnimations() {
  CEGUI::AnimationManager& animMgr = CEGUI::AnimationManager::getSingleton();

  CEGUI::Animation* newAnim1 = animMgr.getAnimation("Rank1MoveInAnimation");
  CEGUI::AnimationInstance* newAnimInstance1 = animMgr.instantiateAnimation(newAnim1);
  newAnimInstance1->setTargetWindow(_layout1);
  newAnimInstance1->start();

  CEGUI::Animation* newAnim2 = animMgr.getAnimation("Rank2MoveInAnimation");
  CEGUI::AnimationInstance* newAnimInstance2 = animMgr.instantiateAnimation(newAnim2);
  newAnimInstance2->setTargetWindow(_layout2);
  newAnimInstance2->start();

  CEGUI::Animation* newAnim3 = animMgr.getAnimation("Rank3MoveInAnimation");
  CEGUI::AnimationInstance* newAnimInstance3 = animMgr.instantiateAnimation(newAnim3);
  newAnimInstance3->setTargetWindow(_layout3);
  newAnimInstance3->start();

  CEGUI::Animation* newAnim4 = animMgr.getAnimation("Rank4MoveInAnimation");
  CEGUI::AnimationInstance* newAnimInstance4 = animMgr.instantiateAnimation(newAnim4);
  newAnimInstance4->setTargetWindow(_layout4);
  newAnimInstance4->start();

  CEGUI::Animation* newAnim5 = animMgr.getAnimation("Rank5MoveInAnimation");
  CEGUI::AnimationInstance* newAnimInstance5 = animMgr.instantiateAnimation(newAnim5);
  newAnimInstance5->setTargetWindow(_layout5);
  newAnimInstance5->start();

  _layout1->show();
  _layout2->show();
  _layout3->show();
  _layout4->show();
  _layout5->show();
}

bool RankingState::back(const CEGUI::EventArgs &e)
{
  popState();
  return true;
}
