#pragma once

#include <imgui.h>

namespace sptr {

    inline static constexpr int INDENT_AMT = 20;

struct ImIndent {
  ImIndent(int amt = INDENT_AMT) : amt(amt) { ImGui::Indent(amt); }
  ~ImIndent() { ImGui::Unindent(amt); }
  int amt;
};

} // namespace sptr
