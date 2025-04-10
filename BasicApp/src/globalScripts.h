#pragma once
#include "objects.h"
#include "objScripts.h"
#include "Text.h"
#include "GlobalVars.h"
#include "Input.h"
#include "transform.h"
#include "UniqueTypes.h"

struct TextBox : public ScriptBase {
  constexpr static const char* name = "TextBox";
  std::vector<void*> startObjs;
  Object* thisObj = nullptr;

  std::string text;
  std::string font = "CascadiaCode_NORMAL";
  float fontSize = 1;
  float lineSize = 1;
  float yStart = 1;
  float margin = 0;
  uint mode = 0;
  Vec3 fontColor = { 0, 0, 0 };


  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>({}, startObjs);
  }

  void* getNew() override {
    return new TextBox;
  }

  const std::string getName() const override {
    return TextBox::name;
  }

  void start() override {
    if (started)
      return;
    started = true;
    thisObj = (Object*)vThisObj;
    if (!thisObj->mesh)
      return;

    tex = new Texture(0, 0, 0, Texture::ALBEDO);

    thisObj->srcMaterial.albedoMap = tex;
    createTextTexture(tex->texture, fontSize, lineSize, thisObj->transform.scale.toVec2(), yStart, margin, mode, font, text);
  }

  void update() override {
    thisObj->srcMaterial.albedo = fontColor;

  }
  void end() override {
    delete(tex);
    glDeleteTextures(1, &tex->texture);
    text.clear();
    font.clear();
    text.~basic_string();
    font.~basic_string();
  }

  void textUpdate() {
    createTextTexture(tex->texture, fontSize, lineSize, thisObj->transform.scale.toVec2(), yStart, margin, mode, font, text);
  }

  TextBox* operator =(const TextBox& val) {
    this->text = val.text;
    this->font = val.font;
    this->fontSize = val.fontSize;
    this->lineSize = val.lineSize;
    this->yStart = val.yStart;
    this->margin = val.margin;
    this->mode = val.mode;
    this->fontColor = val.fontColor;
    return this;
  }

  TextBox() {}

private:
  Texture* tex = nullptr;
};


struct ButtonMain : public ScriptBase {
  constexpr static const char* name = "ButtonMain";
  std::vector<void*> startObjs;
  Object* thisObj = nullptr;

  Object* textObj = nullptr;
  TextBox* textScr = nullptr;
  bool held = false;

  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>(std::vector<std::pair<Unique::Types, std::string>> { {Unique::OBJECT, "square"} }, startObjs);
  }

  void* getNew() override {
    return new ButtonMain;
  }

  const std::string getName() const override {
    return ButtonMain::name;
  }

  void start() override {
    if (started)
      return;
    started = true;

    thisObj = (Object*)vThisObj;
    thisObj->ui = true;

    textScr = new TextBox();

    textObj = (Object*)startObjs[0];
    textScr->text = "Button";
    textScr->font = "CascadiaCode_SMALL";
    textScr->fontSize = 0.5;
    textScr->lineSize = 0.55;
    textScr->mode = TEXT_CENTER_RENDER;
    textScr->fontColor = Vec3(0, 0, 0);
    textObj->ui = true;

    textObj->transform = thisObj->transform;
    textObj->setParent(thisObj);
    textObj->relativeTransform.position.z = 0.05f;
    textObj->setToRelative();

    addUniqueTypeScript(textObj, textScr);

    cStart();
  }


  void update() override {
    if (keyAction::keyReleased(GLFW_MOUSE_BUTTON_1) && held) {
      held = false;
      onReleased();
      return;
    }

    if (_hideMouse)
      return;

    if (keyAction::keyPressed(GLFW_MOUSE_BUTTON_1)) {
      if (mouseWithin(thisObj)) {
        onPressed();
        held = true;
      }
    }

    if (held)
      onHeld();

    cUpdate();
  }

  virtual void cStart() {}
  virtual void cUpdate() {}
  virtual void onPressed() {}
  virtual void onHeld() {}
  virtual void onReleased() {}

  static bool mouseWithin(Object*& obj) {
    float left = obj->transform.position.x - obj->transform.scale.x;
    float right = obj->transform.position.x + obj->transform.scale.x;
    float bottom = obj->transform.position.y - obj->transform.scale.y;
    float top = obj->transform.position.y + obj->transform.scale.y;
    return _mousePosX <= right && _mousePosX >= left && _mousePosY <= top && _mousePosY >= bottom;
  }

  ButtonMain() {}
};


