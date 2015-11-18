//===-- BuildKey.cpp ------------------------------------------------------===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#include "llbuild/BuildSystem/BuildKey.h"

#include "llbuild/Basic/LLVM.h"

#include "llvm/Support/raw_ostream.h"

using namespace llbuild;
using namespace llbuild::buildsystem;

StringRef BuildKey::stringForKind(BuildKey::Kind kind) {
  switch (kind) {
#define CASE(kind) case Kind::kind: return #kind
    CASE(Command);
    CASE(CustomTask);
    CASE(Node);
    CASE(Target);
    CASE(Unknown);
#undef CASE
  }
  return "<unknown>";
}

void BuildKey::dump(raw_ostream& os) const {
  os << "BuildKey(" << stringForKind(getKind());
  switch (getKind()) {
  case Kind::Command: {
    os << ", name='" << getCommandName() << "'";
    break;
  }
  case Kind::CustomTask: {
    os << ", commandName='" << getCustomTaskCommandName() << "'";
    os << ", name='" << getCustomTaskName() << "'";
    break;
  }
  case Kind::Node: {
    os << ", name='" << getNodeName() << "'";
    break;
  }
  case Kind::Target: {
    os << ", name='" << getTargetName() << "'";
    break;
  }
  case Kind::Unknown: {
    break;
  }
  }
  os << ")";
}
