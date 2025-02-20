#define _PROG_UI
#include "progUI.h"

Object* UIFPSBG = nullptr;
Object* UIFPSObj = nullptr;
TextBox* UIFPSScr = nullptr;

namespace nProgUI {
  void start() {
    UIFPSBG = (Object*)createUniqueType(Unique::OBJECT);
    setObjMesh(UIFPSBG, "square");
    UIFPSBG->transform.scale = { 0.3, 0.075, 1 };
    UIFPSBG->transform.position = { _screenRatio - UIFPSBG->transform.scale.x, 1 - UIFPSBG->transform.scale.y, 1 };
    UIFPSBG->transform.position.z = 0.85f;
    UIFPSBG->active = false;
    UIFPSBG->ui = true;

    UIFPSObj = (Object*)createUniqueType(Unique::OBJECT);
    setObjMesh(UIFPSObj, "square");
    UIFPSScr = new TextBox;
    UIFPSObj->transform.scale = { 0.3, 0.075, 1 };
    UIFPSObj->transform.position = { _screenRatio - UIFPSObj->transform.scale.x, 1 - UIFPSObj->transform.scale.y, 1 };
    UIFPSObj->transform.position.z = 0.9f;
    UIFPSObj->ui = true;

    UIFPSScr->font = "CascadiaCode_BIG";
    UIFPSScr->fontSize = 1;
    addUniqueTypeScript(UIFPSObj, UIFPSScr);

    UIFPSObj->active = false;
  }

  float timeSpan = 1;
  int span = 0;
  float curSpan = 0;
  void update() {
    if (UIFPSObj->active) {
      curSpan += _deltaTime;
      span++;

      if (curSpan >= timeSpan) {
        UIFPSScr->text = "micro : " + std::to_string((int)(curSpan * 1000000 / span));
        //UIFPSScr->text = "FPS : " + std::to_string((int)(span / curSpan));

        UIFPSScr->textUpdate();
        curSpan = 0;
        span = 0;
      }
    }
  }
}

namespace progUI {
  void fps(bool val) {
    UIFPSObj->active = val;
    UIFPSBG->active = val;
  }
  void fps() {
    UIFPSObj->active = !UIFPSObj->active;
    UIFPSBG->active = !UIFPSBG->active;
  }
}