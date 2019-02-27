#!/bin/bash
sed -i -e "s/class wxDocChildFrame;/#include <wx\/docview.h>\n#include <wx\/config.h>\n#include \"ExtendedTextCtrl.h\"/" -e "s/class wxDocParentFrame\;//" -e "s/GUIFrameMain(\s*wxWindow\* parent,/GUIFrameMain(wxDocument\* doc, wxView\* view, wxDocParentFrame\* parent,/" -e "s/wxTextCtrl/ExtendedTextCtrl/" ../src/gui/gui.h
sed -i -e "s/GUIFrameMain( wxWindow\* parent,/GUIFrameMain(wxDocument\* doc, wxView\* view, wxDocParentFrame\* parent,/" -e "s/wxDocChildFrame( parent,/wxDocChildFrame( doc, view, parent,/" -e "s/wxTextCtrl/ExtendedTextCtrl/" ../src/gui/gui.cpp