struct Button : public ScriptBase {
  constexpr static const char* name = "Button";
  Object* thisObj = nullptr;
  std::vector<void*> startObjs;

  Object* textObj = nullptr;
  TextBox* textScr = nullptr;
  bool held = false;

  void (*onPressed)() = nullptr;
  void (*BonPressed)(Button*) = nullptr;
  void (*onHeld)() = nullptr;
  void (*BonHeld)(Button*) = nullptr;
  void (*onReleased)() = nullptr;
  void (*BonReleased)(Button*) = nullptr;

  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>(std::vector<std::pair<Unique::Types, std::string>> {{Unique::OBJECT, "square"}}, startObjs);
  }

  void* getNew() override {
    return new Button;
  }

  const std::string getName() const override {
    return Button::name;
  }

  void start() override {
    if (started)
      return;
    started = true;

    thisObj = (Object*)vThisObj;
    thisObj->ui = true;

    textScr = new TextBox();

    textObj = (Object*)startObjs[0];
    textScr->text = "Button";
    textScr->font = "CascadiaCode_NORMAL";
    textScr->fontSize = 0.5;
    textScr->lineSize = 0.55;
    textScr->mode = TEXT_CENTER_RENDER;
    textScr->fontColor = Vec3(0, 0, 0);
    textObj->ui = true;

    textObj->transform = thisObj->transform;
    textObj->setParent(thisObj);
    textObj->relativeTransform.position.z = 0.05f;

    addUniqueTypeScript(textObj, textScr);
  }


  void update() override {
    if (keyAction::keyReleased(GLFW_MOUSE_BUTTON_1) && held) {
      held = false;
      if (onReleased)
        onReleased();
      else if (BonReleased)
        BonReleased(this);
      return;
    }

    if (_hideMouse)
      return;

    float left = thisObj->transform.position.x - thisObj->transform.scale.x;
    float right = thisObj->transform.position.x + thisObj->transform.scale.x;
    float bottom = thisObj->transform.position.y - thisObj->transform.scale.y;
    float top = thisObj->transform.position.y + thisObj->transform.scale.y;
    if (keyAction::keyPressed(GLFW_MOUSE_BUTTON_1)) {
      if (_mousePosX <= right && _mousePosX >= left && _mousePosY <= top && _mousePosY >= bottom) {
        if (onPressed)
          onPressed();
        else if (BonPressed)
          BonPressed(this);
        held = true;
      }
    }
    if (held)
      if (onHeld)
        onHeld();
      else if (BonHeld)
        BonHeld(this);
  }

  Button() {}
};


struct VoidButton : public ScriptBase {
  constexpr static const char* name = "VoidButton";
  std::vector<void*> startObjs;
  Object* thisObj = nullptr;

  bool inParent = false;

  Object* textObj = nullptr;
  TextBox* textScr = nullptr;
  bool held = false;

  void* pressVal = nullptr;
  void* heldVal = nullptr;
  void* releaseVal = nullptr;

  void (*pressDelete)(void* val) = nullptr;
  void (*heldDelete)(void* val) = nullptr;
  void (*releaseDelete)(void* val) = nullptr;

