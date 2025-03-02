#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Unique.h"

struct scriptBase {
  virtual void start() {}
  virtual void update() {}
  virtual void end() {}
  virtual const std::string getName() const { return ""; }
  virtual void* getNew() { return nullptr; }
  virtual std::pair<std::vector<std::pair<Unique::Types, std::string>>, std::vector<void*>&> objsNeeded() { throw std::logic_error("'objsNeeded' function has to have an override'"); }
  void* vThisObj = nullptr;
  bool started = false;
};