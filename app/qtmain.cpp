// Copyright (C) 2022 Then Try This
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <QtGui>
#include "MainWindow.h"

#include "process_thread.h"
#include "audio_thread.h"

using namespace std;

int main( int argc , char *argv[] ){
    QApplication app(argc, argv);

    // Dark theme + clean font, applied to the whole program
    app.setStyle("Fusion");
    app.setStyleSheet(
        "* { font-family: 'Segoe UI', Arial, sans-serif; color: #e6e6e6; }"
        "QMainWindow, QDialog, QWidget { background-color: #121212; }"
        "QLabel { background: transparent; }"
        "QTabWidget::pane { border: 1px solid #333; }"
        "QTabBar::tab { background: #1e1e1e; padding: 8px 18px; border: 1px solid #333; }"
        "QTabBar::tab:selected { background: #2d2d2d; color: #ffffff; }"
        "QPushButton, QToolButton { background-color: #2a2a2a; border: 1px solid #3c3c3c;"
        "  border-radius: 6px; padding: 6px 12px; }"
        "QPushButton:hover, QToolButton:hover { background-color: #383838; border-color: #4da3ff; }"
        "QPushButton:pressed, QToolButton:pressed { background-color: #4da3ff; color: #000000; }"
        "QSpinBox, QDoubleSpinBox, QComboBox { background-color: #1e1e1e; border: 1px solid #3c3c3c;"
        "  border-radius: 4px; padding: 3px 6px; }"
        "QComboBox QAbstractItemView { background-color: #1e1e1e; selection-background-color: #4da3ff;"
        "  selection-color: #000000; }"
        "QSlider::groove:horizontal { height: 6px; background: #333; border-radius: 3px; }"
        "QSlider::sub-page:horizontal { background: #4da3ff; border-radius: 3px; }"
        "QSlider::handle:horizontal { background: #e6e6e6; width: 14px; margin: -5px 0;"
        "  border-radius: 7px; }"
        "QScrollArea, QScrollArea > QWidget > QWidget { background-color: #181818; }"
        "QCheckBox::indicator { width: 16px; height: 16px; }"
        "QToolTip { background-color: #2a2a2a; color: #ffffff; border: 1px solid #4da3ff; padding: 4px; }"
    );

    MainWindow mainWin;
    mainWin.show();
    process_thread pt;
    audio_thread at(pt);
    pt.register_renderer(at.m_left_renderer, at.m_right_renderer, at.m_block_stream);

    mainWin.set_audio_thread(&at);

    return app.exec();
}
