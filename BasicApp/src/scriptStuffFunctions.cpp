#include "globalScripts.h"




#ifdef __cplusplus
extern "C" {
#endif

  //--------------------------------------------------
  __declspec(dllexport) void* basicApp_createTextBox() {
    Object* textBoxBg = (Object*)createUniqueType(Unique::OBJECT);
    setObjMesh(textBoxBg, "square");
    textBoxBg->transform.scale = { 0.3, 0.3, 1 };
    textBoxBg->transform.position.z = 0.85f;
    textBoxBg->ui = true;

    Object* textBoxObj = (Object*)createUniqueType(Unique::OBJECT);
    setObjMesh(textBoxObj, "square");
    TextBox* textBoxScr = new TextBox;
    textBoxObj->transform.scale = { 0.3, 0.3, 1 };
    textBoxObj->transform.position.z = 0.9f;
    textBoxObj->ui = true;
    textBoxObj->setParent(textBoxBg);

    textBoxScr->font = "CascadiaCode_BIG";
    textBoxScr->fontSize = 0.25f;
    addUniqueTypeScript(textBoxObj, textBoxScr);

    return textBoxBg;
  }



  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setTextBoxText(Object* objectSrc, char* str) {

    if (!str || !objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return;

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return;
    box->text = str;
  }

  //--------------------------------------------------
  __declspec(dllexport) const char* basicApp_textBoxText(Object* objectSrc) {
    if (!objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return "\0";

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return "\0";
    return box->text.c_str();
  }





  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setTextBoxFontSize(Object* objectSrc, float size) {
    if (!objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return;

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return;

    box->fontSize = size;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_textBoxFontSize(Object* objectSrc) {
    if (!objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return 0;

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return 0;

    return box->fontSize;
  }





  //--------------------------------------------------
  __declspec(dllexport) void basicApp_setTextBoxLineSize(Object* objectSrc, float size) {
    if (!objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return;

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return;

    box->lineSize = size;
  }

  //--------------------------------------------------
  __declspec(dllexport) float basicApp_textBoxLineSize(Object* objectSrc) {
    if (!objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return 0;

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return 0;

    return box->lineSize;
  }





  //--------------------------------------------------
  __declspec(dllexport) void basicApp_textBoxUpdateText(Object* objectSrc) {
    if (!objectSrc || !objectSrc->children.size() || !objectSrc->children[0]->scripts.size())
      return;

    TextBox* box = (TextBox*)objectSrc->children[0]->scripts[0];
    if (!box)
      return;
    box->textUpdate();
  }







  //--------------------------------------------------
  //__declspec(dllexport) void* basicApp_createTextField() {

  //}

#ifdef __cplusplus
}
#endif