  void (*onPressed)(void* val) = nullptr;
  void (*onHeld)(void* val) = nullptr;
  void (*onReleased)(void* val) = nullptr;

  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>(std::vector<std::pair<Unique::Types, std::string>> {{Unique::OBJECT, "square"}}, startObjs);
  }

  void* getNew() override {
    return new VoidButton;
  }

  const std::string getName() const override {
    return VoidButton::name;
  }

  void start() override {
    if (started)
      return;
    started = true;

    thisObj = (Object*)vThisObj;
    thisObj->ui = true;

    textScr = new TextBox();

    textObj = (Object*)startObjs[0];
    textScr->text = "Button";
    textScr->font = "CascadiaCode_SMALL";
    textScr->fontSize = 0.5;
    textScr->lineSize = 0.55;
    textScr->mode = TEXT_CENTER_RENDER;
    textScr->fontColor = Vec3(0, 0, 0);
    textObj->ui = true;

    textObj->transform = thisObj->transform;
    textObj->setParent(thisObj);
    textObj->relativeTransform.position.z = 0.05f;
    textObj->setToRelative();

    addUniqueTypeScript(textObj, textScr);
  }


  void update() override {
    if (keyAction::keyReleased(GLFW_MOUSE_BUTTON_1) && held) {
      held = false;
      if (onReleased)
        onReleased(releaseVal);
      return;
    }

    if (_hideMouse)
      return;

    float left = thisObj->transform.position.x - thisObj->transform.scale.x;
    float right = thisObj->transform.position.x + thisObj->transform.scale.x;
    float bottom = thisObj->transform.position.y - thisObj->transform.scale.y;
    float top = thisObj->transform.position.y + thisObj->transform.scale.y;

    if (inParent && thisObj->parent != nullptr) {
      float pLeft = thisObj->parent->transform.position.x - thisObj->parent->transform.scale.x;
      float pRight = thisObj->parent->transform.position.x + thisObj->parent->transform.scale.x;
      float pBottom = thisObj->parent->transform.position.y - thisObj->parent->transform.scale.y;
      float pTop = thisObj->parent->transform.position.y + thisObj->parent->transform.scale.y;

      if (keyAction::keyPressed(GLFW_MOUSE_BUTTON_1)) {
        if (_mousePosX <= right && _mousePosX >= left && _mousePosY <= top && _mousePosY >= bottom && _mousePosX <= pRight && _mousePosX >= pLeft && _mousePosY <= pTop && _mousePosY >= pBottom) {
          if (onPressed)
            onPressed(pressVal);
          held = true;
        }
      }
    } else if (keyAction::keyPressed(GLFW_MOUSE_BUTTON_1)) {
      if (_mousePosX <= right && _mousePosX >= left && _mousePosY <= top && _mousePosY >= bottom) {
        if (onPressed)
          onPressed(pressVal);
        held = true;
      }
    }

    if (onHeld && held)
      onHeld(heldVal);
  }

  void end() override {
    if (pressDelete)
      pressDelete(pressVal);
    if (heldDelete)
      heldDelete(heldVal);
    if (releaseDelete)
      releaseDelete(releaseVal);

    deleteUniqueType(textObj);
  }


  VoidButton() {}
};


struct TextField : public ButtonMain {
  constexpr static const char* name = "TextField";

  bool insideOf = false;
  std::string text = "";
  std::string emptyText = "Enter text here...";
  Vec3 emptyColor = Vec3(0.7, 0.7, 0.7);
  Vec3 color = Vec3(0, 0, 0);

  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>(std::vector<std::pair<Unique::Types, std::string>> {{ Unique::OBJECT, "square" }}, startObjs);
  }

  const std::string getName() const override {
    return TextField::name;
  }

  void* getNew() override {
    return new TextField;
  }

  void cStart() override {
    textScr->text = emptyText;
    textScr->fontColor = emptyColor;
    textScr->mode = TEXT_LINE_LEFT_RENDER;
    textScr->textUpdate();
  }

  void cUpdate() override {
    if (_hideMouse)
      return;

    giveKeyAction::setIgnore(false);
    if (keyAction::keyPressed(GLFW_KEY_ESCAPE)) {
      insideOf = false;
      _lockMouse = false;
    }

    if (insideOf) {
      textScr->fontColor = color;
      keyAction::buildText(text);
      giveKeyAction::setIgnore(true);
      if (text != textScr->text) {
        textScr->text = text;
        textScr->textUpdate();
      }
    } else if (textScr->text != emptyText && text == "") {
      textScr->text = emptyText;
      textScr->fontColor = emptyColor;
      textScr->textUpdate();
    }
  }

  void onPressed() override {
    _lockMouse = true;
    insideOf = true;
  }

  void end() override {
    text.clear();
    text.~basic_string();
    emptyText.clear();
    emptyText.~basic_string();
  }

  TextField() {}
};


struct DropDownFieldDynamic : public ButtonMain {
  constexpr static const char* name = "DropDownFieldDynamic";

  std::string unknownMessage = "Select Option";
  float optionHeight = 0.125f;
  float optionOffset = 0.01f;
  std::string choice;
  TextBox buttonText;
  Object* background = nullptr;
  std::vector<Object*> optionObjs;

  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types,
      std::string>>, std::vector<void*>&>(std::vector<std::pair<Unique::Types, std::string>>
    {{Unique::OBJECT, "square"}, { Unique::OBJECT, "square" }}, startObjs);
  }

  const std::string getName() const override {
    return DropDownFieldDynamic::name;
  }

  void* getNew() override {
    return new DropDownFieldDynamic;
  }

  void onPressed() override {
    background->active = !background->active;
  }

  void cStart() override {
    textScr->text = unknownMessage;
    textScr->textUpdate();

    background = (Object*)startObjs[1];
    background->transform.position = thisObj->transform.position;
    background->transform.position.y -= thisObj->transform.scale.y;
    background->transform.scale = { thisObj->transform.scale.x, 0, 1 };
    background->srcMaterial.albedo = Vec4{ 0.4, 0.7, 0.7, 1 };
    background->setParent(thisObj);
    background->relativeTransform.position.z = 0.05f;
    background->ui = true;
    background->setToRelative();
    onPressed();
  }

  void cUpdate() override {
    if (_hideMouse)
      return;


    if (keyAction::keyPressed(0) && background->active && !ButtonMain::mouseWithin(background) && !ButtonMain::mouseWithin(thisObj))
      onPressed();

    if (background->active)
      for (int i = 0; i < optionObjs.size(); i++)
        optionObjs[i]->relativeTransform.position.y = ((thisObj->transform.position.y - thisObj->transform.scale.y -
          optionHeight - optionOffset -
          i * (2 * optionHeight + optionOffset)) -
          background->transform.position.y) / background->transform.scale.y;
  }

  void addOption(std::string option) {
    background->relativeTransform.scale.y += (optionHeight + optionOffset) / thisObj->transform.scale.y;
    background->relativeTransform.position.y -= (optionHeight + optionOffset) / thisObj->transform.scale.y;
    background->setToRelative();

    for (Object*& i : optionObjs)
      i->setParent(background);

    Object* newOption = (Object*)createUniqueType(Unique::OBJECT);
    setObjMesh(newOption, "square");
    VoidButton* newScr = new VoidButton;

    newOption->ui = true;

    void dynamicDropDownFunction(void*);
    newScr->onPressed = dynamicDropDownFunction;
    newScr->pressVal = (void*)new std::pair<DropDownFieldDynamic*, std::string>(this, option);
    void dynamicDropDownDelete(void* val);
    newScr->pressDelete = dynamicDropDownDelete;

    newOption->transform.position = background->transform.position;
    newOption->transform.scale = { thisObj->transform.scale.x, optionHeight, 1 };
    newOption->setParent(background);
    newOption->relativeTransform.position.z = 0.1f;
    newOption->setToRelative();
    newOption->srcMaterial.albedo = Vec4(1);
    addUniqueTypeScript(newOption, newScr);
    *newScr->textScr = buttonText;
    newScr->textScr->text = option;
    newScr->textScr->textUpdate();

    optionObjs.push_back(newOption);

  }

  void selectOption(std::string option) {
    textScr->text = option;
    textScr->textUpdate();
    onPressed();
    choice = option;
  }

  void removeOption(uint index) {
    if (index >= optionObjs.size())
      return;

    background->relativeTransform.scale.y -= (optionHeight + optionOffset) / thisObj->transform.scale.y;
    background->relativeTransform.position.y += (optionHeight + optionOffset) / thisObj->transform.scale.y;
    background->setToRelative();

    for (Object*& i : optionObjs)
      i->setParent(background);

    deleteUniqueType(optionObjs[index]);
    optionObjs.erase(optionObjs.begin() + index);
  }

  void end() override {
    optionObjs.clear();
    choice.~basic_string();
  }
};


struct DropDownFieldStatic : public ButtonMain {
  constexpr static const char* name = "DropDownFieldStatic";

  float height = 0.5f;
  float optionHeight = 0.125f;
  float optionOffset = 0.01f;
  float objOffset = 0;
  float scrollSpeed = 0.1f;
  std::string unknownMessage = "Select Option";
  std::string choice;
  TextBox buttonText;
  Object* background = nullptr;
  std::vector<Object*> optionObjs;

  std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() override {
    return std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&>(std::vector<std::pair<Unique::Types, std::string>> { {Unique::OBJECT, "square"}, { Unique::OBJECT, "square" } }, startObjs);
  }

  void* getNew() override {
    return new DropDownFieldStatic;
  }

  const std::string getName() const override {
    return DropDownFieldStatic::name;
  }

  void onPressed() override {
    background->active = !background->active;
    objOffset = 0;
  }

  void cStart() override {
    textScr->text = unknownMessage;
    textScr->textUpdate();

    background = (Object*)startObjs[1];
    background->transform.position = thisObj->transform.position;
    background->transform.position.y -= thisObj->transform.scale.y + height;
    background->transform.scale = { thisObj->transform.scale.x, height, 1 };
    background->setParent(thisObj);
    background->setToRelative();
    background->srcMaterial.albedo = Vec4{ 0.7, 0.7, 0.7, 1 };
    background->ui = true;

    onPressed();
  }

  void cUpdate() override {
    if (_hideMouse)
      return;

    if (keyAction::scrollUp() && objOffset > 0)
      objOffset -= scrollSpeed;
    if (keyAction::scrollDown() && objOffset < optionObjs.size() * (2 * optionHeight + optionOffset))
      objOffset += scrollSpeed;

    if (keyAction::keyPressed(0) && background->active && !ButtonMain::mouseWithin(background) && !ButtonMain::mouseWithin(thisObj))
      onPressed();

    if (background->active)
      for (int i = 0; i < optionObjs.size(); i++)
        optionObjs[i]->relativeTransform.position.y = ((thisObj->transform.position.y - thisObj->transform.scale.y -
          optionHeight - optionOffset -
          i * (2 * optionHeight + optionOffset) + objOffset) -
          background->transform.position.y) / background->transform.scale.y;
  }

  void addOption(std::string option) {
    Object* newOption = (Object*)createUniqueType(Unique::OBJECT);
    setObjMesh(newOption, "square");
    VoidButton* newScr = new VoidButton;
    newScr->inParent = true;

    void staticDropDownFunction(void*);
    newScr->onPressed = staticDropDownFunction;
    newScr->pressVal = (void*)new std::pair<DropDownFieldStatic*, std::string>(this, option);
    void staticDropDownDelete(void* val);
    newScr->pressDelete = staticDropDownDelete;

    newOption->transform.position = { thisObj->transform.position.x, thisObj->transform.position.y, 1 };
    newOption->transform.scale = { thisObj->transform.scale.x, optionHeight, 1 };
    newOption->setParent(background);
    newOption->setDependent(background);
    newOption->relativeTransform.position.z = 0.05f;
    newOption->setToRelative();
    addUniqueTypeScript(newOption, newScr);
    newScr->textObj->setDependent(background);
    *newScr->textScr = buttonText;
    newScr->textScr->text = option;
    newScr->textScr->textUpdate();
    newOption->ui = true;

    optionObjs.push_back(newOption);
  }

  void removeOption(uint index) {
    if (index >= optionObjs.size())
      return;

    deleteUniqueType(optionObjs[index]);
    optionObjs.erase(optionObjs.begin() + index);
  }

  void selectOption(std::string option) {
    textScr->text = option;
    textScr->textUpdate();
    onPressed();
    choice = option;
  }
};